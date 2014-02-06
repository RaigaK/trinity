#include "StdAfx.h"

#if INTERIORS_ENABLED

#include "TriEnlightenUtils.h"

void TriEnlightenProgressBar::SetProgressString( const Geo::c8* desc )
{
	CCP_LOG( desc );
}

void TriEnlightenProgressBar::SetProportionDone( float amount )
{
	const unsigned bufferSize = 40;
	char buffer[bufferSize];
	sprintf_s( &buffer[0], bufferSize, "%.2f percent done.", 100.0f*amount );
	CCP_LOG( &buffer[0] );
}


//-------------------------------------------------------------------------------------------------
namespace GeoEngine
{
using namespace Geo;

//-------------------------------------------------------------------------------------------------
bool NonAABoundingBox::Initialise(v128* basis, v128 pos, v128 size)
{
	GEO_ASSERT(basis);
	if (fabs(VGetX(VDot3(basis[0],basis[1])))>1E-5f || fabs(VGetX(VDot3(basis[0],basis[2])))>1E-5f || fabs(VGetX(VDot3(basis[1],basis[2])))>1E-5f)
	{
		CCP_LOGWARN( "NonAABoundingBox::Initialise - Basis is not orthonormal." );
	}
	m_Basis[0]=basis[0];
	m_Basis[1]=basis[1];
	m_Basis[2]=basis[2];	
	m_Basis[0] = VOpAnd(m_Basis[0], VGetMaskXYZ());
	m_Basis[1] = VOpAnd(m_Basis[1], VGetMaskXYZ());
	m_Basis[2] = VOpAnd(m_Basis[2], VGetMaskXYZ());
	m_Pos=pos;
	m_Pos = VSelect(VGetMaskXYZ(), m_Pos, VBroadcast(1.f));
	m_Size=size;
	m_Size = VSelect(VGetMaskXYZ(), m_Size, VBroadcast(1.f));
	return SetMatrices();
}

//-------------------------------------------------------------------------------------------------
bool NonAABoundingBox::operator==(const NonAABoundingBox& other) const
{
	float f;
	f=VGetX(VCompareEquals(m_Pos,other.m_Pos));
	if ( *(u32*)&f == 0 )
	{
		return false;
	}
	f=VGetX(VCompareEquals(m_Size,other.m_Size));
	if ( *(u32*)&f == 0 )
	{
		return false;
	}
	f=VGetX(VCompareEquals(m_Basis[0],other.m_Basis[0]));
	if ( *(u32*)&f == 0 )
	{
		return false;
	}
	f=VGetX(VCompareEquals(m_Basis[1],other.m_Basis[1]));
	if ( *(u32*)&f == 0 )
	{
		return false;
	}
	f=VGetX(VCompareEquals(m_Basis[2],other.m_Basis[2]));
	if ( *(u32*)&f == 0 )
	{
		return false;
	}
	return true;
}
bool NonAABoundingBox::operator!=(const NonAABoundingBox& other) const
{
	return !(*this == other);
}
//-------------------------------------------------------------------------------------------------
bool NonAABoundingBox::SetMatrices(void)
{
	// set LU2WC matrix
	m_LU2WC.SetCol( 0, m_Basis[0]*VBroadcastX(m_Size) );
	m_LU2WC.SetCol( 1, m_Basis[1]*VBroadcastY(m_Size) );
	m_LU2WC.SetCol( 2, m_Basis[2]*VBroadcastZ(m_Size) );
	m_LU2WC.SetCol( 3, m_Pos      );
	// set WC2LU matrix
	m_WC2LU=MInverse(m_LU2WC);
	bool r = IsFinite(m_WC2LU.c0) && IsFinite(m_WC2LU.c1) && IsFinite(m_WC2LU.c2) && IsFinite(m_WC2LU.c3);
	return r;
}

//-------------------------------------------------------------------------------------------------
v128 NonAABoundingBox::MapToLocalUnitCube(const v128& p) const
{
	return m_WC2LU*VSetW(p,1.0f);
}

//-------------------------------------------------------------------------------------------------
v128 NonAABoundingBox::MapFromLocalUnitCube(const v128& p) const
{
	return m_LU2WC*p;
}

//-------------------------------------------------------------------------------------------------
bool NonAABoundingBox::ContainsPoint(const v128& p) const
{
	v128 lp = MapToLocalUnitCube( VSetW(p,1.0f) );
	float x = VGetX( lp );
	float y = VGetY( lp );
	float z = VGetZ( lp );
	return ( x >= 0 && x <= 1 &&
			 y >= 0 && y <= 1 &&
			 z >= 0 && z <= 1 );
}

//-------------------------------------------------------------------------------------------------
float NonAABoundingBox::SquaredDistanceToPoint(const v128& p) const
{

	v128 lp = MapToLocalUnitCube( VSetW(p,1.0f) );
	float x = VGetX( lp );
	float y = VGetY( lp );
	float z = VGetZ( lp );

	if ( x >= 0 && x <= 1 && y >= 0 && y <= 1 && z >= 0 && z <= 1 )
	{
		// inside box
		v128 dlp=p-MapFromLocalUnitCube( VConstruct( floor(x+.5f), floor(y+.5f), floor(z+.5f), 1.f ) );
		return -(VGetX( dlp ) * VGetX( dlp ) + VGetY( dlp ) * VGetY( dlp ) + VGetZ( dlp ) * VGetZ( dlp ));
	}
	else
	{
		v128 dlp=p-MapFromLocalUnitCube( Geo::Max( VBroadcast(.0f), Geo::Min( VBroadcast(1.f), lp ) ) );
		return VGetX( dlp ) * VGetX( dlp ) + VGetY( dlp ) * VGetY( dlp ) + VGetZ( dlp ) * VGetZ( dlp );
	}
}

//-------------------------------------------------------------------------------------------------
float NonAABoundingBox::DistanceToPoint(const v128& p) const
{

	v128 lp = MapToLocalUnitCube( VSetW(p,1.0f) );
	float x = VGetX( lp );
	float y = VGetY( lp );
	float z = VGetZ( lp );

	if ( x >= 0 && x <= 1 && y >= 0 && y <= 1 && z >= 0 && z <= 1 )
	{
		// inside box
		v128 dlp=p-MapFromLocalUnitCube( VConstruct( floor(x+.5f), floor(y+.5f), floor(z+.5f), 1.f ) );
		return -VGetX(VLength3( dlp ));
	}
	else
	{
		v128 dlp=p-MapFromLocalUnitCube( Geo::Max( VBroadcast(.0f), Geo::Min( VBroadcast(1.f), lp ) ) );
		return VGetX(VLength3( dlp ));
	}
}

//=================================================================================================
NonAAVolume::NonAAVolume()
:	m_XRes(0)
,	m_YRes(0)
,	m_ZRes(0)
{
}

//-------------------------------------------------------------------------------------------------
bool NonAAVolume::Initialise(const NonAABoundingBox* bb, u32 resX, u32 resY, u32 resZ)
{
	GEO_ASSERT( bb );
	if ( !bb ) 
	{
		return false;
	}
	*((NonAABoundingBox*)this)=*bb;
	m_XRes=resX;
	m_YRes=resY;
	m_ZRes=resZ;
	if (GetNumProbes()<1)
	{	
		CCP_LOGWARN( "Empty volume. Was this intended?" );
	}
	return true;
};

//-------------------------------------------------------------------------------------------------
bool NonAAVolume::operator==(const NonAAVolume& other) const
{
	if ( !( *(NonAABoundingBox*)this == *(NonAABoundingBox*)&other ) ) return false;
	if ( !(m_XRes==other.m_XRes && m_YRes==other.m_YRes && m_ZRes==other.m_ZRes) ) return false;
	return true;
}

bool NonAAVolume::operator!=(const NonAAVolume& other) const
{
	return !(*this == other);
}

//--------------------------------------------------------------------------------------------------
bool NonAAVolume::LineariseVoxelID(Geo::u32& i,const Geo::u32 x,const Geo::u32 y,const Geo::u32 z) const
{
	GEO_ASSERT(x<GetXRes()&&y<GetYRes()&&z<GetZRes());
	if (!(x<GetXRes()&&y<GetYRes()&&z<GetZRes())) return false;
	i=(z*GetXRes()*GetYRes()+y*GetXRes()+x);
	return true;
}

//--------------------------------------------------------------------------------------------------
bool NonAAVolume::UnLineariseVoxelID(Geo::u32& x,Geo::u32& y,Geo::u32& z,const Geo::u32 i) const
{
	GEO_ASSERT( i < (Geo::u32)GetNumProbes() );
	if (!(i < (Geo::u32)GetNumProbes())) return false;
	x=i%GetXRes();
	y=(i/GetXRes())%GetYRes();
	z=(i/(GetXRes()*GetYRes()))%GetZRes();
	return true;
}

//--------------------------------------------------------------------------------------------------
bool NonAAVolume::GetNearestSamples(Geo::s32 voxIDs[], float weights[], Geo::v128 point, Geo::s32 INTERP) const
{
	GEO_ASSERT( voxIDs );
	GEO_ASSERT( weights );
	if ( !voxIDs || !weights || (Geo::u32)GetNumProbes()<1 )
	{
		return false;
	}
	// interpolate
	switch (INTERP)
	{
	case VOL_INTERP_NN:
		{
			// http://en.wikipedia.org/wiki/Trilinear_interpolation
			// map point to a periodic and cubic lattice with spacing 1
			Geo::v128 lpos = Geo::Max( Geo::VBroadcast(.0f), Geo::Min( Geo::VBroadcast(1.f), MapToLocalUnitCube( point ) ) ) * 
				Geo::VConstruct( (float)GetXRes(), (float)GetYRes(), (float)GetZRes(), 1 ) - 
				Geo::VBroadcast(.5f);

			// calculate origin voxel ID, of the 4 voxels surrounding the point
			const Geo::u32 ox=(Geo::u32)Geo::Max( (Geo::s32)0, Geo::Min( (Geo::s32)Geo::Floor(Geo::VGetX(lpos)+.5f), (Geo::s32)GetXRes()-1) );
			const Geo::u32 oy=(Geo::u32)Geo::Max( (Geo::s32)0, Geo::Min( (Geo::s32)Geo::Floor(Geo::VGetY(lpos)+.5f), (Geo::s32)GetYRes()-1) );
			const Geo::u32 oz=(Geo::u32)Geo::Max( (Geo::s32)0, Geo::Min( (Geo::s32)Geo::Floor(Geo::VGetZ(lpos)+.5f), (Geo::s32)GetZRes()-1) );
			Geo::u32 vid;
			if ( !LineariseVoxelID(vid, ox, oy, oz) ) return false;
			voxIDs[0] = (Geo::s32)vid;
			weights[0] = 1.f;
			return true;
		}
		case VOL_INTERP_TRI:
		{
			// http://en.wikipedia.org/wiki/Trilinear_interpolation
			// map point to a periodic and cubic lattice with spacing 1
			Geo::v128 lpos = Geo::Max( Geo::VBroadcast(.0f), Geo::Min( Geo::VBroadcast(1.f), MapToLocalUnitCube( point ) ) ) * 
				Geo::VConstruct( (float)GetXRes(), (float)GetYRes(), (float)GetZRes(), 1 ) - 
				Geo::VBroadcast(.5f);

			// calculate origin voxel ID, of the 4 voxels surrounding the point
			const Geo::u32 ox=(Geo::u32)Geo::Max( (Geo::s32)0, Geo::Min( (Geo::s32)Geo::Floor(Geo::VGetX(lpos)), (Geo::s32)GetXRes()-1) );
			const Geo::u32 oy=(Geo::u32)Geo::Max( (Geo::s32)0, Geo::Min( (Geo::s32)Geo::Floor(Geo::VGetY(lpos)), (Geo::s32)GetYRes()-1) );
			const Geo::u32 oz=(Geo::u32)Geo::Max( (Geo::s32)0, Geo::Min( (Geo::s32)Geo::Floor(Geo::VGetZ(lpos)), (Geo::s32)GetZRes()-1) );

			const float xd=Geo::Max(0.f,Geo::VGetX(lpos)-ox);
			const float yd=Geo::Max(0.f,Geo::VGetY(lpos)-oy);
			const float zd=Geo::Max(0.f,Geo::VGetZ(lpos)-oz);

			Geo::u32 vid;
			// C_000
			if ( !LineariseVoxelID(vid, ox, oy, oz) ) return false;
			voxIDs[0]  = (Geo::s32)vid;
			weights[0] = (1-xd) * (1-yd) * (1-zd);
			// C_100
			if ( !LineariseVoxelID(vid, Geo::Min(ox+1,(Geo::u32)GetXRes()-1), oy, oz) ) return false;
			voxIDs[1]  = (Geo::s32)vid;
			weights[1] = (  xd) * (1-yd) * (1-zd);
			// C_110
			if ( !LineariseVoxelID(vid, Geo::Min(ox+1,(Geo::u32)GetXRes()-1), Geo::Min(oy+1,(Geo::u32)GetYRes()-1), oz) ) return false;
			voxIDs[2]  = (Geo::s32)vid;
			weights[2] = (  xd) * (  yd) * (1-zd);
			// C_010
			if ( !LineariseVoxelID(vid, ox, Geo::Min(oy+1,(Geo::u32)GetYRes()-1), oz) ) return false;
			voxIDs[3]  = (Geo::s32)vid;
			weights[3] = (1-xd) * (  yd) * (1-zd);
			// C_001
			if ( !LineariseVoxelID(vid, ox, oy, Geo::Min(oz+1,(Geo::u32)GetZRes()-1)) ) return false;
			voxIDs[4]  = (Geo::s32)vid;
			weights[4] = (1-xd) * (1-yd) * (  zd);
			// C_101
			if ( !LineariseVoxelID(vid, Geo::Min(ox+1,(Geo::u32)GetXRes()-1), oy, Geo::Min(oz+1,(Geo::u32)GetZRes()-1)) ) return false;
			voxIDs[5]  = (Geo::s32)vid;
			weights[5] = (  xd) * (1-yd) * (  zd);
			// C_111
			if ( !LineariseVoxelID(vid, Geo::Min(ox+1,(Geo::u32)GetXRes()-1), Geo::Min(oy+1,(Geo::u32)GetYRes()-1), Geo::Min(oz+1,(Geo::u32)GetZRes()-1)) ) return false;
			voxIDs[6]  = (Geo::s32)vid;
			weights[6] = (  xd) * (  yd) * (  zd);
			// C_011
			if ( !LineariseVoxelID(vid, ox, Geo::Min(oy+1,(Geo::u32)GetYRes()-1), Geo::Min(oz+1,(Geo::u32)GetZRes()-1)) ) return false;
			voxIDs[7]  = (Geo::s32)vid;
			weights[7] = (1-xd) * (  yd) * (  zd);
			return true;
		}
	}
	return false;
}

//--------------------------------------------------------------------------------------------------
bool NonAAVolume::GetVoxelCentre(Geo::v128& point,Geo::u32 i) const
{
	GEO_ASSERT( i < (Geo::u32)GetNumProbes() );
	Geo::u32 x,y,z;
	if ( !( i < (Geo::u32)GetNumProbes() && UnLineariseVoxelID(x,y,z,i) ) ) return false;
	point=MapFromLocalUnitCube( VConstruct( (x+.5f)*(1.0f / GetXRes()), (y+.5f)*(1.0f / GetYRes()), (z+.5f)*(1.0f / GetZRes()), 1 ) );
	return true;
}

}

#endif
