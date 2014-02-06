/* 
	*************************************************************************************

	EveSOModelCenterPos.h

	Created:   November 2007
	OS:        Win32
	Project:   Trinity

	Description:   

		I apologise profusely for the existence of this class, but it's the fastest way to
		fix the camera issues with EveSpaceObjects until we revisit the camera.

	(c) CCP 2007

	*************************************************************************************
*/
#ifndef _EVESPACEOBJECTMODELCENTERPOSITION_H_
#define _EVESPACEOBJECTMODELCENTERPOSITION_H_

#include "include/ITriFunction.h"
#include "EveSpaceObject.h"
#include <blue/include/IBluePython.h>
#include <blue/include/IBlueOS.h>
#include <blue/include/BlueListUtil.h>
#include "include/TriVector.h"

class EveSOModelCenterPos:
	public ITriVectorFunction
{
public:
	EXPOSE_TO_BLUE();

	EveSOModelCenterPos(IRoot* lockobj = NULL);
	~EveSOModelCenterPos();
	
	void UpdateValue( double time ) { Vector3 v; Update( &v, time ); }

	/////////////////////////////////////////////////////////////////////////////////////
	// ITriVectorFunction
	/////////////////////////////////////////////////////////////////////////////////////

	Vector3* BLUEAPI Update( Vector3* in, Be::Time time	);
	Vector3* BLUEAPI Update( Vector3* in, double time );
	Vector3* BLUEAPI GetValueAt( Vector3* in, Be::Time time	);
	Vector3* BLUEAPI GetValueAt( Vector3* in, double time );
	Vector3* BLUEAPI GetValueDotAt( Vector3* in, Be::Time time );
	Vector3* BLUEAPI GetValueDotAt(	Vector3* in, double time );
	Vector3* BLUEAPI GetValueDoubleDotAt( Vector3* in, Be::Time time );
	Vector3* BLUEAPI GetValueDoubleDotAt( Vector3* in, double time );
	Vector3d* BLUEAPI InterpolatedPosition(Vector3d* out, Be::Time time);

protected:
	std::wstring  mName;
	BlueSimplePtr<EveSpaceObject, &EveSpaceObjectType> m_parentObject;
	PTriVector mValue;
};

TYPEDEF_BLUECLASS(EveSOModelCenterPos);

#endif 