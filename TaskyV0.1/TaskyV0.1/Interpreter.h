#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <sstream>
#include <regex>
#include "Essential.h"
#include "Task.h"
#include "BasicDateTime.h"

class Interpreter {
private:
	vector<string>* _wordsList;
	string _title;
	int _type;
	BasicDateTime _start;
	BasicDateTime _end;


private:
	static const string EMPTY_STRING;
	static const string NEW_LINE_STRING;
	static const string FROM_KEY_WORD;
	static const string TO_KEY_WORD;
	static const string BY_KEY_WORD;

	static const char NEW_LINE;
	static const char SLASH;
	static const char BACK_SLASH;
	static const char DOT;
	static const char COLON;
	static const char DASH;
	static const char ZERO;
	static const char NINE;
	static const char SPACE;

public:
	Interpreter();
	///return status code
	int interpretAdd(string str, string& title, int& type, BasicDateTime& start, BasicDateTime& end, string& comment);
	///return status code; for search, -1 : failure; 0 : no dates; 2 :  with two dates;
	int interpretSearch(string str, vector<string>& keywords, BasicDateTime& start, BasicDateTime& end);
	///return status code; for display, -1 : failure; 0: all; 1 : status; 2 : with 2 datetimes;
	int interpretDisplay(string str, BasicDateTime& start, BasicDateTime& end, bool& status);
	///
	int interpretUpdate(string str, string& oldTitle, string& newTitle);
	///
	int interpretReschedule(string str, string& title, int& type, BasicDateTime& start, BasicDateTime& end);
	///
	int interpretMark(string str, string& title, bool& status);
	///
	int interpretRemove(string str, string& title);
	///
	vector<int> stringToIntVec(string str);
	///return string in lower case
	string toLowerCase(const string& input);
	///return -1 if unable to convert
	int stringToInt(string);
	~Interpreter();

private:
	vector<int> identifyKeyWordsCreatingTask();
	bool fromToCheck(int pos1, int pos2);
	bool byCheck(int pos1);
	bool translateDateTime(string str1, string str2, string str3, string str4, int either);
	bool translateDate(string str1, string str2, string str3, int either);
	bool translateTime(string str1, int either);
	bool dateStandardInput(string str, int either);
	bool timeStandardInput(string str, char delim, int either);
	bool timeSpecialNumsOnly(string str, int either);

	void setTimeParam(int num1, int value, int either);

	int breakIntoStringVectorBySpace(const string& str);
	int stringToInt(string);
	string combineStringsWithNewLine(string, string);
	string removeLeadingSpaces(string);
	int characterType(char);

	void cleanUpPrivateVariables();
};

#endif
