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
public:
	BasicDateTime();
	BasicDateTime(int year, int month, int _day, int _hour, int _minute);
	~BasicDateTime();
	void setDateTime(int year, int month, int _day, int _hour, int _minute);
	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getMinute();
	int getSec();
	string getDateTime();
	int compareTo(BasicDateTime another);

private:
	int _year;
	int _month;
	int _day;
	int _hour;
	int _minute;
	int _sec;
};

#endif
