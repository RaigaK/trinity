//////////////////////////////////////////////////////////////////////////
//
// Created: December 2010
// Copyright CCP 2010
//

#include "StdAfx.h"
#include "Tr2Sprite2dLineTrace.h"
#include "Tr2Sprite2dTexture.h"
#include "Tr2Sprite2dScene.h"

Tr2Sprite2dLineTraceVertex::Tr2Sprite2dLineTraceVertex( IRoot* lockobj /*= NULL */ ) :
	m_position( 0.0f, 0.0f ),
	m_color( 1.0f, 1.0f, 1.0f, 1.0f )
{
}

Tr2Sprite2dLineTrace::Tr2Sprite2dLineTrace( IRoot* lockobj /*= NULL */ ) :
	PARENTLOCK( m_vertices ),
	m_lineWidth( 1.0f ),
	m_length( 0.0f ),
	m_start( 0.0f ),
	m_end( 1.0f ),
	m_isLoop( false ),
	m_renderVertices( nullptr ),
	m_renderVertexCapacity( 0 ),
	m_renderVertexCount( 0 ),
	m_renderIndices( "Tr2Sprite2dLineTrace/m_renderIndices" ),
	m_textureWidth( 1.0f),
	m_textureOffset( 0.0f ),
	m_textureOffsetAccum( 0.0f )
{
	m_vertices.SetNotify( this );
}

Tr2Sprite2dLineTrace::~Tr2Sprite2dLineTrace()
{
	ClearVertices();
}

void Tr2Sprite2dLineTrace::GatherSprites( Tr2Sprite2dScene* renderer )
{
	CCP_STATS_ZONE( __FUNCTION__ );

	if( !m_display || m_vertices.empty() || (m_end <= m_start) || (m_spriteEffect == TR2_SFX_NONE) )
	{
		if( m_renderVertices )
		{
			ClearVertices();
		}
		return;
	}

	if( m_isDirty )
	{
		ClearVertices();

		if( !ValidateAndSetTextures( renderer ) )
		{
			return;
		}

		renderer->SetSpriteEffect( m_spriteEffect );
		renderer->SetTileMode( S2D_TS_TILE_X | S2D_TS_TILE_Y);

		SetRegularRenderState( renderer );

		renderer->PushTranslation( m_translation );

		m_renderVertexCapacity = GetVertexCount();
		m_renderVertices = (Tr2Sprite2dD3DVertex*)CCP_MALLOC( 
			"Tr2Sprite2dLineTrace/m_renderVertices", 
			m_renderVertexCapacity * sizeof( Tr2Sprite2dD3DVertex ) );
		m_renderVertexCount = 0;

		m_length = CalcLength();
		float relativeLength = 0.0f;
		float lastRelativeLength = 0.0f;
		float length = 0.0f;

		bool hasReachedStart = (m_start == 0.0f);
		bool hasReachedEnd = false;

		Vector2 fromPos = m_vertices[0]->m_position;
		Color fromColor = m_vertices[0]->m_color;

		float prevCapAngle = 0.0f;

		float end = m_end;
		if( end > m_start + 1.0f )
		{
			// Prevent looping around multiple times
			end = m_start + 1.0f;
		}

		auto it = m_vertices.begin() + 1;
		while( !hasReachedEnd )
		{
			const Vector2& toPos = (*it)->m_position;
			const Color& toColor = (*it)->m_color;

			Vector2 d = toPos - fromPos;
			float curLength = D3DXVec2Length( &d );
			length += curLength;
			relativeLength = length / m_length;

			Vector2 adjustedFromPos;
			Color adjustedFromColor;

			if( !hasReachedStart && (relativeLength > m_start) )
			{
				// Line is starting - adjust fromPos
				float linePortionOfTotal = curLength / m_length;
				float portionOfLineToRender = (m_start - lastRelativeLength) / linePortionOfTotal;
				adjustedFromPos = toPos*portionOfLineToRender + fromPos*(1.0f - portionOfLineToRender);
				adjustedFromColor = toColor*portionOfLineToRender + fromColor*(1.0f - portionOfLineToRender);
				hasReachedStart = true;
			}
			else
			{
				adjustedFromPos = fromPos;
				adjustedFromColor = fromColor;
			}

			if( hasReachedStart )
			{
				if( relativeLength > end )
				{
					// Line is ending - adjust toPos
					float linePortionOfTotal = curLength / m_length;
					float portionOfLineToRender = (m_end - lastRelativeLength) / linePortionOfTotal;
					Vector2 adjustedToPos = toPos*portionOfLineToRender + fromPos*(1.0f - portionOfLineToRender);
					Color adjustedToColor = toColor*portionOfLineToRender + fromColor*(1.0f - portionOfLineToRender);
					AddSegment( renderer, adjustedFromPos, adjustedFromColor, prevCapAngle, adjustedToPos, adjustedToColor, 0.0f);
					hasReachedEnd = true;
				}
				else
				{
					float capAngleTo = 0.0f;
					if( m_lineWidth > 1.0f )
					{
						auto nextIt = it + 1;
						if( nextIt == m_vertices.end() && m_isLoop )
						{
							nextIt = m_vertices.begin();
						}

						if( nextIt != m_vertices.end() )
						{
							const Vector2& toPos2 = (*nextIt)->m_position;
							Vector2 d2 = toPos2 - toPos;

							D3DXVec2Normalize( &d, &d );
							D3DXVec2Normalize( &d2, &d2 );

							capAngleTo = atan2(d2.y,d2.x) - atan2(d.y,d.x);
							// acosf( D3DXVec2Dot( &d, &d2 ) );
						}
					}
					AddSegment( renderer, adjustedFromPos, adjustedFromColor, prevCapAngle, toPos, toColor, capAngleTo );
					prevCapAngle = capAngleTo;
				}
			}

			++it;

			if( it == m_vertices.end() )
			{
				if( m_isLoop )
				{
					// Wrap around, to allow rendering with start towards the
					// end of the trace, and the end near the beginning, i.e.
					// treat the trace as a closed loop.
					it = m_vertices.begin();
				}
				else
				{
					hasReachedEnd = true;
				}
			}

			fromPos = toPos;
			fromColor = toColor;
			lastRelativeLength = relativeLength;
		}

		renderer->PopTranslation();

		m_isDirty = false;
	}

	SetValidatedTextures( renderer );
	renderer->RenderTriangleVerts( m_renderVertices, m_renderVertexCount, &m_renderIndices[0], (unsigned short)m_renderIndices.size() );
}

ITr2SpriteObject* Tr2Sprite2dLineTrace::PickPoint( float x, float y, Tr2Sprite2dScene* renderer )
{
	// TODO: Implement!
	return NULL;
}

float Tr2Sprite2dLineTrace::CalcLength()
{
	if( m_vertices.size() < 2 )
	{
		return 0.0f;
	}

	Vector2 fromPos = m_vertices[0]->m_position;
	float length = 0.0f;

	for( auto it = m_vertices.begin() + 1; it != m_vertices.end(); ++it )
	{
		const Vector2& toPos = (*it)->m_position;

		Vector2 d = toPos - fromPos;
		length += D3DXVec2Length( &d );

		fromPos = toPos;
	}

	if( m_isLoop )
	{
		Vector2 d = m_vertices[0]->m_position - fromPos;
		length += D3DXVec2Length( &d );
	}

	return length;
}

unsigned int Tr2Sprite2dLineTrace::GetVertexCount()
{
	unsigned int vertsNeeded = (unsigned int)m_vertices.size() * 4 + 2;

	// Add verts for line joints
	unsigned int w = (unsigned int)m_lineWidth;
	vertsNeeded += (unsigned int)m_vertices.size() * w;

	return vertsNeeded;
}

void Tr2Sprite2dLineTrace::AddSegment( 
	Tr2Sprite2dScene* renderer, 
	const Vector2& from, 
	const Color& fromColor, 
	float capAngleFrom,
	const Vector2& to, 
	const Color& toColor, 
	float capAngleTo )
{
	CCP_ASSERT( m_renderVertexCount + 4 <= m_renderVertexCapacity );
	if( m_renderVertexCount + 4 > m_renderVertexCapacity )
	{
		return;
	}

	Vector2 d = to - from;
	float segmentLength = D3DXVec2Length( &d );
	D3DXVec2Normalize( &d, &d );


	// calculate texture offset
	float texOffset1 = m_textureOffsetAccum / m_textureWidth - m_textureOffset;
	m_textureOffsetAccum += segmentLength;
	float texOffset2 = m_textureOffsetAccum / m_textureWidth - m_textureOffset;

	// Anti-aliased lines are rendered with a quad that is larger. This is then 
	// compensated for in the pixel shader, using the extra pixels to fill in
	// alpha values to do the anti-aliasing

	bool isAA = m_spriteEffect == TR2_SFX_FILL_AA;
	float pixelWidthInTexels;

	float halfWidth = 0.5f * m_lineWidth;

	if( isAA )
	{
		halfWidth += 2.0f;
		pixelWidthInTexels = 1.0f / (m_lineWidth + 4.0f);
	}

	capAngleFrom = ClampAngle(capAngleFrom);
	capAngleTo = ClampAngle(capAngleTo);

	float shorteningForCap = halfWidth * tan( std::abs( capAngleTo ) * 0.5f );
	Vector2 adjustedTo = to - shorteningForCap * d;

	shorteningForCap = halfWidth * tan( std::abs( capAngleFrom ) * 0.5f );
	Vector2 adjustedFrom = from + shorteningForCap * d;

	d = adjustedTo - adjustedFrom;
	D3DXVec2Normalize( &d, &d );

	// Rotate 90 degrees
	Vector2 normal;
	normal.x = d.y;
	normal.y = -d.x;

	Tr2Sprite2dVertexBase verts[4];

	Color modulatedFromColor;
	modulatedFromColor.r = m_color.r * fromColor.r;
	modulatedFromColor.g = m_color.g * fromColor.g;
	modulatedFromColor.b = m_color.b * fromColor.b;
	modulatedFromColor.a = m_color.a * fromColor.a;

	Color modulatedToColor;
	modulatedToColor.r = m_color.r * toColor.r;
	modulatedToColor.g = m_color.g * toColor.g;
	modulatedToColor.b = m_color.b * toColor.b;
	modulatedToColor.a = m_color.a * toColor.a;

	// v0 - top left
	Tr2Sprite2dVertexBase& v0 = verts[0];
	v0.position.x = adjustedFrom.x - normal.x*halfWidth;
	v0.position.y = adjustedFrom.y - normal.y*halfWidth;
	v0.position.z = m_depth;
	v0.color = modulatedFromColor;

	v0.texCoord[0] = Vector2( texOffset1, 0.0f );

	if(	isAA )
	{
		v0.texCoord[1] = Vector2( -pixelWidthInTexels, m_lineWidth );
	}
	else
	{
		v0.texCoord[1] = Vector2( texOffset1, 0.0f );
	}

	// v1 - bottom left
	Tr2Sprite2dVertexBase& v1 = verts[1];
	v1.position.x = adjustedFrom.x + normal.x*halfWidth;
	v1.position.y = adjustedFrom.y + normal.y*halfWidth;
	v1.position.z = m_depth;
	v1.color = modulatedFromColor;
	v1.texCoord[0] = Vector2( texOffset1, 1.0f );

	if( isAA )
	{
		v1.texCoord[1] = Vector2( 1.0f + pixelWidthInTexels, m_lineWidth );
	}
	else
	{
		v1.texCoord[1] = Vector2( texOffset1, 1.0f );
	}

	// v2 - bottom right
	Tr2Sprite2dVertexBase& v2 = verts[2];
	v2.position.x = adjustedTo.x + normal.x*halfWidth;
	v2.position.y = adjustedTo.y + normal.y*halfWidth;
	v2.position.z = m_depth;
	v2.color = modulatedToColor;
	v2.texCoord[0] = Vector2( texOffset2, 1.0f );

	if( isAA )
	{
		v2.texCoord[1] = Vector2( 1.0f + pixelWidthInTexels, m_lineWidth );
	}
	else
	{
		v2.texCoord[1] = Vector2( texOffset2, 1.0f );
	}

	// v3 - top right
	Tr2Sprite2dVertexBase& v3 = verts[3];
	v3.position.x = adjustedTo.x - normal.x*halfWidth;
	v3.position.y = adjustedTo.y - normal.y*halfWidth;
	v3.position.z = m_depth;
	v3.color = modulatedToColor;
	v3.texCoord[0] = Vector2( texOffset2, 0.0f );

	if( isAA )
	{
		v3.texCoord[1] = Vector2( -pixelWidthInTexels, m_lineWidth );
	}
	else
	{
		v3.texCoord[1] = Vector2( texOffset2, 0.0f );
	}

	renderer->PrepareTriangleVerts( 
		m_renderVertices + m_renderVertexCount, 
		verts, 
		sizeof( Tr2Sprite2dVertexBase ), 
		4 );

	m_renderIndices.push_back( 0 + m_renderVertexCount );
	m_renderIndices.push_back( 1 + m_renderVertexCount );
	m_renderIndices.push_back( 3 + m_renderVertexCount );
	m_renderIndices.push_back( 3 + m_renderVertexCount );
	m_renderIndices.push_back( 1 + m_renderVertexCount );
	m_renderIndices.push_back( 2 + m_renderVertexCount );

	m_renderVertexCount += 4;
	unsigned int fanVertexBase = m_renderVertexCount;

	// Construct joint
	if( capAngleTo == 0.0f )
	{
		// No need for a joint
		return;
	}

	unsigned short fanBase;
	Vector2 fanBaseTranslation;
	float sign = 1.0f;
	if( capAngleTo < 0.0f )
	{
		fanBase = 2 + m_renderVertexCount - 4;
		fanBaseTranslation = v2.position;
		sign = -1.0f;
	}
	else if( capAngleTo > 0.0f )
	{
		fanBase = 3 + m_renderVertexCount - 4;
		fanBaseTranslation = v3.position;
	}

	float startAngle = atan2( normal.y, normal.x );
	float endAngle = startAngle + capAngleTo;
	float angleDiff = endAngle - startAngle;
	
	float arcLength = angleDiff * m_lineWidth;
	unsigned int numSteps = (unsigned int)arcLength / 4;
	if( numSteps < 1 )
	{
		numSteps = 1;
	}
	float stepSize = angleDiff / (float)numSteps;
	++numSteps;

	// This needs to be synced up with GetVertexCount
	unsigned int w = (unsigned int)m_lineWidth;

	if( numSteps > w )
	{
		numSteps = w;
		stepSize = angleDiff / (float)(numSteps - 1);
	}

	Tr2Sprite2dVertexBase* fanVerts = (Tr2Sprite2dVertexBase*)CCP_MALLOC( 
		"Tr2Sprite2dLineTrace/fanVerts", 
		numSteps * sizeof( Tr2Sprite2dVertexBase ) );
	
	Tr2Sprite2dVertexBase* currentVertex = fanVerts;
	float a = startAngle;
	float jointWidth = halfWidth * 2.0f;
	for( unsigned int i = 0; i < numSteps; ++i )
	{
		
		Tr2Sprite2dVertexBase& v = *currentVertex++;
		v.position.x = sign * cos( a ) * jointWidth + fanBaseTranslation.x;
		v.position.y = sign * sin( a ) * jointWidth + fanBaseTranslation.y;
		v.position.z = m_depth;
		v.color = modulatedToColor;

		if( isAA )
		{
			if( sign > 0.0f )
			{
				v.texCoord[1] = Vector2( 1.0f + pixelWidthInTexels, m_lineWidth );
			}
			else
			{
				v.texCoord[1] = Vector2( -pixelWidthInTexels, m_lineWidth );
			}
		}
		else
		{
			m_textureOffsetAccum += abs(arcLength) / float(numSteps);
			texOffset2 = m_textureOffsetAccum / m_textureWidth - m_textureOffset;
			if( sign > 0.0f )
			{
				v.texCoord[0] = Vector2( texOffset2, 1.0f );
			}
			else
			{
				v.texCoord[0] = Vector2( texOffset2, 0.0f );
			}
		}

		if( i > 0 )
		{
			m_renderIndices.push_back( -1 + m_renderVertexCount );
			m_renderIndices.push_back(  0 + m_renderVertexCount );
			m_renderIndices.push_back( fanBase );
		}

		m_renderVertexCount += 1;
		a += stepSize;

		CCP_ASSERT( m_renderVertexCount <= m_renderVertexCapacity );
	}

	renderer->PrepareTriangleVerts( 
		m_renderVertices + fanVertexBase, 
		fanVerts, 
		sizeof( Tr2Sprite2dVertexBase ), 
		numSteps );

	CCP_FREE( fanVerts );
}

float Tr2Sprite2dLineTrace::ClampAngle(float angle)
{
	if (angle < -XM_PI)
	{
		return angle + 2 * XM_PI;
	}
	else if (angle > XM_PI)
	{
		return angle - 2 * XM_PI;
	}
	return angle;
}

void Tr2Sprite2dLineTrace::ClearVertices()
{
	CCP_FREE( m_renderVertices );
	m_renderVertices = nullptr;
	m_renderVertexCapacity = 0;
	m_renderVertexCount = 0;
	m_renderIndices.clear();
	m_renderIndices.shrink_to_fit();
	m_textureOffsetAccum = 0.0f;
}

void Tr2Sprite2dLineTrace::OnListModified( long event, /* BLUELISTEVENT values */ ssize_t key, ssize_t key2, IRoot* value, const IList* theList )
{
	switch( event )
	{
		case BELIST_INSERTED:
		case BELIST_REMOVED:
		case BELIST_UNLOADSTART:
			SetDirty();
			break;
	}
}
