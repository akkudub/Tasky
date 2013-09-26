#include "Task.h"

Task::Task(){

}

Task::Task(string title,DateTime dt1, DateTime dt2, int type, bool done, string comment){
	_title=title;
	_type=type;
	_done=done;
	_comment=comment;
}

string Task::getTitle(){
	return _title;
}

DateTime Task::getStart(){
	return *_start;
}

DateTime Task::getEnd(){
	return *_end;
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