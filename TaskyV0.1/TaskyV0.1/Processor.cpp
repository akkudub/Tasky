#include "Processor.h"

Processor::Processor(){
	_taskListPointer=_logic.returnTaskListPointer();
	_statusFlag=0;
}


//additional helping methods
int Processor::breakIntoStringVector(string longStr){
	stringstream ss(longStr);
	string tempStr;

	while (std::getline(ss, tempStr, ' ')){
		_wordsList->push_back(tempStr);
	}

	return 0;
}

int Processor::stringToInt(string str){
	int num;
	if ((stringstream(str)>>num)){
		return num;
	}else{
		return -1;  //to be defined as const int; negative number will be treated as illegal input
	}
}

string Processor::combineStringsWithSpace(int start, int end){
	string result=_wordsList->at(start);
	for (int i=start+1;i<end;i++){
		if(_wordsList->at(i)!=""){
			result=result+" "+_wordsList->at(i);
		}
	}
	return removeLeadingSpaces(result);
}

string Processor::combineStringsWithNewLine(int start, int end){
	string result=taskToString(_tempTaskList.at(start));
	for (int i=start+1;i<end;i++){
		result=result+"\n"+taskToString(_tempTaskList.at(i));
	}
	return result;
}


string Processor::toLowCaseString(string str){
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

string Processor::removeLeadingSpaces(string str){
	int num=str.find_first_not_of(' ');
	return str.substr(num);
}

Processor::~Processor(){
	delete _wordsList;
}
