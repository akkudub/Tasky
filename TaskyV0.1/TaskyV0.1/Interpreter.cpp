#include "Interpreter.h"
#include <assert.h>

const string Interpreter::EMPTY_STRING = "";
const string Interpreter::FROM_KEY_WORD = "from";
const string Interpreter::TO_KEY_WORD = "to";
const string Interpreter::BY_KEY_WORD = "by";
const string Interpreter::NEW_LINE_STRING = "\n";

const char Interpreter::SLASH = '/';
const char Interpreter::BACK_SLASH = '\\';
const char Interpreter::DOT = '.';
const char Interpreter::COLON = ':';
const char Interpreter::DASH = '-';
const char Interpreter::ZERO = '0';
const char Interpreter::NINE = '9';
const char Interpreter::SPACE = ' ';
const char Interpreter::NEW_LINE = '\n';

Interpreter::Interpreter(){
	_wordsList=new vector<string>;
}

int Interpreter::interpreteTaskFromString(string str, string& title, int& type, BasicDateTime& start, BasicDateTime& end, string& comment){
	breakIntoStringVectorBySpace(str);
	vector<int> tempVec=identifyKeyWordsCreatingTask();

	if (tempVec.size() == 2){

	}else if(tempVec.size() == 1) {

	}else if(tempVec.size() == 0){

	}else{
		cleanUpPrivateVariables();
		return -1;
	}
	cleanUpPrivateVariables();
	return STATUS_CODE_SET::SUCCESS;
}

vector<int> Interpreter::identifyKeyWordsCreatingTask(){
	int tempSize=_wordsList->size();
	int findPattern=0;
	vector<int> vec;

	for (int i=1;i<tempSize;i++){
		if (_wordsList->at(i) == FROM_KEY_WORD){
			for (int j=2;j<=5;j++){
				if (_wordsList->at(i+j) == TO_KEY_WORD){
					if (fromToCheck(i, i+j)){
						findPattern=1;
						vec.clear();
						vec.push_back(i);
						vec.push_back(j);
					}
					break;
				}
			}
		}else if(_wordsList->at(i) == BY_KEY_WORD && tempSize>i+1){
			if (byCheck(i)){
				findPattern=2;
				vec.clear();
				vec.push_back(i);
			}
		}
	}

	return vec;
}

bool Interpreter::fromToCheck(int pos1, int pos2){
	assert((pos2-pos1)>1);
	bool fromFlag=false, toFlag=false;
	//assume symemtric input for now
    if (pos2-pos1 == 2){
		fromFlag=translateDateTime(_wordsList->at(pos1+1), EMPTY_STRING, EMPTY_STRING, EMPTY_STRING, 1);
		toFlag=translateDateTime(_wordsList->at(pos2+1), EMPTY_STRING, EMPTY_STRING, EMPTY_STRING, 2);
	}else if (pos2-pos1 == 3){
		fromFlag=translateDateTime(_wordsList->at(pos1+1), _wordsList->at(pos1+2), EMPTY_STRING, EMPTY_STRING, 1);
		toFlag=translateDateTime(_wordsList->at(pos2+1), _wordsList->at(pos2+2), EMPTY_STRING, EMPTY_STRING, 2);
	}else if (pos2-pos1 == 4){
		fromFlag=translateDateTime(_wordsList->at(pos1+1), _wordsList->at(pos1+2), _wordsList->at(pos1+3), EMPTY_STRING, 1);
		toFlag=translateDateTime(_wordsList->at(pos2+1), _wordsList->at(pos2+2), _wordsList->at(pos2+3), EMPTY_STRING, 2);
	}else if (pos2-pos1 == 5){
		fromFlag=translateDateTime(_wordsList->at(pos1+1), _wordsList->at(pos1+2), _wordsList->at(pos1+3), _wordsList->at(pos1+4), 1);
		toFlag=translateDateTime(_wordsList->at(pos2+1), _wordsList->at(pos2+2), _wordsList->at(pos2+3), _wordsList->at(pos2+4), 2);
	}else{
		return false;  //if reach here, we will have a bug
	}

	return fromFlag&&toFlag;
}

bool Interpreter::byCheck(int pos){
	int tempSize=_wordsList->size(), dashM=tempSize;
	assert(pos+1<tempSize);
	for (int i=pos;i<tempSize; i++){
		if (_wordsList->at(i) == "-m"){
			dashM=i;
			break;
		}
	}
	if (dashM-pos>5){
		return false;
	}else if(dashM-pos==5){
		return translateDateTime(_wordsList->at(pos+1), _wordsList->at(pos+2), _wordsList->at(pos+3), _wordsList->at(pos+4), 2);
	}else if(dashM-pos==4){
		return translateDateTime(_wordsList->at(pos+1), _wordsList->at(pos+2), _wordsList->at(pos+3), EMPTY_STRING, 2);
	}else if(dashM-pos==3){
		return translateDateTime(_wordsList->at(pos+1), _wordsList->at(pos+2), EMPTY_STRING, EMPTY_STRING, 2);
	}else if(dashM-pos==2){
		return translateDateTime(_wordsList->at(pos+1), EMPTY_STRING, EMPTY_STRING, EMPTY_STRING, 2);
	}else{
		return false;
	}
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
	regex reg("[0-9.]|[0-9:]");

	if (!std::regex_match(str1, reg)){
		return false;
	}else{
		if (str1.find(DOT)!=std::string::npos){
			return timeStandardInput(str1, DOT, either);
		}else if(str1.find(COLON)!=std::string::npos){
			return timeStandardInput(str1, COLON, either);
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

int Interpreter::breakIntoStringVectorBySpace(const string& str){
	stringstream ss(str);
	string tempStr;

	while (std::getline(ss, tempStr, SPACE)){
		if (tempStr != EMPTY_STRING){
		    _wordsList->push_back(tempStr);
		}
	}

	return 0;
}

int Interpreter::stringToInt(string str){
	int num;
	if ((stringstream(str)>>num)){
		return num;
	}else{
		return -1;
	}
}

void Interpreter::cleanUpPrivateVariables(){
	delete _wordsList;
	_wordsList=new vector<string>;
	_title=EMPTY_STRING;
	_type=2;
}

Interpreter::~Interpreter(){
	delete _wordsList;
}
