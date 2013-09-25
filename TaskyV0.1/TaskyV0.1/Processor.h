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

#include <sstream>
#include <algorithm>
#include "Task.h"
#include "History.h"
#include "FileProcessing.h"
#include "Logic.h"
#include "Essential.h"

class Processor{
private:
	vector<Task> _tempTaskList; //hold the tasks returned by search and display
	vector<string> _stringList; //hold the tasks in a string format, pass to FileProcessing and that
	                            //will read and write accordingly
	vector<Task>* _taskListPointer;
	Logic _logic;
	History _history;
	FileProcessing _fileProcessing;
	vector<string> *_wordsList;
	int _statusFlag;  //0 : last operation has ended;
	                  //1 : update operation has not ended;
	                  //2 : remove operation has not ended;
	                  //3 : mark operation has not ended;
	                  
	
	
public:
	Processor();
	string mainProcessor(string); //processes the string, calls the appropriate logic methods, returns string
	                              //to UI
	                              //create a new vector of strings and delete that at the end
	~Processor();

private:
	//level 1 abstraction
	string addCommandProcessor();  //create an int to keep track of the position of checked vector
	                               //create two datetime and pass the reference to 
	string displayCommandProcessor();
	string updateCommandProcessor(int&);  //change the flag if necessary
	string removeCommandProcessor(int&);  //change the flag if necessary
	string markCommandProcessor(int&);  //change the flag if necessary
	string otherCommandProcessor();

	//level 2 abstraction
	int findType(int&);
	int findDate(DateTime&);

    


	//additional helper methods
	int breakIntoStringVector(string);
	int stringToInt(string);
	string combineStringsWithSpace(int,int);
	string combineStringsWithNewLine(int,int);
	string taskToString(const Task&);
	string toLowCaseString(string);
	string removeLeadingSpaces(string);
	vector<int> identifyKeyWords(string);
};

#endif