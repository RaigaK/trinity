//////////////////////////////////////////////////////////////////////////
//
// Created: December 2010
// Copyright CCP 2010
//

#pragma once

#ifndef Tr2Sprite2dLineTrace_h
#define Tr2Sprite2dLineTrace_h

#include "Tr2SpriteObject.h"

BLUE_DECLARE( Tr2Sprite2dLineTrace );
BLUE_DECLARE_INTERFACE( ITr2Sprite2dTexture );
BLUE_DECLARE( Tr2Sprite2dLineTraceVertex );
BLUE_DECLARE_VECTOR( Tr2Sprite2dLineTraceVertex );

class Tr2Sprite2dLineTraceVertex :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	Tr2Sprite2dLineTraceVertex( IRoot* lockobj = NULL );

private:
	friend class Tr2Sprite2dLineTrace;

	std::string m_name;
	Vector2 m_position;
	Color m_color;
};

TYPEDEF_BLUECLASS( Tr2Sprite2dLineTraceVertex );

class Tr2Sprite2dLineTrace :
	public Tr2TexturedSpriteObject,
	public IListNotify
{
public:
	EXPOSE_TO_BLUE();

	Tr2Sprite2dLineTrace( IRoot* lockobj = NULL );
	~Tr2Sprite2dLineTrace();

	//////////////////////////////////////////////////////////////////////////
	// ITr2SpriteObject
	unsigned int GetVertexCount();
	void GatherSprites( Tr2Sprite2dScene* renderer );

	ITr2SpriteObject* PickPoint( float x, float y, Tr2Sprite2dScene* renderer );

	//////////////////////////////////////////////////////////////////////////
	// IListNotify
	void OnListModified(
		long event,		// BLUELISTEVENT values
		ssize_t key,
		ssize_t key2,
		IRoot* value,
		const IList* theList
		);

private:
	void ClearVertices();
	float CalcLength();
	void AddSegment( 
		Tr2Sprite2dScene* renderer, 
		const Vector2& from, 
		const Color& fromColor, 
		float capAngleFrom,
		const Vector2& to, 
		const Color& toColor, 
		float capAngleTo);
	float ClampAngle(float angle);

private:
	std::wstring m_name;

	PTr2Sprite2dLineTraceVertexVector m_vertices;

	float m_lineWidth;
	float m_textureWidth;
	float m_textureOffset;
	float m_textureOffsetAccum;
	float m_length;

	float m_start;
	float m_end;
	bool m_isLoop;

	Tr2Sprite2dD3DVertex* m_renderVertices;
	unsigned int m_renderVertexCapacity;
	unsigned int m_renderVertexCount;
	TrackableStdVector<unsigned short> m_renderIndices;
};

TYPEDEF_BLUECLASS( Tr2Sprite2dLineTrace );

#endif