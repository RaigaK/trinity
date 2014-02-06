////////////////////////////////////////////////////////////
//
//    Created:   February 2013
//    Copyright: CCP 2013
//

#include "StdAfx.h"
#include "Tr2GpuBuffer.h"

BLUE_DEFINE_INTERFACE( ITr2GpuBuffer );
BLUE_DEFINE( Tr2GpuBuffer );

const Be::ClassInfo* Tr2GpuBuffer::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2GpuBuffer, "" )

		MAP_INTERFACE( INotify )
		MAP_INTERFACE( IInitialize )
		MAP_INTERFACE( ITr2GpuBuffer )
		MAP_INTERFACE( Tr2GpuBuffer )

		MAP_METHOD_AND_WRAP_OPTIONAL_ARGS(
			"__init__",
			__init__,
			4,
			"Arguments (optional):\n"
			"count - number of elements in the buffer\n"
			"format - buffer pixel format (trinity.PIXEL_FORMAT.foo)\n"
			"cpuWritable - if CPU should have write access to the buffer\n"
			"drawIndirect - if the buffer is used as parameters source for indirect draw calls" )
		MAP_ATTRIBUTE( 
			"count", 
			m_count, 
			"Number of elements in the buffer", 
			Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE_WITH_CHOOSER(
			"format",
			m_format,
			"Buffer pixel format (trinity.PIXEL_FORMAT.foo)",
			Be::READWRITE | Be::ENUM | Be::PERSIST | Be::NOTIFY, 
			Tr2RenderContextEnum_PixelFormat_Chooser )
		MAP_ATTRIBUTE( 
			"cpuWritable", 
			m_cpuWritable, 
			"If CPU should have write access to the buffer", 
			Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_ATTRIBUTE( 
			"drawIndirect", 
			m_drawIndirect, 
			"If the buffer is used as parameters source for indirect draw calls", 
			Be::READWRITE | Be::PERSIST | Be::NOTIFY )
		MAP_PROPERTY_READONLY( 
			"isValid",
			IsValid,
			"Is the underlying GPU object valid" )
	EXPOSURE_END()
}
