#pragma once
#ifndef ViewDistanceInfo_h
#define ViewDistanceInfo_h

class TriFrustum;
struct Vector4;

struct ViewDistanceInfo
{
	ViewDistanceInfo();
	ViewDistanceInfo( float nearClipMin, float farClipMax );

	void UpdateClipPlanes( Vector4 boundingSphere, const TriFrustum& frustum );

	float m_near;
	float m_far;

	float m_nearClipMin;
	float m_farClipMax;
};

#endif