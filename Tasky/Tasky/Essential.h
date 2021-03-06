#ifndef _ESSENTIAL_H_
#define _ESSENTIAL_H_

/*
*This class is mainly for definition of statuc code, it also includes some command header file
*names.
*
*Main Author: Akshat, Kai Wen, Joan, Junchao
*/

#include <vector>
#include <string>

using namespace std;

enum STATUS_CODE_SET_OVERALL{
	OVERALL_SUCCESS,
	OVERALL_WARNING,
	OVERALL_ERROR,
	OVERALL_PROMPT,
	OVERALL_EXIT,
};

enum STATUS_CODE_SET_SUCCESS{
	SUCCESS_ADD = OVERALL_EXIT + 1,
	SUCCESS_REMOVE,
	SUCCESS_DISPLAY,
	SUCCESS_UPDATE,
	SUCCESS_RESHCEDULE,
	SUCCESS_MARK,
	SUCCESS_SEARCH,
	SUCCESS_LOAD,
	SUCCESS_SAVE,
	SUCCESS_UNDO,
	SUCCESS_REDO,
	SUCCESS_HELP,
	SUCCESS_RECORD,
	SUCCESS_INTERPRET_SEARCH_RENAME,
	SUCCESS_INTERPRET_SEARCH_RESCHEDULE,
	SUCCESS_INTERPRET_SEARCH_MARK,
	SUCCESS_INTERPRET_ADD,
	SUCCESS_INTERPRET_REMOVE,
	SUCCESS_INTERPRET_DISPLAY,
	SUCCESS_INTERPRET_RENAME,
	SUCCESS_INTERPRET_RESCHEDULE,	
	SUCCESS_INTERPRET_MARK,
	SUCCESS_INTERPRET_SEARCH,
};

enum STATUS_CODE_SET_WARNING{
	WARNING_ADD_CLASH = SUCCESS_INTERPRET_SEARCH + 1,	
	WARNING_DISPLAY_NO_RESULT,
	WARNING_UPDATE_SAME,	
	WARNING_UPDATE_CLASH,
	WARNING_MARK_NO_CHANGE,
	WARNING_SEARCH_NO_RESULT,
	WARNING_SEARCH_NO_SLOTS,
	WARNING_UNDO_NO_TASKS,
	WARNING_REDO_NO_TASKS,
	WARNING_LOAD_EMPTY_FILE,	
	WARNING_INTERPRET_ADDITIONAL_USELESS_STUFF,
	WARNING_WRONG_INPUT,
};

enum STATUS_CODE_SET_ERROR{
	ERROR_ADD = WARNING_WRONG_INPUT + 1,
	ERROR_ADD_DUPLICATE,
	ERROR_REMOVE,
	ERROR_DISPLAY,
	ERROR_UPDATE,
	ERROR_MARK,
	ERROR_SEARCH,
	ERROR_UNDO,
	ERROR_REDO,
	ERROR_LOAD_OPENFILE,
	ERROR_LOAD_CORRUPTED_DATA,
	ERROR_SAVE_SAVEFILE,
	ERROR_RECORD,
	ERROR_INVALID_CHOICE,
	ERROR_NO_SEARCH_ACTION,
	ERROR_INTERPRET_SEARCH_RENAME,
	ERROR_INTERPRET_SEARCH_RESCHEDULE,
	ERROR_INTERPRET_SEARCH_MARK,
	ERROR_INTERPRET_EMPTY_INPUT,  //after stripped out all the spaces from beginning and ending, the input becomes empty
	ERROR_INTERPRET_TITLE_FORMAT,  //input format for title is wrong
	ERROR_INTERPRET_DATETIME_FORMAT,  //input format for date time is wrong, including logic error and date time cannot be interpreted
	ERROR_INTERPRET_MISSING_ESSENTIAL_COMPONENTS_IN_COMMAND,  //missing essential components
	ERROR_INTERPRET_MIXED_UP_INPUT,  //user trying to use two or more command types at the same time
	ERROR_INTERPRET_ADD,  //general error for add
	ERROR_INTERPRET_REMOVE,  //general error for remove
	ERROR_INTERPRET_DISPLAY,   //out of allowed command range
	ERROR_INTERPRET_RENAME,	  //the pattern cannot be recognized, general error
	ERROR_INTERPRET_RESCHEDULE,  //general error for reschedule
	ERROR_INTERPRET_MARK,  //general error for mark
	ERROR_INTERPRET_POWER_SEARCH  //missing essential components, general error
};

enum STATUS_CODE_SET_PROPMT{
	PROMPT_REMOVE_CHOOSE = ERROR_INTERPRET_POWER_SEARCH+1,
	PROMPT_RENAME_CHOOSE,
	PROMPT_RESCHEDULE_CHOOSE,
	PROMPT_MARK_CHOOSE,
};

#endif
