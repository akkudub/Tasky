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
	/*
	* Purpose:
	* Handle user input based on first keyword
	* and call appropriate functions to handle the command
	*
	* @param input the raw user input passed in from the UI
	* @param message the feedback message to be passed to the UI
	* @param list the list of tasks to be displayed by the UI
	* @return overall status code
	*/
	int UImainProcessor(string input, string& message, vector<string>& list);
	int GUImainProcessor(string);
	~Processor();

private:
	//level 1 abstraction

	/*
	* Purpose:
	* Handle add commands
	*
	* @param input the input passed in from the main processor without the add keyword
	* @return status code
	*/
	int addCommandProcessor(string input);
	/*
	* Purpose:
	* Handle remove commands
	*
	* @param input the input passed in from the main processor without the remove keyword
	* @return status code
	*/
	int removeCommandProcessor(string input);
	/*
	* Purpose:
	* Handle display commands
	*
	* @param input the input passed in from the main processor without the display keyword
	* @return status code
	*/
	int displayCommandProcessor(string input);
	/*
	* Purpose:
	* Handle rename commands from update
	*
	* @param input the input passed in from the main processor without the update keyword
	* @return status code
	*/
	int renameCommandProcessor(string input);
	/*
	* Purpose:
	* Handle reschedule commands from update
	*
	* @param input the input passed in from the main processor without the update keyword
	* @return status code
	*/
	int rescheduleCommandProcessor(string input);
	/*
	* Purpose:
	* Handle mark commands
	*
	* @param input the input passed in from the main processor without the mark keyword
	* @return status code
	*/
	int markCommandProcessor(string input);
	/*
	* Purpose:
	* Handle search commands
	*
	* @param input the input passed in from the main processor without the search keyword
	* @return status code
	*/
	int searchCommandProcessor(string input);
	/*
	* Purpose:
	* Handle undo commands
	*
	* @param input the input passed in from the main processor without the undo keyword(single undo)
	* @return status code
	*/
	int undoCommandProcessor(string input);
	/*
	* Purpose:
	* Handle redo commands
	*
	* @param input the input passed in from the main processor without the mark keyword(single redo)
	* @return status code
	*/
	int redoCommandProcessor(string input);
	/*
	* Purpose:
	* Handle wrong/invalid commands
	*
	* @param input the input passed in from the main processor
	* @return status code(always WARNING_WRONG_INPUT)
	*/
	int otherCommandProcessor();
	/*
	* Purpose:
	* Handle save command
	*
	* @return status code
	*/
	int saveFile();
	/*
	* Purpose:
	* Handle load command
	*
	* @return status code
	*/
	int loadFile();
	/*
	* Purpose:
	* To return feedback to the user and give the overall status of the operation
	*
	* @param returnCode feedback from commandProcessors
	* @param message message to be passed to the UI
	* @param list the list of strings that need to be printed out with the message
	*
	* @return overall status code
	*/
	int feedbackToUI(int returnCode, string& message, vector<string>& list);

	//for add command processing

	/*
	* Purpose:
	* add Floating tasks, put any clashes in _tempTaskList
	*
	* @param title name of task
	* @param comment additional description
	* @return status code
	*/
	int addFloatingTask(string title, string comment);//need to refactor to only create a task
	/*
	* Purpose:
	* add Deadline tasks, put any clashes in _tempTaskList
	*
	* @param title name of task
	* @param end deadline of task
	* @param comment additional description
	* @return status code
	*/
	int addDeadlineTask(string title, BasicDateTime end, string comment);//need to refactor to only create a task
	/*
	* Purpose:
	* add Timed tasks, put any clashes in _tempTaskList
	*
	* @param title name of task
	* @param srat start time of task
	* @param end end time of task
	* @param comment additional description
	* @return status code
	*/
	int addTimedTask(string title, BasicDateTime start, BasicDateTime end, string comment);//need to refactor to only create a task

	//additional helper methods

	/*
	* Purpose:
	* extract the command out of the raw user input and remove it from the input
	*
	* @param input raw input from UI
	* @return string containing command if command is found, else empty string
	*/
	string getCommand(string& input);
	/*
	* Purpose:
	* checks to see if the user wanted to escape out of a ambiguous situation that required a choice
	*
	* @param command command from the UI
	* @return true if the user wanted to escape, else return false
	*/
	bool isEscape(string command);
	/*
	* Purpose:
	* record command to assist with undo and redo
	*
	* @param commandType the command type that was performed
	* @param oldTask the task that was changed(empty in case of add)
	* @param newTask the task that the old task was changed to(empty in case of remove)
	* @return voi
	*/
	int recordCommand(COMMAND_TYPES commandType, Task oldTask, Task newTask);
	/*
	* Purpose:
	* break a string into a vector of words by space
	*
	* @param longStr the command type that was performed
	* @param outputVector the task that was changed(empty in case of add)
	* @return nothing
	*/
	bool choiceIsValid(vector<int> choice);
	/*
	* Purpose:
	* converts a vector of tasks into a vector of strings
	*
	* @param taskList the vector of the Tasks passed in
	* @return a vector of strings based on the vector of tasks
	*/
	vector<string> taskVecToStringVec(vector<Task> taskList);
	/*
	* Purpose:
	* checks if the command entered is one of the acceptable commands
	*
	* @param command the command that needs to be checked
	* @return true if the command is a normal command, false otherwise
	*/
	bool commandIsNormal(string command);
};

#endif
