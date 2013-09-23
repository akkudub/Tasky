#ifndef _HISTORY_H_
#define _HISTORY_H_

#include "Essential.h"

class History{
private:
	vector<string> _historyRecord; //formatted strings from Processor
	
public:
	int undo(string&); //takes a string from Processor, reads last historyRecord, writes it into the
						// string reference.
	int record(string); //takes string and push into the historyRecord
	
};

#endif