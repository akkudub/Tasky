#include "Logic.h"

Logic::Logic(){
}

vector<Task>* Logic::returnTaskListPointer(){
	return &(_taskList);
}