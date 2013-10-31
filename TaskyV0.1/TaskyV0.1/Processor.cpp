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
const string Processor::TASK_DESCRIPTION = "Task Description:";
const string Processor::CLASHES = "Clashes:";
const string Processor::TASKS_REMOVED = "Tasks removed:";
const string Processor::TASKS_REMOVING_ERROR = "Tasks removing error:";
const string Processor::TASK_RENAMED = "Task renamed:";
const string Processor::TASK_RENAME_ERROR = "Tasks renaming error:";
const string Processor::TASK_RESCHEDULED = "Task rescheduled:";
const string Processor::TASK_RESCHEDULED_ERROR = "Tasks rescheduling error:";
const string Processor::TASKS_MARKED = "Tasks marked:";
const string Processor::TASKS_MARKING_ERROR = "Tasks marking error:";
const string Processor::UNDO_TASK_ADDED = "Undo Tasks added:";
const string Processor::UNDO_TASK_ADDING_ERROR = "Undo tasks adding error:";
const string Processor::UNDO_TASK_REMOVED = "Undo Tasks removed:";
const string Processor::UNDO_TASK_REMOVING_ERROR = "Undo Tasks removing error";
const string Processor::UNDO_TASK_UPDATED = "Undo Tasks updated:";
const string Processor::UNDO_TASK_UPDATING_ERROR = "Undo Tasks updating error:";

Processor::Processor(){
	_statusFlag=0;
	loadFile();
}

Processor::~Processor(){
}

int Processor::UImainProcessor(string input, string& message, vector<string>& list){
	string command, tempCommand;
	int returnCode = STATUS_CODE_SET_OVERALL::OVERALL_EXIT;
	_tempStringList.clear();
	assert(_statusFlag >= 0 && _statusFlag < 5);
	command = _interpreter.toLowerCase(getCommand(input));

	if (_statusFlag != 0){
		if (commandIsNormal(command)){
			_statusFlag = 0;
			_tempTaskList.clear();
		}else{
			input = command+input;
		}
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


int Processor::addCommandProcessor(string input){
	int type;
	string title, comment;
	BasicDateTime startingDateTime;
	BasicDateTime endingDateTime;
	_tempTaskList.clear();
	_tempStringList.clear();

	int returnCode = _interpreter.interpretAdd(input, title, type, startingDateTime, endingDateTime, comment);
	if (returnCode != STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_ADD){
		return returnCode;
	}else{
		switch (type){
		case 0:
			return addFloatingTask(title, comment);
			break;
		case 1:
			return addDeadlineTask(title, endingDateTime, comment);
			break;
		case 2:
			return addTimedTask(title, startingDateTime, endingDateTime, comment);
			break;
		default:
			return ERROR_ADD;
		}
	}
}


int Processor::removeCommandProcessor(string input){
	int returnCode;
	Task oldTask;
	vector<Task> removedTasks;
	vector<Task> errorTasks;
	if(_statusFlag == 1){
		vector<int> choice = _interpreter.stringToIntVec(input);
		if(choiceIsValid(choice)){
			for (unsigned int i = 0; i < choice.size(); i++){
				returnCode=_taskList.remove(_tempTaskList[choice[i]-1]);
				if (returnCode != STATUS_CODE_SET_ERROR::ERROR_REMOVE)	{
					recordCommand(COMMAND_TYPES::REMOVE, _tempTaskList[choice[i]-1], oldTask);
					removedTasks.push_back(_tempTaskList[choice[i]-1]);
				}else{
					errorTasks.push_back(_tempTaskList[choice[i]-1]);
				}
			}
		}
		_tempStringList.push_back(TASKS_REMOVED);
		taskVecToStringVec(removedTasks, _tempStringList);
		_tempStringList.push_back(TASKS_REMOVING_ERROR);
		taskVecToStringVec(errorTasks, _tempStringList);

		_tempTaskList.clear();
		_statusFlag = 0;
		return returnCode;
	}else if(_statusFlag == 0){
		_tempTaskList.clear();
		_tempStringList.clear();
		returnCode = _interpreter.interpretRemove(input, _tempTitle);
		if (returnCode != STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_REMOVE){
			return returnCode;
		}else{
			_taskList.search(_tempTitle, _tempTaskList);
			if (_tempTaskList.size() == 1){
				returnCode = _taskList.remove(_tempTaskList[0]);
				if (returnCode != STATUS_CODE_SET_ERROR::ERROR_REMOVE)	{
					recordCommand(COMMAND_TYPES::REMOVE, _tempTaskList[0], oldTask);
					_tempStringList.push_back(TASKS_REMOVED);
				}else{
					_tempStringList.push_back(TASKS_REMOVING_ERROR);
				}
				_tempStringList.push_back(_tempTaskList[0].toString());
				_tempTaskList.clear();
				return returnCode;
			}else if(!_tempTaskList.empty()){
				_statusFlag = 1;
				taskVecToStringVec(_tempTaskList, _tempStringList);
				return PROMPT_REMOVE_CHOOSE;
			}else if(_tempTaskList.empty()){
				return WARNING_SEARCH_NO_RESULT;

			}
		}
	}
	return ERROR_REMOVE;
}


int Processor::displayCommandProcessor(string input){
	bool done = true;
	bool pending = false;
	int type;
	int returnCode = _interpreter.interpretDisplay(input, type);

	_tempTaskList.clear();
	_tempStringList.clear();

	if (returnCode != STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_DISPLAY){
		return returnCode;
	}else{
		switch (type){
		case 0:
			returnCode = _taskList.displayAll(_tempTaskList);
			break;
		case 1:
			returnCode = _taskList.displayStatus(pending, _tempTaskList);
			break;
		case 2:
			returnCode = _taskList.displayStatus(done, _tempTaskList);
			break;
		case 3:
			returnCode = _taskList.displayToday(_tempTaskList);
			break;
		default:
			returnCode = STATUS_CODE_SET_ERROR::ERROR_DISPLAY;
			break;
		}
	}
	taskVecToStringVec(_tempTaskList, _tempStringList);
	_tempTaskList.clear();
	return returnCode;
}

int Processor::renameCommandProcessor(string input){
	int returnCode;
	if(_statusFlag == 2){
		unsigned int choice = _interpreter.stringToInt(input);
		if((choice <=_tempTaskList.size()) && choice > 0){
			string title, comment;
			BasicDateTime startingDateTime;
			BasicDateTime endingDateTime;
			Task newTask = _tempTaskList[choice-1];
			Task oldTask = newTask;

			newTask.setTitle(_tempTitle);
			returnCode = _taskList.update(oldTask, newTask, _tempTaskList);

			if (returnCode != STATUS_CODE_SET_ERROR::ERROR_UPDATE){
				recordCommand(COMMAND_TYPES::UPDATE, oldTask, newTask);
				_tempStringList.push_back(TASK_RENAMED);
			}else{
				_tempStringList.push_back(TASK_RENAME_ERROR);
			}
			_tempStringList.push_back(oldTask.toString());
			_tempStringList.push_back(newTask.toString());
			if (returnCode == STATUS_CODE_SET_WARNING::WARNING_UPDATE_CLASH){
				_tempStringList.push_back(CLASHES);
				taskVecToStringVec(_tempTaskList,  _tempStringList);
			}
		}
		_tempTaskList.clear();
		_statusFlag = 0;
		return returnCode;

	}else if(_statusFlag == 0){
		string oldTitle;
		_tempTaskList.clear();
		_tempStringList.clear();

		returnCode = _interpreter.interpretRename(input, oldTitle, _tempTitle);
		if (returnCode != STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_RENAME){
			return returnCode;
		}else{
			_taskList.search(oldTitle, _tempTaskList);
			if (_tempTaskList.size() == 1){
				Task newTask = _tempTaskList[0];
				Task oldTask = newTask;
				newTask.setTitle(_tempTitle);
				returnCode = _taskList.update(oldTask, newTask, _tempTaskList);

				if (returnCode != STATUS_CODE_SET_ERROR::ERROR_UPDATE){
					recordCommand(COMMAND_TYPES::UPDATE, oldTask, newTask);
					_tempStringList.push_back(TASK_RENAMED);
				}else{
					_tempStringList.push_back(TASK_RENAME_ERROR);
				}
				_tempStringList.push_back(oldTask.toString());
				_tempStringList.push_back(newTask.toString());
				if (returnCode == STATUS_CODE_SET_WARNING::WARNING_UPDATE_CLASH){
					_tempStringList.push_back(CLASHES);
					taskVecToStringVec(_tempTaskList,  _tempStringList);
				}
				_tempTaskList.clear();
				return returnCode;

			}else if(!_tempTaskList.empty()){
				taskVecToStringVec(_tempTaskList, _tempStringList);
				_statusFlag = 2;
				return PROMPT_RENAME_CHOOSE;
			}else if(_tempTaskList.empty()){
				return WARNING_SEARCH_NO_RESULT;
			}
		}
	}
	return ERROR_UPDATE;
}

int Processor::rescheduleCommandProcessor(string input){
	int returnCode;
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
			returnCode = _taskList.update(oldTask, newTask, _tempTaskList);

			if (returnCode != STATUS_CODE_SET_ERROR::ERROR_UPDATE){
				recordCommand(COMMAND_TYPES::UPDATE, oldTask, newTask);
				_tempStringList.push_back(TASK_RESCHEDULED);
			}else{
				_tempStringList.push_back(TASK_RESCHEDULED_ERROR);
			}
			_tempStringList.push_back(oldTask.toString());
			_tempStringList.push_back(newTask.toString());
			if (returnCode == STATUS_CODE_SET_WARNING::WARNING_UPDATE_CLASH){
				_tempStringList.push_back(CLASHES);
				taskVecToStringVec(_tempTaskList,  _tempStringList);
			}
		}
		_tempTaskList.clear();
		_statusFlag = 0;
		return returnCode;

	}else if(_statusFlag == 0){
		_tempTaskList.clear();
		_tempStringList.clear();
		returnCode = _interpreter.interpretReschedule(input, _tempTitle, _tempType, _tempStart, _tempEnd);
		if (returnCode != STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_RESCHEDULE){
			return returnCode;
		}else{
			_taskList.search(_tempTitle, _tempTaskList);

			if (_tempTaskList.size() == 1){
				Task newTask = _tempTaskList[0];
				Task oldTask = newTask;

				newTask.setStartDate(_tempStart);
				newTask.setEndDate(_tempEnd);
				newTask.setType(_tempType);
				returnCode = _taskList.update(oldTask, newTask, _tempTaskList);
				if (returnCode != STATUS_CODE_SET_ERROR::ERROR_UPDATE){
					recordCommand(COMMAND_TYPES::UPDATE, oldTask, newTask);
					_tempStringList.push_back(TASK_RESCHEDULED);
				}else{
					_tempStringList.push_back(TASK_RESCHEDULED_ERROR);
				}
				_tempStringList.push_back(oldTask.toString());
				_tempStringList.push_back(newTask.toString());
				if (returnCode == STATUS_CODE_SET_WARNING::WARNING_UPDATE_CLASH){
					_tempStringList.push_back(CLASHES);
					taskVecToStringVec(_tempTaskList,  _tempStringList);
				}
				_tempTaskList.clear();
				return returnCode;

			}else if(!_tempTaskList.empty()){
				taskVecToStringVec(_tempTaskList, _tempStringList);
				_statusFlag = 3;
				return PROMPT_RESCHEDULE_CHOOSE;
			}else if(_tempTaskList.empty()){
				return WARNING_SEARCH_NO_RESULT;

			}
		}
	}
	return ERROR_UPDATE;
}


int Processor::markCommandProcessor(string input){
	int returnCode;
	Task newTask;
	Task oldTask;
	if(_statusFlag == 4){
		vector<Task> markedTasks;
		vector<Task> errorTasks;
		vector<int> choice = _interpreter.stringToIntVec(input);

		if(choiceIsValid(choice)){
			for (unsigned int i = 0; i < choice.size(); i++){
				returnCode=_taskList.mark(_tempStatus, _tempTaskList[choice[i]-1]);
				if (returnCode != STATUS_CODE_SET_ERROR::ERROR_MARK){
					oldTask = _tempTaskList[choice[i]-1];
					newTask = oldTask;
					if(newTask.getDone() != _tempStatus){
						newTask.toggleDone();
					}
					recordCommand(COMMAND_TYPES::UPDATE, oldTask, newTask);
					markedTasks.push_back(newTask);
				}else{
					errorTasks.push_back(newTask);
				}
			}
		}
		_tempStringList.push_back(TASKS_MARKED);
		taskVecToStringVec(markedTasks, _tempStringList);
		_tempStringList.push_back(TASKS_MARKING_ERROR);
		taskVecToStringVec(errorTasks, _tempStringList);

		_tempTaskList.clear();
		_statusFlag = 0;
		return returnCode;
	}else if(_statusFlag == 0){
		_tempTaskList.clear();
		_tempStringList.clear();
		returnCode = _interpreter.interpretMark(input, _tempTitle, _tempStatus);
		if (returnCode != STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_MARK){
			return returnCode;
		}else{
			_taskList.search(_tempTitle, _tempTaskList);
			if (_tempTaskList.size() == 1){
				returnCode = _taskList.mark(_tempStatus, _tempTaskList[0]);
				if (returnCode != STATUS_CODE_SET_ERROR::ERROR_MARK){
					Task oldTask = _tempTaskList[0];
					Task newTask = oldTask;
					if(newTask.getDone() != _tempStatus){
						newTask.toggleDone();
					}
					recordCommand(COMMAND_TYPES::UPDATE, oldTask, newTask);
					_tempStringList.push_back(TASKS_MARKED);
				}else{
					_tempStringList.push_back(TASKS_MARKING_ERROR);
				}
				_tempStringList.push_back(newTask.toString());
				_tempTaskList.clear();
				return returnCode;
			}else if(!_tempTaskList.empty()){
				taskVecToStringVec(_tempTaskList, _tempStringList);
				_statusFlag = 4;
				return PROMPT_MARK_CHOOSE;
			}else if(_tempTaskList.empty()){
				return WARNING_SEARCH_NO_RESULT;
			}
		}
	}
	return ERROR_MARK;
}


int Processor::searchCommandProcessor(string input){
	vector<string> keywords;
	BasicDateTime start, end;
	int type;

	_tempTaskList.clear();
	_tempStringList.clear();

	int returnCode = _interpreter.interpretSearch(input, keywords, type, start, end);
	if (returnCode != STATUS_CODE_SET_SUCCESS::SUCCESS_INTERPRET_SEARCH){
		return returnCode;
	}else{
		if (type == 0){
			returnCode = _taskList.searchKeywords(keywords, _tempTaskList);
		}else if(type == 2){
			returnCode = _taskList.searchKeywordsInRange(keywords, start, end, _tempTaskList);
		}else{
			returnCode = ERROR_SEARCH;
		}
	}
	taskVecToStringVec(_tempTaskList, _tempStringList);
	_tempTaskList.clear();
	return returnCode;
}


int Processor::undoCommandProcessor(string input){
	Task oldTask, newTask;
	COMMAND_TYPES type = COMMAND_TYPES::ADD;//Just for initialization
	int undoCount, returnCode;
	HistoryCommand command(type, oldTask, newTask);
	undoCount = _interpreter.stringToInt(input);
	_tempTaskList.clear();
	_tempStringList.clear();
	if (undoCount!=0){
		undoCount --;
	}
	for (int i = undoCount; i >=0; i--){
		returnCode = _history.undo(command);	
		if (returnCode != STATUS_CODE_SET_ERROR::ERROR_UNDO){
			switch (command.getCommandTypeUndo()){
			case COMMAND_TYPES::ADD:
				returnCode = _taskList.add(command.getOld(), _tempTaskList);
				if (returnCode != STATUS_CODE_SET_ERROR::ERROR_ADD){
					_tempStringList.push_back(UNDO_TASK_ADDED);
				}else{
					_tempStringList.push_back(UNDO_TASK_ADDING_ERROR);
				}
				_tempStringList.push_back(command.getOld().toString());
				if (returnCode == STATUS_CODE_SET_WARNING::WARNING_ADD_CLASH){
					_tempStringList.push_back(CLASHES);
					taskVecToStringVec(_tempTaskList, _tempStringList);
				}
				break;
			case COMMAND_TYPES::REMOVE:
				returnCode = _taskList.remove(command.getNew());
				if (returnCode != STATUS_CODE_SET_ERROR::ERROR_REMOVE){
					_tempStringList.push_back(UNDO_TASK_REMOVED);
				}else{
					_tempStringList.push_back(UNDO_TASK_REMOVING_ERROR);
				}
				_tempStringList.push_back(command.getNew().toString());
				break;
			case COMMAND_TYPES::UPDATE:
				returnCode = _taskList.update(command.getNew(), command.getOld(), _tempTaskList);
				if (returnCode != STATUS_CODE_SET_ERROR::ERROR_UPDATE){
					_tempStringList.push_back(UNDO_TASK_UPDATED);
				}else{
					_tempStringList.push_back(UNDO_TASK_UPDATING_ERROR);
				}
				_tempStringList.push_back(command.getNew().toString());
				_tempStringList.push_back(command.getOld().toString());
				if (returnCode == STATUS_CODE_SET_WARNING::WARNING_UPDATE_CLASH){
					_tempStringList.push_back(CLASHES);
					taskVecToStringVec(_tempTaskList, _tempStringList);
				}
				break;
			default:
				break;
			}
		}
	}
	_tempTaskList.clear();
	return returnCode;
}

int Processor::redoCommandProcessor(string input){
	_tempTaskList.clear();
	_tempStringList.clear();
	Task oldTask, newTask;
	COMMAND_TYPES type = COMMAND_TYPES::ADD;//Just for initialization
	HistoryCommand command(type, oldTask, newTask);
	int returnCode = _history.redo(command);
	if (returnCode != STATUS_CODE_SET_ERROR::ERROR_REDO){
		switch (command.getCommandTypeRedo()){
		case COMMAND_TYPES::ADD:
			returnCode = _taskList.add(command.getNew(), _tempTaskList);
			if (returnCode != STATUS_CODE_SET_ERROR::ERROR_ADD){
				_tempStringList.push_back(UNDO_TASK_ADDED);
			}else{
				_tempStringList.push_back(UNDO_TASK_ADDING_ERROR);
			}
			_tempStringList.push_back(command.getNew().toString());
			if (returnCode == STATUS_CODE_SET_WARNING::WARNING_ADD_CLASH){
				_tempStringList.push_back(CLASHES);
				taskVecToStringVec(_tempTaskList, _tempStringList);
			}
			break;
		case COMMAND_TYPES::REMOVE:
			returnCode = _taskList.remove(command.getOld());
			if (returnCode != STATUS_CODE_SET_ERROR::ERROR_REMOVE){
				_tempStringList.push_back(UNDO_TASK_REMOVED);
			}else{
				_tempStringList.push_back(UNDO_TASK_REMOVING_ERROR);
			}
			_tempStringList.push_back(command.getOld().toString());
			break;
		case COMMAND_TYPES::UPDATE:
			returnCode = _taskList.update(command.getOld(), command.getNew(), _tempTaskList);
			if (returnCode != STATUS_CODE_SET_ERROR::ERROR_UPDATE){
				_tempStringList.push_back(UNDO_TASK_UPDATED);
			}else{
				_tempStringList.push_back(UNDO_TASK_UPDATING_ERROR);
			}
			_tempStringList.push_back(command.getOld().toString());
			_tempStringList.push_back(command.getNew().toString());
			if (returnCode == STATUS_CODE_SET_WARNING::WARNING_UPDATE_CLASH){
				_tempStringList.push_back(CLASHES);
				taskVecToStringVec(_tempTaskList, _tempStringList);
			}
			break;
		default:
			break;
		}
	}
	_tempTaskList.clear();
	return returnCode;
}

int Processor::otherCommandProcessor(){
	_tempTaskList.clear();
	_tempStringList.clear();
	return WARNING_WRONG_INPUT;
}

int Processor::saveFile(){
	return _taskList.saveFile();
}

int Processor::loadFile(){
	return _taskList.loadFile();
}


int Processor::feedbackToUI(int returnCode, string& message, vector<string>& list){
	assert(returnCode>=STATUS_CODE_SET_OVERALL::OVERALL_SUCCESS &&
		returnCode<=STATUS_CODE_SET_PROPMT::PROMPT_MARK_CHOOSE);

	message = _messages.getMessage(returnCode);

	if (returnCode == STATUS_CODE_SET_OVERALL::OVERALL_EXIT){
		message += NEW_LINE_STRING + _messages.getMessage(saveFile());
		list.clear();
		saveFile();
		return returnCode;
	}else if(returnCode == STATUS_CODE_SET_WARNING::WARNING_WRONG_INPUT){
		return STATUS_CODE_SET_OVERALL::OVERALL_WARNING;
	}else{
		list = _tempStringList;

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


int Processor::addFloatingTask(string title, string comment){
	BasicDateTime start, end;
	Task tNew, tOld;
	tNew = Task(title, start, end, 0, false, comment);
	int statusCode = _taskList.add(tNew, _tempTaskList);

	if(statusCode != STATUS_CODE_SET_ERROR::ERROR_ADD){
		recordCommand(COMMAND_TYPES::ADD, tOld, tNew);
		_tempStringList.push_back(TASK_DESCRIPTION);
		_tempStringList.push_back(tNew.toString());
	}
	if (statusCode == STATUS_CODE_SET_WARNING::WARNING_ADD_CLASH){
		_tempStringList.push_back(CLASHES);
		taskVecToStringVec(_tempTaskList, _tempStringList);
	}
	return statusCode;
}


int Processor::addDeadlineTask(string title, BasicDateTime end, string comment){
	BasicDateTime start;
	Task tNew, tOld;
	tNew = Task(title, start, end, 1, false, comment);

	int statusCode = _taskList.add(tNew, _tempTaskList);
	if(statusCode != STATUS_CODE_SET_ERROR::ERROR_ADD){
		recordCommand(COMMAND_TYPES::ADD, tOld, tNew);
		_tempStringList.push_back(TASK_DESCRIPTION);
		_tempStringList.push_back(tNew.toString());
	}
	if (statusCode == STATUS_CODE_SET_WARNING::WARNING_ADD_CLASH){
		_tempStringList.push_back(CLASHES);
		taskVecToStringVec(_tempTaskList, _tempStringList);
	}
	return statusCode;
}


int Processor::addTimedTask(string title, BasicDateTime start, BasicDateTime end, string comment){
	Task tNew, tOld;
	tNew = Task(title, start, end, 2, false, comment);

	int statusCode = _taskList.add(tNew, _tempTaskList);
	if(statusCode != STATUS_CODE_SET_ERROR::ERROR_ADD){
		recordCommand(COMMAND_TYPES::ADD, tOld, tNew);
		_tempStringList.push_back(TASK_DESCRIPTION);
		_tempStringList.push_back(tNew.toString());
	}
	if (statusCode == STATUS_CODE_SET_WARNING::WARNING_ADD_CLASH){
		_tempStringList.push_back(CLASHES);
		taskVecToStringVec(_tempTaskList, _tempStringList);
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

void Processor::taskVecToStringVec(vector<Task> taskList, vector<string>& stringList){
	if (!taskList.empty()){
		int size=taskList.size();
		for (int i=0;i<size;i++){
			stringList.push_back(taskList[i].toString());
		}
	}
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
