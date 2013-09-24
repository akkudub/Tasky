#ifndef _UI_H_
#define _UI_H_

#include <iostream>
#include "Processor.h"

using namespace std;

class UI
{
private:
	Processor _processor;
	
public:
	void interface(); //takes in user input
};

#endif