#include "Task.h"

string Task::getTitle(){
	return _title;
}

BasicDateTime Task::getStart(){
	return _start;
}

BasicDateTime Task::getEnd(){
	return _end;
}

int Task::getType(){
	return _type;
}

bool Task::getDone(){
	return _done;
}

string Task::getComment(){
	return _comment;
}

void Task::toggleDone(){
	_done=!_done;
}

Task::Task(){

}


Task::Task(string title, BasicDateTime start, BasicDateTime end, int type, bool done, string comment){

	_title = title;
	_start = start;
	_end = end;
	_type = type;
	_done = done;
	_comment = comment;

}

Task::~Task()
{
	
}

bool Task::isEqualTo(Task another){

	return another.getTitle() == _title
		&& !another.getStart().compareTo(_start)
		&& !another.getEnd().compareTo(_end);

}


bool Task::isClashingWith(Task another){
	bool startClash=false;
	bool endClash=false;

	if(another.getStart().compareTo(_start) >= 0 && another.getStart().compareTo(_end) < 0)
		startClash = true;
	else
		startClash = false;

	if(another.getEnd().compareTo(_start) > 0 && another.getEnd().compareTo(_end) <= 0)
		endClash = true;
	else
		endClash = false;

	return startClash || endClash;

}
