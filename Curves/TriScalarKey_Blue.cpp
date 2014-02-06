#include "StdAfx.h"
#include "TriScalarKey.h"

BLUE_DEFINE( TriScalarKey );
BLUE_DEFINE( TriVectorKey );
BLUE_DEFINE( TriQuaternionKey );
BLUE_DEFINE( TriColorKey );

const Be::ClassInfo* TriScalarKey::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriScalarKey, "no comment")
		MAP_INTERFACE( TriScalarKey )
		MAP_ATTRIBUTE( "time",  mTime,  "na", Be::READWRITE | Be::PERSIST)
		MAP_ATTRIBUTE( "value", mValue, "na", Be::READWRITE | Be::PERSIST)
		MAP_ATTRIBUTE( "left",  mLeft,  "na", Be::READWRITE | Be::PERSIST)
		MAP_ATTRIBUTE( "right", mRight, "na", Be::READWRITE | Be::PERSIST)
		MAP_ATTRIBUTE_WITH_CHOOSER(  "interpolation", mInterpolation, "na", Be::READWRITE | Be::PERSIST | Be::ENUM, TriInterpolation)
	EXPOSURE_END()
}

const Be::ClassInfo* TriVectorKey::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriVectorKey, "no comment")
		MAP_INTERFACE( TriVectorKey )
		MAP_ATTRIBUTE( "time",  mTime,  "na", Be::READWRITE | Be::PERSIST)
		MAP_ATTRIBUTE( "value", mValue, "na", Be::READWRITE | Be::PERSIST)
		MAP_ATTRIBUTE( "left",  mLeft,  "na", Be::READWRITE | Be::PERSIST)
		MAP_ATTRIBUTE( "right", mRight, "na", Be::READWRITE | Be::PERSIST)
		MAP_ATTRIBUTE_WITH_CHOOSER(  "interpolation", mInterpolation, "na", Be::READWRITE | Be::PERSIST | Be::ENUM, TriInterpolation)
	EXPOSURE_END()
}

const Be::ClassInfo* TriQuaternionKey::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriQuaternionKey, "no comment")
		MAP_INTERFACE( TriQuaternionKey )
		MAP_ATTRIBUTE( "time",  mTime,  "na", Be::READWRITE | Be::PERSIST)
		MAP_ATTRIBUTE( "value", mValue, "na", Be::READWRITE | Be::PERSIST)
		MAP_ATTRIBUTE( "left",  mLeft,  "na", Be::READWRITE | Be::PERSIST)
		MAP_ATTRIBUTE( "right", mRight, "na", Be::READWRITE | Be::PERSIST)
		MAP_ATTRIBUTE_WITH_CHOOSER(  "interpolation", mInterpolation, "na", Be::READWRITE | Be::PERSIST | Be::ENUM, TriInterpolation)
	EXPOSURE_END()
}

const Be::ClassInfo* TriColorKey::ExposeToBlue()
{
	EXPOSURE_BEGIN(TriColorKey, "no comment")
		MAP_INTERFACE( TriColorKey )
		MAP_ATTRIBUTE( "time",  mTime,  "na", Be::READWRITE | Be::PERSIST)
		MAP_ATTRIBUTE( "value", mValue, "na", Be::READWRITE | Be::PERSIST)
		MAP_ATTRIBUTE( "left",  mLeft,  "na", Be::READWRITE | Be::PERSIST)
		MAP_ATTRIBUTE( "right", mRight, "na", Be::READWRITE | Be::PERSIST)
		MAP_ATTRIBUTE_WITH_CHOOSER(  "interpolation", mInterpolation, "na", Be::READWRITE | Be::PERSIST | Be::ENUM, TriInterpolation)
	EXPOSURE_END()
}