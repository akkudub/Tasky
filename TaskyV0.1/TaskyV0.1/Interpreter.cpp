#include "Interpreter.h"
#include <assert.h>
#include <algorithm>

const string Interpreter::EMPTY_STRING = "";
const string Interpreter::FROM_KEY_WORD = "from";
const string Interpreter::TO_KEY_WORD = "to";
const string Interpreter::BY_KEY_WORD = "by";
const string Interpreter::DASH_M = "-m";
const string Interpreter::PENDING_KEY_WORD = "pending";
const string Interpreter::DONE_KEY_WORD = "done";
const string Interpreter::UPDATE_KEY_WORD = "' to '";
const string Interpreter::ALL_KEY_WORD = "all";

const char Interpreter::SLASH = '/';
const char Interpreter::DOT = '.';
const char Interpreter::COMMA = ',';
const char Interpreter::SINGLE_QUOTE = '\'';
const char Interpreter::SPACE = ' ';
const char Interpreter::DASH = '-';

Interpreter::Interpreter(){
}

int Interpreter::interpretAdd(string str, string& title, int& type, BasicDateTime& start, BasicDateTime& end, string& comment){
	int posDashM=0, posQuote1=0, posQuote2=0;
	bool fromToFlag=false, byFlag=false;

	if (!extractComment(str, comment, posDashM)){
		cleanUpPrivateVariables();
		return -1;
	}
	if (!extractTitle(str, title, posQuote1, posQuote2)){
		cleanUpPrivateVariables();
		return -1;
	}

	if (str.find(FROM_KEY_WORD, posQuote2+1)!=std::string::npos){
		fromToFlag=fromToCheck(str.substr(posQuote2+1, posDashM-posQuote2-1));
	}else if(str.find(BY_KEY_WORD, posQuote2+1)!=std::string::npos){
		byFlag=byCheck(str.substr(posQuote2+1, posDashM-posQuote2-1));
	}else{
		cleanUpPrivateVariables();
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

	cleanUpPrivateVariables();
	return STATUS_CODE_SET::SUCCESS;
}

int Interpreter::interpretSearch(string str, vector<string>& keywords, BasicDateTime& start, BasicDateTime& end){
	int size=str.size();
	vector<string> temp=breakStringWithDelim(str, SPACE);
	keywords.push_back(removeSpacesFromBothEnds(str));
	keywords.insert(keywords.end(),temp.begin(), temp.end());
	return STATUS_CODE_SET::SUCCESS;
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
	if (str.find_first_of(UPDATE_KEY_WORD)==str.find_last_of(UPDATE_KEY_WORD)){
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
	return STATUS_CODE_SET::SUCCESS;
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
	return STATUS_CODE_SET::SUCCESS;
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
	if (str.find_last_of(DASH_M)!=std::string::npos){
		pos=str.find_last_of(DASH_M);
		comment=str.substr(pos);
	}else{
		comment=EMPTY_STRING;
	}
	return true;
}

bool Interpreter::fromToCheck(string str){
	bool fromFlag=false, toFlag=false;
	

	return fromFlag&&toFlag;
}

bool Interpreter::byCheck(string str){
	bool byFlag=false;

	return byFlag;
}

bool Interpreter::translateDateTime(string str1, string str2, string str3, string str4, int either){
	bool dateFlag=false, timeFlag=false;

	if (str4!=EMPTY_STRING){

	}else if(str3!=EMPTY_STRING){

	}else if(str2!=EMPTY_STRING){
		if (str1=="this" || str1=="next"){

		}else{
			dateFlag=translateDate(str1, EMPTY_STRING, EMPTY_STRING, either);
			timeFlag=translateTime(str2, either);
		}
	}else if(str1!=EMPTY_STRING){

	}else{
		return false;  //if reach here, a bug found
	}

	return false;
}

bool Interpreter::translateDate(string str1, string str2, string str3, int either){
	return false;
}

bool Interpreter::translateTime(string str1, int either){
	regex reg("[0-9.]");

	if (!std::regex_match(str1, reg)){
		return false;
	}else{
		if (str1.find(DOT)!=std::string::npos){
			return timeStandardInput(str1, DOT, either);
		}else{
			return false;
		}
	}
}

bool Interpreter::timeStandardInput(string str, char delim, int either){
	bool hourFlag=false, minuteFlag=false, secondFlag=false;
	int hour, minute, second;
	int pos1=str.find(delim);
	int pos2=str.find_last_of(delim);
			
	hour=stringToInt(str.substr(0, pos1-0));
	if (hour>=0 && hour<=23){
		hourFlag=true;
		setTimeParam(3, hour, either);
	}

	if (pos1 == pos2){
		minute=stringToInt(str.substr(pos1+1, str.size()-pos1));
		if (minute>=0 && minute<=59){
	   	   minuteFlag=true;
		   secondFlag=true;
		   setTimeParam(4, minute, either);
		   setTimeParam(5, 0, either);
		}
	}else{
		minute=stringToInt(str.substr(pos1+1, str.size()-pos1));
		if (minute>=0 && minute<=59){
	   	   minuteFlag=true;
		   setTimeParam(4, minute, either);
		}
		second=stringToInt(str.substr(pos2+1, str.size()-pos2));
		if (second>=0 && second<=59){
		    secondFlag=true;
			setTimeParam(5, second, either);
	    }
	}

	return hourFlag&&minuteFlag&&secondFlag;
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

void Interpreter::setTimeParam(int num1, int value, int either){
	switch(num1){
	case 0:
		if (either==1){
			_start.setYear(value);
		}else{
			_start.setYear(value);
		}
		break;
	case 1:
		if (either==1){
			_start.setMonth(value);
		}else{
			_start.setMonth(value);
		}
		break;
	case 2:
		if (either==1){
			_start.setDay(value);
		}else{
			_start.setDay(value);
		}
		break;
	case 3:
		if (either==1){
			_start.setHour(value);
		}else{
			_start.setHour(value);
		}
		break;
	case 4:
		if (either==1){
			_start.setMinute(value);
		}else{
			_start.setMinute(value);
		}
		break;
	case 5:
		if (either==1){
			_start.setSec(value);
		}else{
			_start.setSec(value);
		}
		break;
	default:
		break; //a bug
	}
}

string Interpreter::removeLeadingSpaces(string str){
	int num=str.find_first_not_of(SPACE);

	return str.substr(num);
}

void Interpreter::cleanUpPrivateVariables(){
	_title=EMPTY_STRING;
	_type=0;
}

Interpreter::~Interpreter(){
}
