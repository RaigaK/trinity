// Precompiled header
#include "StdAfx.h"

#if INTERIORS_ENABLED


// Tr2UmbraScene header
#include "Tr2UmbraScene.h"

// Trinity headers
#include "Tr2Renderer.h"
#include "TriFrustum.h"

// ------------------------------------------------------------------------------------------------------
void Tr2UmbraScene::command( Command c )
{
	CCP_STATS_ZONE( __FUNCTION__ );

	switch( c )
	{
	case QUERY_BEGIN:
		OnQueryBegin();
		break;

	case QUERY_END:
		OnQueryEnd();
		break;

	case PORTAL_ENTER:
		OnPortalEnter();
		break;

	case PORTAL_EXIT:
		OnPortalExit();
		break;

	case PORTAL_PRE_EXIT:
		OnPortalPreExit();
		break;

	case CELL_IMMEDIATE_REPORT:
		OnCellImmediateReport();
		break;

	case VIEW_PARAMETERS_CHANGED:
		OnViewParametersChanged();
		break;

	case INSTANCE_VISIBLE:
		OnInstanceVisible();
		break;

	case REMOVAL_SUGGESTED:
		OnRemovalSuggested();
		break;

	case INSTANCE_IMMEDIATE_REPORT:
		OnInstanceImmediateReport();
		break;

	case REGION_OF_INFLUENCE_ACTIVE:
		OnRegionOfInfluenceActive();
		break;

	case REGION_OF_INFLUENCE_INACTIVE:
		OnRegionOfInfluenceInactive();
		break;

	case STENCIL_MASK:
		OnStencilMask();
		break;

	case TEXT_MESSAGE:
		OnTextMessage();
		break;

	case DRAW_LINE_2D:
		OnDrawLine2D();
		break;

	case DRAW_LINE_3D:
		OnDrawLine3D();
		break;

	case DRAW_BUFFER:
		OnDrawBuffer();
		break;

	case OCCLUSION_QUERY_BEGIN:
		OnOcclusionQueryBegin();
		break;

	case OCCLUSION_QUERY_END:
		OnOcclusionQueryEnd();
		break;

	case OCCLUSION_QUERY_GET_RESULT:
		OnOcclusionQueryGetResult();
		break;

	case OCCLUSION_QUERY_DRAW_TEST_DEPTH:
		OnOcclusionQueryDrawTestDepth();
		break;

	case INSTANCE_DRAW_DEPTH:
		OnInstanceDrawDepth();
		break;

	case FLUSH_DEPTH:
		OnFlushDepth();
		break;

	case DEPTH_PASS_BEGIN:
		OnDepthPassBegin();
		break;

	case DEPTH_PASS_END:
		OnDepthPassEnd();
		break;

	case COLOR_PASS_BEGIN:
		OnColorPassBegin();
		break;

	case COLOR_PASS_END:
		OnColorPassEnd();
		break;

	case TILE_BEGIN:
		OnTileBegin();
		break;

	case TILE_END:
		OnTileEnd();
		break;

	case FLUSH_GPU_COMMAND_BUFFER:
		OnFlushGPUCommandBuffer();
		break;
	}
}

// ------------------------------------------------------------------------------------------------------
Tr2UmbraCamera::Tr2UmbraCamera() :
	m_width( 1 ),
	m_height( 1 ),
	m_properties( Umbra::Camera::VIEWFRUSTUM_CULLING | Umbra::Camera::OCCLUSION_CULLING ),
	m_camera( NULL ),
	m_isCameraReady( false )
{
	// Create Umbra camera
	m_camera = Umbra::Camera::create();
}

// ------------------------------------------------------------------------------------------------------
Tr2UmbraCamera::~Tr2UmbraCamera()
{
	if( m_camera )
	{
		m_camera->release();
		m_camera = NULL;
	}
}

// ------------------------------------------------------------------------------------------------------
void Tr2UmbraCamera::SetScreenSize( unsigned int width, unsigned int height )
{
	if( !m_isCameraReady || ( (width != m_width) || (height != m_height) ) )
	{
		m_width = width;
		m_height = height;

		UpdateParameters();
	}
}

// ------------------------------------------------------------------------------------------------------
void Tr2UmbraCamera::EnableVirtualPortals( bool enable )
{
	if( enable )
	{
		if( (m_properties & Umbra::Camera::DISABLE_VIRTUALPORTALS) == Umbra::Camera::DISABLE_VIRTUALPORTALS )
		{
			m_properties ^= Umbra::Camera::DISABLE_VIRTUALPORTALS;
		}
	}
	else
	{
		m_properties |= Umbra::Camera::DISABLE_VIRTUALPORTALS;
	}

	UpdateParameters();
}

void Tr2UmbraCamera::EnableOcclusionCulling( bool enable )
{
	bool enableTest = ((m_properties & Umbra::Camera::OCCLUSION_CULLING)!=0);

	if( enableTest == enable )
	{
		return;
	}

	m_properties ^= Umbra::Camera::OCCLUSION_CULLING;

	UpdateParameters();
}

void Tr2UmbraCamera::EnableFrustumCulling( bool enable )
{

	bool enableTest = ((m_properties & Umbra::Camera::VIEWFRUSTUM_CULLING) != 0);

	if( enableTest == enable )
    {
        return;
    }

    m_properties ^= Umbra::Camera::VIEWFRUSTUM_CULLING;

    UpdateParameters();
}

void Tr2UmbraCamera::EnableDepthPass( bool enable )
{
	bool enableTest = ((m_properties & Umbra::Camera::DEPTH_PASS) != 0);

	if( enableTest == enable )
	{
		return;
	}

	m_properties ^= Umbra::Camera::DEPTH_PASS;

	UpdateParameters();
}

// ------------------------------------------------------------------------------------------------------
void Tr2UmbraCamera::ResolveVisibility( Umbra::Commander* commander, Umbra::Cell* cell, int recursionDepth )
{
	CCP_STATS_ZONE( __FUNCTION__ );
	CCP_ASSERT( m_camera );
    CCP_ASSERT( m_isCameraReady );

	if( !cell )
	{
		return;
	}

	Matrix cameraTransform;
	if( m_camera->getCell() )
	{
		m_camera->getCameraToWorldMatrix( AS_UMBRA_MATRIX(cameraTransform) );
	}
	else
	{
		m_camera->getCameraToCellMatrix( AS_UMBRA_MATRIX(cameraTransform) );
	}
	m_camera->setCell( cell );

	Matrix cellTransform;
	cell->getCellToWorldMatrix( AS_UMBRA_MATRIX(cellTransform) );
	XMVECTOR det;
	cameraTransform = XMMatrixMultiply( 
		cameraTransform, XMMatrixInverse( &det, cellTransform ) );
	m_camera->setCameraToCellMatrix( AS_UMBRA_MATRIX(cameraTransform) );

	m_camera->resolveVisibility( commander, recursionDepth );
}

// ------------------------------------------------------------------------------------------------------
void Tr2UmbraCamera::SetViewParameters( const Matrix& viewToCell, const TriFrustum* frustum )
{
	CCP_ASSERT( m_camera );

	// Adjust the view matrix to account for right-handedness
	Matrix viewToCellForUmbra = viewToCell;
	if( Tr2Renderer::IsRightHanded() )
	{
		// A right-handed camera looks down the negative z-axis so anything in front
		// of the camera has a negative z value in view space. The projection matrix
		// then gets those values into the 0-1 range of clip space by flipping and
		// scaling the z-values. Since we don't include the projection matrix in
		// what we pass to Umbra we need to flip the z here explicitly.
		Vector3& zAxis = viewToCellForUmbra.GetZ();
		zAxis = -zAxis;
	}

	// Build an Umbra frustum
	Umbra::Frustum umbraFrustum;
	float x = tanf( 0.5f * frustum->m_fov );
    umbraFrustum.left = -x * frustum->m_zNear * frustum->m_aspectRatio;
    umbraFrustum.right = x * frustum->m_zNear * frustum->m_aspectRatio;
    umbraFrustum.bottom = -x * frustum->m_zNear;
    umbraFrustum.top = x * frustum->m_zNear;
    umbraFrustum.zNear = frustum->m_zNear;
    umbraFrustum.zFar = frustum->m_zFar;
	umbraFrustum.type = Umbra::Frustum::PERSPECTIVE;

	// Set the camera parameters
	m_camera->setFrustum( umbraFrustum );

	if( m_camera->getCell() )
	{
		Matrix cellToWorld;
		m_camera->getCell()->getCellToWorldMatrix( AS_UMBRA_MATRIX(cellToWorld) );
		XMVECTOR det;
		viewToCellForUmbra = XMMatrixMultiply( 
			viewToCellForUmbra, XMMatrixInverse( &det, cellToWorld ) );
	}

	m_camera->setCameraToCellMatrix( AS_UMBRA_MATRIX( viewToCellForUmbra ) );
}

// ------------------------------------------------------------------------------------------------------
void Tr2UmbraCamera::SetViewParameters( const Matrix& viewToCell, const Matrix& projection )
{
	CCP_ASSERT( m_camera );

	// Adjust the view matrix to account for right-handedness
	Matrix viewToCellForUmbra = viewToCell;

	Umbra::Frustum umbraFrustum;

	if( projection._34 == 0.f )
	{
		umbraFrustum.type = Umbra::Frustum::ORTHOGRAPHIC;
		if( Tr2Renderer::IsRightHanded() )
		{
			// A right-handed camera looks down the negative z-axis so anything in front
			// of the camera has a negative z value in view space. The projection matrix
			// then gets those values into the 0-1 range of clip space by flipping and
			// scaling the z-values. Since we don't include the projection matrix in
			// what we pass to Umbra we need to flip the z here explicitly.
			Vector3& zAxis = viewToCellForUmbra.GetZ();
			zAxis = -zAxis;

			umbraFrustum.zNear = projection._43 / projection._33;
			umbraFrustum.zFar = umbraFrustum.zNear - 1.f / projection._33;
		}
		else
		{
			umbraFrustum.zNear = -projection._43 / projection._33;
			umbraFrustum.zFar = umbraFrustum.zNear + 1.f / projection._33;
		}

		float lr = projection._41 / -projection._11 * 2.f;
		float l_r = 2.f / -projection._11;
		umbraFrustum.left = 0.5f * ( lr + l_r );
		umbraFrustum.right = lr - umbraFrustum.left;

		float tb = projection._42 / -projection._22 * 2.f;
		float t_b = 2.f / -projection._22;
		umbraFrustum.bottom = 0.5f * ( tb + t_b );
		umbraFrustum.top = lr - umbraFrustum.bottom;
	}
	else
	{
		float m31, m32, m33;
		float m43 = projection._43;  // this value is the same for right and left handed matrices
		if( Tr2Renderer::IsRightHanded() )
		{
			// A right-handed camera looks down the negative z-axis so anything in front
			// of the camera has a negative z value in view space. The projection matrix
			// then gets those values into the 0-1 range of clip space by flipping and
			// scaling the z-values. Since we don't include the projection matrix in
			// what we pass to Umbra we need to flip the z here explicitly.
			Vector3& zAxis = viewToCellForUmbra.GetZ();
			zAxis = -zAxis;
			m31 = projection._31;
			m32 = projection._32;
			m33 = projection._33;
		}
		else
		{
			// Left handed matrix has the 3rd row negated, switch it so that 
			// is always the right handed value (so we can just use right handed formulas)
			m31 = -projection._31;
			m32 = -projection._32;
			m33 = -projection._33;
		}

		float zNear = m43 / m33;
		float zFar  = m43 / ( m33 + 1.0f ); 
		
		float m11 = projection._11; // same for left and right handed matrices
		float right = zNear * (m31 + 1.0f) / m11;
		float left  = zNear * (m31 - 1.0f) / m11;

		float m22 = projection._22; // same for left and right handed matrices
		float top =    zNear * (m32 + 1.0f) / m22;
		float bottom = zNear * (m32 - 1.0f) / m22;

		// Build an Umbra frustum
		umbraFrustum.type = Umbra::Frustum::PERSPECTIVE;
		umbraFrustum.left =   left;
		umbraFrustum.right =  right;
		umbraFrustum.top =    top;
		umbraFrustum.bottom = bottom;
		umbraFrustum.zNear =  zNear;
		umbraFrustum.zFar =   zFar;
	}

	// Set the camera parameters
	m_camera->setFrustum( umbraFrustum );

	if( m_camera->getCell() )
	{
		Matrix cellToWorld;
		m_camera->getCell()->getCellToWorldMatrix( AS_UMBRA_MATRIX(cellToWorld) );
		XMVECTOR det;
		viewToCellForUmbra = XMMatrixMultiply( viewToCellForUmbra, 
			XMMatrixInverse( &det, cellToWorld ) );
	}
	m_camera->setCameraToCellMatrix( AS_UMBRA_MATRIX( viewToCellForUmbra ) );
}
// ------------------------------------------------------------------------------------------------------
void Tr2UmbraCamera::SetProperties( unsigned int width, unsigned int height, unsigned int properties )
{
	if( (m_width != width) || (m_height != height) || (m_properties != properties) )
	{
		m_width = width;
		m_height = height;
		m_properties = properties;

		m_camera->setParameters( static_cast<int>( m_width ),
								 static_cast<int>( m_height ),
								 m_properties,
								 GetUmbraCrashWorkaroundScaling( m_width ),
								 GetUmbraCrashWorkaroundScaling( m_height ) );
	}
}

// ------------------------------------------------------------------------------------------------------
unsigned int Tr2UmbraCamera::GetProperties( void ) const
{
	return m_properties;
}

void Tr2UmbraCamera::UpdateParameters()
{
	CCP_ASSERT( m_camera );

	m_camera->setParameters( static_cast<int>( m_width ),
		                     static_cast<int>( m_height ),
		                     m_properties,
		                     GetUmbraCrashWorkaroundScaling( m_width ),
		                     GetUmbraCrashWorkaroundScaling( m_height ) );

	m_isCameraReady = true;
}

// --------------------------------------------------------------------------------------
// Description:
//   Umbra suffers from a crash bug that hits at resolutions >= 2048
// Return Value:
//   Return a non-crashy scaling factor for X or Y resolutions for any given screen size
// --------------------------------------------------------------------------------------
float Tr2UmbraCamera::GetUmbraCrashWorkaroundScaling( unsigned int size ) const
{
	if( size > 1024 )
	{
		return (float)(1024.0/((double)size));
	}
	else
	{
		return 1.0f;
	}
}

#endif
