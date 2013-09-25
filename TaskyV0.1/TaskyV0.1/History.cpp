#include "History.h"

History::History() {
	_historyRecord.clear();
}

int History::undo(string& hist) {
	int size = _historyRecord.size();
	if(!_historyRecord.empty()) {
		hist = _historyRecord.back();
		_historyRecord.pop_back();
		if (size - CHANGEINHISTORYSIZE == _historyRecord.size()) {
			return SUCCESS;
		}
	} else {
		return UNDO_WARNING_EMPTYLIST;
	}
	return UNDO_FAILURE;
}

int History::record(string hist) {
	int size = _historyRecord.size();
	_historyRecord.push_back(hist);
	if (size + CHANGEINHISTORYSIZE == _historyRecord.size()) {
		return SUCCESS;
	}
	return RECORD_FAILURE;
}