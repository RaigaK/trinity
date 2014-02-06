#include "StdAfx.h"

#include "Tr2InteriorBoundingBox.h"

Tr2InteriorBoundingBox::Tr2InteriorBoundingBox( IRoot* lockobj ):
	m_minBounds( 0.0f, 0.0f, 0.0f ),
	m_maxBounds( 0.0f, 0.0f, 0.0f )
{

}

Tr2InteriorBoundingBox::~Tr2InteriorBoundingBox()
{

}

bool Tr2InteriorBoundingBox::OnModified( Be::Var* value )
{
	//	Inform our parent and rebuild the cell appropriately?
	return true;
}