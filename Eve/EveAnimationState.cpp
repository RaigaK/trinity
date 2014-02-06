#include "StdAfx.h"
#include "EveAnimationState.h"
#include "SpaceObject/EveSpaceObject2.h"
#include "SpaceObject/EveMobile.h"
#include "../Curves/TriCurveSet.h"
#include "../Tr2GrannyAnimation.h"
#include "../Tr2Renderer.h"

// --------------------------------------------------------------------------------
// Description:
//   Initialize data members
// --------------------------------------------------------------------------------
EveAnimationState::EveAnimationState( IRoot* lockobj ) :
	PARENTLOCK( m_transitions ),
	m_progress( EVE_ANIM_INACTIVE ),
	m_currentSequence( EVE_ANISTAGE_INVALID ),
	m_transitionName( "" ),
	m_transitionPending( false ),
	m_animationDuration( 0.f ),
	m_startTime( 0.f )
{
}

EveAnimationState::~EveAnimationState() 
{
}

// --------------------------------------------------------------------------------
// Description:
//   Find the end time of a sequence that is starting. Results stored in
//   m_animationsDoneAt
// Arguments:
//   sequence - The animation sequence that is starting
// --------------------------------------------------------------------------------
void EveAnimationState::UpdateSequenceDuration( EveSpaceObject2Ptr owner, const EveAnimationSequencePtr sequence )
{
	float currentAnimationTime = Tr2Renderer::GetAnimationTime();
	m_startTime = currentAnimationTime;
	m_animationDuration = 0;
	auto ac = owner->GetAnimationController();
	if( ac && ac->m_modelInstance )
	{
		m_animationDuration = ac->GetAnimationChainCompleteTime() - currentAnimationTime;
	}

	float maxCurveDuration = 0.f;
	if( sequence )
	{
		for( auto it = sequence->m_curves.cbegin(); it != sequence->m_curves.cend(); it++ )
		{
			maxCurveDuration = max( maxCurveDuration, owner->GetCurveSetDuration( (*it)->m_name ) );
		}
	}
	// NOTE: If a curve takes longer than the animation we get an animation 'jump' unless the animation loops
	m_animationDuration = max( m_animationDuration, maxCurveDuration );
}

// --------------------------------------------------------------------------------
// Description:
//   Starts playing appropriate animation sequences depending on the previous
//   state.
// Arguments:
//   state - the previously completed animation state
// --------------------------------------------------------------------------------
void EveAnimationState::TransitionFrom( EveAnimationStatePtr state, EveSpaceObject2Ptr owner )
{
	m_transitionName = "";
	m_transitionPending = false;
	m_startTime = 0;
	m_animationDuration = 0;

	if( !state )
	{
		DoEnterSequence();
		return;
	}

	if( state->m_transitionName == m_name && state->HasTransition( m_name ) )
	{
		// The other state had a transition to this state. Skip the enter sequence.
		m_currentSequence = EVE_ANISTAGE_ENTER;
		m_progress = EVE_ANIM_ENTERING;
	}
	else
	{
		DoEnterSequence();
	}
}

// --------------------------------------------------------------------------------
// Description:
//   Plays whatever animation sequence is appropriate when going into the state
//   that's passed in.
// Arguments:
//   state - the state we'll go into after this object has finished transitioning.
// --------------------------------------------------------------------------------
void EveAnimationState::TransitionTo( EveAnimationStatePtr state, EveSpaceObject2Ptr owner )
{
	m_transitionName = "";
	m_transitionPending = true;
	if( !state )
	{
		return;
	}
	
	m_transitionName = state->m_name;
}

// --------------------------------------------------------------------------------
// Description:
//   Play this state's enter animation sequence.
// --------------------------------------------------------------------------------
void EveAnimationState::DoEnterSequence()
{
	m_progress = EVE_ANIM_ENTERING;
	m_currentSequence = EVE_ANISTAGE_INVALID;

	if( !GetAnimationSequence( EVE_ANISTAGE_ENTER ) )
	{
		m_startTime = Tr2Renderer::GetAnimationTime();
		m_animationDuration = 0.f;
	}
}

// --------------------------------------------------------------------------------
// Description:
//   Play this state's main animation sequence.
// --------------------------------------------------------------------------------
void EveAnimationState::DoMainSequence()
{
	m_progress = EVE_ANIM_RUNNING;
}

// --------------------------------------------------------------------------------
// Description:
//   Play this state's exit animation sequence.
// --------------------------------------------------------------------------------
void EveAnimationState::DoExitSequence()
{
	m_progress = EVE_ANIM_EXITING;

	if( !GetAnimationSequence( EVE_ANISTAGE_EXIT ) )
	{
		m_progress = EVE_ANIM_DONE;
		return;
	}
}

// --------------------------------------------------------------------------------
// Description:
//   Play this state's transition animation sequence appropriate for the stateID
//   that's passed in.
// Arguments:
//   stateID - id of the state we should transition into.
// --------------------------------------------------------------------------------
void EveAnimationState::DoTransitionSequence( std::string stateName )
{
	m_progress = EVE_ANIM_TRANSITIONING;
	m_transitionName = stateName;

	EveTransitionSequencePtr transition = GetTransition( stateName );
	if( !transition )
	{
		m_progress = EVE_ANIM_DONE;
		return;
	}
}

// --------------------------------------------------------------------------------
// Description:
//   Get animation sequence for the specified stage.
// Arguments:
//   stage - desired animation stage
// Returns:
//   the animation sequence for the specified stage, can be nullptr.
// --------------------------------------------------------------------------------
EveAnimationSequencePtr EveAnimationState::GetAnimationSequence( EveAnimationStage stage )
{
	EveAnimationSequencePtr sequence;
	switch( stage )
	{
	case EVE_ANISTAGE_ENTER:
		sequence = m_enterSequence;
		break;
	case EVE_ANISTAGE_MAIN:
		sequence = m_mainSequence;
		break;
	case EVE_ANISTAGE_EXIT:
		sequence = m_exitSequence;
		break;
	default:
		break;
	};
	return sequence;
}

// --------------------------------------------------------------------------------
// Description:
//   Get transition sequence into the desired state.
// Arguments:
//   stateName - name of the state that we want to get a transition sequence for
// Returns:
//   Transition sequence into stateName if it exists or nullptr otherwise.
// --------------------------------------------------------------------------------
EveTransitionSequencePtr EveAnimationState::GetTransition( std::string stateName )
{
	for( auto it = m_transitions.cbegin(); it != m_transitions.cend(); it++ )
	{
		if( (*it)->m_transitionState == stateName )
		{
			return *it;
		}
	}
	return nullptr;
}

// --------------------------------------------------------------------------------
// Description:
//   Check if this state has a transition sequence for states identified by id.
// Arguments:
//   id - The id of the state we'd transition into
// Returns:
//   boolean indicating weather this state has a transition into the id state.
// --------------------------------------------------------------------------------
bool EveAnimationState::HasTransition( std::string stateName )
{
	return GetTransition( stateName );
}

inline EveMobilePtr GetAsEveMobile( EveSpaceObject2Ptr owner )
{
	EveMobilePtr pOwner;
	if( !((IInitialize*)owner)->QueryInterface( BlueInterfaceIID<EveMobile>(), (void**)&pOwner ) )
	{
		CCP_LOGERR( "EveAnimationState: Object is not EveMobile." );
		return nullptr;
	}
	return pOwner;
}

inline void ExecuteActivationCurveCommand( EveSpaceObject2Ptr owner, EveAnimationCommandPtr cmd )
{
	EveMobilePtr pOwner = GetAsEveMobile( owner );
	if( !pOwner )
	{
		return;
	}

	IRootPtr p;
	p.Attach( BeResMan->LoadObject( cmd->m_data.c_str() ) );
	if( p == NULL )
	{
		CCP_LOGERR( "EveAnimationState: Couldn't find PlayActivationCurve data resource file: %s", cmd->m_data.c_str() );
		return;
	}

	ITriScalarFunctionPtr ptr;
	if( !p->QueryInterface( BlueInterfaceIID<ITriScalarFunction>(), (void**)&ptr ) )
	{
		CCP_LOGERR( "EveAnimationState: PlayActivationCurve resource file %s is not of correct type!", cmd->m_data.c_str() );
		return;
	}
	pOwner->m_activationStrengthCurve = ptr;
	pOwner->PlayActivationCurve();
}

// --------------------------------------------------------------------------------
// Description:
//   Play animations and curves in the animation sequence
// --------------------------------------------------------------------------------
void EveAnimationState::DoAnimationSequence( EveSpaceObject2Ptr owner, EveAnimationSequencePtr sequence )
{
	if( !sequence )
	{
		return;
	}

	// granny animation
	if( sequence->m_animation )
	{
		EveAnimationPtr anim = sequence->m_animation;
		owner->PlayAnimation( anim->m_name.c_str(), false, anim->m_loops, anim->m_delay, anim->m_speed );
	}
	
	// curve sets
	for( auto it = sequence->m_curves.cbegin(); it != sequence->m_curves.cend(); it++ )
	{
		owner->PlayCurveSet( (*it)->m_name );
	}

	// commands
	for( auto it = sequence->m_commands.cbegin(); it != sequence->m_commands.cend(); it++ )
	{
		EveAnimationCommandPtr cmd = *it;
		EveMobilePtr pOwner;
		switch( cmd->m_command )
		{
		case ANIM_CMD_PLAYACTIVATION:
			ExecuteActivationCurveCommand( owner, cmd );
			break;
		case ANIM_CMD_ACTIVATE_TURRETS:
			pOwner = GetAsEveMobile( owner );
			if( pOwner )
			{
				pOwner->ActivateTurrets();
			}
			break;
		case ANIM_CMD_DEACTIVATE_TURRETS:
			pOwner = GetAsEveMobile( owner );
			if( pOwner )
			{
				pOwner->DeactivateTurrets();
			}
			break;
		case ANIM_CMD_ACTIVATION_STRENGTH_ZERO:
			pOwner = GetAsEveMobile( owner );
			if( pOwner )
			{
				pOwner->SetActivationStrength( 0.f );
			}
			break;
		case ANIM_CMD_ACTIVATION_STRENGTH_ONE:
			pOwner = GetAsEveMobile( owner );
			if( pOwner )
			{
				pOwner->SetActivationStrength( 1.f );
			}
			break;
		default:
			break;
		};
	}
}

// --------------------------------------------------------------------------------
// Description:
//   Start the sequence specified, update end time etc.
// --------------------------------------------------------------------------------
void EveAnimationState::PlaySequence( EveSpaceObject2Ptr owner, EveAnimationStage type )
{
	EveAnimationSequencePtr sequence;
	if( type == EVE_ANISTAGE_TRANSITION )
	{
		sequence = GetTransition( m_transitionName );
	}
	else
	{
		sequence = GetAnimationSequence( type );
	}
	DoAnimationSequence( owner, sequence );
	UpdateSequenceDuration( owner, sequence );
	m_currentSequence = type;
}

// --------------------------------------------------------------------------------
// Description:
//   Stop sthe current sequence stage.
// --------------------------------------------------------------------------------
void EveAnimationState::StopCurrentSequence( EveSpaceObject2Ptr owner, Be::Time time )
{
	EveAnimationSequencePtr sequence;
	if( m_currentSequence == EVE_ANISTAGE_TRANSITION )
	{
		sequence = GetTransition( m_transitionName );
	}
	else
	{
		sequence = GetAnimationSequence( m_currentSequence );
	}

	if( sequence )
	{
		for( auto it = sequence->m_curves.cbegin(); it != sequence->m_curves.cend(); it++ )
		{
			owner->UpdateCurveSet( (*it)->m_name, time );
			owner->StopCurveSet( (*it)->m_name );
		}
	}
}

// --------------------------------------------------------------------------------
// Description:
//   Update the state
// --------------------------------------------------------------------------------
void EveAnimationState::Update( Be::Time time, EveSpaceObject2Ptr owner )
{
	float animationDelta = Tr2Renderer::GetAnimationTimeElapsed( m_startTime );
	m_secondsRemaining = m_animationDuration - animationDelta;

	if( animationDelta < m_animationDuration )
	{
		return;
	}
	switch(m_progress)
	{
	case EVE_ANIM_ENTERING:
		if( m_currentSequence == EVE_ANISTAGE_ENTER )
		{
			StopCurrentSequence( owner, time );
			if( !m_transitionPending )
			{
				DoMainSequence();
				PlaySequence( owner, EVE_ANISTAGE_MAIN );
			}
			else if( HasTransition( m_transitionName ) )
			{
				DoTransitionSequence( m_transitionName );
				PlaySequence( owner, EVE_ANISTAGE_TRANSITION );
			}
			else
			{
				DoExitSequence();
				PlaySequence( owner, EVE_ANISTAGE_EXIT );
			}
		}
		else
		{
			PlaySequence( owner, EVE_ANISTAGE_ENTER );
		}
		break;
	case EVE_ANIM_RUNNING:
		if( !m_transitionPending )
		{
			break;
		}
	case EVE_ANIM_TRANSITIONING:
	case EVE_ANIM_EXITING:
		if( m_currentSequence == EVE_ANISTAGE_MAIN )
		{
			StopCurrentSequence( owner, time );
			if( HasTransition( m_transitionName ) )
			{
				DoTransitionSequence( m_transitionName );
				PlaySequence( owner, EVE_ANISTAGE_TRANSITION );
			}
			else
			{
				DoExitSequence();
				PlaySequence( owner, EVE_ANISTAGE_EXIT );
			}
		}
		else
		{
			StopCurrentSequence( owner, time );
			m_progress = EVE_ANIM_DONE;
			Cleanup();
		}
		break;
	default:
		break;
	};
}

void EveAnimationState::Cleanup()
{
	m_currentSequence = EVE_ANISTAGE_INVALID;
}


