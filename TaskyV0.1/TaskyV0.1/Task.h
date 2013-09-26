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

class Task{
private:
	string _title;
	DateTime *_start;
	DateTime *_end;
	int _type;
	bool _done; //true=done, false=pending
	string _comment;
	
public:
	Task();
	Task(string, DateTime, DateTime, int, bool, string);
	
	string getTitle();
	DateTime getStart();
	DateTime getEnd();
	int getType();
	bool getDone(); //true=done, false=pending
	string getComment();

	bool isEqualTo(const Task&);
	bool isClashingWith(const Task&);
};

#endif