////////////////////////////////////////////////////////////////////////////////
//
// Created:		September 2018
// Copyright:	CCP 2018
//

#pragma once
#ifndef Tr2LodResourceCache_h
#define Tr2LodResourceCache_h

#include "Tr2LodResource.h"

template <typename T>
class Tr2LodResourceCache
{
public:
	Tr2LodResourceCache() :
		m_resourceCache( nullptr )
	{
	};

	~Tr2LodResourceCache() {};

	T* GetResource( Tr2LodResourcePtr resource ) const
	{
		if( resource )
		{
			IBlueResource *data = resource->GetResource();
			if( data != static_cast<void*>( m_resourceCache ) )
			{
				// Not undefined behaviour as long as Tr2LodResourceCache is not created as a const object
				const_cast<Tr2LodResourceCache*>( this )->m_resourceCache = dynamic_cast<T*>( data );
			}

			return m_resourceCache;
		}

		return nullptr;
	}
private:
	T* m_resourceCache;
};

#endif