#include "BasicDateTime.h"

BasicDateTime::BasicDateTime()
{
}

BasicDateTime::BasicDateTime(int year, int month, int day, int hour, int minute)
{
	_year = year;
	_month = month;
	_day = day;
	_hour = hour;
	_minute = minute;
}

BasicDateTime::~BasicDateTime(){
}

void BasicDateTime::setDateTime(int year, int month, int day, int hour, int minute)
{
	_year = year;
	_month = month;
	_day = day;
	_hour = hour;
	_minute = minute;
}

int BasicDateTime::getYear(){ 
	return _year;
}

int BasicDateTime::getMonth(){ 
	return _month;
}

int BasicDateTime::getDay(){
	return _day;
}
int BasicDateTime::getHour(){ 
	return _hour;
}

int BasicDateTime::getMinute(){
	return _minute;
}

int BasicDateTime::getSec(){
	return _sec;
}

string BasicDateTime::getDateTime(){
	DateTime temp = DateTime(_year, _month, _day,  _hour, _minute, _sec);
	return marshal_as<std::string>(temp.ToString()); 
}

int BasicDateTime::compareTo(BasicDateTime another){
	DateTime temp = DateTime(another.getYear(),	another.getMonth(),	another.getDay(),
							another.getHour(), another.getMinute(),another.getSec());
	DateTime thisDateTime = DateTime( _year, _month, _day, _hour, _minute, _sec);
	return thisDateTime.CompareTo(temp);
}