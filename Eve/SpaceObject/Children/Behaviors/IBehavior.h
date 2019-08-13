#pragma once
#ifndef IBehavior_h
#define IBehavior_h

BLUE_INTERFACE( IBehavior ): public IRoot
{
public:
	virtual size_t GetScratchMemorySize() const // per-agent
	{
		return 0;
	}
	virtual void InitializeScratch( const DroneAgent& drone, void* scratchMemory )
	{
	}

	// This function should apply a force to the acceleration and return an array with pos and force vector for each agent
	virtual std::vector<Vector3> CalculateBehavior( std::vector<DroneAgent>& agents, void* scratchData, const float deltaTime,
	                                               BehaviorGroup& sys, EveChildBehaviorSystem& system ) = 0;
	virtual void RenderDebugInfo( Tr2DebugRenderer& renderer, std::vector<DroneAgent>& agents, Matrix& parentWorldLocation ) = 0;

	enum TunnelGroupType
	{
		EXIT_TUNNELS = 0,
		ENTRANCE_TUNNELS = 1,
		OTHER_TUNNELS = 2,
	};
};

#endif
