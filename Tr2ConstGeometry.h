////////////////////////////////////////////////////////////
//
//    Created:   August 2012
//    Copyright: CCP 2012
//

#pragma once
#ifndef Tr2ConstGeometry_H
#define Tr2ConstGeometry_H

// --------------------------------------------------------------------------------------
// Description:
//   Tr2ConstGeometry stores shared immutable vertex and index arrays created from 
//   constant data. Used by interior lights.
// --------------------------------------------------------------------------------------
class Tr2ConstGeometry
{
public:
	static Tr2VertexBufferAL* GetVB( const void* vertices, unsigned size );
	static Tr2IndexBufferAL* GetIB( Tr2RenderContextEnum::IndexBufferBitcount bitCount, const void* indices, unsigned indexCount );
};

#endif // Tr2ConstGeometry_H