// HolidayChecker.h
//
// This file is part of the jholiday project
// Copyright (C) 2013 jetbeaver
//
// This is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License, version 2.1 as published by the Free Software Foundation.
// See the file "COPYING" for the exact licensing terms.

#ifndef HolidayChecker_h
#define HolidayChecker_h

#include "CTime.h"

class HolidayChecker
{
private:
    typedef struct
    {
        int mon;
        int mday;
    } Date;
    
    typedef struct
    {
        int mon;
        int ordinal;
        int wday;
    } VariableDate;
    
    static const HolidayChecker::Date constHolidayList[];
    static const HolidayChecker::VariableDate variableHolidayList[];
    static const UInt CONST_HOLIDAY_NUM;
    static const UInt VARY_HOLIDAY_NUM;

    CTime cTime;
    
    Bool isConstHoliday(const CTime::CalenderTime& calTime);
    Bool isVariableHoliday(const CTime::CalenderTime& calTime);
    Bool isSpringEquinoxDay(const CTime::CalenderTime& calTime);
    Bool isAutumnalEquinoxDay(const CTime::CalenderTime& calTime);
    Bool isTrueHoliday(const CTime::CalenderTime& calTime);
    Bool isArticle3Paragraph2(const CTime::CalenderTime& calTime);
    Bool isArticle3Paragraph3(const CTime::CalenderTime& calTime);
public:
    Bool todayIsHoliday(void);
    Bool isHoliday(time_t unixTime);
};

#endif
