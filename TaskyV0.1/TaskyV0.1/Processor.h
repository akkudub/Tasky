#ifndef _Processor_H_
#define _Processor_H_

/*
 *This class is the central controlling unit. It will take string from UI and process it, acknowledge UI
 *if input format is not suitable or it will go ahead and extract command out of input string and call methods
 *in Logic/history/FileProcessing to carry out the command.
 *
 *Main role: string processing, central logic unit, front wall of logic.
 *
 *Additional notice: this class will take the pointer of the _itemList in Logic class to ease the cost of
 *displaying. But the author of this class will only read from _itemList. This method is more like data-binding
 *with only programmers' protection.
 *
 *Author: Akshat, Junchao
*/

#include "Task.h"
#include "History.h"
#include "FileProcessing.h"
#include "Logic.h"
#include "Essential.h"

class Processor{
private:
	vector<Task> _temp; //hold the tasks returned by search and display
	vector<string> _stringList; //hold the tasks in a string format, pass to FileProcessing and that
	                            //will read and write accordingly
	vector<Task>* _taskListPointer;
	Logic _logic;
	History _history;
	FileProcessing _fileProcessing;
	
	
public:
	Processor();
	string mainProcessor(string); //processes the string, calls the appropriate logic methods, returns string
	                              //to UI

private:
	//level 1 abstraction
	string addCommandProcessor(string);
	string displayCommandProcessor(string);
	string updateCommandProcessor(string);
	string removeCommandProcessor(string);
	string markCommandProcessor(string);
	string otherCommandProcessor(string);

	//level 2 abstraction


	//additional helper methods
	string toLowCaseString(string);
	string removeLeadingSpaces(string);
	string breakIntoStringVector(string);
	vector<int> identifyKeyWords(string);
};

#endif