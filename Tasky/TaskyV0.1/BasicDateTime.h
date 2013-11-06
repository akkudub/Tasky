#ifndef BASICDATETIME_H
#define BASICDATETIME_H

#include <iostream>
#include <string>
#include "Essential.h"

/**
* Tasky's version of storing date and time 
* 1. able to set based on date, month, year ,  hour , min , sec
* 2. able to compare to another BasicDateTime object based on contained DateTime object
* 3. format the date and time to be inclusive of 0s
*/

class BasicDateTime
{
private:
	int _year;
	int _month;
	int _day;
	int _hour;
	int _minute;
	int _sec;

private:
	static const string DASH;
	static const string SPACE;
	static const string COLON;
	static const string ZERO_STRING;
	static const int ZERO=0;

public:	
	/**
	* default constructor 
	*/
	BasicDateTime();
	/**
	* year, month, day
	*/
	BasicDateTime(int year, int month, int day);
	/**
	* year, month, day, hour, minute
	*/
	BasicDateTime(int year, int month, int day, int hour, int minute);
	/**
	* year, month, day, hour, minute, sec
	*/
	BasicDateTime(int, int, int, int, int, int);
	/** 
	* destructor
	*/
	~BasicDateTime();
	/**
	* setter 1 : year, month , day
	*/
	void setDateTime(int year, int month, int day);
	/**
	* setter 2 : year, month, day, hour, minute
	*/
	void setDateTime(int year, int month, int day, int hour, int minute);
	/**
	* setter 3 : year, month, day, hour, minute, sec
	*/
	void setDateTime(int year, int month, int day, int hour, int minute, int sec);
	int getYear();
	void setYear(int year);
	int getMonth();
	void setMonth(int month);
	int getDay();
	void setDay(int day);
	int getHour();
	void setHour(int hour);
	int getMinute();
	void setMinute(int minute);
	int getSec();
	void setSec(int sec);
	/**
	* Purpose : translate the datetime into string
	* @return date and time in a string
	*/
	string getDateTimeString();
	/*
	* Purpose :
	* compare to another BasicDateTime object based on internal DateTime object comparison
	* @param another BasicDateTime Object to be compared to
	* @return value of comparision(compareTo)
	*/
	int compareTo(BasicDateTime another);

private:
	string addZeroFromFront(string str);
};

#endif
