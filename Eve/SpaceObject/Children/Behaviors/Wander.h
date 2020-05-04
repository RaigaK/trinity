#pragma once
#ifndef Wander_H
#define Wander_H
#include "Eve/SpaceObject/Children/EveChildBehaviorSystem.h"
#include "IBehavior.h"

BLUE_CLASS( Wander ) :
	public IBehavior
{
public:
	EXPOSE_TO_BLUE();
	Wander( IRoot* lockobj = nullptr );
	~Wander();

	virtual std::vector<Vector3> CalculateBehavior(std::vector<DroneAgent>& agents, void* scratchData, const float deltaTime,
	                                               BehaviorGroup& group, EveChildBehaviorSystem& system, const std::vector<std::vector<DroneAgent*>>& dronesInSearchRadius);

private:
	float m_weightWander;	//priority of behavior
	float rand1;
	float rand2;
	float rand3;
	float m_freq;

};

TYPEDEF_BLUECLASS( Wander );

#endif