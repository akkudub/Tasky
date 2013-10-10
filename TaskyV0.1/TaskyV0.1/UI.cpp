#include "UI.h"


void UI::UI_interface(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	/*displayWelcomeMessage();*/
	string command;
	bool exitTextBuddy = false;
	while (!exitTextBuddy) {
		displayCommandMessage(command);
		SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY);
		if (shouldExit(command)) {
			exitTextBuddy = true;
		} else {
			displayProcessorMessage(command, hConsole);
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


void UI::displayProcessorMessage(string command, HANDLE hConsole){
	string output = _processor.mainProcessor(command);
	//DO SOME COLOR PROCESSING HERE
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << output << endl;
}


void UI::displayExitMessage(){
	cout << MESSAGE_GOODBYE <<endl;
	//should save again before closing program?
}


bool UI::shouldExit(string command){
	string lowerCaseCommand = command;
	convertLowerCase(lowerCaseCommand);
	if (COMMAND_EXIT.compare(lowerCaseCommand) == 0)
		return true;

	return false;
}


void UI::convertLowerCase(string& str){
	const int length = str.length();
	for(int i=0; i < length; ++i){
		str[i] = tolower(str[i]);
	}
}