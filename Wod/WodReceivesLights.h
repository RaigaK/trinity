#pragma once
#ifndef WodReceivesLights_H
#define WodReceivesLights_H

#include "WodLightSource.h"
#include "WodLightSourceOverride.h"
#define MAX_EXTERIOR_LIGHTS_PER_OBJECT (8)

BLUE_DECLARE( WodReceivesLights );

struct LightsAndTransform {
	WodLightSourceOverrideVector *lights;
	Matrix parentTrans;
};

class WodReceivesLights :
public IRoot 
{
public:
	EXPOSE_TO_BLUE();

    using IRoot::Lock;
    using IRoot::Unlock;

	WodReceivesLights(IRoot* lockobj = 0);
	~WodReceivesLights();
    void AddMostSignificantLights(std::vector<LightsAndTransform> *lightsAndTransforms, const Vector3 &objectBoundingBoxWorldMin, const Vector3 &objectBoundingBoxWorldMax );
	void ClearLights();
protected:	
	// All these vectors should match up - same size, indices refer to same light source
	struct LightInstance
	{
		LightInstance(WodLightSourceOverridePtr _light, float _intensity, const Matrix &_worldTransform) : 
			m_light(_light), m_intensity(_intensity), m_worldTransform(_worldTransform) {}
		WodLightSourceOverridePtr m_light;
		float m_intensity;
		Matrix m_worldTransform;
	};
	void InsertInOrderOfIntensity(std::list<LightInstance> &newLightsInOrder, const LightInstance &lightInstance);
    std::vector<LightInstance> m_lightInstances;
	unsigned int m_numLights;

	// This is a list of the received lights that is exposed to python
	// so we can examine and visualize the m_light assignments
	PWodLightSourceOverrideVector m_receivedLights;

};

TYPEDEF_BLUECLASS( WodReceivesLights );

// Interface set on classes that require dynamic lighting because they move around the world
BLUE_INTERFACE( IWodDynamicallyLit ) : public  IRoot
{
	virtual void SetLightsOfInfluence( std::set<WodLightSourceOverridePtr> lights ) = 0;
};

BLUE_DECLARE_INTERFACE( IWodDynamicallyLit );

class LightSignificanceItem
{
public:
	// An item appears earlier, if the intensity is greater
	bool operator <( const LightSignificanceItem& right ) const { return m_intensity > right.m_intensity; };

	LightSignificanceItem( WodLightSourceOverridePtr _light, float _intensity) : 
		m_light(_light), 
		m_intensity(_intensity)
	{};

	WodLightSourceOverridePtr m_light;
	float m_intensity;
	
};

#endif