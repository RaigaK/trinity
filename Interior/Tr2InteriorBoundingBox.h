#pragma once
#ifndef Tr2InteriorBoundingBox_H
#define Tr2InteriorBoundingBox_H

BLUE_DECLARE( Tr2InteriorBoundingBox );

class Tr2InteriorBoundingBox :
	public INotify
{
public:
	Tr2InteriorBoundingBox( IRoot* lockobj = 0 ) ;
	~Tr2InteriorBoundingBox();


	EXPOSE_TO_BLUE();

	/////////////////////////////////////////////////////////////////////////////////////
	// INotify
	virtual bool OnModified( Be::Var* value );

public:
	//	Our bounding box minimum
	Vector3	m_minBounds;

	//	Our bounding box maximum
	Vector3 m_maxBounds;
};

TYPEDEF_BLUECLASS( Tr2InteriorBoundingBox );
BLUE_DECLARE_VECTOR( Tr2InteriorBoundingBox );

#endif

