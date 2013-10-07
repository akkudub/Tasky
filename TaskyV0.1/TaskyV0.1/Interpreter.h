#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <sstream>
#include <regex>
#include "Essential.h"
#include "Task.h"
#include "BasicDateTime.h"

class Interpreter {
private:
	string _title;
	int _type;
	BasicDateTime _start;
	BasicDateTime _end;


private:
	static const string EMPTY_STRING;
	static const string FROM_KEY_WORD;
	static const string TO_KEY_WORD;
	static const string BY_KEY_WORD;
	static const string DASH_M;

	static const char SLASH;
	static const char DOT;
    static const char COMMA;
	static const char SINGLE_QUOTE;
	static const char SPACE;
	static const char DASH;

public:
	Interpreter();
	///return status code
	int interpretAdd(string str, string& title, int& type, BasicDateTime& start, BasicDateTime& end, string& comment);
	///return status code; for search, -1 : failure; 0 : no dates; 2 :  with two dates;
	int interpretSearch(string str, vector<string>& keywords, BasicDateTime& start, BasicDateTime& end);
	///return status code; for display, -1 : failure; 0: all; 1 : status; 2 : with 2 datetimes;
	int interpretDisplay(string str, BasicDateTime& start, BasicDateTime& end, bool& status);
	///return status code; for update, -1: failure; 0 : success
	int interpretUpdate(string str, string& oldTitle, string& newTitle);
	///return status code; for reschedule, -1 : failue; 0 : sucess
	int interpretReschedule(string str, string& title, int& type, BasicDateTime& start, BasicDateTime& end);
	///return status code; for mark, -1 : failue; 0 : sucess
	int interpretMark(string str, string& title, bool& status);
	///return status code; for remove, -1 : failue; 0 : sucess
	int interpretRemove(string str, string& title);
	///return -1 if unable to convert
	int stringToInt(string);
	///return vector of integers based interpretation of the input
	vector<int> stringToIntVec(string str);
	///return string in lower case
	string toLowerCase(string input);
	///destructor
	~Interpreter();

private:
	bool extractTitle(const string& str, string& title, int& pos1, int& pos2);
	bool extractComment(const string& str, string& comment, int& pos);
	bool fromToCheck(string str);
	bool byCheck(string str);
	bool translateDateTime(string str1, string str2, string str3, string str4, int either);
	bool translateDate(string str1, string str2, string str3, int either);
	bool translateTime(string str1, int either);
	bool dateStandardInput(string str, int either);
	bool timeStandardInput(string str, char delim, int either);
	bool timeSpecialNumsOnly(string str, int either);
	vector<string> breakStringWithDelim(string str, char delim);
	void setTimeParam(int num1, int value, int either);
	string removeLeadingSpaces(string);
	void cleanUpPrivateVariables();
};

#endif
