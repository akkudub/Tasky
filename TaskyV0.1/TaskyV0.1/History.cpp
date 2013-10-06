#include "History.h"

/*Purpose:
* Clears the vector containing history actions upon start up
*/
History::History() {
}

/*Purpose:
* Retrieves the last action from vector of history records
*
* Param:
* hist - last action done will be passed back to calling function
* via this referenced string
*
* Returns:
* Success in retrival; Empty records, nothing to be undone; Failure
*/
int History::undo(string& hist) {
	int size = _historyRecord.size();
	if(!_historyRecord.empty()) {
		hist = _historyRecord.back();
		_historyRecord.pop_back();
		if (size - CHANGE_IN_HISTORY_SIZE == _historyRecord.size()) {
			return SUCCESS;
		}
	} else {
		return UNDO_WARNING_EMPTYLIST;
	}
	return UNDO_FAILURE;
}

/*Purpose:
* saves the successful action into vectory of history records
*
* Param:
* hist - string containing successful user action preformed
*
* Returns:
* Success in putting the record into history; Failure
*/
int History::record(string hist) {
	int size = _historyRecord.size();
	_historyRecord.push_back(hist);
	if (size + CHANGE_IN_HISTORY_SIZE == _historyRecord.size()) {
		return SUCCESS;
	}
	return RECORD_FAILURE;
}