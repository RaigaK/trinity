////////////////////////////////////////////////////////////
//
//    Created:   March 2011
//    Copyright: CCP 2011
//
#pragma once
#ifndef EveSpaceSceneLightMgr_H
#define EveSpaceSceneLightMgr_H

// constants
// maximum number of point lights in space (depends on the shaders)
const unsigned int EVE_MAX_POINTLIGHT_COUNT = 8;

// forwards
BLUE_DECLARE( EveSpaceScenePointLight );

// --------------------------------------------------------------------------------
// Description:
//   This class holds all data of a light source
// SeeAlso:
//   EveSpaceSceneLightMgr
// --------------------------------------------------------------------------------
class EveSpaceScenePointLight :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();

	using IRoot::Unlock;
	using IRoot::Lock;

	EveSpaceScenePointLight( IRoot* lockobj = NULL );

	// query
	bool IsDisplay() const;
	const Vector3& GetPosition() const;
	float GetOuterRadius() const;
	const Color& GetColor() const;

private:
	// name
	std::string m_name;
	// turn on/off
	bool m_display;
	// position in render space
	Vector3 m_position;
	// outer radius
	float m_outerRadius;
	// color
	Color m_color;
};
TYPEDEF_BLUECLASS( EveSpaceScenePointLight );
BLUE_DECLARE_VECTOR( EveSpaceScenePointLight );


// --------------------------------------------------------------------------------
// Description:
//   This class holds all light sources in a space scene.
//
//   Just an early implementation, much more to come...
// SeeAlso:
//   EveSpaceScene
// --------------------------------------------------------------------------------
class EveSpaceSceneLightMgr :
	public IInitialize,
	public INotify
{
public:
	EXPOSE_TO_BLUE();

	using IInitialize::Unlock;
	using IInitialize::Lock;

	EveSpaceSceneLightMgr( IRoot* lockobj = NULL );
	~EveSpaceSceneLightMgr();

	//////////////////////////////////////////////////////////////////////////////////////
	// IInitialize
	bool Initialize();
	
	//////////////////////////////////////////////////////////////////////////
	// INotify
	bool OnModified( Be::Var* val );

	// query static content
	unsigned int GetStaticPointlightCount() const;
	const EveSpaceScenePointLightPtr GetStaticPointlight( unsigned int n );

	// this defines a point light inspace
	struct PointLightData
	{
		Vector3 m_position;
		float m_radius;
		Color m_color;
	};

private:
	// statics
	PEveSpaceScenePointLightVector m_staticPointlights;
};

TYPEDEF_BLUECLASS( EveSpaceSceneLightMgr );
BLUE_DECLARE_VECTOR( EveSpaceSceneLightMgr );



#endif // EveSpaceSceneLightMgr_H


