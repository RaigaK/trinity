#pragma once
#ifndef Tr2ApexScene_h
#define Tr2ApexScene_h

#include "include/IPhysXSdk.h"

namespace physx
{
	namespace apex
	{
		class NxApexSDK;
		class NxApexScene;
	};
};

class NxPhysicsSDK;
class NxScene;

// Wrapper around a pair of apex+physx scene; contains all the data needed to run cloth simulation,
// used to be global, turned into a class so we can have an apex scene per Tr2InteriorScene.
BLUE_CLASS( Tr2ApexScene ) : public IPhysXScene
{
public:
	Tr2ApexScene( IRoot* lockobj = 0 );
	~Tr2ApexScene(void);

	EXPOSE_TO_BLUE();

	unsigned int GetNbActorsInPhysxScene();
	unsigned int GetNbStaticShapesInPhysxScene();
	unsigned int GetNbDynamicShapesInPhysxScene();
	unsigned int GetNbJointsInPhysxScene();
	unsigned int GetNbEffectorsInPhysxScene();

	void SetLODResourceBudget(float val);
	
	void DumpStats();
	
	NxScene							*GetPhysXScene(void) const	{ return m_physXScene; };	
	physx::apex::NxApexScene		*GetApexScene(void) const	{ return m_apexScene; };
	
	void							CreateScene();
	void							DeleteScene();

	// IPhysXScene
	NxScene*						GetScene() { return GetPhysXScene(); }
	bool							CreatePlane( Vector3 position, Vector3 normal, float distance );
	
	void							Simulate( Be::Time time, float lodResourceBudget );
	void							FetchResults( float& lodResourceBudgetConsumed );
	void							PreUpdate( Be::Time time, float lodResourceBudget, float& lodResourceBudgetConsumed );
	void							PreRender( Be::Time time, float lodResourceBudget, float& lodResourceBudgetConsumed );
	void							PostRender( Be::Time time, float lodResourceBudget, float& lodResourceBudgetConsumed );
	
	void							PostUpdate( Be::Time time, float lodResourceBudget, float& lodResourceBudgetConsumed );
	void							RenderDebugInfo( Tr2RenderContext& renderContext );
	
	bool							IsParallel();

	bool GetIsVisualizationEnabled();
	void SetIsVisualizationEnabled( bool val );

	bool GetVisualizeClothingSkinnedPositions();
	void SetVisualizeClothingSkinnedPositions( bool val );

	bool GetVisualizeClothingSphereCollisions();
	void SetVisualizeClothingSphereCollisions( bool val );

	bool GetVisualizeClothingMaxDistanceOut();
	void SetVisualizeClothingMaxDistanceOut( bool val );

	bool GetVisualizeClothingMaxDistanceIn();
	void SetVisualizeClothingMaxDistanceIn( bool val );

	bool GetVisualizeClothingSkinMap();
	void SetVisualizeClothingSkinMap( bool val );

	bool GetVisualizeClothingRenderNormals();
	void SetVisualizeClothingRenderNormals( bool val );

	bool GetVisualizeClothingRenderTangents();
	void SetVisualizeClothingRenderTangents( bool val );

	bool GetVisualizeClothingPhysicsMeshWire();
	void SetVisualizeClothingPhysicsMeshWire( bool val );

	bool GetVisualizeClothingPhysicsMeshSolid();
	void SetVisualizeClothingPhysicsMeshSolid( bool val );

	bool GetVisualizeClothingSkeleton();
	void SetVisualizeClothingSkeleton( bool val );

	bool GetVisualizeClothingVelocities();
	void SetVisualizeClothingVelocities( bool val );

	bool GetVisualizeClothingGraphicalVertexBones();
	void SetVisualizeClothingGraphicalVertexBones( bool val );

	bool GetVisualizeClothingPhysicalVertexBones();
	void SetVisualizeClothingPhysicalVertexBones( bool val );

	bool GetVisualizeClothingAllSkinMap(void);
	void SetVisualizeClothingAllSkinMap(bool val); 
	bool GetVisualizeClothingBadSkinMap(void); 
	void SetVisualizeClothingBadSkinMap(bool val);
	bool GetVisualizeClothingBoneFrames(void); 
	void SetVisualizeClothingBoneFrames(bool val); 
	bool GetVisualizeClothingBoneNames(void); 
	void SetVisualizeClothingBoneNames(bool val); 
	bool GetVisualizeClothingAcollisionUmbrellas(void); 
	void SetVisualizeClothingAcollisionUmbrellas(bool val); 

	bool							GetApexClothingModuleSetting( const char* name );
	void							SetApexClothingModuleSetting( const char* name, bool val,float distance = 1.0f );
	
	static	unsigned				s_numClothSimInProgress;

private:
	NxScene							*m_physXScene;
	physx::apex::NxApexScene		*m_apexScene;

	unsigned int					m_apexViewMatrixId;
	unsigned int					m_apexProjectionMatrixId;

	NxParameterized::Interface		*m_apexModuleClothingDbgParams;

	bool							m_debugVisualize:1;
	bool							m_hasSimulated;
	bool							m_isClothSimInProgress;

	Be::Time						m_lastUpdateTime;
	
private:
	Tr2ApexScene( const Tr2ApexScene & );
	Tr2ApexScene& operator=( const Tr2ApexScene & );
};

TYPEDEF_BLUECLASS( Tr2ApexScene );

#endif	// Tr2ApexScene_h
