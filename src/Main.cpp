// Main.cpp
//
// This file is part of the jholiday project
// Copyright (C) 2013 jetbeaver
//
// This is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License, version 2.1 as published by the Free Software Foundation.
// See the file "COPYING" for the exact licensing terms.

#include "HolidayChecker.h"
#include <cstdio>

int main(int argc,char *argv[])
{
	HolidayChecker hChecker;
	if (hChecker.todayIsHoliday()) {
		printf("holiday\n");
	}
	else {
		printf("non-holiday\n");
	}
	return 0;
}
