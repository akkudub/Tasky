#include "UI.h"

void UI::UI_interface(){
	/*displayWelcomeMessage();*/
	string command;
	bool exitTextBuddy = false;
	while (!exitTextBuddy) {
		displayCommandMessage(command);
		if (shouldExit(command)) {
			exitTextBuddy = true;
		} else {
			displayProcessorMessage(command);
		}
	}
	displayExitMessage();
}
void UI::displayWelcomeMessage(){
	cout << MESSAGE_WELCOME <<endl;
	string output = _processor.mainProcessor(COMMAND_DISPLAY_TASK_PENDING);
	cout << output << endl;
}

void UI::displayCommandMessage(string& command){
	cout << MESSAGE_COMMAND;
	getline(cin, command);
}

void UI::displayProcessorMessage(string& command){
	string output = _processor.mainProcessor(command);
	cout << output << endl;
}

void UI::displayExitMessage(){
	cout << MESSAGE_GOODBYE <<endl;
	//should save again before closing program?
}

bool UI::shouldExit(string input){
	string c = input;
	convertLowerCase(c);
	if (COMMAND_EXIT.compare(c) == 0)
		return true;

	return false;
}

void UI::convertLowerCase(string& str){
	const int length = str.length();
	for(int i=0; i < length; ++i){
		str[i] = tolower(str[i]);
	}
}