#pragma once

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "../Resources.h"

#include <string>

#ifdef DLL_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

namespace RFCore
{
    class DLL_API Logger
    {
    public:
	    enum LogType { FATAL_TYPE, WARNING_TYPE, NOTICE_TYPE, DEBUG_TYPE };					

	    static Logger * GetLogger();									

	    void Log(char* pFormat, ...);									
	    void Log(LogType type, char* pFormat, ...);

    private:
	    static Logger _instance;

	    Logger();
	    virtual ~Logger();
	    void _Log(LogType type, char* pFormat, va_list pArguments);
    };
}

#endif