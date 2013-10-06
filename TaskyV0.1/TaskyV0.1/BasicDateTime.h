#ifndef _BASICDATETIME_H_
#define _BASICDATETIME_H_

#include <iostream>
#include <string>
#include <msclr\marshal_cppstd.h>
#include "Essential.h"

using namespace System;
using namespace msclr::interop;

///wrap date and time into a simple class

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
	///default constructor
	BasicDateTime();
	///year, month, day
	BasicDateTime(int year, int month, int day);
	///year, month, day, hour, minute
	BasicDateTime(int year, int month, int day, int hour, int minute);
	///year, month, day, hour, minute, sec
	BasicDateTime(int, int, int, int, int, int);
	///destructor
	~BasicDateTime();
	///<summary>void; year, month, day</summary>
	void setDateTime(int year, int month, int day);
	///<summary>void; year, month, day, hour, minute</summary>
	void setDateTime(int year, int month, int day, int hour, int minute);
	///<summary>void; year, month, day, hour, minute, sec</summary>
	void setDateTime(int year, int month, int day, int hour, int minute, int sec);
	///<summary>int; void</summary>
	int getYear();
	///<summary>int; void</summary>
	int getMonth();
	///<summary>int; void</summary>
	int getDay();
	///<summary>int; void</summary>
	int getHour();
	///<summary>int; void</summary>
	int getMinute();
	///<summary>int; void</summary>
	int getSec();
	///<summary>String; void</summary>
	string getDateTimeString();
	///<summary>int; BasicDateTime</summary>
	int compareTo(BasicDateTime another);
};

#endif
