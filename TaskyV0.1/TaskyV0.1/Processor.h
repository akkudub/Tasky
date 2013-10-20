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
#include "Task.h"
#include "BasicDateTime.h"
#include "History.h"
#include "FileProcessing.h"
#include "TaskList.h"
#include "Interpreter.h"
#include "Essential.h"
#include "Messages.h"

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
	Messages _messages;
	int _statusFlag; 

private:

	static const char NEW_LINE;
	static const char SLASH;
	static const char BACK_SLASH;
	static const char DOT;
	static const char COLON;
	static const char DASH;
	static const char ZERO;
	static const char NINE;
	static const char SPACE;

	static const string EMPTY_STRING;
	static const string NEW_LINE_STRING;

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
	bool isEscape(string command);
	int recordCommand(COMMAND_TYPES commandType, Task oldTask, Task newTask);
	int breakIntoStringVectorBySpace(string, vector<string>& outputVector);
	bool choiceIsValid(vector<int> choice);
	string combineStringsWithNewLine(string, string);
	vector<string> taskVecToStringVec(vector<Task> taskList);

	bool commandIsNormal(string command);
};

#endif
