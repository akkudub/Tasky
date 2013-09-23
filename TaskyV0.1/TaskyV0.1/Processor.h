#ifndef _Processor_H_
#define _Processor_H_

/*



*/

#include "Task.h"
#include "History.h"
#include "FileProcessing.h"
#include "Logic.h"
#include "Essential.h"

class Processor{
private:
	vector<Task> _temp; //hold the tasks returned by search and display
	vector<string> _stringList; //hold the tasks in a string format
	Logic _logic;
	History _history;
	FileProcessing _fileProcessing;
	vector<Task>* _taskListPointer;
	
	
public:
	Processor();
	string mainProcessor(string); //processes the string, calls the appropriate logic methods, returns 
};

#endif