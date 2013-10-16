#include "TaskList-v2.h"
#include <assert.h>

static const int FLOATING_TASK = 0;
static const int DEADLINE_TASK = 1;
static const int NORMAL_TASK = 2;

TaskList::TaskList(){
}

int TaskList::add(Task toAdd, vector<Task>& _temp){

	_temp.clear();

	if(isExisting(toAdd))
		return WARNING_ADD_DUPLICATE;

	if(toAdd.getType() == NORMAL_TASK)
		pushClashing(toAdd, _temp);

	if(!_temp.empty())
		return WARNING_ADD_CLASH;
	else	
		return SUCCESS_ADD;

	return ERROR_ADD;

}

int TaskList::remove(Task toRemove){

	if(isSuccessfullyRemoved(toRemove))
		return SUCCESS_REMOVE;
	else
		return ERROR_REMOVE;
}

int TaskList::search(string searchLine, vector<Task>& _temp){

	_temp.clear();

	searchTitle(searchLine, _temp);

	if(_temp.empty())
		return WARNING_SEARCH_NO_RESULT;
	else
		return SUCCESS_SEARCH;

	return ERROR_SEARCH;

}

int TaskList::searchKeywords(vector<string> keywords, vector<Task>& _temp){

	assert(!keywords.empty());

	_temp.clear();

	searchVectors(keywords, _temp);

	if(!_temp.empty())
		return SUCCESS_SEARCH;
	else
		return WARNING_SEARCH_NO_RESULT;

	return ERROR_SEARCH;
}

int TaskList::searchKeywordsInRange(vector<string> keywords, vector<Task>& _temp, BasicDateTime start, BasicDateTime end){

	assert(!keywords.empty());

	_temp.clear();

	searchVectorsWithRange(keywords, _temp, start, end);

	if(!_temp.empty())
		return SUCCESS_SEARCH;
	else
		return WARNING_SEARCH_NO_RESULT;

	return ERROR_SEARCH;
}

int TaskList::displayAll(vector<Task>& _temp){

	_temp.clear();

	appendVectors(_temp);

	if(!_temp.empty())
		return SUCCESS_DISPLAY;
	else
		return WARNING_DISPLAY_NO_RESULT;

	return ERROR_DISPLAY;

}

int TaskList::displayStatus(bool done, vector<Task>& _temp){

	_temp.clear();

	pushStatus(done, _temp);

	if(!_temp.empty())
		return SUCCESS_DISPLAY;
	else
		return WARNING_DISPLAY_NO_RESULT;

	return ERROR_DISPLAY;

}

int TaskList::displayInRange(BasicDateTime start, BasicDateTime end, vector<Task>& _temp){

	_temp.clear();

	pushInRange(_temp, start, end);

	if(!_temp.empty())
		return SUCCESS_DISPLAY;
	else
		return WARNING_DISPLAY_NO_RESULT;

	return ERROR_DISPLAY;
}

int TaskList::displayStatusInRange(bool done, BasicDateTime start, BasicDateTime end, vector<Task>& _temp){

	_temp.clear();

	pushStatusInRange(done, start, end, _temp);

	if(!_temp.empty())
		return SUCCESS_DISPLAY;
	else
		return WARNING_DISPLAY_NO_RESULT;

	return ERROR_DISPLAY;

}

int TaskList::update(Task existingTask, Task newTask, vector<Task>& _temp){

	if(existingTask.isEqualTo(newTask))
		return WARNING_UPDATE_SAME;

	assert(remove(existingTask) == SUCCESS_REMOVE);

	add(newTask, _temp);

	if(!_temp.empty())
		return WARNING_UPDATE_CLASH;
	else
		return SUCCESS_UPDATE;

	return ERROR_UPDATE;

}

int TaskList::mark(bool mark, Task task){

	if(task.getDone() == mark)
		return WARNING_MARK_NO_CHANGE;

	if(isSuccessfullyMarked(mark, task))
		return SUCCESS_MARK;
	else
		return ERROR_MARK;
}

void TaskList::getOccupiedDates(vector<BasicDateTime>& usedDates){

	usedDates.clear();
	pushOccupiedDates(usedDates);

}






void TaskList::searchVectors(vector<string> keywords, vector<Task>& _temp){

	_duplicateFloating = _floatingTask;
	_duplicateDeadline = _deadlineTask;
	_duplicateNormal = _normalTask;

	exactSearch(keywords[0], _temp);
	containingExactStringSearch(keywords[0], _temp);
	containingBreakdownStringSearch(keywords, _temp);

}

void TaskList::searchVectorsWithRange(vector<string> keywords, vector<Task>& _temp, BasicDateTime start, BasicDateTime end){

	_duplicateDeadline = _deadlineTask;
	_duplicateNormal = _normalTask;

	exactSearchWithRange(keywords[0], _temp, start, end);
	containingExactStringSearchWithRange(keywords[0], _temp, start, end);
	containingBreakdownStringSearchWithRange(keywords, _temp, start, end);

}


void TaskList::exactSearch(string exactString, vector<Task>& _temp){

	for(unsigned int i = 0; i < _duplicateFloating.size(); i++){

		if(_duplicateFloating[i].getTitle() == exactString){
			_temp.push_back(_duplicateFloating[i]);
			_duplicateFloating.erase(_duplicateFloating.begin()+i);
			i--;
		}
	}


	for(unsigned int i = 0; i < _duplicateDeadline.size(); i++){

		if(_duplicateDeadline[i].getTitle() == exactString){
			_temp.push_back(_duplicateDeadline[i]);
			_duplicateDeadline.erase(_duplicateDeadline.begin()+i);
			i--;
		}
	}


	for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

		if(_duplicateNormal[i].getTitle() == exactString){
			_temp.push_back(_duplicateNormal[i]);
			_duplicateNormal.erase(_duplicateNormal.begin()+i);
			i--;
		}
	}


}

void TaskList::containingExactStringSearch(string exactString, vector<Task>& _temp){


	for(unsigned int i = 0; i < _duplicateFloating.size(); i++){

		if(_duplicateFloating[i].getTitle().find(exactString) != std::string::npos){
			_temp.push_back(_duplicateFloating[i]);
			_duplicateFloating.erase(_duplicateFloating.begin()+i);
			i--;
		}
	}


	for(unsigned int i = 0; i < _duplicateDeadline.size(); i++){

		if(_duplicateDeadline[i].getTitle().find(exactString) != std::string::npos){
			_temp.push_back(_duplicateDeadline[i]);
			_duplicateDeadline.erase(_duplicateDeadline.begin()+i);
			i--;
		}
	}


	for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

		if(_duplicateNormal[i].getTitle().find(exactString) != std::string::npos){
			_temp.push_back(_duplicateNormal[i]);
			_duplicateNormal.erase(_duplicateNormal.begin()+i);
			i--;
		}
	}


}

void TaskList::containingBreakdownStringSearch(vector<string> keywords, vector<Task>& _temp){

	for(unsigned int i = 1; i < keywords.size(); i++){

		containingExactStringSearch(keywords[i], _temp);
		if(i == 6)
			break;
	}
}

void TaskList::exactSearchWithRange(string exactString, vector<Task>& _temp, BasicDateTime start, BasicDateTime end){

	if(!_duplicateDeadline.empty()){

		for(unsigned int i = 0; i < _duplicateDeadline.size(); i++){

			if(_duplicateDeadline[i].getTitle() == exactString && isInRange(_duplicateDeadline[i].getEnd(), start, end)){
				_temp.push_back(_duplicateDeadline[i]);
				_duplicateDeadline.erase(_duplicateDeadline.begin()+i);
				i--;
			}
		}
	}

	if(!_duplicateNormal.empty()){

		Task tempTask;
		tempTask = Task("temp", start, end, 2, false, "comment");

		for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

			if(_duplicateNormal[i].getTitle() == exactString && tempTask.isClashingWith(_duplicateNormal[i])){
				_temp.push_back(_duplicateNormal[i]);
				_duplicateNormal.erase(_duplicateNormal.begin()+i);
				i--;
			}
		}
	}

}


void TaskList::containingExactStringSearchWithRange(string exactString, vector<Task>& _temp, BasicDateTime start, BasicDateTime end){

	if(!_duplicateDeadline.empty()){

		for(unsigned int i = 0; i < _duplicateDeadline.size(); i++){

			if(_duplicateDeadline[i].getTitle().find(exactString) != std::string::npos && isInRange(_duplicateDeadline[i].getEnd(), start, end)){
				_temp.push_back(_duplicateDeadline[i]);
				_duplicateDeadline.erase(_duplicateDeadline.begin()+i);
				i--;
			}
		}
	}

	if(!_duplicateNormal.empty()){

		Task tempTask;
		tempTask = Task("temp", start, end, 2, false, "comment");

		for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

			if(_duplicateNormal[i].getTitle().find(exactString) != std::string::npos && tempTask.isClashingWith(_duplicateNormal[i])){
				_temp.push_back(_duplicateNormal[i]);
				_duplicateNormal.erase(_duplicateNormal.begin()+i);
				i--;
			}
		}
	}
}


void TaskList::containingBreakdownStringSearchWithRange(vector<string> keywords, vector<Task>& _temp, BasicDateTime start, BasicDateTime end){

	for(unsigned int i = 1; i < keywords.size(); i++){

		containingExactStringSearchWithRange(keywords[i], _temp, start, end);
		if(i == 6)
			break;
	}
}

bool TaskList::isInRange(BasicDateTime time, BasicDateTime start, BasicDateTime end){

	return time.compareTo(start) >= 0 && time.compareTo(end) <= 0;

}

bool TaskList::isExisting(Task task){

	switch(task.getType()){

	case FLOATING_TASK:
		for(unsigned int i = 0; i < _floatingTask.size(); i++){

			if(task.isEqualTo(_floatingTask[i])){
				return true;
			}
		}
		break;
	case DEADLINE_TASK:
		for(unsigned int i = 0; i < _deadlineTask.size(); i++){

			if(task.isEqualTo(_deadlineTask[i])){
				return true;
			}
		}
		break;
	case NORMAL_TASK:
		for(unsigned int i = 0; i < _normalTask.size(); i++){

			if(task.isEqualTo(_normalTask[i])){
				return true;
			}
		}
		break;
	}
	return false;
}

bool TaskList::isSuccessfullyRemoved(Task task){

	switch(task.getType()){

	case FLOATING_TASK:
		for(unsigned int i = 0; i < _floatingTask.size(); i++){

			if(task.isEqualTo(_floatingTask[i])){
				_floatingTask.erase(_floatingTask.begin()+i);
				return true;
			}
		}
		break;
	case DEADLINE_TASK:
		for(unsigned int i = 0; i < _deadlineTask.size(); i++){

			if(task.isEqualTo(_deadlineTask[i])){
				_deadlineTask.erase(_deadlineTask.begin()+i);
				return true;
			}
		}
		break;
	case NORMAL_TASK:
		for(unsigned int i = 0; i < _normalTask.size(); i++){

			if(task.isEqualTo(_normalTask[i])){
				_normalTask.erase(_normalTask.begin()+i);
				return true;
			}
		}
		break;
	}

	return false;

}

void TaskList::pushClashing(Task task, vector<Task>& _temp){

	for(unsigned int i = 0; i < _normalTask.size(); i++){

		if(_normalTask[i].isClashingWith(task)){
			_temp.push_back(_normalTask[i]);
		}
	}
}

void TaskList::searchTitle(string searchLine, vector<Task>& _temp){

	for(unsigned int i = 0; i < _floatingTask.size(); i++){

		if(_floatingTask[i].getTitle() == searchLine)
			_temp.push_back(_floatingTask[i]);
	}

	for(unsigned int i = 0; i < _deadlineTask.size(); i++){

		if(_deadlineTask[i].getTitle() == searchLine)
			_temp.push_back(_deadlineTask[i]);
	}

	for(unsigned int i = 0; i < _normalTask.size(); i++){

		if(_normalTask[i].getTitle() == searchLine)
			_temp.push_back(_normalTask[i]);
	}

}

void TaskList::appendVectors(vector<Task>& _temp){

	_temp = _floatingTask;
	_temp.insert(_temp.end(), _deadlineTask.begin(), _deadlineTask.end());
	_temp.insert(_temp.end(), _normalTask.begin(), _normalTask.end());

}

void TaskList::pushStatus(bool done, vector<Task>& _temp){

	for(unsigned int i = 0; i < _floatingTask.size(); i++){

		if(_floatingTask[i].getDone() == done)
			_temp.push_back(_floatingTask[i]);
	}

	for(unsigned int i = 0; i < _deadlineTask.size(); i++){

		if(_deadlineTask[i].getDone() == done)
			_temp.push_back(_deadlineTask[i]);
	}

	for(unsigned int i = 0; i < _normalTask.size(); i++){

		if(_normalTask[i].getDone() == done)
			_temp.push_back(_normalTask[i]);
	}

}

void TaskList::pushInRange(vector<Task>& _temp, BasicDateTime start, BasicDateTime end){

	Task tempTask;

	tempTask = Task("temp", start, end, 2, false, "comment");

	for(unsigned int i = 0; i < _normalTask.size(); i++){

		if(tempTask.isClashingWith(_normalTask[i]))
			_temp.push_back(_normalTask[i]);

	}

	for(unsigned int i = 0; i < _deadlineTask.size(); i++){

		if(isInRange(_deadlineTask[i].getEnd(), start, end))
			_temp.push_back(_deadlineTask[i]);

	}

}

bool TaskList::isSuccessfullyMarked(bool mark, Task task){

	switch(task.getType()){

	case FLOATING_TASK:
		for(unsigned int i = 0; i < _floatingTask.size(); i++){

			if(task.isEqualTo(_floatingTask[i])){
				_floatingTask[i].toggleDone();
				return true;
			}
		}
		break;
	case DEADLINE_TASK:
		for(unsigned int i = 0; i < _deadlineTask.size(); i++){

			if(task.isEqualTo(_deadlineTask[i])){
				_deadlineTask[i].toggleDone();
				return true;
			}
		}
		break;
	case NORMAL_TASK:
		for(unsigned int i = 0; i < _normalTask.size(); i++){

			if(task.isEqualTo(_normalTask[i])){
				_normalTask[i].toggleDone();
				return true;
			}
		}
		break;
	}

	return false;
}

void TaskList::pushOccupiedDates(vector<BasicDateTime>& usedDates){

	for(unsigned int i = 0; i < _normalTask.size(); i++){

		usedDates.push_back(_normalTask[i].getStart());
		usedDates.push_back(_normalTask[i].getEnd());
	}

	for(unsigned int i = 0; i < _deadlineTask.size(); i++){

		usedDates.push_back(_deadlineTask[i].getEnd());
	}

}

void TaskList::pushStatusInRange(bool done, BasicDateTime start, BasicDateTime end, vector<Task>& _temp){

	Task tempTask;

	tempTask = Task("temp", start, end, 2, false, "comment");

	for(unsigned int i = 0; i < _normalTask.size(); i++){

		if(tempTask.isClashingWith(_normalTask[i]) && _normalTask[i].getDone() == done)
			_temp.push_back(_normalTask[i]);

	}

	for(unsigned int i = 0; i < _deadlineTask.size(); i++){

		if(isInRange(_deadlineTask[i].getEnd(), start, end) && _normalTask[i].getDone() == done)
			_temp.push_back(_deadlineTask[i]);

	}
}
/*
vector<Task>* TaskList::returnTaskListPointer(){
return &(_taskList);
}
*/