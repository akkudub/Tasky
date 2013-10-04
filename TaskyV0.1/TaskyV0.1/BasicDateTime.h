#ifndef _BASICDATETIME_H_
#define _BASICDATETIME_H_

#include <iostream>
#include <string>
#include <msclr\marshal_cppstd.h>
#include "Essential.h"

using namespace System;
using namespace msclr::interop;

class BasicDateTime
{
private:
	int _year;
	int _month;
	int _day;
	int _hour;
	int _minute;
	int _sec;

public:	
	///<BasicDateTime>default+3 int(year, month, day)+5 int(year, month, day, hour, minute)+6 int</BasicDateTime>
	///<setDateTime>same as above, maybe optimized later</setDateTime>
	///<getters>year(int), month(int), day(int), hour(int), minute(int), sec(int), dateTimeString(string)</getters>
	///<compareTo> compare which one is ealier</compareTo>
	BasicDateTime();
	BasicDateTime(int, int, int);
	BasicDateTime(int, int, int, int, int);
	BasicDateTime(int, int, int, int, int, int);
	~BasicDateTime();
	void setDateTime(int, int, int);
	void setDateTime(int, int, int, int, int);
	void setDateTime(int, int, int, int, int, int);
	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getMinute();
	int getSec();
	string getDateTimeString();
	int compareTo(BasicDateTime another);
};

#endif
