#pragma once
#ifndef UmbraTypes_H
#define UmbraTypes_H

#include "D3DFundamentalTypes.h"

namespace Umbra
{
    class Vector3 : public ::Vector3 {};
    class Vector4 : public ::Vector4 {};
    class Matrix4x4 : public ::Matrix {};

    class Vector2    { public: float v[2];			};
    class Vector3d   { public: double v[3];			};
    class Vector3i   { public: INT32 i,j,k;			};
    class Vector4d   { public: double v[4];			};
    class Matrix4x4d { public: double m[4][4];		};
}

//#define AS_UMBRA_MATRIX( m ) (*(Umbra::Matrix4x4*)&m)
//#define AS_UMBRA_VECTOR3( v ) (*(Umbra::Vector3*)&v)

inline const Umbra::Matrix4x4& AS_UMBRA_MATRIX( const Matrix& m )
{
	return *( reinterpret_cast<const Umbra::Matrix4x4*>( &m ) );
}

inline const Umbra::Vector3& AS_UMBRA_VECTOR3( const Vector3& v )
{
	return *( reinterpret_cast<const Umbra::Vector3*>( &v ) );
}

inline Umbra::Matrix4x4& AS_UMBRA_MATRIX( Matrix& m )
{
	return *( reinterpret_cast<Umbra::Matrix4x4*>( &m ) );
}

inline Umbra::Vector3& AS_UMBRA_VECTOR3( Vector3& v )
{
	return *( reinterpret_cast<Umbra::Vector3*>( &v ) );
}

#endif // UmbraTypes_H
