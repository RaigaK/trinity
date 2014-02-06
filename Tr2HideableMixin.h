#pragma once
#ifndef Tr2HideableMixin_H
#define Tr2HideableMixin_H

// #define ENABLE_HIDEABLE_MIXIN (TRINITYDEV || _DEBUG)

// At some point Dan Speed got this mixed up and enabled the mixin for everything but
// the debug config. Now we have Python code relying on this and until that is fixed
// we've got to enable the mixin for all configs.
#define ENABLE_HIDEABLE_MIXIN 1

#if ENABLE_HIDEABLE_MIXIN
// Use this macro to map the members of this mix-in
#define MAPHIDEABLE() MAP_ATTRIBUTE( "debugIsHidden", m_debugIsHidden, "DEBUG ONLY: Used to omit from rendering", Be::READWRITE )
#else
#define MAPHIDEABLE()
#endif

class Tr2HideableMixin 
{
public:
	bool IsHidden() const
	{
		#if ENABLE_HIDEABLE_MIXIN
			return m_debugIsHidden;
		#else
			return false;
		#endif
	}

	Tr2HideableMixin() : m_debugIsHidden( false )
	{}

protected:
	bool m_debugIsHidden;
};

#endif
