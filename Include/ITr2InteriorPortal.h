#pragma once

#ifndef IWodInteriorPortal_H
#define IWodInteriorPortal_H

// Forward declarations
namespace Umbra
{
	class PhysicalPortal;
};
struct ITr2Renderable;

class IWodInteriorPortal
{
public:
	enum PortalType
	{
		PORTALTYPE_PHYSICAL,
		PORTALTYPE_VIRTUAL,
		PORTALTYPE_MIRROR_FRONT,
		PORTALTYPE_MIRROR_BACK
	};

public:
	virtual ~IWodInteriorPortal() { /* Do nothing */ }

	// Get the portal type
	virtual PortalType GetPortalType( const Umbra::PhysicalPortal* portal ) const = 0;
	// Get the renderable hosting the portal
	virtual ITr2Renderable* GetRenderable( void ) = 0;
};

#endif