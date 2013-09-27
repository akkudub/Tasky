#include "Task.h"

string Task::getTitle(){return _title;}
DateTime Task::getStart(){return *_start;}
DateTime Task::getEnd(){return *_end;}
int Task::getType(){return _type;}
bool Task::getDone(){return _done;}
string Task::getComment(){return _comment;}

void Task::toggleDone(){
	_done=!_done;
}

Task::Task(){

}


Task::Task(string title, DateTime start, DateTime end, int type, bool done, string comment){

	_title = title;
	_start = &start;
	_end = &end;
	_type = type;
	_done = done;
	_comment = comment;

}

Task::~Task()
{
	
}

bool Task::isEqualTo(Task& compare){

	return compare.getTitle() == _title
		&& compare.getStart() == *_start
		&& compare.getEnd() == *_end;

}


//clash: if start >= _start && < _end || if end > _start && <= _end
bool Task::isClashingWith(Task& compare){

	bool startClash = compare.getStart() >= *_start
		&& compare.getStart() < *_end;
	bool endClash = compare.getEnd() > *_start
		&& compare.getEnd() <= *_end;

	return startClash || endClash;

}

