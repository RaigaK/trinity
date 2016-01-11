////////////////////////////////////////////////////////////
//
//    Created:   2015
//    Copyright: CCP 2015
//
#include "StdAfx.h"
#include "EveSwarm.h"


BLUE_DEFINE( EveSwarmRenderable );
const Be::ClassInfo* EveSwarmRenderable::ExposeToBlue()
{
    EXPOSURE_BEGIN( EveSwarmRenderable, "" )
    EXPOSURE_END()
}


BLUE_DEFINE( EveSwarm );
const Be::ClassInfo* EveSwarm::ExposeToBlue()
{
    EXPOSURE_BEGIN( EveSwarm, "" )
        MAP_INTERFACE( EveSwarm )
		MAP_INTERFACE( IEveSpaceObject2 )
		MAP_INTERFACE( IInitialize )
		MAP_INTERFACE( INotify )

		MAP_ATTRIBUTE( "mesh", m_mesh, "", Be::READWRITE | Be::PERSIST | Be::NOTIFY )

		MAP_ATTRIBUTE( "count", m_count, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "mass", m_mass, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "maxSpeed", m_maxSpeed, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "maxAcceleration", m_maxAcceleration, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "maxDistance", m_maxOffset, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "maxTime", m_maxTime, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "timeMultiplier", m_timeMultiplier, "", Be::READWRITE );
		
		MAP_ATTRIBUTE( "weightCohesion", m_behavior.m_weightCohesion, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "weightSeparation", m_behavior.m_weightSeparation, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "weightAlign", m_behavior.m_weightAlign, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "weightWander", m_behavior.m_weightWander, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "weightAnchor", m_behavior.m_weightAnchor, "", Be::READWRITE | Be::PERSIST )
		
		MAP_ATTRIBUTE( "separationDistance", m_behavior.m_separationDistance, "", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "wanderFluctuation", m_behavior.m_wanderFluctuation, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "wanderDistance", m_behavior.m_wanderDistance, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "wanderRadius", m_behavior.m_wanderRadius, "", Be::READWRITE | Be::PERSIST )

		MAP_ATTRIBUTE( "velocity", m_rootVelocity, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "position", m_rootPosition, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "translationCurve", m_ballPosition, "", Be::READWRITE | Be::PERSIST )
		MAP_ATTRIBUTE( "rotationCurve", m_ballRotation, "", Be::READWRITE | Be::PERSIST )

		MAP_METHOD_AND_WRAP( "AddSwarmer", AddSwarmer, "" )
		
    EXPOSURE_CHAINTO( EveSpaceObject2 )
}