#pragma once
#ifndef BackAndForth_H
#define BackAndForth_H
#include "Eve/SpaceObject/Children/EveChildBehaviorSystem.h"
#include "IBehavior.h"


struct BackAndForthData
{
	BackAndForthData() :
		locatorTarget( 0, 0, 0 ),
		seek( true ),
		deliver( false ),
		arrived( true )
	{}

	Vector3 locatorTarget;
	bool seek;
	bool deliver;
	bool arrived;
};

BLUE_CLASS( BackAndForth ) :
	public IBehavior
{
public:
	EXPOSE_TO_BLUE();
	BackAndForth( IRoot* lockobj = nullptr );
	~BackAndForth();


	virtual size_t GetScratchMemorySize() const;
	virtual void InitializeScratch( const DroneAgent& drone, void* scratchMemory );

	virtual std::vector<Vector3> CalculateBehavior(std::vector<DroneAgent>& agents, void* scratchData, const float deltaTime,
	                                               BehaviorGroup& group, EveChildBehaviorSystem& system );
	void RenderDebugInfo(Tr2DebugRenderer& renderer, std::vector<DroneAgent>& agents, Matrix& parentWorldLocation);

private:
	float m_arrivedRadius;
	float m_slowDownRadius;
	int m_rand;
	float m_backAndForthWeight;
};

TYPEDEF_BLUECLASS( BackAndForth );

#endif