#include "Interpreter.h"
#include <assert.h>
#include <algorithm>

const string Interpreter::EMPTY_STRING = "";
const string Interpreter::FROM_KEY_WORD = "from ";
const string Interpreter::TO_KEY_WORD = "to ";
const string Interpreter::BY_KEY_WORD = "by ";
const string Interpreter::DASH_M = "-m";
const string Interpreter::PENDING_KEY_WORD = "pending";
const string Interpreter::DONE_KEY_WORD = "done";
const string Interpreter::RENAME_KEY_WORD = "' to '";
const string Interpreter::ALL_KEY_WORD = "all";
const string Interpreter::TODAY_KEY_WORD = "today";
const string Interpreter::TOMORROW_KEY_WORD = "tomorrow";
const string Interpreter::THIS_KEY_WORD = "this";
const string Interpreter::NEXT_KEY_WORD = "next";
const string Interpreter::MON_KEY_WORD = "mon";
const string Interpreter::MON_FULL_KEY_WORD = "monday";
const string Interpreter::TUE_KEY_WORD = "tue";
const string Interpreter::TUE_FULL_KEY_WORD = "tuesday";
const string Interpreter::WED_KEY_WORD = "wed";
const string Interpreter::WED_FULL_KEY_WORD = "wednesday";
const string Interpreter::THU_KEY_WORD = "thu";
const string Interpreter::THU_FULL_KEY_WORD = "thursday";
const string Interpreter::FRI_KEY_WORD = "fri";
const string Interpreter::FRI_FULL_KEY_WORD = "friday";
const string Interpreter::SAT_KEY_WORD = "sat";
const string Interpreter::SAT_FULL_KEY_WORD = "saturday";
const string Interpreter::SUN_KEY_WORD = "sun";
const string Interpreter::SUN_FULL_KEY_WORD = "sunday";

const char Interpreter::SLASH = '/';
const char Interpreter::DOT = '.';
const char Interpreter::COMMA = ',';
const char Interpreter::SINGLE_QUOTE = '\'';
const char Interpreter::SPACE = ' ';
const char Interpreter::DASH = '-';
const char Interpreter::COLON = ':';
const char Interpreter::ZERO = '0';
const char Interpreter::NINE = '9';

Interpreter::Interpreter(){
}

int Interpreter::interpretAdd(string str, string& title, int& type, BasicDateTime& start, BasicDateTime& end, string& comment){
	int posDashM=str.size(), posQuote1=0, posQuote2=0;
	bool fromToFlag=false, byFlag=false;

	if (!extractComment(str, comment, posDashM)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_ADD;
	}
	if (!extractTitle(str, title, posQuote1, posQuote2)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_ADD;
	}
	if (!firstCheckForFromToOrBy(str.substr(posQuote2+1, posDashM-posQuote2-1), fromToFlag, byFlag)){
		type = NO_DATETIME;
		return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_ADD;
	}
	if (!judgeFromToOrBy(fromToFlag, byFlag, type, start, end)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_ADD;
	}
	return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_ADD;
}

int Interpreter::interpretSearch(string str, vector<string>& keywords, int& type, BasicDateTime& start, BasicDateTime& end){
	str=removeLeadingSpaces(str);
	int size=str.size(), pos1, pos2;
	bool fromToFlag=false, byFlag=false;
	string title;
	keywords.clear();
	if (!extractTitle(str, title, pos1, pos2)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_SEARCH;
	}
	keywords=extractKeywords(title);
	if (!firstCheckForFromToOrBy(str.substr(), fromToFlag, byFlag)){
		type = NO_DATETIME;
		return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH;
	}
	if (!judgeFromToOrBy(fromToFlag, byFlag, type, start, end)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_SEARCH;
	}
	return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH;
}

int Interpreter::interpretPowerSearch(string str, bool& slotEnabled, vector<string>& keywords, int& searchingStatus, int& type, BasicDateTime& start, BasicDateTime& end){
	str=removeLeadingSpaces(str);
	int size=str.size(), pos1, pos2;
	bool fromToFlag=false, byFlag=false, slotFlag=false, keywordFlag=false, statusFlag=false, timeFlag=false;
	string title;
	keywords.clear();

	if (!extractTitle(str, title, pos1, pos2)){
		keywordFlag=false;
	}else{
		keywordFlag=true;
		keywords=extractKeywords(title);
	}

	if (!firstCheckForFromToOrBy(str.substr(), fromToFlag, byFlag)){
		timeFlag=false;
		type = NO_DATETIME;
		return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH;
	}
	if (!judgeFromToOrBy(fromToFlag, byFlag, type, start, end)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_SEARCH;
	}

	return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH;
}

int Interpreter::interpretDisplay(string str, int& type, BasicDateTime& start, BasicDateTime& end, bool& status){
	str=removeLeadingSpaces(str);
	bool statusFlag=false, fromToFlag=false, byFlag=false;
	int pos=0, size=str.size();
	if (str.find(ALL_KEY_WORD)!=std::string::npos){
		type=NO_DATETIME;
		return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_DISPLAY;
	}else{
		if (str.find(PENDING_KEY_WORD)!=std::string::npos){
			statusFlag=true;
			status=false;
			pos=str.find(PENDING_KEY_WORD);
		}else if(str.find(DONE_KEY_WORD)!=std::string::npos){
			statusFlag=true;
			status=true;
			pos=str.find(DONE_KEY_WORD);
		}
		if (pos>=size-1){
			return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_DISPLAY;
		}else{
			if (!firstCheckForFromToOrBy(str, fromToFlag, byFlag)){
		        type = NO_DATETIME;
		        return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_ADD;
	        }
	        if (!judgeFromToOrBy(fromToFlag, byFlag, type, start, end)){
		        return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_ADD;
	        }
		}
	}
	if (statusFlag){
		type=TWO_DATETIME;
	}else{
		type=TWO_DATETIME_WITH_STATUS_FOR_DISPLAY;
	}
	return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_DISPLAY;
}

int Interpreter::interpretRename(string str, string& oldTitle, string& newTitle){
	str=removeLeadingSpaces(str);
	int posQuote1=0, posKey=0, posQuote2=0;
	posKey=str.find(RENAME_KEY_WORD);
	posQuote1=str.find_first_of(SINGLE_QUOTE);
	posQuote2=str.find_last_of(SINGLE_QUOTE);
	if (posKey==INTERNAL_ERROR_CODE){
        return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_RENAME;
	}
	if (posQuote2-posQuote1<=5){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_RENAME;
	}else{
		oldTitle=str.substr(posQuote1+1,posKey-posQuote1-1);
		newTitle=str.substr(posKey+6, posQuote2-posKey-6);
	}
	return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_RENAME;
}

int Interpreter::interpretReschedule(string str, string& title, int& type, BasicDateTime& start, BasicDateTime& end){
	str=removeLeadingSpaces(str);
	int posQuote1=0, posQuote2=0;
	bool fromToFlag=false, byFlag=false;
	if (!extractTitle(str, title, posQuote1, posQuote2)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_RESCHEDULE;
	}
	if (!firstCheckForFromToOrBy(str.substr(posQuote2+1), fromToFlag, byFlag)){
		type=NO_DATETIME;
		return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_RESCHEDULE;
	}
	if (!judgeFromToOrBy(fromToFlag, byFlag, type, start, end)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_RESCHEDULE;
	}
	return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_RESCHEDULE;
}

int Interpreter::interpretMark(string str, string& title, bool& status){
	str=removeLeadingSpaces(str);
	int posQuote1=0, posQuote2=0;
	if (!extractTitle(str, title, posQuote1, posQuote2)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_MARK;
	}
	if (str.size()==posQuote2+1){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_MARK;
	}
	if (str.find(DONE_KEY_WORD, posQuote2+1)!=std::string::npos){
		status=true;
	}else if(str.find(PENDING_KEY_WORD, posQuote2+1)!=std::string::npos){
		status=false;
	}else{
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_MARK;
	}
	return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_MARK;
}

int Interpreter::interpretRemove(string str, string& title){
	str=removeLeadingSpaces(str);
	int num1, num2;
	if (!extractTitle(str, title, num1, num2)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_REMOVE;
	}
	return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_REMOVE;
}

int Interpreter::stringToInt(string str){
	str=removeLeadingSpaces(str);
	int num=0;
	int size=str.size();
	for (int i=0;i<size;i++){
		if (str[i]>=ZERO && str[i]<=NINE){
			num=num*RADIX_TEN+str[i]-ZERO;
		}else{
			return STRING_TO_INT_ERROR;
		}
	}
	return num;
}

vector<int> Interpreter::stringToIntVec(string str){
	str=removeLeadingSpaces(str);
	vector<int> vec;
	vector<string> vecStr;
	if (containChar(str, COMMA)){
		vecStr=breakStringWithDelim(str, COMMA);
		vec=pushNumsWithComma(vecStr);
	}else if(containChar(str, DASH)){
		vecStr=breakStringWithDelim(str, DASH);
		vec=pushNumsWithDash(vecStr);
	}else{
		int temp=stringToInt(str);
		if (temp!=-1){
			vec.push_back(temp);
		}
	}
	return vec;
}

string Interpreter::toLowerCase(string str){
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

int Interpreter::stringToBasicDateTime(string input, BasicDateTime& time){
	input=removeLeadingSpaces(input);
	vector<string> vec=breakStringWithDelim(input, SPACE);
	bool flag=false;
	if (vec.size()!=2){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_STRINGTODATETIME;
	}else{
		flag=translateDateTime(vec.at(0), vec.at(1), 2);
	}
	if (!flag){
        return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_STRINGTODATETIME;
	}else{
		time=_end;
	}
	return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_STRINGTODATETIME;
}

bool Interpreter::extractTitle(const string& str, string& title, int& pos1, int& pos2){
	if (str.find_first_of(SINGLE_QUOTE)!=std::string::npos){
		pos1=str.find_first_of(SINGLE_QUOTE);
		pos2=str.find_last_of(SINGLE_QUOTE);
	}else{
		return false;
	}
	if (pos1 != pos2){
		title=str.substr(pos1+1, pos2-pos1-1);
	}else{
		return false;
	}
	return true;
}

bool Interpreter::extractComment(const string& str, string& comment, int& pos){
	if (str.find(DASH_M)!=std::string::npos){
		pos=findLastOfWord(str, DASH_M);
		comment=str.substr(pos);
	}else{
		comment=EMPTY_STRING;
	}
	return true;
}

bool Interpreter::extractFirstWord(const string& str, string& firstWord){
	return false;
}

vector<string> Interpreter::extractKeywords(const string& str){
	vector<string> keywords;
	vector<string> temp=breakStringWithDelim(str, SPACE);
	keywords.push_back(str);
	keywords.insert(keywords.end(),temp.begin(), temp.end());
	return keywords;
}

bool Interpreter::firstCheckForFromToOrBy(const string& str, bool& fromToFlag, bool& byFlag){
	if (str.find(FROM_KEY_WORD)!=std::string::npos){
		fromToFlag=fromToCheck(str);
		return true;
	}else if(str.find(BY_KEY_WORD)!=std::string::npos){
		byFlag=byCheck(str);
		return true;
	}else{
		return false;
	}
}

bool Interpreter::judgeFromToOrBy(bool fromToFlag, bool byFlag, int& type, BasicDateTime& start, BasicDateTime& end){
	assert(!(fromToFlag&&byFlag));
	if (fromToFlag){
        start=_start;
		end=_end;
		type=TWO_DATETIME;
		return true;
	}else if(byFlag){
		start=_start;
		end=_end;
		type=ONE_DATETIME;
		return true;
	}else{
		return false;
	}
}

bool Interpreter::fromToCheck(string str){
	bool fromFlag=false, toFlag=false;
	int pos1=0, pos2=0;
	string tempStr;
	vector<string> vec;
	pos1=str.find(FROM_KEY_WORD);
	pos2=str.find(TO_KEY_WORD);
	tempStr=str.substr(pos1+4, pos2-pos1-4);
	vec=breakStringWithDelim(tempStr, SPACE);
	if (vec.size()==1){
		fromFlag=translateDateTime(vec.at(0), EMPTY_STRING, 1);
	}else if (vec.size()==2){
		fromFlag=translateDateTime(vec.at(0), vec.at(1), 1) || translateNaturalDate(vec.at(0), vec.at(1), 1);
	}else if (vec.size()==3){
		fromFlag=translateNaturalDateTime(vec.at(0), vec.at(1), vec.at(2), 1);
    }else{
		return false;
	}
	tempStr=str.substr(pos2+3);
	vec=breakStringWithDelim(tempStr, SPACE);
	if (vec.size()==1){
		toFlag=translateDateTime(vec.at(0), EMPTY_STRING, 2);
	}else if (vec.size()==2){
		toFlag=translateDateTime(vec.at(0), vec.at(1), 2) || translateNaturalDate(vec.at(0), vec.at(1), 2);
	}else if(vec.size()==3){
		toFlag=translateNaturalDateTime(vec.at(0), vec.at(1), vec.at(2), 2);
    }else{
		return false;
	}
	if (fromFlag&&toFlag){
		return (_start.compareTo(_end)<0);
	}else{
		return false;
	}
}

bool Interpreter::byCheck(string str){
	bool byFlag=false;
	string tempStr;
	vector<string> vec;
	tempStr=str.substr(3);
	vec=breakStringWithDelim(tempStr, SPACE);
	if (vec.size()==1){
		byFlag=translateDateTime(vec.at(0), EMPTY_STRING, 2);
	}else if (vec.size()==2){
		byFlag=translateDateTime(vec.at(0), vec.at(1), 2) || translateNaturalDate(vec.at(0), vec.at(1), 2);
	}else if (vec.size()==3){
		byFlag=translateNaturalDateTime(vec.at(0), vec.at(1), vec.at(2), 2);
    }else{
		return false;
	}
	if (byFlag){
		DateTime dt=DateTime::Now;
		_start=BasicDateTime(dt.Year, dt.Month, dt.Day, dt.Hour, dt.Minute, dt.Second);
		return (_start.compareTo(_end)<0);
	}else{
		return false;
	}
}

bool Interpreter::translateDateTime(string str1, string str2, int either){
	bool dateFlag=false, timeFlag=false;
	if(str2!=EMPTY_STRING){
		dateFlag=interpretDate(str1, either);
		timeFlag=interpretTime(str2, either);
	}else if(str1!=EMPTY_STRING){
		dateFlag=interpretDate(str1, either);
		timeFlag=true;
		setTimeParams(HOUR_LOWER_BOUND, MINUTE_LOWER_BOUND, SECOND_LOWER_BOUND, either);
	}else{
		return false;  //if reach here, a bug found
	}
	return dateFlag&&timeFlag;
}

bool Interpreter::translateNaturalDateTime(string str1, string str2, string str3, int either){
	return translateNaturalDate(str1, str2, either) && interpretTime(str3, either);
}

bool Interpreter::translateOnlyDate(string str1, int either){
	return interpretDate(str1, either);
}

bool Interpreter::translateNaturalDate(string str1, string str2, int either){
	int todayOfWeek=mapTodayDayOfWeek(), thatOfWeek=mapDayOfWeekToInt(str2);
	if (thatOfWeek==INTERNAL_ERROR_CODE){
		return false;
	}
	if (str1 == THIS_KEY_WORD){
		return dateThisOrNextDateFormat(thatOfWeek-todayOfWeek, 0, either);
	}else if (str1 == NEXT_KEY_WORD){
		return dateThisOrNextDateFormat(thatOfWeek-todayOfWeek, 1, either);
	}else{
		return false;  //possibly a bug or wrong input from the user
	}
}

bool Interpreter::interpretDate(string str1, int either){
	return dateStandardInput(str1, either) || dateTodayOrTomorrow(str1, either);
}

bool Interpreter::interpretTime(string str1, int either){
	return timeStandardInput(str1, DOT, either)||timeSpecialNumsOnly(str1, either)||timeStandardInput(str1, COLON, either);
}

bool Interpreter::dateStandardInput(string str, int either){
	vector<string> vec=breakStringWithDelim(str, SLASH);
	bool dateFlag=false;
	int year=0, month=0, day=0;
	int size=vec.size();
	if (size<=1 || size>=4){
		return false;
	}else if(size==3){
		year=stringToInt(vec.at(2));
		month=stringToInt(vec.at(1));
		day=stringToInt(vec.at(0));
		if (year>=0&&year<=99){
			year=year+2000;
		}
		dateFlag=validateDate(year, month, day);
	}else if(size==2){
		month=stringToInt(vec.at(1));
		day=stringToInt(vec.at(0));
		year=DateTime::Now.Year;
		dateFlag=validateDate(year, month, day);
	}
	if (dateFlag){
		setDateParams(year, month, day, either);
	    return true;
	}else{
		return false;
	}
}

bool Interpreter::dateTodayOrTomorrow(string str, int either){
	DateTime dt=DateTime::Now;
	str=removeSpacesFromBothEnds(str);
	if (str==TODAY_KEY_WORD){
		setDateParams(dt.Year, dt.Month, dt.Day, either);
		return true;
	}else if(str==TOMORROW_KEY_WORD){
		dt=dt.AddDays(1);
		setDateParams(dt.Year, dt.Month, dt.Day, either);
		return true;
	}
	return false;
}

bool Interpreter::dateThisOrNextDateFormat(int day, int week, int either){
	DateTime dt=DateTime::Now;
	int incremental=week*7+day;
	if (incremental < 0){
		incremental+=7;
	}
	dt=dt.AddDays(incremental);
	setDateParams(dt.Year, dt.Month, dt.Day, either);
	return true;
}

bool Interpreter::timeStandardInput(string str, char delim, int either){
	bool timeFlag=false;
	int hour, minute, second;
	vector<string> vec=breakStringWithDelim(str, delim);
	int size=vec.size();
	if (size<=1 || size>=4){
		return false;
	}else if(size==2){
		hour=stringToInt(vec.at(0));
		minute=stringToInt(vec.at(1));
		second=SECOND_LOWER_BOUND;
		timeFlag=validateTime(hour, minute, SECOND_LOWER_BOUND);
	}else if(size==3){
		hour=stringToInt(vec.at(0));
		minute=stringToInt(vec.at(1));
		second=stringToInt(vec.at(2));
		timeFlag=validateTime(hour, minute, SECOND_LOWER_BOUND);
	}
	if (timeFlag){
		setTimeParams(hour, minute, second, either);
		return true;
	}else{
		return false;
	}	
}

bool Interpreter::timeSpecialNumsOnly(string str, int either){
	int num=stringToInt(str);
	int hour=num/100, minute=num%100;
	bool timeFlag=false;
	timeFlag=validateTime(hour, minute, SECOND_LOWER_BOUND);
	if (timeFlag){
		setTimeParams(hour, minute, SECOND_LOWER_BOUND, either);
		return true;
	}else{
		return false;
	}
}

int Interpreter::mapTodayDayOfWeek(){
	DateTime dt=DateTime::Now;
	if (dt.DayOfWeek == System::DayOfWeek::Sunday){
		return INT_SUNDAY;
	}if (dt.DayOfWeek == System::DayOfWeek::Monday){
		return INT_MONDAY;
	}else if(dt.DayOfWeek == System::DayOfWeek::Tuesday){
		return INT_TUESDAY;
	}else if(dt.DayOfWeek == System::DayOfWeek::Wednesday){
		return INT_WEDNESDAY;
	}else if(dt.DayOfWeek == System::DayOfWeek::Thursday){
		return INT_THURSDAY;
	}else if(dt.DayOfWeek == System::DayOfWeek::Friday){
		return INT_FRIDAY;
	}else if(dt.DayOfWeek == System::DayOfWeek::Saturday){
		return INT_SATURDAY;
	}else{
		return INTERNAL_ERROR_CODE;
	}
}

int Interpreter::mapDayOfWeekToInt(const string& str){
	string str1=toLowerCase(str);
	if (str1==SUN_KEY_WORD || str1==SUN_FULL_KEY_WORD){
		return INT_SUNDAY;
	}else if(str1==MON_KEY_WORD || str1==MON_FULL_KEY_WORD){
		return INT_MONDAY;
	}else if(str1==TUE_KEY_WORD || str1==TUE_FULL_KEY_WORD){
		return INT_TUESDAY;
	}else if(str1==WED_KEY_WORD || str1==WED_FULL_KEY_WORD){
		return INT_WEDNESDAY;
	}else if(str1==THU_KEY_WORD || str1==THU_FULL_KEY_WORD){
		return INT_THURSDAY;
	}else if(str1==FRI_KEY_WORD || str1==FRI_KEY_WORD){
		return INT_FRIDAY;
	}else if(str1==SAT_KEY_WORD || str1==SAT_FULL_KEY_WORD){
		return INT_SATURDAY;
	}else{
		return INTERNAL_ERROR_CODE;
	}
}

void Interpreter::setDateParams(int yearValue, int monthValue, int dayValue, int either){
	if (either==EITHER_AS_START){
		_start.setYear(yearValue);
		_start.setMonth(monthValue);
		_start.setDay(dayValue);
	}else{
		_end.setYear(yearValue);
		_end.setMonth(monthValue);
		_end.setDay(dayValue);
	}
}

void Interpreter::setTimeParams(int hourValue, int minuteValue, int secondValue, int either){
	if (either==EITHER_AS_START){
		_start.setHour(hourValue);
		_start.setMinute(minuteValue);
		_start.setSec(secondValue);
	}else{
		_end.setHour(hourValue);
		_end.setMinute(minuteValue);
		_end.setSec(secondValue);
	}
}

bool Interpreter::validateDate(int year, int month, int day){
	if (!validateYear(year)){
		return false;
	}
	if (System::DateTime::IsLeapYear(year)){
		return validateMonthDay(month, day, false);
	}else{
		return validateMonthDay(month, day, true);
	}
	return true;
}

bool Interpreter::validateTime(int hour, int minute, int second){
	bool hourFlag=false, minuteFlag=false, secondFlag=false;
	if (hour>=HOUR_LOWER_BOUND && hour<=HOUR_UPPER_BOUND){
		hourFlag=true;
	}
	if (minute>=MINUTE_LOWER_BOUND && minute<=MINUTE_UPPER_BOUND){
		minuteFlag=true;
	}
	if (second>=SECOND_LOWER_BOUND && second<=SECOND_UPPER_BOUND){
		secondFlag=true;
	}
	return hourFlag&&minuteFlag&&secondFlag;
}

bool Interpreter::validateYear(int year){
	if (year>=YEAR_LOWER_BOUND && year<=YEAR_UPPER_BOUND){
		return true;
	}else{
		return false;
	}
}

bool Interpreter::validateMonthDay(int month, int day, bool leap){
	bool valid=false;
	switch (month){
	case JANUARY: case MARCH: case MAY: case JULY: case AUGUST: case OCTOBER: case DECEMBER:
		if (day>=DAY_LOWER_BOUND && day<=DAY_UPPER_BOUND1){
			valid=true;
		}
		break;
	case APRIL: case JUNE: case SEPTEMBER: case NOVEMBER:
		if (day>=DAY_LOWER_BOUND && day<=DAY_UPPER_BOUND2){
			valid=true;
		}
		break;
	case FEBRUARY:
		if (leap){
			if (day>=DAY_LOWER_BOUND && day<=DAY_UPPER_BOUND3-1){
				valid=true;
			}
		}else{
			if (day>=DAY_LOWER_BOUND && day<=DAY_UPPER_BOUND3){
				valid=true;
			}
		}
		break;
	default:
		break;
	}
	return valid;
}

vector<string> Interpreter::breakStringWithDelim(string str, char delim){
	vector<string> vec;
	stringstream ss(str);
	string tempStr;
	while (std::getline(ss, tempStr, delim)){
		if (tempStr!=EMPTY_STRING){
			vec.push_back(tempStr);
		}
	}
	return vec;
}

string Interpreter::removeLeadingSpaces(string str){
	if (str==EMPTY_STRING){
		return str;
	}
	int num=str.find_first_not_of(SPACE);
	return str.substr(num);
}

string Interpreter::removeTailSpaces(string str){
	int num=str.find_last_not_of(SPACE);
	return str.substr(0,num+1);
}

string Interpreter::removeSpacesFromBothEnds(string str){
	return removeTailSpaces(removeLeadingSpaces(str));
}

int Interpreter::findFirstOfWord(const string& source, const string& word){
	int num=source.find(word);
	return num;
}

int Interpreter::findLastOfWord(const string& source, const string& word){
	int num=source.find(word), prev=num;
	while(num!=-1){
		prev=num;
		num=source.find(word, num+1);
	}
	return prev;
}

vector<int> Interpreter::pushNumsWithComma(const vector<string>& strVec){
	vector<int> vec;
	int size=strVec.size();
	for (int i=0;i<size;i++){
		int temp=stringToInt(strVec.at(i));
		if (temp>=0){
			vec.push_back(temp);
		}else{
			vec.clear();
			return vec;
		}
	}
	return vec;
}

vector<int> Interpreter::pushNumsWithDash(const vector<string>& strVec){
	vector<int> vec;
	int temp1=stringToInt(strVec.at(0));
	int temp2=stringToInt(strVec.at(1));
	if (temp1>=0 && temp2>=temp1){
		for (int i=temp1;i<=temp2; i++){
			vec.push_back(i);
		}
	}else{
		vec.clear();
		return vec;
	}
	return vec;
}

bool Interpreter::containChar(string input, char ch){
	return input.find(ch)!=std::string::npos;
}

Interpreter::~Interpreter(){
}
