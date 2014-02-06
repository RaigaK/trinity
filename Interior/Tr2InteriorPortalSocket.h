////////////////////////////////////////////////////////////
//
//    Created:   May 2010
//    Copyright: CCP 2010
//

#pragma once
#ifndef Tr2InteriorPortalSocket_H
#define Tr2InteriorPortalSocket_H

BLUE_DECLARE( Tr2InteriorPhysicalPortal );
BLUE_DECLARE( Tr2InteriorCell );
BLUE_DECLARE( TriLineSet );
class TriEnlightenProgressBar;

// -------------------------------------------------------------
// Description:
//   Tr2InteriorPortalSocket is a class that handles Enlighten light
//   transport though portals. Pairs of portal sockets are linked with
//   Tr2InteriorPhysicalPortal objects. The list of sockets is maintained by
//   Tr2InteriorEnlightenSystem class. 
// SeeAlso:
//   Tr2InteriorEnlightenSystem, Tr2InteriorPhysicalPortal
// -------------------------------------------------------------
BLUE_CLASS( Tr2InteriorPortalSocket ) :
	public INotify,
	public IInitialize
{
public:
	Tr2InteriorPortalSocket( IRoot* lockobj = 0 );
	~Tr2InteriorPortalSocket();

	EXPOSE_TO_BLUE();

	using INotify::Lock;
	using INotify::Unlock;

	/////////////////////////////////////////////////////////////////////////////////////
	// IInitialize
	bool Initialize();

	/////////////////////////////////////////////////////////////////////////////////////
	// INotify
	virtual bool OnModified( Be::Var* value );

	// Set L2 SH coefficients for lighting coming into the portal socket
	void SetInputColor( const Matrix& redMat, const Matrix& greenMat, const Matrix& blueMat );
	// Set L2 SH coefficients for lighting coming from opposite linked socket
	void SetOutputColor( const Matrix& redMat, const Matrix& greenMat, const Matrix& blueMat );

	// Returns SH probe position for the socket
	bool GetInputProbePosition( Geo::v128& position );
	// Notify socket if it contains a valid SH probe
	void SetHasValidProbe( bool validProbe );
	// Returns true iff the socket contains a valid probe
	bool HasValidProbe() const;

#if defined(ENLIGHTEN_PRECOMPUTE_ENABLED)
	// Returns packed geometry for emissive surface
	Enlighten::IPrecompPackedGeometry* GetEnlightenPackedGeometry( Enlighten::IPrecompute* pPrecompute, TriEnlightenProgressBar& prog, float outputPixelSize );
#endif

	// Assign instance index for emissive geometry
	void SetInstanceInSystemIdx( unsigned int index );
	// Returns instance index for emissive geometry
	unsigned int GetInstanceInSystemIdx() const;
	// Returns emissive geometry color
	const Color& GetEmissiveColor();

	void SetTexturePixelPosition( const Vector2& position );
	const Vector2& GetTexturePixelPosition() const;

	// Notifies socket when it's added to a system
	void AddToCell( Tr2InteriorCell* cell );
	// Notifies socket when it's added to a portal
	void AddToPortal( Tr2InteriorPhysicalPortal* portal );

	// Returns containing cell
	Tr2InteriorCell* GetCell() const;

	const Matrix& GetTransform() const;
	void SetTransform( const Matrix& transform );
	Matrix GetWorldTransform() const;

	// Returns bounding box in local socket's space
	void GetLocalBoundingBox( Vector3& minBounds, Vector3& maxBounds );
	// Returns bounding box world space
	void SetLocalBoundingBox( const Vector3& minBounds, const Vector3& maxBounds );

	// Renders debugging info
	void RenderDebugInfo( TriLineSetPtr lines );
private:
	const Vector3& GetNormalCell();
	const Vector3& GetNormalLocal();

	const Matrix& GetParentTransform() const;

	// Name
	std::string m_name;

	// Bounding box
	Vector3 m_minBounds;
	Vector3 m_maxBounds;

	Matrix m_transform;

	// Scaling factor for lighting emitted by socket
	float m_scale;

	Tr2InteriorPhysicalPortal* m_portal;
	Tr2InteriorCell* m_cell;

	// SH probe offset along socket's normal from its center
	float m_probeOffset;

	// "Normal" is a vector pointing towards the containing system
	// Cached normal in parent cell space
	Vector3 m_normalCell;
	// Cached normal in world space
	Vector3 m_normalLocal;

#if defined(ENLIGHTEN_PRECOMPUTE_ENABLED)
	// Enlighten packed geometry
	Geo::GeoAutoReleasePtr<Enlighten::IPrecompPackedGeometry> m_packedGeometry;
#endif

	// Index of geometry in Enlighten system
	unsigned int m_instanceInSystemIdx;
	// Unique id for socket's geometry
	unsigned int m_geometryGuid;
	// Emissive geometry color
	Color m_emissiveColor;
	// Flag if the SH probe for portal is valid
	bool m_validProbe;
	// Position in Enlighten albedo texture
	Vector2 m_texturePosition;
};

TYPEDEF_BLUECLASS( Tr2InteriorPortalSocket );
BLUE_DECLARE_VECTOR( Tr2InteriorPortalSocket );

#endif // Tr2InteriorPortalSocket_H