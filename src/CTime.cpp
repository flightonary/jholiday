// CTime.cpp
//
// This file is part of the jholiday project
// Copyright (C) 2013 jetbeaver
//
// This is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License, version 2.1 as published by the Free Software Foundation.
// See the file "COPYING" for the exact licensing terms.

#include "CTime.h"

const CTime::UnixTime CTime::ErrorNumber = -1;

CTime::UnixTime CTime::time(void)
{
    return ::time((UnixTime*)NULL);
}

void CTime::localtime(const UnixTime &unixTime, CalenderTime &calTime)
{
    ::localtime_r(&unixTime, &calTime);
}

SuccessFlag CTime::mktime(CalenderTime &calTime)
{
    if (::mktime(&calTime) == CTime::ErrorNumber) {
        return false;
    }
    return true;
}

CTime::Size CTime::strftime(char* buffer, int bufSize, const char* format, CalenderTime &calTime)
{
    return ::strftime(buffer, bufSize, format, &calTime);
}
