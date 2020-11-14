/*
W0401444 Arthur Bondar
29.03.17 Project 2
EETG Programming I
*/
// stdafx.h : include file for standard system include files,

#pragma once

/* General purpose include */
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


// Error Table
#define INVALID_SELECTION 1
#define ALLOCATION_ERROR 2
#define RECORDS_LIMIT 3
#define INVALID_RECORD_ACCESS 4
#define INVALID_RECORD_RANGE 5


/* Record of person's information */
struct record
{
	int Rec_number;
	char First_Name[15];
	char Last_Name[15];
	int Age;
	char Gender[10];
};
