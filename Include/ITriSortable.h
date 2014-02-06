#pragma once
#ifndef ITRISORTABLE_H
#define ITRISORTABLE_H

#include <blue/include/Blue.h>

BLUE_INTERFACE( ITriSortable ) : public IRoot
{
	virtual float GetSortValue() = 0;
};
#endif