#include "Logic.h"

Logic::Logic(){
}

//if temp is empty,it means no tasks exists with same name, add task, return success. Otherwise, add task and return warning clash.
int Logic::add(Task toAdd, vector<Task>& _temp){

	if(_temp.empty()){
		_taskList.push_back(toAdd);
		return SUCCESS;
	}
	else{
		_taskList.push_back(toAdd);
		return ADD_WARNING_CLASH;
	}

}

int Logic::remove(Task tasked){

	return 0;//stub


}

int Logic::update(Task, Task, vector<Task>&){

	
	return 0;//stub
}

//clears temp, then pushes tasks that that has the same title as searchLine into temp.
int Logic::search(string searchLine, vector<Task>& _temp){

	_temp.clear();

	for(unsigned int i = 0; i < _taskList.size(); i++){

		if(_taskList[i].getTitle() == searchLine)
			_temp.push_back(_taskList[i]);
	}

	if(_temp.empty())
		return SEARCH_WARNING_NO_RESULT;
	else
		return SUCCESS;

}

int Logic::display(bool, vector<Task>&){

	
	return 0;//stub
}

int Logic::mark(bool, Task){

	
	return 0;//stub
}

vector<Task>* Logic::returnTaskListPointer(){
	return &(_taskList);
}

