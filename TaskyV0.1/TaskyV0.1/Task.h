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
	bool _done; //true=done, false=pending
	string _comment;
	
public:

	///<summary>default constructor</summary>
	Task();
	///<summary>overloaded constructor</summary>
	///<value>title, start, end, type, status, comment</value>
	Task(std::string title, BasicDateTime start, BasicDateTime end, int type, bool status, std::string comment);
	~Task();	
	string getTitle();
	BasicDateTime getStart();
	BasicDateTime getEnd();
	int getType();
	bool getDone(); //true=done, false=pending
	string getComment();
	void toggleDone();
	bool isEqualTo(Task);
	bool isClashingWith(Task);
};

#endif
