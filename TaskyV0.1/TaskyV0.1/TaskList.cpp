#include "TaskList.h"
#include <assert.h>
#include <algorithm>

static const int FLOATING_TASK = 0;
static const int DEADLINE_TASK = 1;
static const int NORMAL_TASK = 2;
static const string STRING_DONE = "Done";
static const string STRING_FLOATING = "Floating";
static const string STRING_DEADLINE = "Deadline";
static const string STRING_TIMED = "Timed";
static const string STRING_NON = "None";

TaskList::TaskList(){
}

int TaskList::add(Task toAdd, vector<Task>& _temp){

	_temp.clear();

	if(isExisting(toAdd))
		return WARNING_ADD_DUPLICATE;

	if(toAdd.getType() == NORMAL_TASK)
		pushClashing(toAdd, _temp);

	addTask(toAdd);

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

	if(!_temp.empty())
		return SUCCESS_SEARCH;
	else
		return WARNING_SEARCH_NO_RESULT;

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

int TaskList::searchInRange(BasicDateTime start, BasicDateTime end, vector<Task>& _temp){

	_temp.clear();

	pushInRange(_temp, start, end);

	if(!_temp.empty())
		return SUCCESS_DISPLAY;
	else
		return WARNING_DISPLAY_NO_RESULT;

	return ERROR_DISPLAY;
}

int TaskList::searchStatusInRange(bool done, BasicDateTime start, BasicDateTime end, vector<Task>& _temp){

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

int TaskList::saveFile(){

	vector<Task> allTasks;

	appendVectors(allTasks);

	vector<string> allTasksString = taskVecToStringVec(allTasks);
	return _fileProcessing.save(allTasksString);
}

int TaskList::loadFile(){
	vector<string> stringsFromFile;
	string currStr;
	int count;

	string title, comment;
	int type;
	bool status;
	BasicDateTime start, end;

	_fileProcessing.load(stringsFromFile);

	for (unsigned int i = 0; i < stringsFromFile.size(); i++){

		currStr = stringsFromFile[i];

		switch (i % 6){
		case 0:
			if (currStr.substr(6) == STRING_FLOATING){
				type = 0;
			}else if (currStr.substr(6) == STRING_DEADLINE){
				type = 1;
			}else if (currStr.substr(6) == STRING_TIMED){
				type = 2;			
			}
			count++;
			break;
		case 1:
			title = currStr.substr(7);
			count++;
			break;
		case 2:
			if (currStr.substr(8) == STRING_DONE){
				status = true;
			}else{
				status = false;
			}
			count++;
			break;
		case 3:
			stringToBasicDateTime(currStr.substr(7), start);
			count++;
			break;
		case 4:
			stringToBasicDateTime(currStr.substr(5), end);
			count++;
			break;
		case 5:
			comment = currStr.substr(9);
			Task tempTask(title, start, end, type, status, comment);
			addTask(tempTask);
			count++;
			break;
		}
	}
	return 0;
}

void TaskList::addTask(Task toAdd){

	switch(toAdd.getType()){

	case FLOATING_TASK:
		_floatingTask.push_back(toAdd);
		break;
	case DEADLINE_TASK:
		_deadlineTask.push_back(toAdd);
		break;
	case NORMAL_TASK:
		_normalTask.push_back(toAdd);
		break;
	}
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

	stringToLower(exactString);

	for(unsigned int i = 0; i < _duplicateFloating.size(); i++){

		string tempString = _duplicateFloating[i].getTitle();

		if(stringToLower(tempString) == exactString){
			_temp.push_back(_duplicateFloating[i]);
			_duplicateFloating.erase(_duplicateFloating.begin()+i);
			i--;
		}
	}


	for(unsigned int i = 0; i < _duplicateDeadline.size(); i++){

		string tempString = _duplicateDeadline[i].getTitle();

		if(stringToLower(tempString) == exactString){
			_temp.push_back(_duplicateDeadline[i]);
			_duplicateDeadline.erase(_duplicateDeadline.begin()+i);
			i--;
		}
	}


	for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

		string tempString = _duplicateNormal[i].getTitle();

		if(stringToLower(tempString) == exactString){
			_temp.push_back(_duplicateNormal[i]);
			_duplicateNormal.erase(_duplicateNormal.begin()+i);
			i--;
		}
	}


}

void TaskList::containingExactStringSearch(string exactString, vector<Task>& _temp){

	stringToLower(exactString);

	for(unsigned int i = 0; i < _duplicateFloating.size(); i++){

		string tempString = _duplicateFloating[i].getTitle();

		if(tempString.find(exactString) != std::string::npos){
			_temp.push_back(_duplicateFloating[i]);
			_duplicateFloating.erase(_duplicateFloating.begin()+i);
			i--;
		}
	}


	for(unsigned int i = 0; i < _duplicateDeadline.size(); i++){

		string tempString = _duplicateDeadline[i].getTitle();

		if(tempString.find(exactString) != std::string::npos){
			_temp.push_back(_duplicateDeadline[i]);
			_duplicateDeadline.erase(_duplicateDeadline.begin()+i);
			i--;
		}
	}


	for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

		string tempString = _duplicateNormal[i].getTitle();

		if(tempString.find(exactString) != std::string::npos){
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

	stringToLower(exactString);

	for(unsigned int i = 0; i < _duplicateDeadline.size(); i++){

		string tempString = _duplicateDeadline[i].getTitle();

		if(stringToLower(tempString) == exactString && isInRange(_duplicateDeadline[i].getEnd(), start, end)){
			_temp.push_back(_duplicateDeadline[i]);
			_duplicateDeadline.erase(_duplicateDeadline.begin()+i);
			i--;
		}
	}


	Task tempTask;
	tempTask = Task("temp", start, end, 2, false, "comment");

	for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

		string tempString = _duplicateNormal[i].getTitle();

		if(stringToLower(tempString) == exactString  && tempTask.isClashingWith(_duplicateNormal[i])){
			_temp.push_back(_duplicateNormal[i]);
			_duplicateNormal.erase(_duplicateNormal.begin()+i);
			i--;
		}
	}


}


void TaskList::containingExactStringSearchWithRange(string exactString, vector<Task>& _temp, BasicDateTime start, BasicDateTime end){

	stringToLower(exactString);

	for(unsigned int i = 0; i < _duplicateDeadline.size(); i++){

		string tempString = _duplicateDeadline[i].getTitle();

		if(stringToLower(tempString).find(exactString) != std::string::npos && isInRange(_duplicateDeadline[i].getEnd(), start, end)){
			_temp.push_back(_duplicateDeadline[i]);
			_duplicateDeadline.erase(_duplicateDeadline.begin()+i);
			i--;
		}
	}



	Task tempTask;
	tempTask = Task("temp", start, end, 2, false, "comment");

	for(unsigned int i = 0; i < _duplicateNormal.size(); i++){

		string tempString = _duplicateNormal[i].getTitle();

		if(stringToLower(tempString).find(exactString) != std::string::npos && tempTask.isClashingWith(_duplicateNormal[i])){
			_temp.push_back(_duplicateNormal[i]);
			_duplicateNormal.erase(_duplicateNormal.begin()+i);
			i--;
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

		if(!isExistingDate(_normalTask[i].getStart(), usedDates))
			usedDates.push_back(_normalTask[i].getStart());

		if(!isExistingDate(_normalTask[i].getEnd(), usedDates))
			usedDates.push_back(_normalTask[i].getEnd());
	}

	for(unsigned int i = 0; i < _deadlineTask.size(); i++){

		if(!isExistingDate(_deadlineTask[i].getEnd(), usedDates))
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

vector<string> TaskList::taskVecToStringVec(vector<Task>& allTasks){

	vector<string> taskLines;
	vector<string> temp;

	for (unsigned int i = 0; i < allTasks.size(); i++){
		temp = allTasks[i].toStringVector();
		taskLines.insert(taskLines.end(), temp.begin(), temp.end());
	}

	return taskLines;
}

void TaskList::stringToBasicDateTime(string dateTimeString, BasicDateTime& bdt){

	if(dateTimeString == STRING_NON)
		return;
	


}

string TaskList::stringToLower(string& toLowerString){

	std::transform(toLowerString.begin(), toLowerString.end(), toLowerString.begin(), ::tolower);

	return toLowerString;

}

bool TaskList::isExistingDate(BasicDateTime date, vector<BasicDateTime> vector){

	for(unsigned int i = 0; i < vector.size(); i++){

		if(vector[i].compareTo(date) == 0)
			return true;

	}
}

/*
vector<Task>* TaskList::returnTaskListPointer(){
return &(_taskList);
}
*/