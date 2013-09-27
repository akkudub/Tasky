#include "Processor.h"

const string Processor::EMPTY_STRING = "";
const string Processor::FROM_KEY_WORD = "from";
const string Processor::TO_KEY_WORD = "to";
const string Processor::BY_KEY_WORD = "by";
const string Processor::NEW_LINE_STRING = "\n";

const string Processor::ADD_TASK_SUCCESS = "Task added successfully: ";
const string Processor::ADD_TASK_FAILURE_DUPLICATE = "Failed! Task existed: ";
const string Processor::ADD_TASK_FAILURE_UNEXPECTED = "Failed! Unexpected error during task adding: ";
const string Processor::ADD_TASK_WARNING_CLASH = "Warning: this task clashes with existing ones";
const string Processor::DISPLAY_TASK_SUCCESS="Task Display success!";
const string Processor::DISPLAY_TASK_FAILURE_UNEXPECTED="Unexpected task failure";
const string Processor::WRONG_INPUT="Wrong input";
const string Processor::UNEXPECTED_ERROR="Unexpected error";
const string Processor::UPDATE_CHOOSE_TASK="Enter the task number to update: ";
const string Processor::UPDATE_MESSAGE_WARNING_SAME="Warning! The new data is the same as the old data";
const string Processor::UPDATE_MESSAGE_WARNING_CLASH="Warning! The new data will make the task clash with the following:";
const string Processor::UPDATE_MESSAGE_FAILURE="Error! Unable to update task";
const string Processor::REMOVE_CHOOSE_TASK="Enter the task number to remove: ";
const string Processor::MARK_CHOOSE_TASK="Enter the task number to mark: ";
const string Processor::NO_SUCH_TASK="No such task!";

const char Processor::SLASH = '/';
const char Processor::BACK_SLASH = '\\';
const char Processor::DOT = '.';
const char Processor::COLON = ':';
const char Processor::DASH = '-';
const char Processor::ZERO = '0';
const char Processor::NINE = '9';
const char Processor::SPACE = ' ';
const char Processor::NEW_LINE = '\n';

Processor::Processor(){
	_taskListPointer=_logic.returnTaskListPointer();
	_statusFlag=0;
}

string Processor::mainProcessor(string command){
	command = toLowCaseString(command);
	breakIntoStringVectorBySpace(command);
	if(_statusFlag == 0){
		string firstWord = _wordsList->at(0);
		if(firstWord == "add"){
			return addCommandProcessor();
		}else if(firstWord == "display"){
			return displayCommandProcessor();
		}else if(firstWord == "update"){
			return updateCommandProcessor();
		}else if(firstWord == "remove"){
			return removeCommandProcessor();
		}else if(firstWord == "mark"){
			return markCommandProcessor();
		}else{
			return otherCommandProcessor();
		}

	}else if(_statusFlag == 1){
		return updateCommandProcessor();
	}else if(_statusFlag == 2){
		return removeCommandProcessor();
	}else if(_statusFlag == 3){
		return markCommandProcessor();
	}
	return "";
}
//level 1 abstraction
string Processor::addCommandProcessor(){
	int type, dtFormat1, dtFormat2, pos1, pos2;
	int addOperationStatus;
	string title;
	DateTime startingDateTime;
	DateTime endingDateTime;

	determineType(type, dtFormat1, dtFormat2, pos1, pos2);
	switch (type){
	case 0:
		title=combineStringsWithSpaceOnVector(1, _wordsList->size()-1);
		addOperationStatus=addFloatingTask(title, EMPTY_STRING);
		return determineMsgToUI(addOperationStatus);
		break;
	case 1:
		title=combineStringsWithSpaceOnVector(0, pos2-1);//shouldnt the first argument be 1?
		if (formatDateTime(endingDateTime, dtFormat2, pos2)==0){
			addOperationStatus=addDeadlineTask(title, endingDateTime, EMPTY_STRING);
			return determineMsgToUI(addOperationStatus);
		}else{
			return determineMsgToUI(-1);
		}
		break;
	case 2:
		title=combineStringsWithSpaceOnVector(0, pos1-1);//shouldnt the first argument be 1?
		if (formatDateTime(startingDateTime, dtFormat1, pos1)==0
			&&formatDateTime(endingDateTime, dtFormat2, pos2)==0){
				addOperationStatus=addNormalTask(title, startingDateTime, endingDateTime, EMPTY_STRING);
				return determineMsgToUI(addOperationStatus);
		}else{
			return determineMsgToUI(-1);
		}
		break;
	default:
		return determineMsgToUI(-1);
		break;
	}
}

string Processor::displayCommandProcessor(){
	string result;
	if (_wordsList->at(1)=="pending"){
		if (_logic.display(false, _tempTaskList) == 0){
			int size=_tempTaskList.size();
			for (int i=0;i<size;i++){
				result=combineStringsWithNewLine(result, taskToString(_tempTaskList[i]));
			}
		}else{
			result=DISPLAY_TASK_FAILURE_UNEXPECTED;
		}
	}else if (_wordsList->at(1)=="done"){
		if (_logic.display(true, _tempTaskList) == 0){
			int size=_tempTaskList.size();
			for (int i=0;i<size;i++){
				result=combineStringsWithNewLine(result, taskToString(_tempTaskList[i]));
			}
		}else{
			result=DISPLAY_TASK_FAILURE_UNEXPECTED;
		}
	}else{
		result=WRONG_INPUT;
	}

	return result;
}

//pass the created task and the task in the vector at position
//create a new vector and pass in that for new clashes
string Processor::updateCommandProcessor(){
	if(_statusFlag == 1){
		unsigned int choice = stringToInt(_wordsList->at(1));
		if((choice <=_tempTaskList.size()) && choice < 0 && _wordsList->size()>2){
			int type, dtFormat1, dtFormat2, pos1, pos2;
			int operationStatus;
			string title;
			DateTime startingDateTime;
			DateTime endingDateTime;
			Task t;
			vector<Task> clash;

			determineType(type, dtFormat1, dtFormat2, pos1, pos2);
			switch (type){
			case 0:
				title=combineStringsWithSpaceOnVector(2, _wordsList->size()-1);
				createTask(t, title, startingDateTime, endingDateTime, type, false, EMPTY_STRING);
				operationStatus = _logic.update(_tempTaskList[choice-1], t, clash);
				break;
			case 1:
				title=combineStringsWithSpaceOnVector(2, pos2-1);
				if (formatDateTime(endingDateTime, dtFormat2, pos2)==0){
					createTask(t, title, startingDateTime, endingDateTime, type, false, EMPTY_STRING);
					operationStatus=_logic.update(_tempTaskList[choice-1], t, clash);
				}else{
					return determineMsgToUI(-1);
				}
				break;
			case 2:
				title=combineStringsWithSpaceOnVector(2, pos1-1);
				if (formatDateTime(startingDateTime, dtFormat1, pos1)==0
					&&formatDateTime(endingDateTime, dtFormat2, pos2)==0){
						createTask(t, title, startingDateTime, endingDateTime, type, false, EMPTY_STRING);
						operationStatus=_logic.update(_tempTaskList[choice-1], t, clash);
				}else{
					return determineMsgToUI(-1);
				}
				break;
			default:
				return determineMsgToUI(-1);
				break;
			}
			return determineMsgToUI(operationStatus);
			//here i need a separate case for clash to display the clashes,
			//but i cant use any combineStrings methods.
			//I wanted to change the combineStringsWithNewLineOnVector method to take in a vector
			//and convert the contents into strings rather than only using _tempTaskList
		}
	}else if(_statusFlag == 0){
		if(_wordsList->size()>1){
			string title=combineStringsWithSpaceOnVector(1, _wordsList->size()-1);
			_tempTaskList.clear();
			_logic.search(title, _tempTaskList);
			if(_tempTaskList.size()>0){
				_statusFlag = 1;
				return UPDATE_CHOOSE_TASK;
			}else if(_tempTaskList.empty()){
				return NO_SUCH_TASK;
			}
		}
	}
	return EMPTY_STRING;
}
string Processor::removeCommandProcessor(){
	if(_statusFlag == 2){
		unsigned int choice = stringToInt(_wordsList->at(1));
		int operationStatus;
		if((choice <=_tempTaskList.size()) && choice < 0){
			operationStatus=_logic.remove(_tempTaskList[choice-1]);
			return determineMsgToUI(operationStatus);
		}
	}else if(_statusFlag == 0){
		if(_wordsList->size()>1){
			string title=combineStringsWithSpaceOnVector(1, _wordsList->size()-1);
			_tempTaskList.clear();
			_logic.search(title, _tempTaskList);
			if(_tempTaskList.size()>0){
				_statusFlag = 2;
				return REMOVE_CHOOSE_TASK;
			}else if(_tempTaskList.empty()){
				return NO_SUCH_TASK;
			}
		}
	}
	return EMPTY_STRING;
}
string Processor::markCommandProcessor(){
	if(_statusFlag == 3){
		unsigned int choice = stringToInt(_wordsList->at(1));
		int operationStatus;
		if((choice <=_tempTaskList.size()) && choice < 0){
			operationStatus=_logic.mark(true, _tempTaskList[choice-1]);
			return determineMsgToUI(operationStatus);
		}else if(_statusFlag == 0){
			if(_wordsList->size()>1){
				string title=combineStringsWithSpaceOnVector(1, _wordsList->size()-1);
				_tempTaskList.clear();
				_logic.search(title, _tempTaskList);
				if(_tempTaskList.size()>0){
					_statusFlag = 3;
					return MARK_CHOOSE_TASK;
				}else if(_tempTaskList.empty()){
					return NO_SUCH_TASK;
				}
			}
		}
	}
	return EMPTY_STRING;
}

string Processor::otherCommandProcessor(){
	return WRONG_INPUT;
}

string Processor::determineMsgToUI(int statusReturnedFromLogic){
	switch (statusReturnedFromLogic){
	case STATUS_CODE_SET::SUCCESS:
		return combineStatusMsgWithFeedback(ADD_TASK_SUCCESS);
		break;
	case STATUS_CODE_SET::ADD_FAILURE_DUPLICATE:
		return combineStatusMsgWithFeedback(ADD_TASK_FAILURE_DUPLICATE);
		break;
	case STATUS_CODE_SET::ADD_WARNING_CLASH:
		return combineStatusMsgWithFeedback(ADD_TASK_WARNING_CLASH);
		break;
	case STATUS_CODE_SET::ADD_FAILURE:
		return combineStatusMsgWithFeedback(ADD_TASK_FAILURE_UNEXPECTED);
		break;
	default:
		return ADD_TASK_FAILURE_UNEXPECTED;
		break;
	}
}

int Processor::addFloatingTask(string title, string comment){
	DateTime dt1, dt2;
	Task t;
	createTask(t, title, dt1, dt2, 0, false, EMPTY_STRING);
	_tempTaskList.clear();
	return _logic.add(t, _tempTaskList);
}

int Processor::addDeadlineTask(string title, DateTime dt, string comment){
	DateTime dt1;
	Task t;
	createTask(t, title, dt1, dt, 1, false, EMPTY_STRING);
	_tempTaskList.clear();
	return _logic.add(t, _tempTaskList);
}

int Processor::addNormalTask(string title, DateTime dt1, DateTime dt2, string comment){
	Task t;
	createTask(t, title, dt1, dt2, 2, false, EMPTY_STRING);
	_tempTaskList.clear();
	return _logic.add(t, _tempTaskList);
}

int Processor::createTask(Task& t, string title, DateTime dt1, DateTime dt2, int type, bool done, string comment){
	t=Task(title, dt1, dt2, type, done, comment);
	return 0;
}

int Processor::formatDateTime(DateTime& dt, int dtFormat, int pos){
	if (dtFormat == 1){
		if (translateDateTime(dt, _wordsList->at(pos+1), EMPTY_STRING) != 0){
			return -1;
		}
	}else if(dtFormat == 2){
		if (translateDateTime(dt, _wordsList->at(pos+1),_wordsList->at(pos+2)) !=0){
			return -1;
		}
	}else{
		return -1;
	}

	return 0;
}

int Processor::translateDateTime(DateTime& dt, string str1, string str2){
	int year=0, month=0, day=0, hour=0, minute=0, second=0;
	bool dateFlag=false, timeFlag=true;

	if (str1!=EMPTY_STRING){
		if (translateDate(year, month, day, str1) != 0){
			return 1;
		}else{
			dateFlag=true;
		}
	}
	if (str2!=EMPTY_STRING){
		if (translateTime(hour, minute, second,str2) != 0){
			return 1;
		}else{
			timeFlag=true;
		}
	}
	if (dateFlag && timeFlag){
		try{
			dt=DateTime(year, month, day, hour, minute, second);
		}catch (const exception& e){
			return 1;
		}
	}else if(dateFlag && !timeFlag){
		try{
			dt=DateTime(year, month, day, hour, minute, second);
		}catch (const exception& e){
			return 1;
		}
	}else{
		return 1;
	}

	return 0;
}

int Processor::translateDate(int& year, int& month, int& day, string date){
	DateTime now;
	year=stringToInt(date.substr(0,4));
	if (year < now.Year){
		return 1;
	}
	month=stringToInt(date.substr(5,2));
	if (month>12 || month<1){
		return 1;
	}
	day=stringToInt(date.substr(8,2));
	if (day>31 || day<1){
		return 1;
	}

	return STATUS_CODE_SET::SUCCESS;
}

int Processor::translateTime(int& hour, int& minute, int& second, string time){
	hour=stringToInt(time.substr(0,2));
	if (hour>24 || hour<0){
		return 1;
	}
	minute=stringToInt(time.substr(3,2));
	if (minute>60 || minute<0){
		return 1;
	}
	if (time.size() == 8){
		second=stringToInt(time.substr(6,2));
		if (second>60 || second<0){
			return 1;
		}
	}

	return STATUS_CODE_SET::SUCCESS;
}

int Processor::determineType(int& type, int& dtFromat1, int& dtFormat2, int& pos1, int& pos2){
	vector<int> positionVector = identifyKeyWords();
	int endPosition = _wordsList->size()-1;

	if (positionVector.size() == 0){
		type=0;
	}else if(positionVector.size()==1){
		if (positionVector[0] == endPosition){
			type = 0;
		}else if(positionVector[0] == endPosition-1){
			string tempStr=_wordsList->at(endPosition);
			if (dateCheck(tempStr)){
				type = 1;
				dtFormat2 = 1;
				pos2 = positionVector[0];
			}else{
				type = 0;
			}
		}else if(positionVector[0] == endPosition-2){
			string tempStr1=_wordsList->at(endPosition-1);
			string tempStr2=_wordsList->at(endPosition);
			if (dateTimeCheck(tempStr1, tempStr2)){
				type = 1;
				dtFormat2 = 2;
				pos2 = positionVector[0];
			}else{
				type=0;
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

bool Processor::fromToCheck(int posDiff, int iterator){
	if (_wordsList->at(iterator) == TO_KEY_WORD){
		return ((_wordsList->at(iterator-posDiff)) == FROM_KEY_WORD);
	}else{
		return false;
	}
}

bool Processor::byCheck(int iterator){
	return (_wordsList->at(iterator) == BY_KEY_WORD);
}

bool Processor::dateTimeCheck(string date, string time){
	return (dateCheck(date) && timeCheck(time));
}

bool Processor::dateCheck(string test){
	int size=test.size();
	int index=0;

	if(size != 10){
		return false;
	}
	for (;index<4;index++){
		if (characterType(test[index]) != 0){
			return false;
		}
	}
	if (characterType(test[index]) != 1){
		return false;
	}
	index++;
	for (;index<7;index++){
		if (characterType(test[index]) != 0){
			return false;
		}
	}
	if (characterType(test[index]) != 1){
		return false;
	}
	index++;
	for (;index<size;index++){
		if (characterType(test[index]) != 0){
			return false;
		}
	}

	return true;
}

bool Processor::timeCheck(string test){
	int size=test.size();
	int index=0;

	if (size!=5 && size!=8){
		return false;
	}
	for (;index<2;index++){
		if (characterType(test[index])!=0){
			return false;
		}
	}
	if (characterType(test[index])!=1){
		return false;
	}
	index++;
	for (;index<5;index++){
		if (characterType(test[index])!=0){
			return false;
		}
	}
	if (size==8){
		if (characterType(test[index])!=1){
			return false;
		}
		for (;index<8;index++){
			if (characterType(test[index])!=0){
				return false;
			}
		}
	}

	return true;
}

int Processor::breakIntoStringVectorBySpace(string longStr){
	stringstream ss(longStr);
	string tempStr;

	while (std::getline(ss, tempStr, SPACE)){
		_wordsList->push_back(tempStr);
	}

	return 0;
}

int Processor::stringToInt(string str){
	int num;
	if ((stringstream(str)>>num)){
		return num;
	}else{
		return -1;
	}
}

string Processor::combineStringsWithSpaceOnVector(int start, int end){
	string result=_wordsList->at(start);
	for (int i=start+1;i<end;i++){
		if(_wordsList->at(i)!=""){
			result=result+" "+_wordsList->at(i);
		}
	}
	return removeLeadingSpaces(result);
}

string Processor::combineStringsWithNewLineOnVector(int start, int end){
	string result=taskToString(_tempTaskList.at(start));
	for (int i=start+1;i<end;i++){
		result=combineStringsWithNewLine(result, taskToString(_tempTaskList.at(i)));
	}
	return result;
}

string Processor::combineStringsWithNewLine(string str1, string str2){
	return str1+NEW_LINE_STRING+str2;
}

string Processor::taskToString(Task t){
	if(t.getType() == 0)
	{
		return printFloatingTask(t);
	}else if(t.getType() == 1){
		return printDeadlineTask(t);
	}else if(t.getType() == 2){
		return printTimedTask(t);
	}else{
		return UNEXPECTED_ERROR;
	}
}

string Processor::printFloatingTask(Task t){
	string result;
	result="title: "+t.getTitle();
	result=combineStringsWithNewLine(result, "Status: ");
	result+= printStatus(t.getDone());
	result=combineStringsWithNewLine(result, "Type: ");
	result+="Floating task";
	return result;
}

string Processor::printDeadlineTask(Task t){
	string result;
	result="title: "+t.getTitle();
	result=combineStringsWithNewLine(result, "Status: ");
	result+= printStatus(t.getDone());
	result=combineStringsWithNewLine(result, "Type: ");
	result+="Deadline task";
	result=combineStringsWithNewLine(result, "Deadline: ");
	result+= marshal_as<std::string>(t.getEnd().ToString());
	return result;
}

string Processor::printTimedTask(Task t){
	string result;
	result="title: "+t.getTitle();
	result=combineStringsWithNewLine(result, "Status: ");
	result+= printStatus(t.getDone());
	result=combineStringsWithNewLine(result, "Type: ");
	result+="Timed task";
	result=combineStringsWithNewLine(result, "Start Date: ");
	result+= marshal_as<std::string>(t.getStart().ToString());
	result=combineStringsWithNewLine(result, "End Date: ");
	result+= marshal_as<std::string>(t.getEnd().ToString());
	return result;
}

string Processor::printStatus(bool status){
	if(status){
		return "done";
	}else{
		return "pending";
	}
}


string Processor::toLowCaseString(string str){
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

string Processor::removeLeadingSpaces(string str){
	int num=str.find_first_not_of(SPACE);
	return str.substr(num);
}

int Processor::characterType(char ch){
	if (ch==DOT || ch==BACK_SLASH || ch==SLASH || ch==COLON || ch==DASH){
		return 1;
	}else if(ch>=ZERO && ch<=NINE){
		return 0;
	}else{
		return -1;
	}
}

string Processor::combineStatusMsgWithFeedback(string msg){
	string feedback=msg;
	int size=_tempTaskList.size();

	for (int i=0;i<size;i++){
		feedback=combineStringsWithNewLine(feedback, taskToString(_tempTaskList.at(i)));
	}

	return feedback;
}

Processor::~Processor(){
	delete _wordsList;
}

string Processor::mainProcessor(string s){
return "processing return";
}