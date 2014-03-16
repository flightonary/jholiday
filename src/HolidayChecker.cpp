// HolidayChecker.cpp
//
// This file is part of the jholiday project
// Copyright (C) 2013 jetbeaver
//
// This is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License, version 2.1 as published by the Free Software Foundation.
// See the file "COPYING" for the exact licensing terms.

#include "HolidayChecker.h"
#include "LogManager.h"

const UInt HolidayChecker::CONST_HOLIDAY_NUM = 9;
const UInt HolidayChecker::VARY_HOLIDAY_NUM  = 4;

const HolidayChecker::Date HolidayChecker::constHolidayList[CONST_HOLIDAY_NUM] =
{
    { 1,  1},  // 元日
    { 2, 11},  // 建国記念の日
    { 4, 29},  // 昭和の日
    { 5,  3},  // 憲法記念日
    { 5,  4},  // みどりの日
    { 5,  5},  // こどもの日
    {11,  3},  // 文化の日
    {11, 23},  // 勤労感謝の日
    {12, 23}   // 天皇誕生日
};

const HolidayChecker::VariableDate HolidayChecker::variableHolidayList[VARY_HOLIDAY_NUM] =
{
    { 1, 2, CTime::Monday},   // 成人の日
    { 7, 3, CTime::Monday},   // 海の日
    { 9, 3, CTime::Monday},   // 敬老の日
    {10, 2, CTime::Monday}    // 体育の日
};

Bool HolidayChecker::isConstHoliday(const CTime::CalenderTime& calTime)
{
    for ( int i = 0; i < CONST_HOLIDAY_NUM; i++ ) {
        if ( calTime.tm_mon + 1 == constHolidayList[i].mon && calTime.tm_mday == constHolidayList[i].mday ) {
            return true;
        }
    }
    return false;
}

Bool HolidayChecker::isVariableHoliday(const CTime::CalenderTime& calTime)
{
    for ( int i = 0; i < VARY_HOLIDAY_NUM; i++ ) {
        if ( calTime.tm_mon + 1 == variableHolidayList[i].mon && calTime.tm_wday == variableHolidayList[i].wday ) {
            int ordinal = (calTime.tm_mday - 1) / 7 + 1;
            if ( ordinal == variableHolidayList[i].ordinal ) {
                return true;
            }
        }
    }
    return false;
}

Bool HolidayChecker::isSpringEquinoxDay(const CTime::CalenderTime& calTime)
{
    int day = 0;
    // 1992-2023
    if( 92 <= calTime.tm_year && calTime.tm_year <= 123 ) {
        if( ((calTime.tm_year+1900) % 4) == 2 || ((calTime.tm_year+1900) % 4) == 3 ) {
            day = 21;
        }
        else {
            day = 20;
        }
    }
    // 2024-2055
    else if( 124 <= calTime.tm_year && calTime.tm_year <= 155 ) {
        if( ((calTime.tm_year+1900) % 4) == 3 ) {
            day = 21;
        }
        else {
            day = 20;
        }
    }
    
    if( calTime.tm_mon + 1 == 3 && calTime.tm_mday == day ) {
        return true;
    }
    
    return false;
}

Bool HolidayChecker::isAutumnalEquinoxDay(const CTime::CalenderTime& calTime)
{
    int day = 0;
    
    // 1980-2011
    if( 80 <= calTime.tm_year && calTime.tm_year <= 111 ) {
        day = 23;
    }
    // 2012-2043
    else if( 112 <= calTime.tm_year && calTime.tm_year <= 143 ) {
        if( ((calTime.tm_year+1900) % 4) == 0 ) {
            day = 22;
        }
        else {
            day = 23;
        }
    }
    // 2044-2075
    else if( 144 <= calTime.tm_year && calTime.tm_year <= 175 ) {
        if( ((calTime.tm_year+1900) % 4) == 0 || ((calTime.tm_year+1900) % 4) == 1 ) {
            day = 22;
        }
        else {
            day = 23;
        }
    }
    
    if( calTime.tm_mon + 1 == 9 && calTime.tm_mday == day ) {
        return true;
    }
    return false;
}

Bool HolidayChecker::isTrueHoliday(const CTime::CalenderTime& calTime)
{
    if( isConstHoliday(calTime) ||
        isVariableHoliday(calTime) ||
        isSpringEquinoxDay(calTime) ||
        isAutumnalEquinoxDay(calTime) ) {
        return true;
    }
    return false;
}

// 国民の祝日に関する法律
// 第三条 第２項
// 「国民の祝日」が日曜日に当たるときは、その日後において
// その日に最も近い「国民の祝日」でない日を休日とする。
Bool HolidayChecker::isArticle3Paragraph2(const CTime::CalenderTime& calTime)
{
    CTime::CalenderTime yestCalTime = calTime;
    
    yestCalTime.tm_mday--;
    
    SuccessFlag sucFlag = false;
    sucFlag |= cTime.mktime(yestCalTime);
    
    if ( !sucFlag ) {
        LogManager::Logging(LogManager::Debug, "Error in mktime()");
        return false;
    }
    
    if ( isTrueHoliday(yestCalTime) ) {
        if( yestCalTime.tm_wday == CTime::Sunday ) {
            return true;
        }
        else if( isArticle3Paragraph2(yestCalTime) ) {
            return true;
        }
    }
    
    return false;
}

// 第三条 第３項
// その前日及び翌日が「国民の祝日」である日（「国民の祝日」
// でない日に限る。）は、休日とする。
Bool HolidayChecker::isArticle3Paragraph3(const CTime::CalenderTime& calTime)
{
    CTime::CalenderTime yestCalTime = calTime;
    CTime::CalenderTime tomoCalTime = calTime;
    
    yestCalTime.tm_mday--;
    tomoCalTime.tm_mday++;
    
    SuccessFlag sucFlag = false;
    sucFlag |= cTime.mktime(yestCalTime);
    sucFlag |= cTime.mktime(tomoCalTime);
    
    if (!sucFlag) {
        LogManager::Logging(LogManager::Debug, "Error in mktime()");
        return false;
    }
    
    if( isTrueHoliday(yestCalTime) && isTrueHoliday(tomoCalTime) ) {
        return true;
    }
    
    return false;
}

Bool HolidayChecker::todayIsHoliday(void)
{
    return isHoliday(cTime.time());
}

Bool HolidayChecker::isHoliday(time_t unixTime)
{
    CTime::CalenderTime calTime;
    
    cTime.localtime(unixTime, calTime);
    
    if( isTrueHoliday(calTime) ||
       isArticle3Paragraph2(calTime) ||
       isArticle3Paragraph3(calTime) ) {
        return true;
    }
    return false;
}
