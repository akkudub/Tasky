#include "Processor.h"

Processor::Processor(){
	_taskListPointer=_logic.returnTaskListPointer();
	_statusFlag=0;
}

string Processor::mainProcessor(string command){
	command = toLowCaseString(command);
	breakIntoStringVector(command);
	if(_statusFlag == 0){
		string firstWord = _wordsList->at(0);
		if(firstWord == "add"){
			return addCommandProcessor();
		}else if(firstWord == "display"){
			return displayCommandProcessor();
		}else if(firstWord == "update"){
			return updateCommandProcessor(_statusFlag);
		}else if(firstWord == "remove"){
			return removeCommandProcessor(_statusFlag);
		}else if(firstWord == "mark"){
			return markCommandProcessor(_statusFlag);
		}else if(firstWord == "other"){
			return otherCommandProcessor();
		}

	}else if(_statusFlag == 1){
		return updateCommandProcessor(_statusFlag);
	}else if(_statusFlag == 2){
		removeCommandProcessor(_statusFlag);
	}else if(_statusFlag == 3){
		markCommandProcessor(_statusFlag);
	}
}
//level 1 abstraction

string Processor::addCommandProcessor(){

}

string Processor::displayCommandProcessor(){

}

string Processor::updateCommandProcessor(int& _statusFlag){

}

string Processor::removeCommandProcessor(int& _statusFlag){

}

string Processor::markCommandProcessor(int& _statusFlag){

}

string Processor::otherCommandProcessor(){

}


//level 2 abstraction

int Processor::findType(int& type){
	vector<int> positionVector = identifyKeyWords();
	int endPosition = _wordsList->size()-1;
	if (positionVector.size() == 0){
		type=0;
	}else if(positionVector.size()==1){
		if (positionVector[0] == endPosition){
			type = 0;
		}else if(positionVector[0] == endPosition-1){
			if (dateCheck(_wordsList->at(endPosition))){
				type =1;
			}else{
				type = 0;
			}
		}else if(positionVector[0] == endPosition-2){
			if (dateTimeCheck(_wordsList->at(endPosition-1), _wordsList->at(endPosition))){
				type = 1;
			}
		}
	}else if(positionVector.size()==2){
		int fromPos = positionVector[0];
		int toPos = positionVector[1];
		if (toPos == endPosition){
			type = 0;
		}else if(toPos == endPosition-1){
			if (dateCheck(_wordsList->at(endPosition)) && dateCheck(_wordsList->at(fromPos+1))){
				type=2;
			}else{
				type=0;
			}
		}else if(toPos == endPosition-2){
			if (dateTimeCheck(_wordsList->at(endPosition-1), _wordsList->at(endPosition)) && dateTimeCheck(_wordsList->at(fromPos+1), _wordsList->at(fromPos+2))){
				type=2;
			}else{
				type=0;
			}
		}
	}else{
		return -1;
	}
	return 0;
}

int Processor::findDate(DateTime&){
	return 1;
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

string Processor::taskToString(const Task&){
	return "";
}


string Processor::toLowCaseString(string str){
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

string Processor::removeLeadingSpaces(string str){
	int num=str.find_first_not_of(' ');
	return str.substr(num);
}

vector<int> Processor::identifyKeyWords(){
	int endPosition = _wordsList->size()-1;
	vector<int> positionVector;
	for (int i = endPosition; i > endPosition-6; i--){
		if(fromToCheck(2, i)){
			positionVector.push_back(i-2);
			positionVector.push_back(i);
			return positionVector;
		}else if(fromToCheck(3, i)){
			positionVector.push_back(i-3);
			positionVector.push_back(i);
			return positionVector;
		}else if(byCheck(i)){
			positionVector.push_back(i);
			return positionVector;
		}
	}
	return positionVector;
}

bool Processor::fromToCheck(int int1, int iterator){
	if (_wordsList->at(iterator) == "to"){
		return ((_wordsList->at(iterator-int1)) == "from");
	}else{
		return false;
	}
}

bool Processor::byCheck(int iterator){
	return (_wordsList->at(iterator) == "by");
}

bool Processor::dateCheck(string test){
	return true;
}

bool Processor::timeCheck(string test){
	return true;
}

bool Processor::dateTimeCheck(string date, string time){
	return (dateCheck(date) && timeCheck(time));
}


int Processor::characterType(char ch){
	if (ch=='.' || ch=='/' || ch=='\\'){
		return 1;
	}else if(ch>='0' && ch<='9'){
		return 0;
	}else{
		return -1;
	}
}



Processor::~Processor(){
	delete _wordsList;
}
