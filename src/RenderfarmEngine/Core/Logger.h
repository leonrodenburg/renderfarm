#pragma once

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "../Resources.h"

#include <string>

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

namespace RFCore
{
    class DLL_API Logger
    {
    public:
	    enum LogType { FATAL, WARNING, NOTICE, DEBUG };					

	    static Logger * GetLogger();									

	    void Log(char *p_format, ...);									
	    void Log(LogType type, char *p_format, ...);

    private:
	    static Logger _instance;

	    Logger();
	    virtual ~Logger();
	    void Log(LogType type, char *p_format, va_list p_arguments);
    };
}

#endif