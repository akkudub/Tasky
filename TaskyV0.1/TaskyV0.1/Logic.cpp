#include "Logic.h"
#include <assert.h>

Logic::Logic(){
}


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


int Logic::remove(Task toRemove){

	for(unsigned int i = 0; i < _taskList.size(); i++){

		if(toRemove.isEqualTo(_taskList[i])){
			_taskList.erase(_taskList.begin()+i);
			return SUCCESS;
		}
	}
	return REMOVE_FAILURE;
}




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

	for(unsigned int i = 0; i < duplicateTaskList.size(); i++){

		if(duplicateTaskList[i].getTitle().find(keywords[0]) != std::string::npos){
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
			if(i == 6)
				break;
	}

	return SUCCESS;

}

int Logic::searchKeywordsInRange(vector<string> keywords, vector<Task>& _temp, BasicDateTime start, BasicDateTime end){

	assert(!keywords.empty());

	_temp.clear();

	Task tempTask;

	tempTask = Task("temp", start, end, 2, false, "comment");

	vector<Task> duplicateTaskList = _taskList;

	for(unsigned int i = 0; i < duplicateTaskList.size(); i++){

		if(duplicateTaskList[i].getTitle() == keywords[0] && tempTask.isClashingWith(duplicateTaskList[i])){
			_temp.push_back(duplicateTaskList[i]);
			duplicateTaskList.erase(duplicateTaskList.begin()+i);
			i--;
		}
	}

	for(unsigned int i = 0; i < duplicateTaskList.size(); i++){

		if(duplicateTaskList[i].getTitle().find(keywords[0]) != std::string::npos && tempTask.isClashingWith(duplicateTaskList[i])){
			_temp.push_back(duplicateTaskList[i]);
			duplicateTaskList.erase(duplicateTaskList.begin()+i);
			i--;
		}
	}


	for(unsigned int i = 1; i < keywords.size(); i++){

		for(unsigned int j = 0; j < duplicateTaskList.size(); j++)
			if(duplicateTaskList[j].getTitle().find(keywords[i]) != std::string::npos && tempTask.isClashingWith(duplicateTaskList[j])){
				_temp.push_back(duplicateTaskList[j]);
				duplicateTaskList.erase(duplicateTaskList.begin()+j);
				j--;
			}
			if(i == 6)
				break;
	}

	return SUCCESS;
}

int Logic::displayAll(vector<Task>& _temp){

	_temp.clear();

	_temp = _taskList;

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

	Task tempTask;

	tempTask = Task("temp", start, end, 2, false, "comment");

	for(unsigned int i = 0; i < _taskList.size(); i++){

		if(tempTask.isClashingWith(_taskList[i])){
			_temp.push_back(_taskList[i]);
		}
	}

	return SUCCESS;
}



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