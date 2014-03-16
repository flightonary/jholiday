// LogManager.cpp
//
// This file is part of the jholiday project
// Copyright (C) 2013 jetbeaver
//
// This is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License, version 2.1 as published by the Free Software Foundation.
// See the file "COPYING" for the exact licensing terms.

#include "LogManager.h"
#include <cstdio>

LogManager* LogManager::logManager = 0;

const LogManager::LogString timeFormat = LogManager::LogString("%Y/%m/%d %H:%M:%S.%L%z");
const char*   LogLevelString[] = { "Error", "Warning", "Message", "Debug" };

LogManager::LogManager(void)
{
    this->outputLogLevel = Warning;
}

void LogManager::Initialize(LogLevel outputLogLevel)
{
    if (LogManager::logManager == 0) {
        LogManager::logManager = new LogManager();
    }
    
    logManager->outputLogLevel = outputLogLevel;
}

void LogManager::writeLog(LogString logString)
{
    ::write(stdout->_file, logString.c_str(), logString.size());
}

void LogManager::Logging(LogLevel logLevel, LogString logString)
{
    if (LogManager::logManager == 0) {
        LogManager::logManager = new LogManager();
    }
    
    if (logLevel <= logManager->outputLogLevel) {
        const int bufSize = 100;
        char buffer[bufSize];
        CTime::CalenderTime calTime;
        LogString finalLogStr;
        
        logManager->cTime.localtime(logManager->cTime.time(), calTime);
        logManager->cTime.strftime(buffer, bufSize, timeFormat.c_str(), calTime);
        
        finalLogStr = LogString(buffer) + " <Log." + LogLevelString[logLevel] + "> " + logString + "\n";
        logManager->writeLog(finalLogStr);
    }
}
