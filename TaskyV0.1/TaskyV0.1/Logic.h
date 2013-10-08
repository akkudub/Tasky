#ifndef _LOGIC_H_
#define _LOGIC_H_

/*
 *This class is mainly to store tasks and manipulate tasks according to processor's command.
 *
 *Main author: Kai Wen
*/

#include "Essential.h"
#include "Task.h"

class Logic{
private:
	vector<Task> _taskList;
	
public:
	Logic();
	///adds the task to the taskList. Pushes any tasks that clashes into the referenced vector
	int add(Task toAdd, vector<Task>& _temp);
	/// finds a task in the vector that isEqual to the task to be removed and removes it.
	int remove(Task toRemove);
	///clears temp, then pushes tasks that that has the same title as searchLine into temp.
	int search(string searchLine, vector<Task>& _temp); 
	///searches for tasks corresponding to the keywords and pushes those tasks by relevance into referenced vector.
	int searchKeywords(vector<string> keywords, vector<Task>& _temp);
	///same as searchKeywords but only searches for tasks that are in range.
	int searchKeywordsInRange(vector<string> keywords, vector<Task>& _temp, BasicDateTime start, BasicDateTime end);
	///pushes all tasks into referenced vector
	int displayAll(vector<Task>& _temp);
	///pushes tasks that are done/pending accordingly into referenced vector; done: true, pending:false;
	int displayStatus(bool done, vector<Task>& _temp);
	///pushes tasks in range into referenced vector
	int displayInRange(BasicDateTime start, BasicDateTime end, vector<Task>& _temp);
	///updates the existing task into the new task. any tasks that clashes will be pushed into referenced vector.
	int update(Task existingTask, Task newTask, vector<Task>& _temp);
	///marks the task as done or pending
	int mark(bool mark, Task task);

};

#endif
