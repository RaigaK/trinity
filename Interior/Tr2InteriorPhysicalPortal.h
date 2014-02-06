#pragma once
#ifndef Tr2InteriorPhysicalPortal_H
#define Tr2InteriorPhysicalPortal_H

// Forward declarations
namespace Umbra
{
	class Object;
	class Model;
}

// Blue forward declarations
BLUE_DECLARE( TriLineSet );
BLUE_DECLARE( Tr2InteriorPhysicalPortal );
BLUE_DECLARE( Tr2InteriorCell );
BLUE_DECLARE( Tr2InteriorPortalSocket );
BLUE_DECLARE_INTERFACE( ITr2InteriorDynamic );

class Tr2InteriorPhysicalPortal : 
	public IInitialize,
	public INotify
{
public:
	Tr2InteriorPhysicalPortal( IRoot* lockobj = 0 );
	~Tr2InteriorPhysicalPortal();

	EXPOSE_TO_BLUE();

	using IInitialize::Lock;
	using IInitialize::Unlock;

	/////////////////////////////////////////////////////////////////////////////////////
	// IInitialize
	virtual bool Initialize( void );

	/////////////////////////////////////////////////////////////////////////////////////
	// INotify
	virtual bool OnModified( Be::Var* value );

	/////////////////////////////////////////////////////////////////////////////////////
	// Tr2InteriorPhysicalPortal public members
	void ConnectCells( Tr2InteriorCell* cellA, Tr2InteriorCell* cellB );
	Tr2InteriorCellPtr GetCellA( void ) const;
	Tr2InteriorCellPtr GetCellB( void ) const;
	void RenderDebugInfo( TriLineSetPtr lines ) const;

	// Connects two sockets and their cells
	void ConnectSockets( Tr2InteriorPortalSocket* socketA, Tr2InteriorPortalSocket* socketB );

	Tr2InteriorPortalSocket* GetSocketA() const;
	Tr2InteriorPortalSocket* GetSocketB() const;

	// Sets color of emissive geometry of the socket connected to the given (source) one
	void SetOutputSocketColor( Tr2InteriorPortalSocket* source, const Matrix& redMat, const Matrix& greenMat, const Matrix& blueMat );

	// Create sockets in each connected cell
	void CreateSockets();
	// Position the portal so that its bounding box encloses both socket BBs
	void PositionFromSockets();

	// Called when one of the cells in the scene has been moved
	void OnCellTransformChanged( Tr2InteriorCell* cell );

    void AddDoorToUmbra();

private:
	// Helper functions to add/remove portals in Umbra
	void AddToCells( Tr2InteriorCell* cellA, Tr2InteriorCell* cellB );
	void RemoveFromCells( void );
	// Builds bounding box in transformSocket CS that encloses both sockets
	void PositionFromSocket( Tr2InteriorPortalSocket* transformSocket, Tr2InteriorPortalSocket* boundsSocket, Vector3& minBounds, Vector3& maxBounds );
    void ReleaseDoorUmbraObjects();

private:
	// Culling
	Umbra::PhysicalPortal* m_umbraPortalAtoB;
	Umbra::PhysicalPortal* m_umbraPortalBtoA;
	Umbra::Model* m_umbraModel;

	// The cells
	Tr2InteriorCellPtr m_cellA;
	Tr2InteriorCellPtr m_cellB;

	// Cell portal sockets
	Tr2InteriorPortalSocketPtr m_socketA;
	Tr2InteriorPortalSocketPtr m_socketB;

	// Bounding box
	Vector3 m_minBounds;
	Vector3 m_maxBounds;

	// Name
	std::string m_name;

	// Switch to enable/disable a portal
	bool m_enabled;

	// World transform (assuming cells are always defined in world-space)
	Vector3 m_position;
	Quaternion m_rotation;
	Matrix m_worldTransform;

	// A door for this portal
	ITr2InteriorDynamicPtr m_doorObject;
	// Umbra object for a door in cell A
	Umbra::Object* m_doorInCellA;
	// Umbra object for a door in cell B
	Umbra::Object* m_doorInCellB;
};

TYPEDEF_BLUECLASS( Tr2InteriorPhysicalPortal );
BLUE_DECLARE_VECTOR( Tr2InteriorPhysicalPortal );

#endif