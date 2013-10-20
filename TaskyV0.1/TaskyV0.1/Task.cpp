#include "Task.h"

static const int FLOATING_TASK = 0;
static const int DEADLINE_TASK = 1;
static const int NORMAL_TASK = 2;

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

	switch(another.getType()){

	case FLOATING_TASK:
		return another.getTitle() == _title
			&& another.getType() == _type;
		break;
	case DEADLINE_TASK:
		return another.getTitle() == _title
			&& another.getEnd().compareTo(_end) == 0
			&& another.getType() == _type;
		break;
	case NORMAL_TASK:
		return another.getTitle() == _title
			&& another.getStart().compareTo(_start) == 0
			&& another.getEnd().compareTo(_end) == 0
			&& another.getType() == _type;
		break;

	}
	return false;
}


bool Task::isClashingWith(Task another){

	bool startClash = false;
	bool endClash = false;
	bool spanClash = false;

	if(another.getStart().compareTo(_start) >= 0 && another.getStart().compareTo(_end) < 0)
		startClash = true;

	if(another.getEnd().compareTo(_start) > 0 && another.getEnd().compareTo(_end) <= 0)
		endClash = true;

	if(another.getStart().compareTo(_start) <= 0 && another.getEnd().compareTo(_end) >= 0)
		spanClash = true;

	return startClash || endClash || spanClash;

}

string Task::toString(){
	string outputString = "Type: " + printType() + "\n";
	outputString += "Title: " + _title + "\n";
	outputString += "Status: " + printStatus() + "\n";
	outputString += "Start: " + printStart() + "\n";
	outputString += "End: " + printEnd() + "\n";
	outputString += "Comment: " + _comment;

	return outputString;
}


string Task::printStatus(){
	if(_done){
		return "done";
	}else{
		return "pending";
	}
}

string Task::printType(){
	switch (_type)
	{
	case 0:
		return "Floating";
		break;
	case 1:
		return "Deadline";
		break;
	case 2:
		return "Timed";
		break;
	default:
		return "";
		break;
	}
}

string Task::printStart(){
	switch (_type){
	case 0:  case 1:
		return "None";
		break;
	case 2:
		return _start.getDateTimeString();
		break;
	default:
		return "";
		break;
	}
}
string Task::printEnd(){
	switch (_type){
	case 0:
		return "None";
		break;
	case 1:	case 2:
		return _end.getDateTimeString();
		break;
	default:
		return "";
		break;
	}
}

void Task::setTitle(string title){
	_title = title;
}

void Task::setStartDate(BasicDateTime start){
	_start = start;
}

void Task::setEndDate(BasicDateTime end){
	_end = end;
}

void Task::setType(int type){
	_type = type;
}