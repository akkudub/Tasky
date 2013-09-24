#ifndef _ESSENTIAL_H_
#define _ESSENTIAL_H_

/*
 *This class is mainly for definition of statuc code, it also includes some command header file
 *names.
 *
 *Main Author: Akshat, Kai Wen, Joan, Junchao
 hello
 */

#include <vector>
#include <string>

using namespace std;
using namespace System;

enum STATUS_CODE_SET
{
	SUCCESS,
	ADD_WARNING_CLASH,
	ADD_FAILURE,
	ADD_FAILURE_DUPLICATE,

	REMOVE_FAILURE,

	UPDATE_WARNING_SAME,
	UPDATE_WARNING_CLASH,
	UPDATE_FAILURE,

	SEARCH_WARNING_NO_RESULT,
	SEARCH_FAILURE,

	DISPLAY_WARNING_NO_RESULT,

	MARK_WARNING_NO_CHANGE,

	UNDO_WARNING_EMPTYLIST,
	UNDO_FAILURE,

	RECORD_FAILURE,

	LOAD_FAILURE_OPENFILE,
	SAVE_FAILURE_SAVEFILE

};

#endif
