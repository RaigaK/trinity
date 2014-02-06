////////////////////////////////////////////////////////////
//
//    Created:   January 2014
//    Copyright: CCP 2014
//
#pragma once
#ifndef EveMetaballItem_H
#define EveMetaballItem_H

// --------------------------------------------------------------------------------
// Description:
//   This class is for rendering metaballs (aka isosurfaces)
// --------------------------------------------------------------------------------
BLUE_CLASS( EveMetaballItem ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();

	EveMetaballItem(IRoot* lockobj = NULL);
	~EveMetaballItem();

	// access to this field
	float GetNormalizedDistanceTo( const Vector3* samplePosition ) const;
	float GetSmoothness( const Vector3* samplePosition ) const;

	// add this to a bounding box
	void AddToBoundingBox( Vector3& min, Vector3& max ) const;
	
private:
	// center
	Vector3 m_position;
	// radius
	float m_radius;
	
	float m_strength;
};

TYPEDEF_BLUECLASS( EveMetaballItem );
BLUE_DECLARE_VECTOR( EveMetaballItem );

#endif