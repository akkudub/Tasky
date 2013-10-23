#include <assert.h>
#include "Processor.h"

const char Processor::SLASH = '/';
const char Processor::BACK_SLASH = '\\';
const char Processor::DOT = '.';
const char Processor::COLON = ':';
const char Processor::DASH = '-';
const char Processor::ZERO = '0';
const char Processor::NINE = '9';
const char Processor::SPACE = ' ';
const char Processor::NEW_LINE = '\n';

const string Processor::EMPTY_STRING = "";
const string Processor::NEW_LINE_STRING = "\n";

Processor::Processor(){
	_statusFlag=0;
	loadFile();
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
int Processor::UImainProcessor(string input, string& message, vector<string>& list){
	string command, tempCommand;
	int returnCode = STATUS_CODE_SET_OVERALL::OVERALL_EXIT;
	assert(_statusFlag >= 0 && _statusFlag < 5);
	if (_statusFlag == 0){
		command = _interpreter.toLowerCase(getCommand(input));
	}else{
		command = input;
	}
	if (isEscape(command)){
		_statusFlag = 0;
	}
	if (command != "exit"){
		switch (_statusFlag){
		case 0:
			if(command == "add"){
				returnCode = addCommandProcessor(input);
			}else if(command == "remove"){
				returnCode = removeCommandProcessor(input);
			}else if(command == "display"){
				returnCode = displayCommandProcessor(input);
			}else if(command == "rename"){
				returnCode = renameCommandProcessor(input);
			}else if(command == "reschedule"){
				returnCode = rescheduleCommandProcessor(input);
			}else if(command == "mark"){
				returnCode = markCommandProcessor(input);
			}else if(command == "search"){
				returnCode = searchCommandProcessor(input);
			}else if(command == "undo"){
				returnCode = undoCommandProcessor(input);
			}else if(command == "redo"){
				returnCode = redoCommandProcessor(input);
			}else{
				returnCode = otherCommandProcessor();
			}
			break;

		case 1:
			returnCode = removeCommandProcessor(input);
			break;
		case 2:
			returnCode = renameCommandProcessor(input);
			break;
		case 3:
			returnCode = rescheduleCommandProcessor(input);
			break;
		case 4:
			returnCode = markCommandProcessor(input);
			break;
		default:
			break;
		}
	}

	return feedbackToUI(returnCode, message, list);
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
int Processor::addCommandProcessor(string input){
	int type;
	string title, comment;
	BasicDateTime startingDateTime;
	BasicDateTime endingDateTime;

	_interpreter.interpretAdd(input, title, type, startingDateTime, endingDateTime, comment);

	switch (type){
	case 0:
		return addFloatingTask(title, comment);
		break;
	case 1:
		return addDeadlineTask(title, endingDateTime, comment);
		break;
	case 2:
		return addNormalTask(title, startingDateTime, endingDateTime, comment);
		break;
	default:
		return ERROR_ADD;
	}
}

/*
* Purpose: Remove task (from search results)
*
* Returns: 
* Task successfully removed; Ask user to choose task to remove; No such task found
*/
int Processor::removeCommandProcessor(string input){
	int operationStatus;
	Task oldTask;
	vector<Task> removedTasks;
	if(_statusFlag == 1){
		vector<int> choice = _interpreter.stringToIntVec(input);
		if(choiceIsValid(choice)){
			for (unsigned int i = 0; i < choice.size(); i++){
				operationStatus=_taskList.remove(_tempTaskList[choice[i]-1]);
				if (operationStatus != STATUS_CODE_SET_ERROR::ERROR_REMOVE)	{
					recordCommand(COMMAND_TYPES::REMOVE, _tempTaskList[choice[i]-1], oldTask);
					removedTasks.push_back(_tempTaskList[choice[i]-1]);
				}
			}
		}
		_tempTaskList = removedTasks;
		_statusFlag = 0;
		return operationStatus;
	}else if(_statusFlag == 0){
		vector<string> keywords;
		_interpreter.interpretRemove(input, _tempTitle);
		_tempTaskList.clear();
		breakIntoStringVectorBySpace(_tempTitle, keywords);
		_taskList.searchKeywords(keywords, _tempTaskList);
		if (_tempTaskList.size() == 1){
			operationStatus = _taskList.remove(_tempTaskList[0]);
			if (operationStatus != STATUS_CODE_SET_ERROR::ERROR_REMOVE)	{
				recordCommand(COMMAND_TYPES::REMOVE, _tempTaskList[0], oldTask);
			}
			return operationStatus;
		}else if(!_tempTaskList.empty()){
			_statusFlag = 1;
			return PROMPT_REMOVE_CHOOSE;
		}else if(_tempTaskList.empty()){
			return WARNING_SEARCH_NO_RESULT;

		}
	}
	return ERROR_REMOVE;
}

/*
* Purpose: Display to user type of task
*
* Returns: 
* Tasks of type; Unable to display
*/
int Processor::displayCommandProcessor(string input){
	string user_command;
	BasicDateTime start, end;
	bool status;
	int type;
	int return_code = _interpreter.interpretDisplay(input, type, start, end, status);
	if (type == 0){
		return _taskList.displayAll(_tempTaskList);
	}else if(type == 2){
		return ERROR_DISPLAY;//needs to be removed later
	}else if (type == 3){//no api in taskList, skipping the dates
		return _taskList.displayStatus(status, _tempTaskList);
	}else{
		return ERROR_DISPLAY;
	}

}

//pass the created task and the task in the vector at position
//create a new vector and pass in that for new clashes
int Processor::renameCommandProcessor(string input){
	int operationStatus;
	if(_statusFlag == 2){
		unsigned int choice = _interpreter.stringToInt(input);
		if((choice <=_tempTaskList.size()) && choice > 0){
			string title, comment;
			BasicDateTime startingDateTime;
			BasicDateTime endingDateTime;
			Task newTask = _tempTaskList[choice-1];
			Task oldTask = newTask;

			newTask.setTitle(_tempTitle);
			operationStatus = _taskList.update(oldTask, newTask, _tempTaskList);

			if (operationStatus != STATUS_CODE_SET_WARNING::WARNING_UPDATE_CLASH){
				_tempTaskList.push_back(oldTask);
				_tempTaskList.push_back(newTask);
			}
			if (operationStatus != STATUS_CODE_SET_ERROR::ERROR_UPDATE){
				recordCommand(COMMAND_TYPES::UPDATE, oldTask, newTask);
			}			
		}

		_statusFlag = 0;
		return operationStatus;

	}else if(_statusFlag == 0){
		string oldTitle;
		vector<string> keywords;

		_interpreter.interpretRename(input, oldTitle, _tempTitle);
		_tempTaskList.clear();
		breakIntoStringVectorBySpace(oldTitle, keywords);
		_taskList.searchKeywords(keywords, _tempTaskList);
		if (_tempTaskList.size() == 1){
			Task newTask = _tempTaskList[0];
			Task oldTask = newTask;
			newTask.setTitle(_tempTitle);
			operationStatus = _taskList.update(oldTask, newTask, _tempTaskList);
			if (operationStatus != STATUS_CODE_SET_WARNING::WARNING_UPDATE_CLASH){
				_tempTaskList.push_back(oldTask);				
				_tempTaskList.push_back(newTask);
			}
			if (operationStatus != STATUS_CODE_SET_ERROR::ERROR_UPDATE){
				recordCommand(COMMAND_TYPES::UPDATE, oldTask, newTask);
			}
			return operationStatus;

		}else if(!_tempTaskList.empty()){
			_statusFlag = 2;
			return PROMPT_RENAME_CHOOSE;
		}else if(_tempTaskList.empty()){
			return WARNING_SEARCH_NO_RESULT;
		}
	}
	return ERROR_UPDATE;
}

int Processor::rescheduleCommandProcessor(string input){
	int operationStatus;
	if(_statusFlag == 3){
		unsigned int choice = _interpreter.stringToInt(input);
		if((choice <=_tempTaskList.size()) && choice > 0){
			string title, comment;
			BasicDateTime startingDateTime;
			BasicDateTime endingDateTime;
			Task newTask = _tempTaskList[choice-1];
			Task oldTask = newTask;

			newTask.setStartDate(_tempStart);
			newTask.setEndDate(_tempEnd);
			newTask.setType(_tempType);
			operationStatus = _taskList.update(oldTask, newTask, _tempTaskList);
			if (operationStatus != STATUS_CODE_SET_WARNING::WARNING_UPDATE_CLASH){
				_tempTaskList.push_back(oldTask);
				_tempTaskList.push_back(newTask);
			}
			if (operationStatus != STATUS_CODE_SET_ERROR::ERROR_UPDATE){
				recordCommand(COMMAND_TYPES::UPDATE, oldTask, newTask);
			}
		}

		_statusFlag = 0;
		return operationStatus;

	}else if(_statusFlag == 0){
		vector<string> keywords;

		_interpreter.interpretReschedule(input, _tempTitle, _tempType, _tempStart, _tempEnd);
		_tempTaskList.clear();
		breakIntoStringVectorBySpace(_tempTitle, keywords);
		_taskList.searchKeywords(keywords, _tempTaskList);

		if (_tempTaskList.size() == 1){
			Task newTask = _tempTaskList[0];
			Task oldTask = newTask;

			newTask.setStartDate(_tempStart);
			newTask.setEndDate(_tempEnd);
			newTask.setType(_tempType);
			operationStatus = _taskList.update(oldTask, newTask, _tempTaskList);
			if (operationStatus != STATUS_CODE_SET_WARNING::WARNING_UPDATE_CLASH){
				_tempTaskList.push_back(oldTask);
				_tempTaskList.push_back(newTask);
			}
			if (operationStatus != STATUS_CODE_SET_ERROR::ERROR_UPDATE){
				recordCommand(COMMAND_TYPES::UPDATE, oldTask, newTask);
			}
			return operationStatus;

		}else if(!_tempTaskList.empty()){
			_statusFlag = 3;
			return PROMPT_RESCHEDULE_CHOOSE;
		}else if(_tempTaskList.empty()){
			return WARNING_SEARCH_NO_RESULT;

		}
	}
	return ERROR_UPDATE;
}

/*
* Purpose: Mark Task as Done/Pending (from search results)
*
* Returns: 
* Task is marked; Ask user to choose task to mark from results; No such task found
*/
int Processor::markCommandProcessor(string input){
	int operationStatus;
	if(_statusFlag == 4){
		vector<Task> markedTasks;
		vector<int> choice = _interpreter.stringToIntVec(input);

		if(choiceIsValid(choice)){
			for (unsigned int i = 0; i < choice.size(); i++){
				operationStatus=_taskList.mark(_tempStatus, _tempTaskList[choice[i]-1]);
				if (operationStatus != STATUS_CODE_SET_ERROR::ERROR_MARK){
					Task oldTask = _tempTaskList[choice[i]-1];
					Task newTask = oldTask;
					if(newTask.getDone() != _tempStatus){
						newTask.toggleDone();
					}
					markedTasks.push_back(newTask);
					recordCommand(COMMAND_TYPES::UPDATE, oldTask, newTask);
				}
			}
		}
		_tempTaskList = markedTasks;
		_statusFlag = 0;
		return operationStatus;
	}else if(_statusFlag == 0){
		vector<string> keywords;

		_interpreter.interpretMark(input, _tempTitle, _tempStatus);
		_tempTaskList.clear();
		breakIntoStringVectorBySpace(_tempTitle, keywords);
		_taskList.searchKeywords(keywords, _tempTaskList);
		if (_tempTaskList.size() == 1){
			operationStatus = _taskList.mark(_tempStatus, _tempTaskList[0]);
			if (operationStatus != STATUS_CODE_SET_ERROR::ERROR_MARK){
				Task oldTask = _tempTaskList[0];
				Task newTask = oldTask;
				if(newTask.getDone() != _tempStatus){
					newTask.toggleDone();
				}
				recordCommand(COMMAND_TYPES::UPDATE, oldTask, newTask);				
			}
		}else if(!_tempTaskList.empty()){
			_statusFlag = 4;
			return PROMPT_MARK_CHOOSE;
		}else if(_tempTaskList.empty()){
			return WARNING_SEARCH_NO_RESULT;
		}
	}
	return ERROR_MARK;
}


int Processor::searchCommandProcessor(string input){
	vector<string> keywords;
	BasicDateTime start, end;
	int type;

	_tempTaskList.clear();

	int return_code = _interpreter.interpretSearch(input, keywords, type, start, end);

	if (type == 0){
		return _taskList.searchKeywords(keywords, _tempTaskList);
	}else if(type == 2){
		return _taskList.searchKeywordsInRange(keywords, _tempTaskList, start, end);
	}else{
		return ERROR_SEARCH;
	}
}


int Processor::undoCommandProcessor(string input){
	Task oldTask, newTask;
	COMMAND_TYPES type = COMMAND_TYPES::ADD;//Just for initialization
	int addResult;
	HistoryCommand command(type, oldTask, newTask);
	int returnCode = _history.undo(command);
	_tempTaskList.clear();
	if (returnCode != STATUS_CODE_SET_ERROR::ERROR_UNDO){
		switch (command.getCommandTypeUndo()){
		case COMMAND_TYPES::ADD:
			addResult = _taskList.add(command.getOld(), _tempTaskList);
			if (addResult != STATUS_CODE_SET_WARNING::WARNING_ADD_CLASH){
				_tempTaskList.push_back(command.getOld());
			}
			return addResult;
			break;
		case COMMAND_TYPES::REMOVE:
			_tempTaskList.push_back(command.getNew());
			return _taskList.remove(command.getNew());
			break;
		case COMMAND_TYPES::UPDATE:
			_tempTaskList.push_back(command.getNew());
			_tempTaskList.push_back(command.getOld());
			return _taskList.update(command.getNew(), command.getOld(), _tempTaskList);
		default:
			break;
		}
	}
	return returnCode;
}

int Processor::redoCommandProcessor(string input){
	Task oldTask, newTask;
	COMMAND_TYPES type = COMMAND_TYPES::ADD;//Just for initialization
	int addResult;
	HistoryCommand command(type, oldTask, newTask);
	int returnCode = _history.redo(command);
	_tempTaskList.clear();
	if (returnCode != STATUS_CODE_SET_ERROR::ERROR_UNDO){
		switch (command.getCommandTypeRedo()){
		case COMMAND_TYPES::ADD:
			addResult = _taskList.add(command.getNew(), _tempTaskList);
			if (addResult != STATUS_CODE_SET_WARNING::WARNING_ADD_CLASH){
				_tempTaskList.push_back(command.getNew());
			}
			return addResult;
			break;
		case COMMAND_TYPES::REMOVE:
			_tempTaskList.push_back(command.getOld());
			return _taskList.remove(command.getOld());
			break;
		case COMMAND_TYPES::UPDATE:
			_tempTaskList.push_back(command.getOld());
			_tempTaskList.push_back(command.getNew());
			return _taskList.update(command.getOld(), command.getNew(), _tempTaskList);
		default:
			break;
		}
	}
	return returnCode;
}

int Processor::otherCommandProcessor(){
	_tempTaskList.clear();
	return WARNING_WRONG_INPUT;
}

int Processor::saveFile(){
	vector<Task> allTasks;
	_taskList.displayAll(allTasks);

	vector<string> allTasksString = taskVecToStringVec(allTasks);
	return _fileProcessing.save(allTasksString);
}

int Processor::loadFile(){
	vector<string> stringsFromFile;
	string currStr, tempStr, statusString, typeString;
	int count;

	string title, comment;
	int type;
	bool status;
	BasicDateTime start, end;

	_fileProcessing.load(stringsFromFile);
	for (unsigned int i = 0; i < stringsFromFile.size(); i++){
		currStr = stringsFromFile[i];
		stringstream ss(currStr);
		count = 0;
		while (std::getline(ss, tempStr, NEW_LINE)){
			switch (count){
			case 0:
				typeString = tempStr.substr(6);
				if (typeString == "Floating"){
					type = 0;
				}else if (typeString == "Deadline"){
					type = 1;
				}else if (typeString == "Timed"){
					type = 2;			
				}
				count++;
				break;
			case 1:
				title = tempStr.substr(7);
				count++;
				break;
			case 2:
				statusString = tempStr.substr(8);
				if (statusString == "Done"){
					status = true;
				}else{
					status = false;
				}
				count++;
				break;
			case 3:
				_interpreter.stringToBasicDateTime(tempStr.substr(7), start);
				count++;
				break;
			case 4:
				_interpreter.stringToBasicDateTime(tempStr.substr(5), end);
				break;
			case 5:
				comment = tempStr.substr(9);
			}
		}
		Task tempTask(title, start, end, type, status, comment);
		_taskList.add(tempTask, _tempTaskList);
	}
	return 0;
}

/*
* Purpose: To get feedback to tell user is command is succesful/unsuccessful
*
* Param: 
* returnCode - feedback from commandProcessors
* message - message to be passed to the UI
* list - the list of strings that need to be printed out with the message
*
* Returns: 
* int telling the UI which type of feedback is being given
*/
int Processor::feedbackToUI(int returnCode, string& message, vector<string>& list){
	assert(returnCode>=STATUS_CODE_SET_OVERALL::OVERALL_SUCCESS &&
		returnCode<=STATUS_CODE_SET_PROPMT::PROMPT_MARK_CHOOSE);

	message = _messages.getMessage(returnCode);

	if (returnCode == STATUS_CODE_SET_OVERALL::OVERALL_EXIT){
		message += _messages.getMessage(saveFile());
		list.clear();
		saveFile();
		return STATUS_CODE_SET_OVERALL::OVERALL_EXIT;
	}else if(returnCode == STATUS_CODE_SET_WARNING::WARNING_WRONG_INPUT){
		return STATUS_CODE_SET_OVERALL::OVERALL_WARNING;
	}else{
		list = taskVecToStringVec(_tempTaskList);

		if (returnCode >= SUCCESS_ADD && returnCode < WARNING_ADD_CLASH){
			return STATUS_CODE_SET_OVERALL::OVERALL_SUCCESS;
		}else if (returnCode >= WARNING_ADD_CLASH && returnCode < ERROR_ADD){
			return STATUS_CODE_SET_OVERALL::OVERALL_WARNING;
		}else if (returnCode >= ERROR_ADD && returnCode < PROMPT_REMOVE_CHOOSE){
			return STATUS_CODE_SET_OVERALL::OVERALL_ERROR;
		}else if (returnCode >= PROMPT_REMOVE_CHOOSE && returnCode <= PROMPT_MARK_CHOOSE){
			return STATUS_CODE_SET_OVERALL::OVERALL_PROMPT;
		}else{
			return STATUS_CODE_SET_OVERALL::OVERALL_ERROR;
		}
	}
}

bool Processor::choiceIsValid(vector<int> choice){
	if(choice.empty()){
		return false;
	}else{
		for (unsigned int i = 0; i < choice.size(); i++){
			unsigned int curr_choice = choice[i];
			if(curr_choice>_tempTaskList.size() || curr_choice<1){
				return false;
			}
		}
		return true;
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
	Task tNew, tOld;
	tNew = Task(title, dt1, dt2, 0, false, comment);
	_tempTaskList.clear();
	int statusCode = _taskList.add(tNew, _tempTaskList);
	if (statusCode != STATUS_CODE_SET_WARNING::WARNING_ADD_CLASH){
		_tempTaskList.push_back(tNew);
	}
	if(statusCode != STATUS_CODE_SET_ERROR::ERROR_ADD){
		recordCommand(COMMAND_TYPES::ADD, tOld, tNew);
	}
	return statusCode;
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
	Task tNew, tOld;
	tNew = Task(title, dt1, dt, 1, false, comment);
	_tempTaskList.clear();
	int statusCode = _taskList.add(tNew, _tempTaskList);
	if (statusCode != STATUS_CODE_SET_WARNING::WARNING_ADD_CLASH){
		_tempTaskList.push_back(tNew);
	}

	if(statusCode != STATUS_CODE_SET_ERROR::ERROR_ADD){
		recordCommand(COMMAND_TYPES::ADD, tOld, tNew);
	}
	return statusCode;
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
	Task tNew, tOld;
	tNew = Task(title, dt1, dt2, 2, false, comment);
	_tempTaskList.clear();
	int statusCode = _taskList.add(tNew, _tempTaskList);
	if (statusCode != STATUS_CODE_SET_WARNING::WARNING_ADD_CLASH){
		_tempTaskList.push_back(tNew);
	}

	if(statusCode != STATUS_CODE_SET_ERROR::ERROR_ADD){
		recordCommand(COMMAND_TYPES::ADD, tOld, tNew);
	}
	return statusCode;
}

string Processor::getCommand(string& input){
	stringstream ss(input);
	string tempStr, command;
	string tempOut = "";
	int count = 0;
	bool noSpace = true;
	while (std::getline(ss, tempStr, SPACE)){
		if (count == 0){
			command = tempStr;
		}else{
			tempOut += (SPACE + tempStr);
		}

		count ++;
		noSpace = false;
	}

	if (noSpace){
		return EMPTY_STRING;
	}else{
		input = tempOut;
		return command;
	}
}


bool Processor::isEscape(string command){
	if (_statusFlag != 0 && (commandIsNormal(command))){
		return true;
	}
	else{
		return false;
	}
}

int Processor::recordCommand(COMMAND_TYPES commandType, Task oldTask, Task newTask){
	HistoryCommand tempCommand(commandType, oldTask, newTask);
	return _history.record(tempCommand);
}

/*
* Purpose: Separates the user input word by word into output vector
*
* Param: longStr - user input
*
* Returns: success
*/
int Processor::breakIntoStringVectorBySpace(string longStr, vector<string>& outputVector){
	stringstream ss(longStr);
	string tempStr;
	bool noSpace = true;
	while (std::getline(ss, tempStr, SPACE)){
		outputVector.push_back(tempStr);
		noSpace = false;
	}

	if (noSpace){
		outputVector.push_back(longStr);
	}
	return 0;
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
* Purpose: combines the status message of adding task to task
*(for display and search)
*
* Param: str- status message
*
* Returns: formatted status message of adding task
*/
vector<string> Processor::taskVecToStringVec(vector<Task> taskList){
	vector<string> temp;
	if (!taskList.empty()){
		int size=taskList.size();
		temp.push_back(taskList[0].toString());
		for (int i=1;i<size;i++){
			temp.push_back(taskList[i].toString());
		}
	}
	return temp;
}

bool Processor::commandIsNormal(string command){
	if (command == "exit" || command == "add"
		||command == "remove" || command == "display"
		||command == "rename" ||command == "reschedule"
		||command == "mark" || command == "search"
		||command == "undo" || command == "redo")
	{
		return true;
	}else{
		return false;
	}
}

Processor::~Processor(){
}
