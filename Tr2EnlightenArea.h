#pragma once
#ifndef Tr2EnlightenArea_H
#define Tr2EnlightenArea_H


#include "Tr2MeshArea.h"

BLUE_DECLARE( Tr2EnlightenArea );

class Tr2EnlightenArea: 
	public Tr2MeshArea,
	public INotify
{
public:
	Tr2EnlightenArea( IRoot* lockobj = 0 );
	~Tr2EnlightenArea();;

	const Color& GetAlbedoColor() const { return m_albedoColor; }
	const Color& GetEmissiveColor() const { return m_emissiveColor; }
	bool IsEmissive() const { return m_isEmissive; }
	bool IsDirty() { return m_isDirty; }
	void ClearDirtyFlags() { m_isDirty = false; }
	
	// INotify - catch any changes made
	bool OnModified( Be::Var* val ) 
	{
		m_isDirty = true;
		return true; 
	}

private:

	Color m_albedoColor;
	bool  m_isEmissive;
	bool  m_isDirty;	// If the area was emissive, we need to clear that state in enlighten
	Color m_emissiveColor;
public:
	EXPOSE_TO_BLUE();
};

TYPEDEF_BLUECLASS( Tr2EnlightenArea );
BLUE_DECLARE_VECTOR( Tr2EnlightenArea );

#endif