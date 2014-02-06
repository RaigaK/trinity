#pragma once
#ifndef Tr2FileExportInfo_h
#define Tr2FileExportInfo_h

BLUE_CLASS( Tr2FileExportObject ):
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	IRootPtr	m_object;
	IRootPtr	m_info;
	Tr2FileExportObject( IRoot* lockobj = NULL );
};
BLUE_DECLARE_VECTOR( Tr2FileExportObject );

TYPEDEF_BLUECLASS( Tr2FileExportObject );

BLUE_CLASS( Tr2FileExportInfo ):
     public IRoot
{
public:
    EXPOSE_TO_BLUE();
	std::string						m_tool;
	std::string						m_version;
	PTr2FileExportObjectVector		m_objects;
    Tr2FileExportInfo( IRoot* lockobj = NULL );
};

TYPEDEF_BLUECLASS( Tr2FileExportInfo );
TYPEDEF_BLUECLASS( Tr2FileExportObject );
#endif //Tr2FileExportInfo_h
