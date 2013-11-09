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
#include "HelpUser.h"

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
	*			  5--last operation was search
	*/
private:
	vector<Task> _tempTaskList;
	vector<string> _tempStringList; 
	int _statusFlag;
	bool searched;

	string _tempTitle;
	bool _tempStatus;
	int _tempType;
	BasicDateTime _tempStart;
	BasicDateTime _tempEnd;

	TaskList _taskList;
	History _history;
	Interpreter _interpreter;
	FileProcessing _fileProcessing;
	Messages _messages;
	HelpUser _help;

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
	static const string NONE;

	static const string COMMAND_ADD;
	static const string COMMAND_REMOVE;
	static const string COMMAND_DISPLAY;
	static const string COMMAND_RENAME;
	static const string COMMAND_RESCHEDULE;
	static const string COMMAND_MARK;
	static const string COMMAND_SEARCH;
	static const string COMMAND_UNDO;
	static const string COMMAND_REDO;
	static const string COMMAND_HELP;
	static const string COMMAND_EXIT;

	static const string TASK_ADDED;
	static const string TASK_ADD_ERROR;
	static const string CLASHES;
	static const string TASKS_REMOVED;
	static const string TASKS_REMOVING_ERROR;
	static const string UPDATED_TO;
	static const string TASK_RENAMED;
	static const string TASK_RENAME_ERROR;
	static const string TASK_RESCHEDULED;
	static const string TASK_RESCHEDULED_ERROR;
	static const string TASKS_MARKED;
	static const string TASKS_MARKING_ERROR;
	static const string UNDO_TASK_ADDED;
	static const string UNDO_TASK_ADDING_ERROR;
	static const string UNDO_TASK_REMOVED;
	static const string UNDO_TASK_REMOVING_ERROR;
	static const string UNDO_TASK_UPDATED;
	static const string UNDO_TASK_UPDATING_ERROR;
	static const string REDO_TASK_ADDED;
	static const string REDO_TASK_ADDING_ERROR;
	static const string REDO_TASK_REMOVED;
	static const string REDO_TASK_REMOVING_ERROR;
	static const string REDO_TASK_UPDATED;
	static const string REDO_TASK_UPDATING_ERROR;
	static const string EMPTY_SLOTS;
	static const string NO_EMPTY_SLOTS;
	static const string SLOT_FROM;
	static const string SLOT_TO;

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
	* Handle search actions
	*
	* @param input the input passed in from the main processor with the command
	* @return status code
	*/
	int searchActionProcessor(string command, string input);

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
	* @param input the input passed in from the main processor without the redo keyword(single redo)
	* @return status code
	*/
	int redoCommandProcessor(string input);
	
	/*
	* Purpose:
	* Handle help commands
	*
	* @param input the input passed in from the main processor without the help keyword
	* @return status code
	*/
	int helpCommandProcessor(string input);

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
	* add tasks, put any clashes in _tempTaskList
	*
	* @param title name of task
	* @param type type of task
	* @param start start time of task
	* @param end end time of task
	* @param comment additional description
	* @return status code
	*/
	int addTask(string title, int type, BasicDateTime start, BasicDateTime end, string comment);

	void recordAndFeedback( Task oldTask, Task newTask );

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
	* @return void
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
	bool choiceIsValidVec(vector<int> choice);

	bool choiceIsValid(unsigned int choice);
	
	/*
	* Purpose:
	* converts a vector of tasks into a vector of strings and pushes them in another vector
	*
	* @param taskList the vector of the Tasks passed in
	* @param stringList the vector of string that the strings have to be pushed in
	* @return a vector of strings based on the vector of tasks
	*/
	void taskVecToStringVec(vector<Task> taskList, vector<string>& stringList);

	void dateTimeVecToStringVec(vector<BasicDateTime>slots, vector<string>& stringList);
	
	/*
	* Purpose:
	* checks if the command entered is one of the acceptable commands
	*
	* @param command the command that needs to be checked
	* @return true if the command is a normal command, false otherwise
	*/
	bool commandIsNormal(string command);

	void pushFeedackToStringVec(vector<Task> taskVector, string message);
	
	void removeTask(int& returnCode, vector<Task>& removed, vector<Task>& error, Task newTask, Task oldTask);
};

#endif
