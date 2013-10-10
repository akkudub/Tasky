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
const string Processor::DISPLAY_TASK_SUCCESS = "Task Display success!";
const string Processor::DISPLAY_TASK_FAILURE_UNEXPECTED = "Unexpected task failure";
const string Processor::WRONG_INPUT = "Wrong input";
const string Processor::UNEXPECTED_ERROR = "Unexpected error";
const string Processor::UPDATE_CHOOSE_TASK = "Enter the task number to update: ";
const string Processor::UPDATE_MESSAGE_WARNING_SAME = "Warning! The new data is the same as the old data";
const string Processor::UPDATE_MESSAGE_WARNING_CLASH = "Warning! The new data will make the task clash with the following:";
const string Processor::UPDATE_MESSAGE_FAILURE = "Error! Unable to update task";
const string Processor::REMOVE_CHOOSE_TASK = "Enter the task number to remove: ";
const string Processor::MARK_CHOOSE_TASK = "Enter the task number to mark: ";
const string Processor::NO_SUCH_TASK = "No such task!";

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
	_statusFlag=0;
	_wordsList = new vector<string>;
}

/*
* Purpose: Handle user input based on first keyword
* and call appropriate functions to handle
*
* Param: 
* command - first keyword of user input
*
* Returns: 
* formatted string of feedback and with user command (including task)
*/
string Processor::mainProcessor(string command){
	command = toLowCaseString(command);
	_wordsList->clear();
	breakIntoStringVectorBySpace(command, *_wordsList);
	if(_statusFlag == 0){
		string firstWord = _wordsList->at(0);
		if(firstWord == "add"){
			return addCommandProcessor();
		}else if(firstWord == "display"){
			return displayCommandProcessor();
		}else if(firstWord == "update"){
			return updateCommandProcessor();
		}else if(firstWord == "reschedule"){
			return rescheduleCommandProcessor();
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
/*
* Purpose: Add tasks according to type
* 0 - Floating tasks
* 1 - Deadline tasks
* 2 - Normal tasks
*
* Returns: 
* Message if task is successfully added (or not with reason)
*/
string Processor::addCommandProcessor(){
	int addOperationStatus, type;
	string title, comment;
	BasicDateTime startingDateTime;
	BasicDateTime endingDateTime;

	string user_command = combineStringsWithSpaceOnVector(1, _wordsList->size()-1);
	_interpreter.interpretAdd(user_command, title, type, startingDateTime, endingDateTime, comment);

	switch (type){
	case 0:
		addOperationStatus=addFloatingTask(title, comment);
		return determineMsgToUI(addOperationStatus);
		break;
	case 1:
		addOperationStatus=addDeadlineTask(title, endingDateTime, comment);
		return determineMsgToUI(addOperationStatus);
		break;
	case 2:
		addOperationStatus=addNormalTask(title, startingDateTime, endingDateTime, comment);
		return determineMsgToUI(addOperationStatus);
		break;
	default:
		return determineMsgToUI(-1);
	}
}

/*
* Purpose: Display to user type of task
*
* Returns: 
* Tasks of type; Unable to display
*/
string Processor::displayCommandProcessor(){
	string result, user_command;
	BasicDateTime start, end;
	bool status;
	int displayOperationStatus;
	user_command = combineStringsWithSpaceOnVector(1, _wordsList->size()-1);
	int return_code = _interpreter.interpretDisplay(user_command, start, end, status);
	if (return_code == 0){
		displayOperationStatus = _logic.displayAll(_tempTaskList);
		return determineMsgToUI(displayOperationStatus);
	}else if (return_code == 1){
		displayOperationStatus = _logic.displayStatus(status, _tempTaskList);
		return determineMsgToUI(displayOperationStatus);
	}else if(return_code == 2){
		displayOperationStatus = _logic.displayInRange(start, end, _tempTaskList);
		return determineMsgToUI(displayOperationStatus);
	}else{
		return determineMsgToUI(-1);
	}

}

//pass the created task and the task in the vector at position
//create a new vector and pass in that for new clashes
string Processor::updateCommandProcessor(){
	int operationStatus;
	if(_statusFlag == 1){
		unsigned int choice = stringToInt(_wordsList->at(1));
		if((choice <=_tempTaskList.size()) && choice > 0 && _wordsList->size()==2){
			string title, comment;
			BasicDateTime startingDateTime;
			BasicDateTime endingDateTime;
			Task t = _tempTaskList[choice-1];
			vector<Task> clash;

			t.setTitle(_tempTitle);
			operationStatus = _logic.update(_tempTaskList[choice-1], t, clash);
			_tempTaskList = clash;
			return determineMsgToUI(operationStatus);

		}else if(_statusFlag == 0){
			if(_wordsList->size()>1){
				string user_command=combineStringsWithSpaceOnVector(1, _wordsList->size()-1);
				string oldTitle;
				vector<string> keywords;
				vector<Task> clash;
				_interpreter.interpretUpdate(user_command, oldTitle, _tempTitle);
				_tempTaskList.clear();
				breakIntoStringVectorBySpace(oldTitle, keywords);
				_logic.searchKeywords(keywords, _tempTaskList);
				if (_tempTaskList.size() == 1){
					Task t = _tempTaskList[0];
					t.setTitle(_tempTitle);
					operationStatus=_logic.update(_tempTaskList[0], t, clash);
					return determineMsgToUI(operationStatus);
				}else if(!_tempTaskList.empty()){
					_statusFlag = 1;
					return UPDATE_CHOOSE_TASK;
				}else if(_tempTaskList.empty()){
					return NO_SUCH_TASK;
				}
			}
		}
	}
	return EMPTY_STRING;
}

/*
* Purpose: Remove task (from search results)
*
* Returns: 
* Task successfully removed; Ask user to choose task to remove; No such task found
*/
string Processor::removeCommandProcessor(){
	int operationStatus;
	if(_statusFlag == 2){
		unsigned int choice = stringToInt(_wordsList->at(1));
		if((choice <=_tempTaskList.size()) && choice > 0){
			operationStatus=_logic.remove(_tempTaskList[choice-1]);
			return determineMsgToUI(operationStatus);
		}
	}else if(_statusFlag == 0){
		if(_wordsList->size()>1){
			string user_command=combineStringsWithSpaceOnVector(1, _wordsList->size()-1);
			vector<string> keywords;
			_interpreter.interpretRemove(user_command, _tempTitle);
			_tempTaskList.clear();
			breakIntoStringVectorBySpace(_tempTitle, keywords);
			_logic.searchKeywords(keywords, _tempTaskList);
			if (_tempTaskList.size() == 1){
				operationStatus=_logic.remove(_tempTaskList[0]);
				return determineMsgToUI(operationStatus);
			}else if(!_tempTaskList.empty()){
				_statusFlag = 2;
				return REMOVE_CHOOSE_TASK;
			}else if(_tempTaskList.empty()){
				return NO_SUCH_TASK;
			}
		}
	}
	return EMPTY_STRING;
}

/*
* Purpose: Mark Task as Done/Pending (from search results)
*
* Returns: 
* Task is marked; Ask user to choose task to mark from results; No such task found
*/
string Processor::markCommandProcessor(){
	int operationStatus;
	if(_statusFlag == 3){
		vector<int> choice = _interpreter.stringToIntVec(_wordsList->at(1));

		if(choiceIsValid(choice)){
			for (unsigned int i = 0; i < choice.size(); i++){
				operationStatus=_logic.mark(_tempStatus, _tempTaskList[choice[i]]);
			}
			return determineMsgToUI(operationStatus);
		}else if(_statusFlag == 0){
			if(_wordsList->size()>1){
				string user_command=combineStringsWithSpaceOnVector(1, _wordsList->size()-1);
				_interpreter.interpretMark(user_command, _tempTitle, _tempStatus);
				_tempTaskList.clear();
				_logic.search(_tempTitle, _tempTaskList);
				if (_tempTaskList.size() == 1){
					operationStatus=_logic.mark(_tempStatus, _tempTaskList[0]);
					return determineMsgToUI(operationStatus);
				}	
				else if(!_tempTaskList.empty()){
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

string Processor::rescheduleCommandProcessor(){
	int operationStatus;
	if(_statusFlag == 4){
		unsigned int choice = stringToInt(_wordsList->at(1));
		if((choice <=_tempTaskList.size()) && choice > 0 && _wordsList->size()==2){
			string title, comment;
			BasicDateTime startingDateTime;
			BasicDateTime endingDateTime;
			Task t = _tempTaskList[choice-1];
			vector<Task> clash;

			t.setStartDate(_tempStart);
			t.setEndDate(_tempEnd);
			t.setType(_tempType);
			operationStatus = _logic.update(_tempTaskList[choice-1], t, clash);
			_tempTaskList = clash;		
			return determineMsgToUI(operationStatus);
		}else if(_statusFlag == 0){
			if(_wordsList->size()>1){
				string user_command=combineStringsWithSpaceOnVector(1, _wordsList->size()-1);
				_interpreter.interpretReschedule(user_command, _tempTitle, _tempType, _tempStart, _tempEnd);
				_tempTaskList.clear();
				_logic.search(_tempTitle, _tempTaskList);
				if (_tempTaskList.size() == 1){
					Task t = _tempTaskList[0];
					vector<Task> clash;
					t.setStartDate(_tempStart);
					t.setEndDate(_tempEnd);
					t.setType(_tempType);
					operationStatus=_logic.update(_tempTaskList[0], t, clash);
					return determineMsgToUI(operationStatus);
				}else if(!_tempTaskList.empty()){
					_statusFlag = 1;
					return UPDATE_CHOOSE_TASK;
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

bool Processor::choiceIsValid(vector<int> choice){
	if(choice.empty()){
		return false;
	}else{
		for (unsigned int i = 0; i < choice.size(); i++){
			unsigned int curr_choice = choice[i];
			if(curr_choice>=_tempTaskList.size() || choice[i]<1){
				return false;
			}
		}
		return true;
	}
}
/*
* Purpose: To get feedback to tell user is command is succesful/unsuccessful
*
* Param: 
* statusReturnedFromLogic - feedback from Logic code 
*
* Returns: 
* formatted string of feedback and with user command (including task)
*/
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

/*
* Purpose: Add task of type Floating tasks 
* puts the successfully created task into _tempTaskList
*
* Param: 
* title - name of task
* comment - additional description
*/
int Processor::addFloatingTask(string title, string comment){
	BasicDateTime dt1, dt2;
	Task t;
	t = Task(title, dt1, dt2, 2, false, comment);
	_tempTaskList.clear();
	return _logic.add(t, _tempTaskList);
}

/*
* Purpose: Add task of type Dealine tasks 
* puts the successfully created task into _tempTaskList
*
* Param: 
* title - name of task
* dt - deadline of task in DateTime format
* comment - additional description
*/
int Processor::addDeadlineTask(string title, BasicDateTime dt, string comment){
	BasicDateTime dt1;
	Task t;
	t = Task(title, dt1, dt, 2, false, comment);
	_tempTaskList.clear();
	return _logic.add(t, _tempTaskList);
}

/*
* Purpose: Add task of type Normal tasks 
* puts the successfully created task into _tempTaskList
*
* Param: 
* title - name of task
* dt1 - starting time of task in DateTime format
* dt2 - ending time of task in DateTime format
* comment - additional description
*/
int Processor::addNormalTask(string title, BasicDateTime dt1, BasicDateTime dt2, string comment){
	Task t;
	t = Task(title, dt1, dt2, 2, false, comment);
	_tempTaskList.clear();
	return _logic.add(t, _tempTaskList);
}

/*
* Purpose: Passes in the user input which has the position of date(and time)
* to put it into a DateTime variable dt
*
* Param: 
* dt - DateTime variable stores date and time upon successful convert
* dtFormat - 1 for date only;2 for date with time
* pos - starting position of the user input (in form of vector) which has the date
*
* Returns: 
*  0 - successful; 1 - unsuccessful
*/
int Processor::formatDateTime(BasicDateTime& dt, int dtFormat, int pos){
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

/*
* Purpose: puts the user input of date and time into a DateTime dt
*
* Param: 
* dt - DateTime variable stores date and time upon successful convert
* str1 - Date from user input
* str2 - Time from user input (if exists)
*
* Returns: 
* 0 - successful; 1 - unsuccessful
*/
int Processor::translateDateTime(BasicDateTime& dt, string str1, string str2){
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
			dt=BasicDateTime(year, month, day, hour, minute, second);
			cout<< dt.getDateTimeString() <<endl;
		}catch (const exception& e){
			return 1;
		}
	}else if(dateFlag && !timeFlag){
		try{
			dt=BasicDateTime(year, month, day, hour, minute, second);
		}catch (const exception& e){
			return 1;
		}
	}else{
		return 1;
	}

	return 0;
}

/*
* Purpose: Separates the string containing date into integers
*
* Param: 
* string - user input of date
*
* Returns: 
* SUCCESS; 1 - unsuccessful, wrong date
*/
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

/*
* Purpose: Separates the string containing time into integers
*
* Param: 
* string - user input of time
*
* Returns: 
* SUCCESS; 1 - unsuccessful, wrong time
*/
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

/*
* Purpose: identifies the keywords in the user input and stores into positionVector
*
* Returns: vector containinig position of keyword 
*/
vector<int> Processor::identifyKeyWords(){//fucked up
	int endPosition = _wordsList->size()-1;
	vector<int> positionVector;
	if(_wordsList->size()<=6){
		return positionVector;
	}
	for (int i = endPosition; i > endPosition-6; i--){
		if(fromToCheck(2, i)){
			positionVector.push_back(i-2);
			positionVector.push_back(i);
			return positionVector;
		}else if(fromToCheck(3, i)){
			positionVector.push_back(i-3);		//does this become relative position?
			positionVector.push_back(i);
			return positionVector;
		}else if(byCheck(i)){
			positionVector.push_back(i);
			return positionVector;
		}
	}
	return positionVector;
}

/*
* Purpose: Checks if user has entered the 'FROM-TO' keyword
*
* Param: posDiff - starting point of 'FROM' keyword; iterator - starting point to check from
*
* Returns: true - contains the keyword; false - does not contain
*/
bool Processor::fromToCheck(int posDiff, int iterator){
	if (_wordsList->at(iterator) == TO_KEY_WORD){
		return ((_wordsList->at(iterator-posDiff)) == FROM_KEY_WORD);
	}else{
		return false;
	}
}

/*
* Purpose: Checks if user has entered the 'BY' keyword
*
* Param: iterator - starting point to check from
*
* Returns: true - contains the keyword; false - does not contain
*/
bool Processor::byCheck(int iterator){
	return (_wordsList->at(iterator) == BY_KEY_WORD);
}

/*
* Purpose: Checks if date and time are correctly formatted
*
* Param: date - date in a string form, time - time in a string form
*
* Returns: true - correct; false - incorrect
*/
bool Processor::dateTimeCheck(string date, string time){
	return (dateCheck(date) && timeCheck(time));
}

/*
* Purpose: Checks if date is correctly formatted in YYYY/XX/XX
*
* Param: date in a string form
*
* Returns: true - correct; false - incorrect
*/
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

/*
* Purpose: Checks if time is correctly formatted in XX:XX:XX
*
* Param: time in a string form
*
* Returns: true - correct; false - incorrect
*/
bool Processor::timeCheck(string test){
	int size=test.size();
	int index=0;

	if (size!=5 && size!=8){	//what's this?
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
		index++;
		for (;index<8;index++){
			if (characterType(test[index])!=0){
				return false;
			}
		}
	}

	return true;
}

/*
* Purpose: Separates the user input word by word into vector _wordsList
*
* Param: longStr - user input
*
* Returns: success
*/
int Processor::breakIntoStringVectorBySpace(string longStr, vector<string>& outputVector){
	stringstream ss(longStr);
	string tempStr;

	while (std::getline(ss, tempStr, SPACE)){
		outputVector.push_back(tempStr);
	}

	return 0;
}

/*
* Purpose: converts string into integer
*
* Param: str - string to be converted 
*
* Returns: integer converted; -1 if unable to convert
*/
int Processor::stringToInt(string str){
	int num;
	if ((stringstream(str)>>num)){
		return num;
	}else{
		return -1;
	}
}

/*
* Purpose:Formats the user input which was previously separated
* into vector into a string again
*
* Param: start - beginning of word to be combined in vector;
*		 end - end of word to be combined in vector
*
* Returns: formatted string of user input
*/
string Processor::combineStringsWithSpaceOnVector(int start, int end){
	string result=_wordsList->at(start);
	for (int i=start+1;i<=end;i++){
		if(_wordsList->at(i)!=""){
			result=result+" "+_wordsList->at(i);
		}
	}
	return removeLeadingSpaces(result);
}

/*
* Purpose:Formats all the task between start to end into 1 string
*
* Param: start - beginning of task to be combined in vector;
*		 end - end of task to be combined in vector
*
* Returns: formatted task details
*/
string Processor::combineStringsWithNewLineOnVector(int start, int end){
	string result=taskToString(_tempTaskList.at(start));
	for (int i=start+1;i<end;i++){
		result=combineStringsWithNewLine(result, taskToString(_tempTaskList.at(i)));
	}
	return result;
}

/*
* Purpose:Formats 2 strings separated by a new line character
*
* Returns: formatted string
*/
string Processor::combineStringsWithNewLine(string str1, string str2){
	return str1+NEW_LINE_STRING+str2;
}

/*
* Purpose: Checks the type of the task,
* and print the details of task according to type 
*
* Param: t- task with details
*
* Returns: formatted task details
*/
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

/*
* Purpose:Formats the details task into a string to be printed
*
* Param: t- task with details
*
* Returns: formatted task details
*/
string Processor::printFloatingTask(Task t){
	string result;
	result="title: "+t.getTitle();
	result=combineStringsWithNewLine(result, "Status: ");
	result+= printStatus(t.getDone());
	result=combineStringsWithNewLine(result, "Type: ");
	result+="Floating task";
	return result;
}

/*
* Purpose:Formats the details task into a string to be printed
*
* Param: t- task with details
*
* Returns: formatted task details
*/
string Processor::printDeadlineTask(Task t){
	string result;
	result="title: "+t.getTitle();
	result=combineStringsWithNewLine(result, "Status: ");
	result+= printStatus(t.getDone());
	result=combineStringsWithNewLine(result, "Type: ");
	result+="Deadline task";
	result=combineStringsWithNewLine(result, "Deadline: ");
	result+= t.getEnd().getDateTimeString();
	return result;
}

/*
* Purpose:Formats the details task into a string to be printed
*
* Param: t- task with details
*
* Returns: formatted task details
*/
string Processor::printTimedTask(Task t){
	string result;
	result="title: "+t.getTitle();
	result=combineStringsWithNewLine(result, "Status: ");
	result+= printStatus(t.getDone());
	result=combineStringsWithNewLine(result, "Type: ");
	result+="Timed task";
	result=combineStringsWithNewLine(result, "Start Date: ");
	result+= t.getStart().getDateTimeString();
	result=combineStringsWithNewLine(result, "End Date: ");
	result+= t.getEnd().getDateTimeString();
	return result;
}

/*
* Purpose:Retrieves status of task
*
* Param: status - true - done; false - pending
*
* Returns: string with status of task
*/
string Processor::printStatus(bool status){
	if(status){
		return "done";
	}else{
		return "pending";
	}
}

/*
* Purpose:transform the string into lower case
*
* Param: str- string to be transformed
*
* Returns: string with lower case
*/
string Processor::toLowCaseString(string str){
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

/*
* Purpose: trim spaces ahead of the string
*
* Param: str- string to be transformed
*
* Returns: string without spaces
*/
string Processor::removeLeadingSpaces(string str){
	int num=str.find_first_not_of(SPACE);
	return str.substr(num);
}

/*
* Purpose:checks if the char is symbol/numeric
*
* Param: ch - char to be checked
*
* Returns: 1 - symbol; 0 - numeric; -1 - others
*/
int Processor::characterType(char ch){
	if (ch==DOT || ch==BACK_SLASH || ch==SLASH || ch==COLON || ch==DASH){
		return 1;
	}else if(ch>=ZERO && ch<=NINE){
		return 0;
	}else{
		return -1;
	}
}

/*
* Purpose: combines the status message of adding task to task
*(for display and search)
*
* Param: str- status message
*
* Returns: formatted status message of adding task
*/
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
