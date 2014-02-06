#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "WodLightSource.h"
#include "WodLightSourceOverride.h"
#include "WodReceivesLights.h"
#include "Tr2Effect.h"

WodReceivesLights::WodReceivesLights(IRoot* lockobj): 
	m_numLights(0),
	PARENTLOCK( m_receivedLights )
{
}

WodReceivesLights::~WodReceivesLights()
{
}

void WodReceivesLights::ClearLights()
{
	m_lightInstances.clear();
	m_numLights = 0;
}

void WodReceivesLights::InsertInOrderOfIntensity(std::list<LightInstance> &newLightsInOrder, const LightInstance &lightInstance)
{
    for(std::list<LightInstance>::iterator it = newLightsInOrder.begin();
        it != newLightsInOrder.end();
        ++it)
    {
        if(lightInstance.m_intensity > it->m_intensity)
        {
            newLightsInOrder.insert(it, lightInstance);
            if(newLightsInOrder.size() > MAX_EXTERIOR_LIGHTS_PER_OBJECT)
            {
                newLightsInOrder.pop_back();
            }
            return;
        }
    }

    newLightsInOrder.push_back(lightInstance);
}

void WodReceivesLights::AddMostSignificantLights(std::vector<LightsAndTransform> *lightsAndTransforms, const Vector3 &objectBoundingBoxWorldMin, const Vector3 &objectBoundingBoxWorldMax )
{
    std::list<LightInstance> newLightsInOrder(m_lightInstances.begin(), m_lightInstances.end());
    for(std::vector<LightsAndTransform>::iterator it = lightsAndTransforms->begin();
        it != lightsAndTransforms->end();
        ++it)
    {
        for(unsigned int i = 0; i < it->lights->size(); i++)
        {
            WodLightSourceOverridePtr lightToAdd = (*it->lights)[i];
            const Matrix &localLightTrans = lightToAdd->GetTransform();
            Vector3 localLightPos(localLightTrans._41, localLightTrans._42, localLightTrans._43);
            Vector3 worldLightPos;
            D3DXVec3TransformCoord(&worldLightPos, &localLightPos, &(it->parentTrans));
            Matrix worldTransform;
            D3DXMatrixMultiply(&worldTransform, &localLightTrans, &(it->parentTrans));

            float intensity = lightToAdd->CalculateIntensityInBoundingBox(worldTransform, objectBoundingBoxWorldMin, objectBoundingBoxWorldMax );
            
            // Skip this light if:
            // The intensity is really low
            // OR
            // We're full and the intensity of the last light in the list is more
            // than the intensity of this light
            if(intensity < 0.01f ||
               (newLightsInOrder.size() >= MAX_EXTERIOR_LIGHTS_PER_OBJECT &&
               newLightsInOrder.back().m_intensity >= intensity))
            {
                continue;
            }

            LightInstance lightInstance(lightToAdd, intensity, worldTransform);
            InsertInOrderOfIntensity(newLightsInOrder, lightInstance);
        }
    }

    m_receivedLights.Remove( -1 );
    m_lightInstances.clear();

    for(std::list<LightInstance>::iterator it = newLightsInOrder.begin();
        it != newLightsInOrder.end();
        ++it)
    {
        m_receivedLights.Insert(-1, it->m_light );
        m_lightInstances.push_back(*it);
    }
	m_numLights = (unsigned int)m_lightInstances.size();
}

#endif
