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
const string Interpreter::SLOT_KEY_WORD = "slot";
const string Interpreter::RENAME_KEY_WORD = "' to '";
const string Interpreter::ALL_KEY_WORD = "all";
const string Interpreter::TODAY_KEY_WORD = "today";
const string Interpreter::TODAY_KEY_WORD_SHORTCUT = "tdy";
const string Interpreter::TOMORROW_KEY_WORD = "tomorrow";
const string Interpreter::TOMORROW_KEY_WORD_SHORTCUT = "tmr";
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
	setStartToNow();
}

int Interpreter::interpretAdd(string str, string& title, int& type, BasicDateTime& start, BasicDateTime& end, string& comment){
	int posDashM=str.size();
	int posQuote1=0;
	int posQuote2=0;
	int posBeginningOfDateTimePart=0;
	int lengthOfDateTimePart=0;
	bool fromToFlag=false;
	bool byFlag=false;

	if (!extractComment(str, comment, posDashM)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_ADD;
	}
	if (!extractTitle(str, title, posQuote1, posQuote2)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_TITLE_FORMAT;
	}
	if (title==EMPTY_STRING){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_TITLE_FORMAT;
	}
	posBeginningOfDateTimePart=posQuote2+1;
	lengthOfDateTimePart=posDashM-posQuote2-1;
	if (!firstVerifyFromToOrBy(str.substr(posBeginningOfDateTimePart, lengthOfDateTimePart), fromToFlag, byFlag)){
		type = NO_DATETIME;
		return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_ADD;
	}
	if (!secondVerifyFromToOrBy(fromToFlag, byFlag, type, start, end)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_DATETIME_FORMAT;
	}
	return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_ADD;
}

int Interpreter::interpretPowerSearch(string str, bool& slotEnabled, vector<string>& keywords, int& searchStatus, int& type, BasicDateTime& start, BasicDateTime& end){
	int size=str.size();
	int posQuote1=0;
	int posQuote2=0;
	bool fromToFlag=false;
	bool byFlag=false;
	bool slotFlag=false;
	bool keywordFlag=false;
	bool statusFlag=false;
	bool timeFlag=true;
	bool traditionalSearchFlag=true;
	string title=EMPTY_STRING;

	keywords.clear();
	if (!extractTitle(str, title, posQuote1, posQuote2)){
		keywordFlag=false;
	}else{
		keywordFlag=true;
		keywords=extractKeywords(title);
	}
	if (containKeywordWithoutCase(str.substr(posQuote2+1), SLOT_KEY_WORD)){
		slotFlag=true;
		slotEnabled=true;
	}
	if (containKeywordWithoutCase(str.substr(posQuote2+1), PENDING_KEY_WORD)){
		searchStatus=POWER_SEARCH_PENDING_STATUS;
		statusFlag=true;
	}else if(containKeywordWithoutCase(str.substr(posQuote2+1), DONE_KEY_WORD)){
		searchStatus=POWER_SEARCH_DONE_STATUS;
		statusFlag=true;
	}else{
		searchStatus=POWER_SEARCH_NO_STATUS;
		statusFlag=false;
	}
	if (!firstVerifyFromToOrBy(str.substr(posQuote2), fromToFlag, byFlag)){
		timeFlag=false;
		type = NO_DATETIME;
	}else{
        if (!secondVerifyFromToOrBy(fromToFlag, byFlag, type, start, end)){
		    return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_DATETIME_FORMAT;
		}
	}

	if (keywordFlag || statusFlag){
		traditionalSearchFlag=true;
	}else{
		traditionalSearchFlag=false;
	}
	if (traditionalSearchFlag && slotFlag){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_MIXED_UP_INPUT;
	}
	if (traditionalSearchFlag){
		slotEnabled=false;  //having passed the previous test means this should be false
	}else{
		if (!timeFlag){
			return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_MISSING_ESSENTIAL_COMPONENTS_IN_COMMAND;
		}else{
			slotEnabled=true;
		}
	}

	return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH;
}

int Interpreter::interpretDisplay(const string& str, int& displayType){
	bool statusFlag=false;
	bool fromToFlag=false;
	bool byFlag=false;
	int pos=0, size=str.size();
	if (containKeywordWithoutCase(str, ALL_KEY_WORD)){
		displayType=DISPLAY_TYPE_ALL;
	}else if(containKeywordWithoutCase(str, PENDING_KEY_WORD)){
		displayType=DISPLAY_TYPE_PENDING;
	}else if(containKeywordWithoutCase(str, DONE_KEY_WORD)){
		displayType=DISPLAY_TYPE_DONE;
	}else if(containKeywordWithoutCase(str, TODAY_KEY_WORD)){
		displayType=DISPLAY_TYPE_TODAY;
	}else{
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_DISPLAY;
	}
	return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_DISPLAY;
}

int Interpreter::interpretRename(string str, string& oldTitle, string& newTitle){
	int posQuote1=0;
	int posKey=0;
	int posQuote2=0;
	string str1;
	string str2;
	posQuote1=str.find_first_of(SINGLE_QUOTE);
	posQuote2=str.find_last_of(SINGLE_QUOTE);
	if (!findStartingPosOfKeywordWithoutCase(str, RENAME_KEY_WORD, posKey)){
        return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_MISSING_ESSENTIAL_COMPONENTS_IN_COMMAND;
	}
	if (posQuote1>=posKey || posQuote2<=posKey+5){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_MISSING_ESSENTIAL_COMPONENTS_IN_COMMAND;
	}else{
		str1=str.substr(posQuote1+1, posKey-posQuote1-1);
		str2=str.substr(posKey+6, posQuote2-posKey-6);
	}
	if (str1==EMPTY_STRING || str2==EMPTY_STRING){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_TITLE_FORMAT;
	}
	oldTitle=str1;
	newTitle=str2;
	return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_RENAME;
}

int Interpreter::interpretReschedule(string str, string& title, int& type, BasicDateTime& start, BasicDateTime& end){
	int posQuote1=0;
	int posQuote2=0;
	bool fromToFlag=false, byFlag=false;
	if (!extractTitle(str, title, posQuote1, posQuote2)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_TITLE_FORMAT;
	}
	if (!firstVerifyFromToOrBy(str.substr(posQuote2+1), fromToFlag, byFlag)){
		type=NO_DATETIME;
		return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_RESCHEDULE;
	}
	if (!secondVerifyFromToOrBy(fromToFlag, byFlag, type, start, end)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_DATETIME_FORMAT;
	}
	return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_RESCHEDULE;
}

int Interpreter::interpretMark(string str, string& title, bool& status){
	str=removeLeadingSpaces(str);
	int posQuote1=0;
	int posQuote2=0;
	if (!extractTitle(str, title, posQuote1, posQuote2)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_TITLE_FORMAT;
	}
	if (str.size()==posQuote2+1){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_MISSING_ESSENTIAL_COMPONENTS_IN_COMMAND;
	}
	if (containKeywordWithoutCase(str.substr(posQuote2+1), DONE_KEY_WORD)){
		status=true;
	}else if(containKeywordWithoutCase(str.substr(posQuote2+1), PENDING_KEY_WORD)){
		status=false;
	}else{
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_MISSING_ESSENTIAL_COMPONENTS_IN_COMMAND;
	}
	return STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_MARK;
}

int Interpreter::interpretRemove(string str, string& title){
	str=removeLeadingSpaces(str);
	int num1, num2;
	if (!extractTitle(str, title, num1, num2)){
		return STATUS_CODE_SET_ERROR::ERROR_INTERPRET_TITLE_FORMAT;
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

bool Interpreter::extractTitle(const string& str, string& title, int& pos1, int& pos2){
	if (str.find_first_of(SINGLE_QUOTE)!=std::string::npos){
		pos1=str.find_first_of(SINGLE_QUOTE);
		pos2=str.find_last_of(SINGLE_QUOTE);
	}else{
		return false;
	}
	if (pos1 < pos2-1){
		title=str.substr(pos1+1, pos2-pos1-1);
	}else{
		return false;
	}
	return true;
}

bool Interpreter::extractComment(const string& str, string& comment, int& pos){
	if (str.find(DASH_M)!=std::string::npos){
		pos=findLastOfWord(str, DASH_M);
		comment=str.substr(pos+3);
	}else{
		comment=EMPTY_STRING;
	}
	return true;
}

bool Interpreter::extractFirstWord(string str, string& firstWord){
	vector<string> vec=breakStringWithDelim(str, SPACE);
	if (vec.size()==0){
		return false;
	}else{
		firstWord=vec.at(0);
		return true;
	}
}

bool Interpreter::isEqualToKeyWordWithoutCase(string str, const string& keyword){
	str=toLowerCase(str);
	return str==keyword;
}

bool Interpreter::containKeywordWithoutCase(string str, const string& keyword){
	str=toLowerCase(str);
	return (str.find(keyword)!=std::string::npos);
}

bool Interpreter::findStartingPosOfKeywordWithoutCase(string str, const string& keyword, int& pos){
	if (containKeywordWithoutCase(str, keyword)){
		str=toLowerCase(str);
		pos=str.find(keyword);
		return true;
	}else{
		return false;
	}
}

vector<string> Interpreter::extractKeywords(const string& str){
	vector<string> keywords;
	vector<string> temp=breakStringWithDelim(str, SPACE);
	keywords.push_back(str);
	keywords.insert(keywords.end(),temp.begin(), temp.end());
	return keywords;
}

bool Interpreter::firstVerifyFromToOrBy(const string& str, bool& fromToFlag, bool& byFlag){
	if (containKeywordWithoutCase(str, FROM_KEY_WORD) && containKeywordWithoutCase(str, TO_KEY_WORD)){
		fromToFlag=fromToCheck(str);
		return true;
	}else if(containKeywordWithoutCase(str, BY_KEY_WORD)){
		byFlag=byCheck(str);
		return true;
	}else{
		return false;
	}
}

bool Interpreter::secondVerifyFromToOrBy(bool fromToFlag, bool byFlag, int& type, BasicDateTime& start, BasicDateTime& end){
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
		return false;  //contains the keyword(s) but does not pass further test
	}
}

bool Interpreter::fromToCheck(string str){
	bool fromFlag=false;
	bool toFlag=false;
	int posFrom=0;
	int posTo=0;
	int posOfBeginningDateTime=0;
	int lengthOfDateTime=0;
	int posOfBeginningDateTime2=0;
	string tempStr;
	vector<string> vec;

	posFrom=str.find(FROM_KEY_WORD);
	posTo=str.find(TO_KEY_WORD);
	if (posFrom<0 || (posTo<=posFrom)){
		return false;
	}
	posOfBeginningDateTime=posFrom+4;
	lengthOfDateTime=posTo-posFrom-4;
	posOfBeginningDateTime2=posTo+3;
	tempStr=str.substr(posOfBeginningDateTime, lengthOfDateTime);
	vec=breakStringWithDelim(tempStr, SPACE);
	if (!checkSizeOfDateTimeStringVec(vec)){
		return false;
	}
	generalTranslationOfDateTime(vec, fromFlag, EITHER_AS_START);
	tempStr=str.substr(posOfBeginningDateTime2);
	vec=breakStringWithDelim(tempStr, SPACE);
	if (!checkSizeOfDateTimeStringVec(vec)){
		return false;
	}
	generalTranslationOfDateTime(vec, toFlag, EITHER_AS_END);
	if (fromFlag&&toFlag){
		return isStartEarlierThanEnd();
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
	if (!checkSizeOfDateTimeStringVec(vec)){
		return false;
	}
	generalTranslationOfDateTime(vec, byFlag, EITHER_AS_END);
	if (byFlag){
		setStartToNow();
		return isStartEarlierThanEnd(); 
	}else{
		return false;
	}
}

bool Interpreter::checkSizeOfDateTimeStringVec(const vector<string>& vec){
	if (vec.size()>3 || vec.size()<1){
		return false;
	}else{
		return true;
	}
}

void Interpreter::generalTranslationOfDateTime(const vector<string>& vec, bool &fromFlag, int either){
	assert(vec.size()>0 && vec.size()<4);
	if (vec.size()==1){
		fromFlag=translateDateTime(vec.at(0), EMPTY_STRING, either);
	}else if (vec.size()==2){
		fromFlag=translateDateTime(vec.at(0), vec.at(1), either) || translateNaturalDate(vec.at(0), vec.at(1), either);
	}else if (vec.size()==3){
		fromFlag=translateNaturalDateTime(vec.at(0), vec.at(1), vec.at(2), either);
	}
}


void Interpreter::setStartToNow(){
	time_t time1=time(NULL);
	struct tm time2;
	localtime_s(&time2, &time1);
	_start=BasicDateTime(YEAR_LOWER_BOUND+time2.tm_year, 1+time2.tm_mon, time2.tm_mday, time2.tm_hour, time2.tm_min, time2.tm_sec);
}


bool Interpreter::isStartEarlierThanEnd(){
	return (_start.compareTo(_end)<0);
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
	int year=0;
	int month=0;
	int day=0;
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
		time_t time1=time(NULL);
		struct tm time2;
		localtime_s(&time2, &time1);
		year=YEAR_LOWER_BOUND+time2.tm_year;
		month=stringToInt(vec.at(1));
		day=stringToInt(vec.at(0));
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
	time_t time1=time(NULL);
	struct tm time2;
	localtime_s(&time2, &time1);
	if (containKeywordWithoutCase(str, TODAY_KEY_WORD) || containKeywordWithoutCase(str, TODAY_KEY_WORD_SHORTCUT)){
		setDateParams(YEAR_LOWER_BOUND+time2.tm_year, 1+time2.tm_mon, time2.tm_mday, either);
		return true;
	}else if(containKeywordWithoutCase(str, TOMORROW_KEY_WORD) || containKeywordWithoutCase(str, TOMORROW_KEY_WORD_SHORTCUT)){
		time2.tm_mday=time2.tm_mday+1;
		mktime(&time2);
		setDateParams(YEAR_LOWER_BOUND+time2.tm_year, 1+time2.tm_mon, time2.tm_mday, either);
		return true;
	}
	return false;
}

bool Interpreter::dateThisOrNextDateFormat(int day, int week, int either){
	time_t time1=time(NULL);
	struct tm time2;
	localtime_s(&time2, &time1);
	int incremental=week*7+day;
	if (incremental < 0){
		incremental+=7;
	}
	time2.tm_mday=time2.tm_mday+incremental;
	mktime(&time2);
	setDateParams(YEAR_LOWER_BOUND+time2.tm_year, 1+time2.tm_mon, time2.tm_mday, either);
	return true;
}

bool Interpreter::timeStandardInput(string str, char delim, int either){
	bool timeFlag=false;
	int hour;
	int minute;
	int second;
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
	time_t time1=time(NULL);
	struct tm time2;
	localtime_s(&time2, &time1);
	return time2.tm_wday;
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
	if (isLeapYear(year)){
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
	int num=source.find(word);
	int prev=num;
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

bool Interpreter::isLeapYear(int year){
	if (year<=YEAR_LOWER_BOUND || year>=YEAR_UPPER_BOUND){
		return false;
	}
	if (year%LEAP_YEAR_CONSTANT_100==0){
		return year%LEAP_YEAR_CONSTANT_400==0;
	}else{
		return year%LEAP_YEAR_CONSTANT_4==0;
	}
}
