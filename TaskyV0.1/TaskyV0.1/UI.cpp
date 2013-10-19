#include "UI.h"


void UI::UI_interface(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	string command;
	bool statusFlag = false;
	while (!statusFlag) {
		displayCommandMessage(command, hConsole);
		displayProcessorMessage(command, hConsole, statusFlag);
	}
	system("pause");
}


void UI::displayWelcomeMessage(HANDLE hConsole){
	cout << MESSAGE_WELCOME <<endl;
	bool alwaysFalse = false;
	displayProcessorMessage(COMMAND_DISPLAY_TASK_PENDING,hConsole,alwaysFalse);
}


void UI::displayCommandMessage(string& command, HANDLE hConsole){
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE |FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << MESSAGE_COMMAND;
	getline(cin, command);
}


void UI::displayProcessorMessage(string command, HANDLE hConsole, bool& statusFlag){
	string message;
	vector<string> feedback;
	int output = _processor.UImainProcessor(command, message, feedback);
	switch(output){
	case STATUS_CODE_SET_OVERALL::OVERALL_ERROR:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case STATUS_CODE_SET_OVERALL::OVERALL_SUCCESS:
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case STATUS_CODE_SET_OVERALL::OVERALL_WARNING:
	case STATUS_CODE_SET_OVERALL::OVERALL_PROMPT:
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN |FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case STATUS_CODE_SET_OVERALL::OVERALL_EXIT:
		statusFlag = true;
		break;
	}

	/*
	if (output ==  STATUS_CODE_SET_OVERALL::OVERALL_WARNING || output ==  STATUS_CODE_SET_OVERALL::OVERALL_PROMPT
		|| output ==  STATUS_CODE_SET_OVERALL::OVERALL_ERROR ) {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		int x;
		int y;
		if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
			x = csbi.dwCursorPosition.X;
			y = csbi.dwCursorPosition.Y;	 
		}
		char buf[1000];
		strcpy(buf, message.c_str());
		setBlinkingText(x, y, buf, 3, 800);
		cout<<endl;
	}else {
		cout << endl;
		cout << message << endl;
	}
	*/
	assert(!message.empty());
	cout << endl;
	cout << message << endl;

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE |FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	for (string str:feedback){
		cout << str << endl;
		cout << endl;
	}
	cout << endl;


}


void UI::setBlinkingText(int x, int y, char *buf, int timestoBlink, int delayMilliSecs){
	//assert(buf != NULL);

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
