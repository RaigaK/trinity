#pragma once
#ifndef Tr2InteriorProbeVolume_H
#define Tr2InteriorProbeVolume_H

#include "Enlighten2/Enlighten.h"
#include "blue\include\BlueAsyncRes.h"
#include "GeoCore/GeoFileStream.h"
#include "TriEnlightenUtils.h"
#include "Utilities/BoundingBox.h"

// forwards
BLUE_DECLARE( Tr2InteriorProbeVolume );
BLUE_DECLARE( TriLineSet );
BLUE_DECLARE( Tr2SHProbeRes );
BLUE_DECLARE( Tr2InteriorCell );

// A SH light probe volume class.
// Probe volumes are maintained by interior cells.
BLUE_CLASS( Tr2InteriorProbeVolume ) :
	public IInitialize
{
public:
	Tr2InteriorProbeVolume( IRoot* lockobj = 0 );
	~Tr2InteriorProbeVolume();

	EXPOSE_TO_BLUE();

    using IInitialize::Lock;
    using IInitialize::Unlock;

	/////////////////////////////////////////////////////////////////////////////////////
	// IInitialize
	bool Initialize();

#if TRINITYDEV
	virtual void GetDescription( std::string& desc ) { desc = "Tr2InteriorProbeVolume"; }
#endif

	// Sets parent cell pointer
	void SetParentCell( Tr2InteriorCell* cell );

	// Render bounding box and/or probe positions for debugging
	void RenderDebugInfo( TriLineSetPtr lines ) const;

	// Returns bounding box in local coordinate system
	bool GetLocalBoundingBox( Vector3& min, Vector3& max ) const;
	// Returns bounding box in world coordinate system
	bool GetWorldBoundingBox( Vector3& min, Vector3& max ) const;

	// Returns a transform matrix from local to world coordinate system
    const Matrix& GetTransform( void ) const { return m_transform; }
	// Sets a new transform matrix from local to world coordinate system (Enlighten data is invalidated after setting it)
	void SetTransform( const Matrix &transform );

	// Returns center of the volume in world coordinate system
	const Vector3& GetPosition( void ) const { return *(reinterpret_cast<const Vector3*>(&m_transform._41)); }
	// Sets a new center of the volume position in world coordinate system (Enlighten data is invalidated after setting it)
	void SetPosition( const Vector3& pos );

	// Returns the rotation component of the transformation matrix
	const Quaternion GetRotation( void ) const;
	// Sets a new rotation component of the transformation matrix (Enlighten data is invalidated after setting it)
	void SetRotation( const Quaternion& rotQuat );

	// Returns the scaling component of the transformation matrix
	const Vector3 GetScaling( void ) const;
	// Sets a new scaling component of the transformation matrix (Enlighten data is invalidated after setting it)
	void SetScaling( const Vector3& scaleVec );

	// Returns a probe resolution in local X direction
	int GetResolutionX() const;
	// Sets probe resolution in local X direction (Enlighten data is invalidated after setting it)
	void SetResolutionX(int);
	// Returns a probe resolution in local Y direction
	int GetResolutionY() const;
	// Sets probe resolution in local Y direction (Enlighten data is invalidated after setting it)
	void SetResolutionY(int);
	// Returns a probe resolution in local Z direction
	int GetResolutionZ() const;
	// Sets probe resolution in local Z direction (Enlighten data is invalidated after setting it)
	void SetResolutionZ(int);

	// Returns a contribution of the volume lighting for further mixing (is <1 when the position is outside the volume)
	float GetMixWeight( const Vector3& position ) const;
	// Returns returns 8 nearest probe positions and their mixing weights for a given point
	void GetProbePositions( const Vector3& position, Vector3 *probes, float *weights ) const;
	// Rebuilds probe positions
	virtual void BuildLightVolume( int xRes, int yRes, int zRes );

	// Sets a flag to visualize probes as 
	void SetSphereProbeVisualization( bool visualize );
	// Returns true iff probes need to be visualized as spheres
	bool GetSphereProbeVisualization() const;
	// Sets flag if probes are valid (built)
	void SetValidProbes( bool validProbes );
	// Returns true iff probes are valid (built)
	bool HasValidProbes() const;
public:
	// Light probe positions
	std::vector<Vector3> m_lightProbes;
private:
	AxisAlignedBoundingBox GetBoundingBoxInLocalSpace() const;
	AxisAlignedBoundingBox GetBoundingBoxInWorldSpace() const;

	// Get parent cell transform
	const Matrix& GetParentTransform() const;

	// Flag to draw bounding box for debug rendering
	bool m_drawBoundingBox;

	// A transform matrix from local to world coordinate system
	Matrix m_transform;

	// A volume of probe samples
	GeoEngine::NonAAVolume *m_volumeBox;

	// Parent cell
	Tr2InteriorCell* m_parentCell;
public:
	// Probe resolution in X direction
	int m_lightProbeResX;
	// Probe resolution in Y direction
	int m_lightProbeResY;
	// Probe resolution in Z direction
	int m_lightProbeResZ;

	// Flag to draw probe positions for debug rendering
	bool m_bDrawLightProbes;
	// Flag to draw probes as spheres
	bool m_sphereProbes;
	// Flag to draw probes as red when probe is culled or green otherwise (only works when m_sphereProbes is on)
	bool m_drawProbeCulling;
	// Flag indicating that probes are valid (built)
	bool m_validProbes;
};

TYPEDEF_BLUECLASS( Tr2InteriorProbeVolume );
BLUE_DECLARE_VECTOR( Tr2InteriorProbeVolume );

#endif // Tr2InteriorProbeVolume_H
