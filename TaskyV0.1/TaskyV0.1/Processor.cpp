#include <assert.h>
#include "Processor.h"

const string Processor::EMPTY_STRING = "";
const string Processor::FROM_KEY_WORD = "from";
const string Processor::TO_KEY_WORD = "to";
const string Processor::BY_KEY_WORD = "by";
const string Processor::NEW_LINE_STRING = "\n";

const string Processor::MESSAGE_ARRAY [] = {
	MESSAGE_OVERALL_SUCCESS,
	MESSAGE_OVERALL_WARNING,
	MESSAGE_OVERALL_ERROR,
	MESSAGE_OVERALL_PROMPT,
	MESSAGE_OVERALL_EXIT,

	MESSAGE_SUCCESS_ADD,
	MESSAGE_SUCCESS_REMOVE,
	MESSAGE_SUCCESS_DISPLAY,
	MESSAGE_SUCCESS_UPDATE,
	MESSAGE_SUCCESS_RESHCEDULE,
	MESSAGE_SUCCESS_MARK,
	MESSAGE_SUCCESS_SEARCH,
	MESSAGE_SUCCESS_LOAD,
	MESSAGE_SUCCESS_SAVE,
	MESSAGE_SUCCESS_UNDO,
	MESSAGE_SUCCESS_REDO,
	MESSAGE_SUCCESS_RECORD,
	MESSAGE_SUCCESS_INTERPRET_ADD,
	MESSAGE_SUCCESS_INTERPRET_REMOVE,
	MESSAGE_SUCCESS_INTERPRET_DISPLAY,
	MESSAGE_SUCCESS_INTERPRET_RENAME,
	MESSAGE_SUCCESS_INTERPRET_RESCHEDULE,	
	MESSAGE_SUCCESS_INTERPRET_MARK,
	MESSAGE_SUCCESS_INTERPRET_SEARCH,

	MESSAGE_WARNING_ADD_CLASH,	
	MESSAGE_WARNING_ADD_DUPLICATE,
	MESSAGE_WARNING_DISPLAY_NO_RESULT,
	MESSAGE_WARNING_UPDATE_SAME,	
	MESSAGE_WARNING_UPDATE_CLASH,
	MESSAGE_WARNING_MARK_NO_CHANGE,
	MESSAGE_WARNING_SEARCH_NO_RESULT,
	MESSAGE_WARNING_UNDO_NO_TASKS,
	MESSAGE_WARNING_LOAD_EMPTY_FILE,	
	MESSAGE_WARNING_INTERPRET_ADD_NO_TITLE,
	MESSAGE_WARNING_WRONG_INPUT,

	MESSAGE_ERROR_ADD,
	MESSAGE_ERROR_REMOVE,
	MESSAGE_ERROR_DISPLAY,
	MESSAGE_ERROR_UPDATE,
	MESSAGE_ERROR_MARK,
	MESSAGE_ERROR_SEARCH,
	MESSAGE_ERROR_UNDO,
	MESSAGE_ERROR_LOAD_OPENFILE,
	MESSAGE_ERROR_SAVE_SAVEFILE,
	MESSAGE_ERROR_RECORD,
	MESSAGE_ERROR_INTERPRET_EMPTY_INPUT,
	MESSAGE_ERROR_INTERPRET_TITLE_FORMAT,
	MESSAGE_ERROR_INTERPRET_DATETIME_FORMAT,
	MESSAGE_ERROR_INTERPRET_MISSING_KEYWORD,
	MESSAGE_ERROR_INTERPRET_ADD,
	MESSAGE_ERROR_INTERPRET_REMOVE,
	MESSAGE_ERROR_INTERPRET_DISPLAY,
	MESSAGE_ERROR_INTERPRET_RENAME,	
	MESSAGE_ERROR_INTERPRET_RESCHEDULE,
	MESSAGE_ERROR_INTERPRET_MARK,
	MESSAGE_ERROR_INTERPRET_SEARCH,

	MESSAGE_PROMPT_REMOVE_CHOOSE,
	MESSAGE_PROMPT_RENAME_CHOOSE,
	MESSAGE_PROMPT_RESCHEDULE_CHOOSE,
	MESSAGE_PROMPT_MARK_CHOOSE,
};

const string Processor::MESSAGE_OVERALL_SUCCESS =		"Success!";
const string Processor::MESSAGE_OVERALL_WARNING =		"Warning!";
const string Processor::MESSAGE_OVERALL_ERROR =			"Error!";
const string Processor::MESSAGE_OVERALL_PROMPT =		"Please enter your choice:";
const string Processor::MESSAGE_OVERALL_EXIT =			"The program will now exit, Goodbye!";

const string Processor::MESSAGE_SUCCESS_ADD =			"Success! Task added";
const string Processor::MESSAGE_SUCCESS_REMOVE =		"Success! Task removed";
const string Processor::MESSAGE_SUCCESS_DISPLAY =		"Success! Tasks displayed";
const string Processor::MESSAGE_SUCCESS_UPDATE =		"Success! Task updated";
const string Processor::MESSAGE_SUCCESS_RESHCEDULE =	"Success! Task rescheduled";
const string Processor::MESSAGE_SUCCESS_MARK =			"Success! Task(s) marked";
const string Processor::MESSAGE_SUCCESS_SEARCH =		"Success! Search successful";
const string Processor::MESSAGE_SUCCESS_LOAD =			"Success! File loaded";
const string Processor::MESSAGE_SUCCESS_SAVE =			"Success! File saved";
const string Processor::MESSAGE_SUCCESS_UNDO =			"Success! Undo successful";
const string Processor::MESSAGE_SUCCESS_REDO =			"Success! Redo successful";
const string Processor::MESSAGE_SUCCESS_RECORD =		"Success! Previous action recorded";
const string Processor::MESSAGE_SUCCESS_INTERPRET_ADD = "Success! Interpreted add";
const string Processor::MESSAGE_SUCCESS_INTERPRET_REMOVE = "Success! Interpreted remove";
const string Processor::MESSAGE_SUCCESS_INTERPRET_DISPLAY = "Success! Interpreted display";
const string Processor::MESSAGE_SUCCESS_INTERPRET_RENAME = "Success! Interpreted rename";
const string Processor::MESSAGE_SUCCESS_INTERPRET_RESCHEDULE = "Success! Interpreted reschedule";
const string Processor::MESSAGE_SUCCESS_INTERPRET_MARK = "Success! Interpreted mark";
const string Processor::MESSAGE_SUCCESS_INTERPRET_SEARCH = "Success! Interpreted search";

const string Processor::MESSAGE_WARNING_ADD_CLASH =		"Warning! Task clashes with existing ones";
const string Processor::MESSAGE_WARNING_ADD_DUPLICATE = "Warning! Task already exists";
const string Processor::MESSAGE_WARNING_DISPLAY_NO_RESULT = "Warning! No tasks match the parameters";
const string Processor::MESSAGE_WARNING_UPDATE_SAME =	"Warning! The new data is the same as the old data";
const string Processor::MESSAGE_WARNING_UPDATE_CLASH =	"Warning! The new data will make the task clash with the following:";
const string Processor::MESSAGE_WARNING_MARK_NO_CHANGE = "Warning! There is no change in the status";
const string Processor::MESSAGE_WARNING_SEARCH_NO_RESULT = "Warning! No such task";
const string Processor::MESSAGE_WARNING_UNDO_NO_TASKS = "Warning! There is nothing to undo";
const string Processor::MESSAGE_WARNING_LOAD_EMPTY_FILE = "Warning! The file being loaded is empty";	
const string Processor::MESSAGE_WARNING_INTERPRET_ADD_NO_TITLE = "Warning! No title interpreted";
const string Processor::MESSAGE_WARNING_WRONG_INPUT =	"Warning! Wrong input";

const string Processor::MESSAGE_ERROR_ADD =				"Error! Unexpected error while adding task";
const string Processor::MESSAGE_ERROR_REMOVE =			"Error! Unexpected error while removing task" ;
const string Processor::MESSAGE_ERROR_DISPLAY =			"Error! Unexpected error while displaying tasks";
const string Processor::MESSAGE_ERROR_UPDATE =		"Error! Unexpected error while rescheduling task";
const string Processor::MESSAGE_ERROR_MARK =			"Error! Unexpected error while marking task(s)";
const string Processor::MESSAGE_ERROR_SEARCH =			"Error! Unexpected error while searching for tasks";
const string Processor::MESSAGE_ERROR_UNDO =			"Error! Unexpected error while adding task";
const string Processor::MESSAGE_ERROR_LOAD_OPENFILE =	"Error! Unexpected error while loading file";
const string Processor::MESSAGE_ERROR_SAVE_SAVEFILE =	"Error! Unexpected error while saving to file";
const string Processor::MESSAGE_ERROR_RECORD =			"Error! Unexpected error while recording task";
const string Processor::MESSAGE_ERROR_INTERPRET_EMPTY_INPUT = "Error! Empty input";
const string Processor::MESSAGE_ERROR_INTERPRET_TITLE_FORMAT = "Error! Invalid title format";
const string Processor::MESSAGE_ERROR_INTERPRET_DATETIME_FORMAT = "Error! Invalid datetime format";
const string Processor::MESSAGE_ERROR_INTERPRET_MISSING_KEYWORD = "Error! Missing Keyword";
const string Processor::MESSAGE_ERROR_INTERPRET_ADD = "Error! Unexpected error while interpreting add";
const string Processor::MESSAGE_ERROR_INTERPRET_REMOVE = "Error! Unexpected error while interpreting remove";
const string Processor::MESSAGE_ERROR_INTERPRET_DISPLAY = "Error! Unexpected error while interpreting display";
const string Processor::MESSAGE_ERROR_INTERPRET_RENAME = "Error! Unexpected error while interpreting rename";
const string Processor::MESSAGE_ERROR_INTERPRET_RESCHEDULE = "Error! Unexpected error while interpreting reschedule";
const string Processor::MESSAGE_ERROR_INTERPRET_MARK = "Error! Unexpected error while interpreting mark";
const string Processor::MESSAGE_ERROR_INTERPRET_SEARCH = "Error! Unexpected error while interpreting search";

const string Processor::MESSAGE_PROMPT_REMOVE_CHOOSE =	"Enter task number to remove:";
const string Processor::MESSAGE_PROMPT_RENAME_CHOOSE =	"Enter task number to rename:";
const string Processor::MESSAGE_PROMPT_RESCHEDULE_CHOOSE = "Enter task number to reschedule:";
const string Processor::MESSAGE_PROMPT_MARK_CHOOSE =	"Enter task number to mark:";

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
int Processor::UImainProcessor(string input, string& message, vector<string>& list){
	input = _interpreter.toLowerCase(input);
	_wordsList->clear();
	breakIntoStringVectorBySpace(input, *_wordsList);
	string firstWord = _wordsList->at(0);
	int returnCode = STATUS_CODE_SET_OVERALL::OVERALL_EXIT;
	assert(_statusFlag >= 0 && _statusFlag < 5);
	if (firstWord != "exit"){
		switch (_statusFlag){
		case 0:
			if(firstWord == "add"){
				returnCode = addCommandProcessor();
			}else if(firstWord == "remove"){
				returnCode = removeCommandProcessor();
			}else if(firstWord == "display"){
				returnCode = displayCommandProcessor();
			}else if(firstWord == "rename"){
				returnCode = renameCommandProcessor();
			}else if(firstWord == "reschedule"){
				returnCode = rescheduleCommandProcessor();
			}else if(firstWord == "mark"){
				returnCode = markCommandProcessor();
			}else if(firstWord == "search"){
				returnCode = searchCommandProcessor();
			}else{
				returnCode = otherCommandProcessor();
			}
			break;

		case 1:
			returnCode = removeCommandProcessor();
		case 2:
			returnCode = renameCommandProcessor();
		case 3:
			returnCode = rescheduleCommandProcessor();
		case 4:
			returnCode = markCommandProcessor();
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
int Processor::addCommandProcessor(){
	int type;
	string title, comment;
	BasicDateTime startingDateTime;
	BasicDateTime endingDateTime;

	string user_command = combineStringsWithSpaceOnVector(1, _wordsList->size()-1);
	_interpreter.interpretAdd(user_command, title, type, startingDateTime, endingDateTime, comment);

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
int Processor::removeCommandProcessor(){
	int operationStatus;
	if(_statusFlag == 1){
		unsigned int choice = _interpreter.stringToInt(_wordsList->at(1));
		if((choice <=_tempTaskList.size()) && choice > 0){
			operationStatus=_taskList.remove(_tempTaskList[choice-1]);
		}
		_statusFlag = 0;
		return operationStatus;
	}else if(_statusFlag == 0){
		if(_wordsList->size()>1){
			string user_command=combineStringsWithSpaceOnVector(1, _wordsList->size()-1);
			vector<string> keywords;
			_interpreter.interpretRemove(user_command, _tempTitle);
			_tempTaskList.clear();
			breakIntoStringVectorBySpace(_tempTitle, keywords);
			_taskList.searchKeywords(keywords, _tempTaskList);
			if (_tempTaskList.size() == 1){
				return _taskList.remove(_tempTaskList[0]);

			}else if(!_tempTaskList.empty()){
				_statusFlag = 1;
				return PROMPT_REMOVE_CHOOSE;
			}else if(_tempTaskList.empty()){
				return WARNING_SEARCH_NO_RESULT;
			}
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
int Processor::displayCommandProcessor(){
	string user_command;
	BasicDateTime start, end;
	bool status;
	user_command = combineStringsWithSpaceOnVector(1, _wordsList->size()-1);
	int return_code = _interpreter.interpretDisplay(user_command, start, end, status);
	if (return_code == 0){
		return _taskList.displayAll(_tempTaskList);

	}else if (return_code == 1){
		return _taskList.displayStatus(status, _tempTaskList);

	}else if(return_code == 2){
		return _taskList.displayInRange(start, end, _tempTaskList);

	}else{
		return ERROR_DISPLAY;
	}

}

//pass the created task and the task in the vector at position
//create a new vector and pass in that for new clashes
int Processor::renameCommandProcessor(){
	int operationStatus;
	if(_statusFlag == 2){
		unsigned int choice = _interpreter.stringToInt(_wordsList->at(1));
		if((choice <=_tempTaskList.size()) && choice > 0 && _wordsList->size()==2){
			string title, comment;
			BasicDateTime startingDateTime;
			BasicDateTime endingDateTime;
			Task t = _tempTaskList[choice-1];
			vector<Task> clash;

			t.setTitle(_tempTitle);
			operationStatus = _taskList.update(_tempTaskList[choice-1], t, clash);
			_tempTaskList = clash;
		}

		_statusFlag = 0;
		return operationStatus;

	}else if(_statusFlag == 0){
		if(_wordsList->size()>1){
			string user_command=combineStringsWithSpaceOnVector(1, _wordsList->size()-1);
			string oldTitle;
			vector<string> keywords;
			vector<Task> clash;
			_interpreter.interpretRename(user_command, oldTitle, _tempTitle);
			_tempTaskList.clear();
			breakIntoStringVectorBySpace(oldTitle, keywords);
			_taskList.searchKeywords(keywords, _tempTaskList);
			if (_tempTaskList.size() == 1){
				Task t = _tempTaskList[0];
				t.setTitle(_tempTitle);
				return _taskList.update(_tempTaskList[0], t, clash);

			}else if(!_tempTaskList.empty()){
				_statusFlag = 2;
				return PROMPT_RENAME_CHOOSE;
			}else if(_tempTaskList.empty()){
				return WARNING_SEARCH_NO_RESULT;
			}
		}
	}
	return ERROR_UPDATE;
}

int Processor::rescheduleCommandProcessor(){
	int operationStatus;
	if(_statusFlag == 3){
		unsigned int choice = _interpreter.stringToInt(_wordsList->at(1));
		if((choice <=_tempTaskList.size()) && choice > 0 && _wordsList->size()==2){
			string title, comment;
			BasicDateTime startingDateTime;
			BasicDateTime endingDateTime;
			Task t = _tempTaskList[choice-1];
			vector<Task> clash;

			t.setStartDate(_tempStart);
			t.setEndDate(_tempEnd);
			t.setType(_tempType);
			operationStatus = _taskList.update(_tempTaskList[choice-1], t, clash);
			_tempTaskList = clash;
		}

		_statusFlag = 0;
		return operationStatus;

	}else if(_statusFlag == 0){
		if(_wordsList->size()>1){
			vector<string> keywords;
			string user_command=combineStringsWithSpaceOnVector(1, _wordsList->size()-1);

			//problem in extractDateTimeForReschdule, pos2+4 should be pos2+7
			_interpreter.interpretReschedule(user_command, _tempTitle, _tempType, _tempStart, _tempEnd);
			_tempTaskList.clear();
			breakIntoStringVectorBySpace(_tempTitle, keywords);
			_taskList.searchKeywords(keywords, _tempTaskList);

			if (_tempTaskList.size() == 1){
				Task t = _tempTaskList[0];
				vector<Task> clash;
				t.setStartDate(_tempStart);
				t.setEndDate(_tempEnd);
				t.setType(_tempType);
				return _taskList.update(_tempTaskList[0], t, clash);

			}else if(!_tempTaskList.empty()){
				_statusFlag = 3;
				return PROMPT_RESCHEDULE_CHOOSE;
			}else if(_tempTaskList.empty()){
				return WARNING_SEARCH_NO_RESULT;
			}
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
int Processor::markCommandProcessor(){
	int operationStatus;
	if(_statusFlag == 4){
		//stringtointvec doenst seem to be working
		vector<int> choice = _interpreter.stringToIntVec(_wordsList->at(1));

		if(choiceIsValid(choice)){
			for (unsigned int i = 0; i < choice.size(); i++){
				operationStatus=_taskList.mark(_tempStatus, _tempTaskList[choice[i]]);
			}
		}
		_statusFlag = 0;
		return operationStatus;
	}else if(_statusFlag == 0){
		if(_wordsList->size()>1){
			vector<string> keywords;
			string user_command=combineStringsWithSpaceOnVector(1, _wordsList->size()-1);
			_interpreter.interpretMark(user_command, _tempTitle, _tempStatus);
			_tempTaskList.clear();
			breakIntoStringVectorBySpace(_tempTitle, keywords);
			_taskList.searchKeywords(keywords, _tempTaskList);
			if (_tempTaskList.size() == 1){
				return _taskList.mark(_tempStatus, _tempTaskList[0]);
			}	
			else if(!_tempTaskList.empty()){
				_statusFlag = 4;
				return PROMPT_MARK_CHOOSE;
			}else if(_tempTaskList.empty()){
				return WARNING_SEARCH_NO_RESULT;
			}
		}
	}
	return ERROR_MARK;
}


int Processor::searchCommandProcessor(){
	vector<string> keywords;
	string user_command;
	BasicDateTime start, end;

	user_command = combineStringsWithSpaceOnVector(1, _wordsList->size()-1);
	_tempTaskList.clear();
	breakIntoStringVectorBySpace(_tempTitle, keywords);
	int return_code = _interpreter.interpretSearch(user_command, keywords, start, end);

	if (return_code == 0){
		return _taskList.searchKeywords(keywords, _tempTaskList);

	}else if(return_code == 2){
		return _taskList.searchKeywordsInRange(keywords, _tempTaskList, start, end);

	}else{
		return ERROR_SEARCH;
	}
}


int Processor::otherCommandProcessor(){
	return WARNING_WRONG_INPUT;
}

int Processor::saveFile(){
	vector<Task> allTasks;
	vector<string> allTasksString;
	_taskList.displayAll(allTasks);
	for (unsigned int i = 0; i < allTasks.size(); i++){
		allTasksString.push_back(taskToString(allTasks[i]));
	}
	return _fileProcessing.save(allTasksString);
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

	message = MESSAGE_ARRAY[returnCode];
	if (returnCode == STATUS_CODE_SET_OVERALL::OVERALL_EXIT){
		message += MESSAGE_ARRAY[saveFile()];
		list.clear();
		saveFile();
		return STATUS_CODE_SET_OVERALL::OVERALL_EXIT;
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
			if(curr_choice>=_tempTaskList.size() || choice[i]<1){
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
	Task t;
	t = Task(title, dt1, dt2, 2, false, comment);
	_tempTaskList.clear();
	return _taskList.add(t, _tempTaskList);
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
	return _taskList.add(t, _tempTaskList);
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
	return _taskList.add(t, _tempTaskList);
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
		return EMPTY_STRING;
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
* Purpose: combines the status message of adding task to task
*(for display and search)
*
* Param: str- status message
*
* Returns: formatted status message of adding task
*/
vector<string> Processor::taskVecToStringVec(vector<Task> taskList){
	vector<string> temp;
	int size=_tempTaskList.size();
	temp.push_back(taskToString(_tempTaskList.at(0)));
	for (int i=1;i<size;i++){
		temp.push_back(taskToString(_tempTaskList.at(i)));
	}
	return temp;
}

Processor::~Processor(){
	delete _wordsList;
}
