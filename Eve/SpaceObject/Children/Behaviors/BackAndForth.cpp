#include "StdAfx.h"
#include "BackAndForth.h"
#include "include/TriMath.h"
#include "BehaviorGroup.h"

const BlueSharedString DELIVER_LOCATOR_SET_NAME( "deliver" );
const BlueSharedString SEEK_LOCATOR_SET_NAME( "seek" );

BackAndForth::BackAndForth( IRoot* lockobj ) :
	m_arrivedRadius( 50.f ),
	m_slowDownRadius( 200.f ),
	m_backAndForthWeight( 100.f )
{
}

BackAndForth::~BackAndForth()
{
}

size_t BackAndForth::GetScratchMemorySize() const
{
	return sizeof( BackAndForthData );
}

void BackAndForth::InitializeScratch( const DroneAgent& drone, void* scratchMemory )
{
	*static_cast<BackAndForthData*>( scratchMemory ) = BackAndForthData();
}

std::vector<Vector3> BackAndForth::CalculateBehavior( std::vector<DroneAgent>& agents, void* scratchData, const float deltaTime,
														BehaviorGroup& group, EveChildBehaviorSystem& system )
{	
	auto data = static_cast<BackAndForthData*>( scratchData );

	for (auto agent = agents.begin(); agent != agents.end(); ++agent, data++ )
	{
		if (data->arrived)
		{
			if (data->seek)
			{
				//Get all locators under the "seek" locatorSet
				auto seekLocators = group.GetLocatorsForSet( SEEK_LOCATOR_SET_NAME );
				if (seekLocators != NULL)
				{
					m_rand = TriRandInt( 0, (int)seekLocators->size() );
					data->locatorTarget = seekLocators[0][m_rand].position;
				}
			}
			//If the deliver behavior is active
			else if (data->deliver)
			{
				//Get all locators under the "deliver" locatorSet
				auto deliverLocators = group.GetLocatorsForSet( DELIVER_LOCATOR_SET_NAME );
				if (deliverLocators != NULL)
				{
					m_rand = TriRandInt( 0, (int)deliverLocators->size() );
					data->locatorTarget = deliverLocators[0][m_rand].position;
				}
			}
			data->arrived = false;
		}
		Vector3 target = data->locatorTarget - agent->position;
		float distance = Length( target );
		target = Normalize( target );

		//If we are approaching the target
		if (distance < m_slowDownRadius)
		{
			// make the agent slow down before arriving at target
			target = target * m_backAndForthWeight * (distance / m_slowDownRadius);

			//If the agent has arrived to the target, then switch targets
			if (distance < m_arrivedRadius)
			{
				std::swap( data->seek, data->deliver );
				data->arrived = true;
			}
			else
			{
				target *= m_backAndForthWeight;
			}
		}	
		agent->acceleration += target;

	}
	std::vector<Vector3> todo;
	return todo;
}

void BackAndForth::RenderDebugInfo(Tr2DebugRenderer& renderer, std::vector<DroneAgent>& agents, Matrix& parentWorldLocation)
{
}