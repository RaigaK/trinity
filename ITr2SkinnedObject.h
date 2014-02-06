#pragma once
#ifndef ITR2SKINNEDOBJECT_H
#define ITR2SKINNEDOBJECT_H

#include "blue/include/Blue.h"

//diable warning-type name first seen using 'class' now seen using 'struct'
#pragma warning(disable:4099)

BLUE_INTERFACE( ITr2SkinnedObject ) : public IRoot
{
    virtual const Vector3 GetScaling() const = 0;
    virtual const Quaternion GetRotation() const = 0;
    virtual const Vector3& GetPosition() const = 0;
};

#endif // TR2SKINNEDOBJECT_H