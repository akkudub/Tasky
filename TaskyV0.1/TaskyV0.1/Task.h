#ifndef _TASK_H_
#define _TASK_H_

/**
*This class is mainly to model a task in the real world. It uses
*the BasicDateTime class for the date and time of a task.
*
*
*
*Main author: Kai Wen
*/

#include "Essential.h"
#include "BasicDateTime.h"

using namespace System;

class Task{
private:

private:
	string _title;
	BasicDateTime _start;
	BasicDateTime _end;
	int _type;
	bool _done;
	string _comment;
	/**
	* Purpose:Retrieves status of task
	*
	* @param status - true - done; false - pending
	*
	* @return string with status of task
	*/
	string printStatus();
	/**
	* 
	*/
	string printType();
	string printStart();
	string printEnd();

public:

	Task();
	Task(std::string title, BasicDateTime start, BasicDateTime end, int type, bool status, std::string comment);
	~Task();	
	string getTitle();
	BasicDateTime getStart();
	BasicDateTime getEnd();
	int getType();
	bool getDone();
	string getComment();
	/**
	* Purpose:
	* toggles the state of the task from pending to done or vice versa.
	*/
	void toggleDone();
	/**
	* Purpose:
	* checks if this Task is equal to argument Task
	* @param Task the task to be compared with
	* @return True - Tasks are equal, False - Tasks are not equal
	*/
	bool isEqualTo(Task another);
	/**
	* Purpose:
	* checks if argument Task clashes with this Task.
	* @param Task the task to be compared with
	* @return True - Tasks clash, False - No clash
	*/
	bool isClashingWith(Task another);
	/**
	* Purpose:
	* converts the Task object to a string for saving and displaying,
	* returns that string
	*/
	/*string toString();*/
	vector<string> toStringVector();
	
	void setTitle(string title);
	void setStartDate(BasicDateTime start);
	void setEndDate(BasicDateTime end);
	void setType(int type);
};

#endif
