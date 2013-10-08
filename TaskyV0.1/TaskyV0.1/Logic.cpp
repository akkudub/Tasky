#include "Logic.h"
#include <assert.h>

Logic::Logic(){
}

//if temp is empty,it means no tasks exists with same name, add task, return success. Otherwise, add task and return warning clash.
int Logic::add(Task toAdd, vector<Task>& _temp){

	for(unsigned int i = 0; i < _taskList.size(); i++){

		if(toAdd.isEqualTo(_taskList[i])){
			return ADD_FAILURE_DUPLICATE;
		}
	}

	for(unsigned int i = 0; i < _taskList.size(); i++){

		if(_taskList[i].isClashingWith(toAdd)){
			_temp.push_back(_taskList[i]);
		}
	}

	if(!_temp.empty()){
		_taskList.push_back(toAdd);
		return ADD_WARNING_CLASH;
	}
	else{
		_taskList.push_back(toAdd);
		return SUCCESS;
	}

}

// finds a task in the vector that isEqual to the task to be removed and removes it.
int Logic::remove(Task toRemove){

	for(unsigned int i = 0; i < _taskList.size(); i++){

		if(toRemove.isEqualTo(_taskList[i])){
			_taskList.erase(_taskList.begin()+i);
			return SUCCESS;
		}
	}
	return REMOVE_FAILURE;
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

int Logic::searchKeywords(vector<string> keywords, vector<Task>& _temp){

	assert(!keywords.empty());

	vector<Task> duplicateTaskList = _taskList;

	for(unsigned int i = 0; i < duplicateTaskList.size(); i++){

		if(duplicateTaskList[i].getTitle() == keywords[0]){
			_temp.push_back(duplicateTaskList[i]);
			duplicateTaskList.erase(duplicateTaskList.begin()+i);
			i--;
		}
	}

	for(unsigned int i = 1; i < keywords.size(); i++){

		for(unsigned int j = 0; j < duplicateTaskList.size(); j++)
			if(duplicateTaskList[j].getTitle().find(keywords[i]) != std::string::npos){
				_temp.push_back(duplicateTaskList[j]);
				duplicateTaskList.erase(duplicateTaskList.begin()+j);
				j--;
			}

	}

}

int Logic::searchKeywordsInRange(vector<string> keywords, vector<Task>& _temp, BasicDateTime start, BasicDateTime end){


}

int Logic::displayAll(vector<Task>& _temp){

	_temp.clear();

	for(unsigned int i = 0; i < _taskList.size(); i++){
		_temp.push_back(_taskList[i]);
	}

	if(_temp.empty())
		return DISPLAY_WARNING_NO_RESULT;
	else
		return SUCCESS;

}

int Logic::displayStatus(bool done, vector<Task>& _temp){

	_temp.clear();

	for(unsigned int i = 0; i < _taskList.size(); i++){

		if(_taskList[i].getDone() == done)
			_temp.push_back(_taskList[i]);
	}

	if(_temp.empty())
		return DISPLAY_WARNING_NO_RESULT;
	else
		return SUCCESS;

}

int Logic::displayInRange(BasicDateTime start, BasicDateTime end, vector<Task>& _temp){

	_temp.clear();



}


// old Task, new Task, Tasks that clash push into vector. **is it only tasks that time clash push into vector? or include tasks that same title, tasks that are equal?
int Logic::update(Task existingTask, Task newTask, vector<Task>& _temp){

	_temp.clear();
	if(existingTask.isEqualTo(newTask)){
		return UPDATE_WARNING_SAME;
	}

	for(unsigned int i = 0; i < _taskList.size(); i++){

		if(existingTask.isEqualTo(_taskList[i])){
			_taskList.erase(_taskList.begin()+i);
			break;
		}
	}

	for(unsigned int i = 0; i < _taskList.size(); i++){

		if(_taskList[i].isClashingWith(newTask)){
			_temp.push_back(_taskList[i]);
		}
	}

	_taskList.push_back(newTask);

	if(!_temp.empty())
		return UPDATE_WARNING_CLASH;

	return SUCCESS;

}

int Logic::mark(bool mark, Task task){

	if(task.getDone() == mark)
		return MARK_WARNING_NO_CHANGE;

	for(unsigned int i = 0; i < _taskList.size(); i++){

		if(task.isEqualTo(_taskList[i])){
			_taskList[i].toggleDone();
			return SUCCESS;
		}
	}
	return MARK_FAILURE;
}


/*
vector<Task>* Logic::returnTaskListPointer(){
return &(_taskList);
}
*/