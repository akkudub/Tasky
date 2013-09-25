#ifndef _UI_H_
#define _UI_H_

#include <iostream>
#include "Processor.h"

using namespace std;

static const string MESSAGE_WELCOME = "Welcome!";
static const string MESSAGE_GOODBYE = "GoodBye!";
static const string MESSAGE_COMMAND = "Command: ";

static const string COMMAND_EXIT = "exit";
static string COMMAND_DISPLAY_TASK_PENDING = "display pending";

class UI
{
private:
	Processor _processor;
	void displayWelcomeMessage();	//should display welcome messages + task of the day
	void displayCommandMessage(string&);
	void displayProcessorMessage(string&);
	void displayExitMessage();
	bool shouldExit(string);
	void convertLowerCase(string&);
public:
	void interface(); //takes in user input
};

#endif