#ifndef _TASK_H_
#define _TASK_H_

/*
*This class is mainly to model a task in the real world.
*
*Additional notice: we use pointer to datetime to avoid problems with initialization. Attention to
*memory leak.
*
*Main author: Kai Wen
*/

#include "Essential.h"
#include "BasicDateTime.h"

using namespace System;

class Task{
private:
	string _title;
	BasicDateTime _start;
	BasicDateTime _end;
	int _type;
	bool _done;
	string _comment;

public:

	///<summary>default constructor</summary>
	Task();
	///<summary>overloaded constructor</summary>
	///<value>title, start, end, type, status, comment</value>
	Task(std::string title, BasicDateTime start, BasicDateTime end, int type, bool status, std::string comment);
	~Task();	
	///getter for title
	string getTitle();
	///getter for start
	BasicDateTime getStart();
	///getter for end
	BasicDateTime getEnd();
	///getter for type
	int getType();
	///getter for status; done: true; pending: false;
	bool getDone();
	///getter for comment
	string getComment();
	///toggles the status
	void toggleDone();
	///checks if a task is equal to another task
	bool isEqualTo(Task);
	///checks if a task clashes with another task.
	bool isClashingWith(Task);
	///set title
	void setTitle(string title);
	///set start
	void setStartDate(BasicDateTime start);
	///set end
	void setEndDate(BasicDateTime end);
	///set type
	void setType(int type);
};

#endif
