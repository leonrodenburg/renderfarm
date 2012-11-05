#pragma once

#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#define RF_PLATFORM 2

#define RF_PLATFORM_WIN 1
#define RF_PLATFORM_OSX 2
#define RF_PLATFORM_UNIX 3

#if RF_PLATFORM == RF_PLATFORM_WIN
	#ifdef DLL_IMPORT
		#ifndef DLL_API
			#define DLL_API __declspec(dllimport)
		#endif
	#else
		#ifndef DLL_API
    		#define DLL_API __declspec(dllexport)
    	#endif
    #endif
#else
	#define DLL_API 
#endif

#include "Core/Logger.h"

#endif
