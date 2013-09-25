#ifndef _HISTORY_H_
#define _HISTORY_H_

/*
 *This class is mainly to store previous successful operations. If undo is being called, undo will pop the latest
 *successful command to processor. And record will store the new command to _historyRecord
 *
 *Main author: Joan
*/

#include "Essential.h"

static const int CHANGEINHISTORYSIZE = 1;

class History{
private:
	vector<string> _historyRecord; //formatted strings from Processor
	
public:
	History();
	int undo(string&); //takes a string from Processor, reads last historyRecord, writes it into the
						// string reference.
	int record(string); //takes string and push into the historyRecord
	
};

#endif