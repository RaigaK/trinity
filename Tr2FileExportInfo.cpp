#include "StdAfx.h"
#include "Tr2FileExportInfo.h"

Tr2FileExportObject::Tr2FileExportObject( IRoot* lockobj ):
	m_object(NULL),
	m_info(NULL)
{
}

Tr2FileExportInfo::Tr2FileExportInfo( IRoot* lockobj ):
	PARENTLOCK(m_objects)
{
}
