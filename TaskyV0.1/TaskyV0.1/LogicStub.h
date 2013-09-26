#include "Logic.h"

class LogicStub:public Logic{
	public:
	int add(Task, vector<Task>&);
	int remove(Task);
	int update(Task, Task, vector<Task>&);// old Task, new Task, Tasks that clash push into vector.
	int search(string, vector<Task>&); //search for tasks containing string, pushes into referenced vector
	int display(bool, vector<Task>&); //done=true, pending=false. pushes tasks into referenced vector.
	int mark(bool, Task);//done=true, pending=false. 
	vector<Task>* returnTaskListPointer();
};