#include "UI.h"


void UI::UI_interface(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	/*displayWelcomeMessage();*/
	char buf[] = "I am Blinking!!!!\n";
    setBlinkingText(0, 1, buf, 5, 1000);
	string command;
	bool statusFlag = false;
	while (!statusFlag) {
		displayCommandMessage(command, hConsole);
		displayProcessorMessage(command, hConsole, statusFlag);
	}
	displayExitMessage();
}


void UI::displayWelcomeMessage(){
	cout << MESSAGE_WELCOME <<endl;
	string output = _processor.mainProcessor(COMMAND_DISPLAY_TASK_PENDING);
	cout << output << endl;
}


void UI::displayCommandMessage(string& command, HANDLE hConsole){
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE |FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << MESSAGE_COMMAND;
	getline(cin, command);
}


void UI::displayProcessorMessage(string command, HANDLE hConsole, bool& statusFlag){
	string output = _processor.mainProcessor(command);
	//DO SOME COLOR PROCESSING HERE
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << output << endl;
}


void UI::displayExitMessage(){
	cout << MESSAGE_GOODBYE <<endl;
}

void UI::setBlinkingText(int x, int y, char *buf, int timestoBlink, int delayMilliSecs){
    ::system("cls");
    COORD ord;
    ord.X = x;
    ord.Y = y; 

    int len = strlen(buf);
    char *p = new char[len + 1];
    memset(p, 32, len);
    p[len] = '\0';
    for(int i = 0; i < timestoBlink; i++){

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ord);
        std::cout << p;
        ::Sleep(300);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ord);
        std::cout << buf;
        ::Sleep(delayMilliSecs);
    }
}
