#ifndef EVESTATION2_H
#define EVESTATION2_H


#include "EveSpaceObject2.h"

BLUE_DECLARE( EveStation2 );

class EveStation2 :
	public EveSpaceObject2
{
public:
	EXPOSE_TO_BLUE();

	EveStation2( IRoot* lockobj = NULL );
	~EveStation2();
};

TYPEDEF_BLUECLASS( EveStation2 );

#endif
