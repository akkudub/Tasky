#include "Processor.h"

Processor::Processor(){
	_taskListPointer=_logic.returnTaskListPointer();
	_statusFlag=0;
}

Processor::~Processor(){
	delete _wordsList;
}
