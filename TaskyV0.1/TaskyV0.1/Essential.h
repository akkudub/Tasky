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

enum STATUS_CODE_SET_SUCCESS{
	SUCCESS_ADD,

	SUCCESS_REMOVE,

	SUCCESS_DISPLAY,

	SUCCESS_UPDATE,

	SUCCESS_RESHCEDULE,

	SUCCESS_MARK,

	SUCCESS_SEARCH,

	SUCCESS_UNDO,

	SUCCESS_REDO
};

enum STATUS_CODE_SET_WARNING{
	WARNING_ADD_CLASH = 9,
	WARNING_ADD_DUPLICATE,

	WARNING_UPDATE_SAME,
	WARNING_UPDATE_CLASH,

	WARNING_SEARCH_NO_RESULT,

	WARNING_DISPLAY_NO_RESULT,

	WARNING_MARK_NO_CHANGE,
};

enum STATUS_CODE_SET_ERROR{
	ERROR_ADD = 16,

	ERROR_REMOVE,

	ERROR_DISPLAY,

	ERROR_UPDATE,

	ERROR_SEARCH,

	ERROR_MARK,

	ERROR_UNDO,

	ERROR_RECORD,

	ERROR_LOAD_OPENFILE,

	ERROR_SAVE_SAVEFILE
};

#endif
