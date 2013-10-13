#include "TaskList.h"
#include <assert.h>

static const int FLOATING_TASK = 0;
static const int DEADLINE_TASK = 1;
static const int NORMAL_TASK = 2;

TaskList::TaskList(){
}


int TaskList::add(Task toAdd, vector<Task>& _temp){

	_temp.clear();

	for(unsigned int i = 0; i < _taskList.size(); i++){

		if(toAdd.isEqualTo(_taskList[i])){
			return ADD_FAILURE_DUPLICATE;
		}
	}

	if(toAdd.getType() == NORMAL_TASK){
		for(unsigned int i = 0; i < _taskList.size(); i++){

			if(_taskList[i].isClashingWith(toAdd)){
				_temp.push_back(_taskList[i]);
			}
		}
	}

	_taskList.push_back(toAdd);

	if(!_temp.empty())
		return ADD_WARNING_CLASH;
	else	
		return SUCCESS;


}


int TaskList::remove(Task toRemove){

	for(unsigned int i = 0; i < _taskList.size(); i++){

		if(toRemove.isEqualTo(_taskList[i])){
			_taskList.erase(_taskList.begin()+i);
			return SUCCESS;
		}
	}
	return REMOVE_FAILURE;
}




int TaskList::search(string searchLine, vector<Task>& _temp){

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

int TaskList::searchKeywords(vector<string> keywords, vector<Task>& _temp){

	assert(!keywords.empty());

	_temp.clear();

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

int TaskList::searchKeywordsInRange(vector<string> keywords, vector<Task>& _temp, BasicDateTime start, BasicDateTime end){

	assert(!keywords.empty());

	_temp.clear();

	Task tempTask;

	tempTask = Task("temp", start, end, 2, false, "comment");

	vector<Task> duplicateTaskList = _taskList;

	for(unsigned int i = 0; i < duplicateTaskList.size(); i++){

		if(duplicateTaskList[i].getType() == NORMAL_TASK){
			if(duplicateTaskList[i].getTitle() == keywords[0] && tempTask.isClashingWith(duplicateTaskList[i])){
				_temp.push_back(duplicateTaskList[i]);
				duplicateTaskList.erase(duplicateTaskList.begin()+i);
				i--;
			}
		}

		else if(duplicateTaskList[i].getType() == DEADLINE_TASK){

			if(duplicateTaskList[i].getTitle() == keywords[0] && duplicateTaskList[i].getEnd().compareTo(start) >= 0 
				&& duplicateTaskList[i].getEnd().compareTo(end) <= 0){

					_temp.push_back(duplicateTaskList[i]);
					duplicateTaskList.erase(duplicateTaskList.begin()+i);
					i--;
			}
		}
	}

	for(unsigned int i = 0; i < duplicateTaskList.size(); i++){

		if(duplicateTaskList[i].getType() == NORMAL_TASK){
			if(duplicateTaskList[i].getTitle().find(keywords[0]) != std::string::npos && tempTask.isClashingWith(duplicateTaskList[i])){
				_temp.push_back(duplicateTaskList[i]);
				duplicateTaskList.erase(duplicateTaskList.begin()+i);
				i--;
			}
		}

		else if(duplicateTaskList[i].getType() == DEADLINE_TASK){
			if(duplicateTaskList[i].getTitle().find(keywords[0]) != std::string::npos && duplicateTaskList[i].getEnd().compareTo(start) >= 0 
				&& duplicateTaskList[i].getEnd().compareTo(end) <= 0){
					_temp.push_back(duplicateTaskList[i]);
					duplicateTaskList.erase(duplicateTaskList.begin()+i);
					i--;
			}
		}
	}

	for(unsigned int i = 1; i < keywords.size(); i++){

		for(unsigned int j = 0; j < duplicateTaskList.size(); j++){

			if(duplicateTaskList[j].getType() == NORMAL_TASK){
				if(duplicateTaskList[j].getTitle().find(keywords[i]) != std::string::npos && tempTask.isClashingWith(duplicateTaskList[j])){
					_temp.push_back(duplicateTaskList[j]);
					duplicateTaskList.erase(duplicateTaskList.begin()+j);
					j--;
				}
			}
			else if(duplicateTaskList[j].getType() == DEADLINE_TASK){
				if(duplicateTaskList[j].getTitle().find(keywords[0]) != std::string::npos && duplicateTaskList[j].getEnd().compareTo(start) >= 0 
					&& duplicateTaskList[j].getEnd().compareTo(end) <= 0){
						_temp.push_back(duplicateTaskList[j]);
						duplicateTaskList.erase(duplicateTaskList.begin()+j);
						j--;
				}

			}
		}
		if(i == 6)
			break;
	}

	return SUCCESS;
}

int TaskList::displayAll(vector<Task>& _temp){

	_temp.clear();

	_temp = _taskList;

	if(_temp.empty())
		return DISPLAY_WARNING_NO_RESULT;
	else
		return SUCCESS;

}

int TaskList::displayStatus(bool done, vector<Task>& _temp){

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

int TaskList::displayInRange(BasicDateTime start, BasicDateTime end, vector<Task>& _temp){

	_temp.clear();

	Task tempTask;

	tempTask = Task("temp", start, end, 2, false, "comment");

	for(unsigned int i = 0; i < _taskList.size(); i++){

		if(_taskList[i].getType() == NORMAL_TASK){
			if(tempTask.isClashingWith(_taskList[i])){
				_temp.push_back(_taskList[i]);
			}
		}
		else if(_taskList[i].getType() == DEADLINE_TASK){
			if(_taskList[i].getEnd().compareTo(start) >= 0 && _taskList[i].getEnd().compareTo(end) <= 0){
				_temp.push_back(_taskList[i]);
			}
		}
	}

	return SUCCESS;
}



int TaskList::update(Task existingTask, Task newTask, vector<Task>& _temp){

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

	if(newTask.getType() == NORMAL_TASK){
		for(unsigned int i = 0; i < _taskList.size(); i++){

			if(_taskList[i].getType() == NORMAL_TASK)
				if(_taskList[i].isClashingWith(newTask)){
					_temp.push_back(_taskList[i]);
				}
		}
	}

	_taskList.push_back(newTask);

	if(!_temp.empty())
		return UPDATE_WARNING_CLASH;
	else
		return SUCCESS;

}

int TaskList::mark(bool mark, Task task){

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
vector<Task>* TaskList::returnTaskListPointer(){
return &(_taskList);
}
*/