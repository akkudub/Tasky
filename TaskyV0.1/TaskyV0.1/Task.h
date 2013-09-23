#ifndef _TASK_H_
#define _TASK_H_

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
	Task(string, DateTime, DateTime, int, bool, string);
	
};

#endif