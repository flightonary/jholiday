// LogManager.h
//
// This file is part of the jholiday project
// Copyright (C) 2013 jetbeaver
//
// This is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License, version 2.1 as published by the Free Software Foundation.
// See the file "COPYING" for the exact licensing terms.

#ifndef LogManager_h
#define LogManager_h

#include "CommonType.h"
#include "CTime.h"
#include <string>

class LogManager
{
public:
    enum LogLevel {Error=0, Warning, Message, Debug};
    typedef std::string LogString;
    
private:
    // Singleton and non-copyable class.
    LogManager(void);
    ~LogManager();
    LogManager(const LogManager&);
    LogManager& operator=(const LogManager&);
    
    static LogManager* logManager;

    CTime cTime;
    LogLevel outputLogLevel;

    void writeLog(LogString logString);
public:
    static void Initialize(LogLevel outputLogLevel);
    static void Logging(LogLevel logLevel, LogString logString);
};

#endif
