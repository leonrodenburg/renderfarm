#include "Logger.h"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdarg.h>

/**
 * Static member initialisation.
 */
RFCore::Logger RFCore::Logger::_instance;

/**
 * Private constructor.
 */
RFCore::Logger::Logger()																
{

}

/**
 * Private destructor.
 */
RFCore::Logger::~Logger()
{

}

/**
 * Return a pointer to the static instance.
 *
 * @return Logger instance
 */
RFCore::Logger* RFCore::Logger::GetLogger()
{
	return &_instance;
}

/**
 * Write a line to the log in the given format, using the
 * DEBUG log type.
 *
 * @param pFormat
 * @param ...
 */
void RFCore::Logger::Log(char* pFormat, ...)
{
	va_list pArguments;
	va_start(pArguments, pFormat);
	this->_Log(DEBUG, pFormat, pArguments);
	va_end(pArguments);
}

/**
 * Write a line to the log using the given type, format
 * and a variable number of arguments.
 *
 * @param type
 * @param pFormat
 * @param ...
 */
void RFCore::Logger::Log(LogType type, char* pFormat, ...)
{
	va_list pArguments;
	va_start(pArguments, pFormat);
	this->_Log(type, pFormat, pArguments);
	va_end(pArguments);
}


/**
 * Write a line to the log using a given type, format and
 * a va_list of arguments.
 *
 * @param type
 * @param pFormat
 * @param pArguments
 */
void RFCore::Logger::_Log(LogType type, char* pFormat, va_list pArguments)									
{
	std::string typeString = "";
	switch(type) 
	{
		case FATAL: typeString = "ERROR"; break;
		case WARNING: typeString = "WARNING"; break;
		case NOTICE: typeString = "NOTICE"; break;
		case DEBUG: typeString = "DEBUG"; break;
		default: typeString = "UNKNOWN"; break;
	}

	std::time_t currentTime;
	std::tm timeInfo;

	time(&currentTime);

	localtime_s(&timeInfo, &currentTime);

	std::stringstream timeString;
	timeString.fill('0');
	timeString  << std::setw(2) << timeInfo.tm_mday << "-" 
				<< std::setw(2) << timeInfo.tm_mon + 1 << "-" 
				<< std::setw(4) << timeInfo.tm_year + 1900 << " " 
				<< std::setw(2) << timeInfo.tm_hour << ":" 
				<< std::setw(2) << timeInfo.tm_min << ":"
				<< std::setw(2) << timeInfo.tm_sec;

	char logMessage[256];

	vsprintf_s(logMessage, pFormat, pArguments);

	std::stringstream outputMessage;
	outputMessage << timeString.str() << " " << typeString << ": " << logMessage << std::endl;

	std::cout << outputMessage.str();
}