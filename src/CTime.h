// CTime.h
//
// This file is part of the jholiday project
// Copyright (C) 2013 jetbeaver
//
// This is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License, version 2.1 as published by the Free Software Foundation.
// See the file "COPYING" for the exact licensing terms.

#ifndef CTime_h
#define CTime_h

#include "CommonType.h"
#include <ctime>

class CTime
{
public:
    enum week {Sunday=0, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};
    
    typedef struct tm CalenderTime;
    typedef time_t    UnixTime;
    typedef size_t    Size;
    
private:
    static const UnixTime ErrorNumber;
    
public:
    UnixTime time(void);
    void localtime(const UnixTime &unixTime, CalenderTime &calTime);
    SuccessFlag mktime(CalenderTime &calTime);
    Size strftime(char* buffer, int bufSize, const char* format, CalenderTime &calTime);
};

#endif
