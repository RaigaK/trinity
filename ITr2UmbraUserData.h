#pragma once
#ifndef ITr2UmbraUserData_H
#define ITr2UmbraUserData_H

#define CONVERT_TO_UMBRA_USER_DATA( _a ) reinterpret_cast<void*>( _a )
#define CONVERT_FROM_UMBRA_USER_DATA( _a ) reinterpret_cast<IRoot*>( _a )

#endif

