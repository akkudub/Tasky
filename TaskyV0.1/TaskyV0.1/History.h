#ifndef _HISTORY_H_
#define _HISTORY_H_

/*
 *This class is mainly to store previous successful operations. If undo is being called, undo will pop the latest
 *successful command to processor. And record will store the new command to _historyRecord
 *
 *Main author: Joan
*/

#include "Essential.h"

///record past sucessful operations and pop the last one when undo called

class History{
private:
	static const int CHANGE_IN_HISTORY_SIZE = 1;
private:
	vector<string> _historyRecord; //formatted strings from Processor
	
public:

	History();
	///pop out the last sucessful opeartion
	int undo(string& hist);
	///push a sucessful operation in history record
	int record(string hist);
	
};

#endif