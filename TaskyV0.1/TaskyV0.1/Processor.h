#ifndef _Processor_H_
#define _Processor_H_

/*
*This class is the central controlling unit. It will take string from UI and process it, acknowledge UI
*if input format is not suitable or it will go ahead and extract command out of input string and call methods
*in TaskList/history/FileProcessing to carry out the command.
*
*Main role: string processing, central logic unit, front wall of logic.
*
*Additional notice: this class will take the pointer of the _itemList in TaskList class to ease the cost of
*displaying. But the author of this class will only read from _itemList. This method is more like data-binding
*with only programmers' protection.
*
*Author: Akshat, Junchao
*/

#include <sstream>
#include <iostream>
#include <algorithm>
#include <msclr\marshal_cppstd.h>
#include "Task.h"
#include "BasicDateTime.h"
#include "History.h"
#include "FileProcessing.h"
#include "TaskList.h"
#include "Interpreter.h"
#include "Essential.h"

using namespace System;
using namespace msclr::interop;

class Processor{
	/*
	*_tempTaskList: hold the tasks returned by _taskList.search and _taskList.display
	*_stringList: hold tasks in string format, used to pass to fileProcessing
	*            for it to perform read/write file
	*_taskListPointer: a pointer pointing to _taskList.tasklist. will only read
	*_taskList: an instance of TaskList
	*_history: an instance of History
	*_fileProcessing: an instance of FileProcessing
	*_wordList: a temporary way to help to parse command, will be changed later
	*_statusFlag: 0--last operation ended properly;
	*             1--remove operation has not ended;
	*             2--rename operation has not ended;
	*             3--reschedule operation has not ended;
	*			  4--mark operation has not ended;
	*/
private:
	vector<Task> _tempTaskList; 
	string _tempTitle;
	bool _tempStatus;
	int _tempType;
	BasicDateTime _tempStart;
	BasicDateTime _tempEnd;

	vector<string> _stringList; 
	vector<Task>* _taskListPointer;
	TaskList _taskList;
	History _history;
	Interpreter _interpreter;
	FileProcessing _fileProcessing;
	int _statusFlag; 

private:
	static const string EMPTY_STRING;
	static const string NEW_LINE_STRING;
	static const string FROM_KEY_WORD;
	static const string TO_KEY_WORD;
	static const string BY_KEY_WORD;

	static const int MAX_MESSAGES = 100;
	static const string MESSAGE_ARRAY [MAX_MESSAGES];

	static const string MESSAGE_OVERALL_SUCCESS;
	static const string MESSAGE_OVERALL_WARNING;
	static const string MESSAGE_OVERALL_ERROR;
	static const string MESSAGE_OVERALL_PROMPT;
	static const string MESSAGE_OVERALL_EXIT;

	static const string MESSAGE_SUCCESS_ADD;
	static const string MESSAGE_SUCCESS_REMOVE;
	static const string MESSAGE_SUCCESS_DISPLAY;
	static const string MESSAGE_SUCCESS_UPDATE;
	static const string MESSAGE_SUCCESS_RESHCEDULE;
	static const string MESSAGE_SUCCESS_MARK;
	static const string MESSAGE_SUCCESS_SEARCH;
	static const string MESSAGE_SUCCESS_LOAD;
	static const string MESSAGE_SUCCESS_SAVE;
	static const string MESSAGE_SUCCESS_UNDO;
	static const string MESSAGE_SUCCESS_REDO;
	static const string MESSAGE_SUCCESS_RECORD;
	static const string MESSAGE_SUCCESS_INTERPRET_ADD;
	static const string MESSAGE_SUCCESS_INTERPRET_REMOVE;
	static const string MESSAGE_SUCCESS_INTERPRET_DISPLAY;
	static const string MESSAGE_SUCCESS_INTERPRET_RENAME;
	static const string MESSAGE_SUCCESS_INTERPRET_RESCHEDULE;	
	static const string MESSAGE_SUCCESS_INTERPRET_MARK;
	static const string MESSAGE_SUCCESS_INTERPRET_SEARCH;

	static const string MESSAGE_WARNING_ADD_CLASH;	
	static const string MESSAGE_WARNING_ADD_DUPLICATE;
	static const string MESSAGE_WARNING_DISPLAY_NO_RESULT;
	static const string MESSAGE_WARNING_UPDATE_SAME;	
	static const string MESSAGE_WARNING_UPDATE_CLASH;
	static const string MESSAGE_WARNING_MARK_NO_CHANGE;
	static const string MESSAGE_WARNING_SEARCH_NO_RESULT;
	static const string MESSAGE_WARNING_UNDO_NO_TASKS;
	static const string MESSAGE_WARNING_LOAD_EMPTY_FILE;	
	static const string MESSAGE_WARNING_INTERPRET_ADD_NO_TITLE;
	static const string MESSAGE_WARNING_WRONG_INPUT;

	static const string MESSAGE_ERROR_ADD;
	static const string MESSAGE_ERROR_REMOVE;
	static const string MESSAGE_ERROR_DISPLAY;
	static const string MESSAGE_ERROR_UPDATE;
	static const string MESSAGE_ERROR_MARK;
	static const string MESSAGE_ERROR_SEARCH;
	static const string MESSAGE_ERROR_UNDO;
	static const string MESSAGE_ERROR_LOAD_OPENFILE;
	static const string MESSAGE_ERROR_SAVE_SAVEFILE;
	static const string MESSAGE_ERROR_RECORD;
	static const string MESSAGE_ERROR_INTERPRET_EMPTY_INPUT;
	static const string MESSAGE_ERROR_INTERPRET_TITLE_FORMAT;
	static const string MESSAGE_ERROR_INTERPRET_DATETIME_FORMAT;
	static const string MESSAGE_ERROR_INTERPRET_MISSING_KEYWORD;
	static const string MESSAGE_ERROR_INTERPRET_ADD;
	static const string MESSAGE_ERROR_INTERPRET_REMOVE;
	static const string MESSAGE_ERROR_INTERPRET_DISPLAY;
	static const string MESSAGE_ERROR_INTERPRET_RENAME;	
	static const string MESSAGE_ERROR_INTERPRET_RESCHEDULE;
	static const string MESSAGE_ERROR_INTERPRET_MARK;
	static const string MESSAGE_ERROR_INTERPRET_SEARCH;

	static const string MESSAGE_PROMPT_REMOVE_CHOOSE;
	static const string MESSAGE_PROMPT_RENAME_CHOOSE;
	static const string MESSAGE_PROMPT_RESCHEDULE_CHOOSE;
	static const string MESSAGE_PROMPT_MARK_CHOOSE;

	static const char NEW_LINE;
	static const char SLASH;
	static const char BACK_SLASH;
	static const char DOT;
	static const char COLON;
	static const char DASH;
	static const char ZERO;
	static const char NINE;
	static const char SPACE;

public:
	Processor();
	int UImainProcessor(string input, string& message, vector<string>& list);
	int GUImainProcessor(string);
	~Processor();

private:
	//level 1 abstraction
	int addCommandProcessor(string input);
	int removeCommandProcessor(string input);
	int displayCommandProcessor(string input);
	int renameCommandProcessor(string input);
	int rescheduleCommandProcessor(string input);
	int markCommandProcessor(string input);
	int searchCommandProcessor(string input);
	int undoCommandProcessor(string input);
	int redoCommandProcessor(string input);
	int otherCommandProcessor();
	int saveFile();
	int loadFile();

	int feedbackToUI(int returnCode, string& message, vector<string>& list);

	//for add command processing
	int addFloatingTask(string, string);//need to refactor to only create a task
	int addDeadlineTask(string, BasicDateTime, string);//need to refactor to only create a task
	int addNormalTask(string, BasicDateTime, BasicDateTime, string);//need to refactor to only create a task

	//additional helper methods
	string getCommand(string& input);
	int recordCommand(COMMAND_TYPES commandType, Task oldTask, Task newTask);
	int breakIntoStringVectorBySpace(string, vector<string>& outputVector);
	bool choiceIsValid(vector<int> choice);
	string combineStringsWithNewLine(string, string);
	string taskToString(Task);
	vector<string> taskVecToStringVec(vector<Task> taskList);

	string printFloatingTask(Task);
	string printDeadlineTask(Task);
	string printTimedTask(Task);
	string printStatus(bool);
};

#endif
