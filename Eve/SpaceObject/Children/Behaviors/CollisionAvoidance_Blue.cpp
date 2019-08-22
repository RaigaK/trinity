#include "StdAfx.h"
#include "CollisionAvoidance.h"

BLUE_DEFINE( CollisionAvoidance );

const Be::ClassInfo* CollisionAvoidance::ExposeToBlue()
{
	EXPOSURE_BEGIN( CollisionAvoidance, "" )
		MAP_INTERFACE( CollisionAvoidance )
		MAP_INTERFACE( IBehavior )

		MAP_ATTRIBUTE( "avoidanceScalar", m_collisionAvoidanceScalar, ":jessica-group: Inertia", Be::READWRITE | Be::PERSIST )

	EXPOSURE_END()
}