#include "UI.h"

/*Purpose:
* Function called when program is started up
* Takes in user input/commands and passes to Processor
* Checks if user wishes to exit the program
*/
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

/*Purpose:
* Displays a welcome message to the user
* Displays the tasks of the day/pending tasks
*/
void UI::displayWelcomeMessage(){
	cout << MESSAGE_WELCOME <<endl;
	string output = _processor.mainProcessor(COMMAND_DISPLAY_TASK_PENDING);
	cout << output << endl;
}

/*Purpose:
* Takes in user command & put into string command
* 
* Param:
* command - stores the user input 
*/
void UI::displayCommandMessage(string& command){
	cout << MESSAGE_COMMAND;
	getline(cin, command);
}

/*Purpose:
* Send the user's command to the Processor
*
* Param:
* command - user input to be passed to Processor 
*/
void UI::displayProcessorMessage(string command){
	string output = _processor.mainProcessor(command);
	cout << output << endl;
}

/*Purpose:
* Display Closing Message before exiting the program
* Possible to save the tasks to the Log before exiting
*/
void UI::displayExitMessage(){
	cout << MESSAGE_GOODBYE <<endl;
	//should save again before closing program?
}

/*Purpose:
* Checks if the user wishes to exit
*
* Param:
* command - stores the user input 
*
* Returns:
* True- Exit, False - Do Not Exit
*/
bool UI::shouldExit(string command){
	string lowerCaseCommand = command;
	convertLowerCase(lowerCaseCommand);
	if (COMMAND_EXIT.compare(lowerCaseCommand) == 0)
		return true;

	return false;
}

/*Purpose:
* Converts the user command to lower casing
*
* Param:
* str - string to be converted to lower case
*/
void UI::convertLowerCase(string& str){
	const int length = str.length();
	for(int i=0; i < length; ++i){
		str[i] = tolower(str[i]);
	}
}