#include "Task.h"

string Task::getTitle(){return _title;}
DateTime Task::getStart(){return *_start;}
DateTime Task::getEnd(){return *_end;}
int Task::getType(){return _type;}
bool Task::getDone(){return _done;}
string Task::getComment(){return _comment;}