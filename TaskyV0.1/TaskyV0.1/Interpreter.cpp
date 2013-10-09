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
const string Interpreter::UPDATE_KEY_WORD = "' to '";
const string Interpreter::ALL_KEY_WORD = "all";
const string Interpreter::TODAY_KEY_WORD = "today";
const string Interpreter::TOMORROW_KEY_WORD = "tomorrow";

const char Interpreter::SLASH = '/';
const char Interpreter::DOT = '.';
const char Interpreter::COMMA = ',';
const char Interpreter::SINGLE_QUOTE = '\'';
const char Interpreter::SPACE = ' ';
const char Interpreter::DASH = '-';
const char Interpreter::COLON = ':';

Interpreter::Interpreter(){
}

int Interpreter::interpretAdd(string str, string& title, int& type, BasicDateTime& start, BasicDateTime& end, string& comment){
	int posDashM=str.size(), posQuote1=0, posQuote2=0;
	bool fromToFlag=false, byFlag=false;

	if (!extractComment(str, comment, posDashM)){
		return -1;
	}
	if (!extractTitle(str, title, posQuote1, posQuote2)){
		return -1;
	}

	if (str.find(FROM_KEY_WORD, posQuote2+1)!=std::string::npos){
		fromToFlag=fromToCheck(str.substr(posQuote2+1, posDashM-posQuote2-2));
	}else if(str.find(BY_KEY_WORD, posQuote2+1)!=std::string::npos){
		byFlag=byCheck(str.substr(posQuote2+1, posDashM-posQuote2-2));
	}else{
		return -1;
	}

	if (fromToFlag){
        start=_start;
		end=_end;
		type=2;
	}else if(byFlag){
		end=_end;
		type=1;
	}else{
		type=0;
	}
	return 0;
}

int Interpreter::interpretSearch(string str, vector<string>& keywords, BasicDateTime& start, BasicDateTime& end){
	int size=str.size(), pos1;
	if (str.find(SINGLE_QUOTE)!=std::string::npos){
		pos1=str.find_last_of(SINGLE_QUOTE);
	}else{
		return -1;
	}
	vector<string> temp=breakStringWithDelim(str.substr(0,pos1), SPACE);
	keywords.push_back(removeSpacesFromBothEnds(str));
	keywords.insert(keywords.end(),temp.begin(), temp.end());
	if (fromToCheck(str.substr(pos1))){
		start=_start;
		end=_end;
	}else{
		return -1;
	}
	return 0;
}

int Interpreter::interpretDisplay(string str, BasicDateTime& start, BasicDateTime& end, bool& status){
	bool statusFlag=false;
	int pos=0, size=str.size();
	if (str.find(ALL_KEY_WORD)!=std::string::npos){
		return 0;
	}else{
		if (str.find(PENDING_KEY_WORD)!=std::string::npos){
			statusFlag=true;
			pos=str.find(PENDING_KEY_WORD);
		}else if(str.find(DONE_KEY_WORD)!=std::string::npos){
			statusFlag=true;
			pos=str.find(DONE_KEY_WORD);
		}
		if (pos>=size-1){
			return -1;
		}else{
			if (fromToCheck(str.substr(pos))){
				start=_start;
				end=_end;
			}else{
				return -1;
			}
		}
	}
	if (statusFlag){
		return 1;
	}else{
		return 2;
	}
}

int Interpreter::interpretUpdate(string str, string& oldTitle, string& newTitle){
	int posQuote1=0, posKey=0, posQuote2=0;
	if (str.find(UPDATE_KEY_WORD)==str.find(UPDATE_KEY_WORD)){
		posKey=str.find(UPDATE_KEY_WORD);
		posQuote1=str.find_first_of(SINGLE_QUOTE);
		posQuote2=str.find_last_of(SINGLE_QUOTE);
		if (posQuote2-posQuote1<=5){
			return -1;
		}else{
			oldTitle=str.substr(posQuote1+1,posKey-posQuote1-1);
			newTitle=str.substr(posKey+6,posQuote2-posKey);
		}
	}else{
		return -1;
	}
	return STATUS_CODE_SET::SUCCESS;
}

int Interpreter::interpretReschedule(string str, string& title, int& type, BasicDateTime& start, BasicDateTime& end){
	int posQuote1=0, posQuote2=0;
	if (extractTitle(str, title, posQuote1, posQuote2)){
		if (str.size()==posQuote2){
			type=0;
		}else if (str.find(TO_KEY_WORD, posQuote2+1)!=std::string::npos){
			type=extractDateTimeForReschdule(str.substr(posQuote2+1));
			if (type==1){
				end=_end;
			}else if(type==2){
				start=_start;
				end=_end;
			}else if(type!=0){
				title=EMPTY_STRING;
				return -1;
			}
		}else{
			title=EMPTY_STRING;
			return -1;
		}
	}else{
		title=EMPTY_STRING;
		return -1;
	}
	return 0;
}

//additional note here, we may change this method to make it more strict
int Interpreter::interpretMark(string str, string& title, bool& status){
	int posQuote1=0, posQuote2=0;
	if (extractTitle(str, title, posQuote1, posQuote2)){
		if (str.size()==posQuote2+1){
			title=EMPTY_STRING;
			return -1;
		}
		if (str.find(DONE_KEY_WORD, posQuote2+1)!=std::string::npos){
			status=true;
		}else if(str.find(PENDING_KEY_WORD, posQuote2+1)!=std::string::npos){
			status=false;
		}else{
			title=EMPTY_STRING;
			return -1;
		}
	}
	return 0;
}

int Interpreter::interpretRemove(string str, string& title){
	int num1, num2;
	if (!extractTitle(str, title, num1, num2)){
        return -1;
	}
	return STATUS_CODE_SET::SUCCESS;
}

int Interpreter::stringToInt(string str){
	int num;
	if ((stringstream(str)>>num)){
		return num;
	}else{
		return -1;
	}
}

vector<int> Interpreter::stringToIntVec(string str){
	vector<int> vec;
	vector<string> vecStr;
	std::regex reg1("[0-9,]"), reg2("[0-9-]");
	if (!std::regex_match(str, reg1)){
		return vec;
	}else if(std::regex_match(str, reg2)){
		vecStr=breakStringWithDelim(str, DASH);
		int size=vecStr.size();
		if (size!=2){
			return vec;
		}else{
			int num1=stringToInt(vecStr.at(0)), num2=stringToInt(vecStr.at(1));
			if (num1<=0){
                return vec;
			}else if(num1>=num2){
				return vec;
			}else{
				for (int i=num1;i<=num2;i++){
					vec.push_back(i);
				}
			}
		}
    } else{
		vecStr=breakStringWithDelim(str, COMMA);
		int size=vecStr.size();
		for (int i=0;i<size;i++){
			int tempInt=stringToInt(vecStr.at(i));
			if (tempInt!=-1){
				vec.push_back(tempInt);
			}else{
				vec.clear();
				return vec;
			}
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
		fromFlag=translateDateTime(vec.at(0), vec.at(1), 1);
	}else{
		return false;
	}
	tempStr=str.substr(pos2+3);
	vec=breakStringWithDelim(tempStr, SPACE);
	if (vec.size()==1){
		toFlag=translateDateTime(vec.at(0), EMPTY_STRING, 1);
	}else if (vec.size()==2){
		toFlag=translateDateTime(vec.at(0), vec.at(1), 2);
	}else{
		return false;
	}
	return fromFlag&&toFlag;
}

bool Interpreter::byCheck(string str){
	bool byFlag=false;
	string tempStr;
	vector<string> vec;
	tempStr=str.substr(3);
	vec=breakStringWithDelim(tempStr, SPACE);
	if (vec.size()==1){
		byFlag=translateDateTime(vec.at(0), EMPTY_STRING, 1);
	}else if (vec.size()==2){
		byFlag=translateDateTime(vec.at(0), vec.at(1), 1);
	}else{
		return false;
	}
	return byFlag;
}

bool Interpreter::translateDateTime(string str1, string str2, int either){
	bool dateFlag=false, timeFlag=false;
	if(str2!=EMPTY_STRING){
		dateFlag=translateDate(str1, either);
		timeFlag=translateTime(str2, either);
	}else if(str1!=EMPTY_STRING){
		dateFlag=translateDate(str1, either);
		timeFlag=true;
		setTimeParams(0, 0, 0, either);
	}else{
		return false;  //if reach here, a bug found
	}
	return dateFlag&&timeFlag;
}

bool Interpreter::translateDate(string str1, int either){
	return dateStandardInput(str1, either) || dateTodayOrTomorrow(str1, either);
}

bool Interpreter::translateTime(string str1, int either){
	/*regex reg1("[0-9.]"), reg2("[0-9:]"), reg3("[0-9]");
	if (std::regex_match(str1, reg1)){
		return timeStandardInput(str1, DOT, either);
	}else if(std::regex_match(str1, reg2)){
		return timeStandardInput(str1, COLON, either);
	}else if(std::regex_match(str1, reg3)){
		return timeSpecialNumsOnly(str1, either);
	}else{
		return false;
	}*/
	return timeStandardInput(str1, DOT, either);
}

bool Interpreter::dateStandardInput(string str, int either){
	vector<string> vec=breakStringWithDelim(str, SLASH);
	bool yearFlag=false, monthFlag=false, dayFlag=false;
	int year=0, month=0, day=0;
	int size=vec.size();
	if (size<=1 || size>=4){
		return false;
	}else if(size==3){
		year=stringToInt(vec.at(2));
		month=stringToInt(vec.at(1));
		day=stringToInt(vec.at(0));
		if (year>=2000 && year<=9999){
			yearFlag=true;
		}else if(year>=0 && year<=99){ //short cut input for 20xx
			yearFlag=true;
			year=year+2000;
		}
		if (month>=1 && month<=12){
			monthFlag=true;
		}
		if (day>=1 && day<=31){
			dayFlag=true;
		}
	}else if(size==2){
		month=stringToInt(vec.at(1));
		day=stringToInt(vec.at(0));
		if (month>=1 && month<=12){
			monthFlag=true;
		}
		if (day>=1 && day<=31){
			dayFlag=true;
		}
		year=DateTime::Now.Year;
		yearFlag=true;
	}
	if (yearFlag&&monthFlag&&dayFlag){
		try{
			DateTime dt(year, month, day, 0, 0, 0);
		}catch (const exception& e){
			return false;
		}
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

bool Interpreter::timeStandardInput(string str, char delim, int either){
	bool hourFlag=false, minuteFlag=false, secondFlag=false;
	int hour, minute, second;
	vector<string> vec=breakStringWithDelim(str, delim);
	int size=vec.size();
	if (size<=1 || size>=3){
		return false;
	}else if(size==2){
		hour=stringToInt(vec.at(0));
		minute=stringToInt(vec.at(1));
		if (hour>=0 && hour<=23){
			hourFlag=true;
		}
		if (minute>=0 && minute<=59){
			minuteFlag=true;
		}
		second=0;
		secondFlag=true;
	}else if(size==3){
		hour=stringToInt(vec.at(0));
		minute=stringToInt(vec.at(1));
		second=stringToInt(vec.at(2));
		if (hour>=0 && hour<=23){
			hourFlag=true;
		}
		if (minute>=0 && minute<=59){
			minuteFlag=true;
		}
		if (second>=0 && second<=59){
			secondFlag=true;
		}
	}
	if (hourFlag&&minuteFlag&&secondFlag){
		setTimeParams(hour, minute, second, either);
		return true;
	}else{
		return false;
	}	
}

bool Interpreter::timeSpecialNumsOnly(string str, int either){
	int num=stringToInt(str);
	int hour=num/100, minute=num%100;
	bool hourFlag=false, minuteFlag=false;
	if (hour>=0 && hour<=23){
		hourFlag=true;
	}
	if (minute>=0 && minute<=60){
		minuteFlag=true;
	}
	if (hourFlag&&minuteFlag){
		setTimeParams(hour, minute, 0, either);
		return true;
	}else{
		return false;
	}
}

int Interpreter::extractDateTimeForReschdule(string str){
	return 0;
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

void Interpreter::setDateParams(int yearValue, int monthValue, int dayValue, int either){
	if (either==1){
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
	if (either==1){
		_start.setHour(hourValue);
		_start.setMinute(minuteValue);
		_start.setSec(secondValue);
	}else{
		_end.setHour(hourValue);
		_end.setMinute(minuteValue);
		_end.setSec(secondValue);
	}
}

string Interpreter::removeLeadingSpaces(string str){
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

Interpreter::~Interpreter(){
}
