#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <sstream>
#include <regex>
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
	static const string PENDING_KEY_WORD;
	static const string DONE_KEY_WORD;
	static const string UPDATE_KEY_WORD;
	static const string ALL_KEY_WORD;
	static const string THIS_KEY_WORD;
	static const string NEXT_KEY_WORD;
	static const string MON_KEY_WORD;
	static const string TUE_KEY_WORD;
	static const string WED_KEY_WORD;
	static const string THU_KEY_WORD;
	static const string FRI_KEY_WORD;
	static const string SAT_KEY_WORD;
	static const string SUN_KEY_WORD;
	static const string TODAY_KEY_WORD;
	static const string TOMORROW_KEY_WORD;

	static const char SLASH;
	static const char DOT;
    static const char COMMA;
	static const char SINGLE_QUOTE;
	static const char SPACE;
	static const char DASH;
	static const char COLON;

public:
	///construtor: quite dummy for now
	Interpreter();
	/**
	 *@param str (string) input from processor
	 *@param title (string reference) will change the content of the string if the input format is correct, contain the title
	 *@param type (string reference) will change the content of the innt if the input format is correct, stating 0--floating; 1--deadline; 2--timed
	 *@param start (BasicDateTime reference) will change the value of start if format is correct
	 *@param start (BasicDateTime reference) will change the value of end if format is correct
	 *@param start (BasicDateTime reference) will change the value of comment if format is correct, will be empty string not input
	 *@return int status code, will be further defined later
	 */
	int interpretAdd(string str, string& title, int& type, BasicDateTime& start, BasicDateTime& end, string& comment);
	/**
	 *@param str input string from processor
	 *@param keywords (vector<string> reference) will push the orignal quoted content into the vector first and will break the content into  separate words and push in
	 *@param start (BasicDateTime reference) will have the new value if the input format is right
	 *@param end (BasicDateTime reference) will have the new value if the input format is right
	 *@return int status code, -1: failue; 0: no dates; 2: with two dates;
	 */
	int interpretSearch(string str, vector<string>& keywords, BasicDateTime& start, BasicDateTime& end);
	/**
	 *@param str (string) input from processor
	 *@param start (BasicDateTime reference) will have the new value if the input format is right
	 *@param end (BasicDateTime reference) will have the new value if the input format is right
	 *@param status (bool refernce) will have true--done false pending if the user has specified
	 */
	int interpretDisplay(string str, BasicDateTime& start, BasicDateTime& end, bool& status);
	/**
	 *@param str (string) input from processor
	 *@param oldTitle (string reference) will have the extracted the first qouted string
	 *@param newTitle (string reference) will have the extracted the second quoted string
	 *@return int status code--will be further defined later, right now -1 means failure and 0 means success
	 */
	int interpretRename(string str, string& oldTitle, string& newTitle);
	/**
	 *@param str (string) input from processor
	 *@param title (string reference) will have the value of the extracted quoted string
	 *@param type (int reference) will be changed according to input: 0--floating; 1--deadline task; 2--timed task;
	 *@param start (BasicDateTime reference) will be changed if the input date time format is right
	 *@param end (BasicDateTime reference) will be changed if the input date time format is right
	 *@return int status code--0: success; -1: failure
	 */
	int interpretReschedule(string str, string& title, int& type, BasicDateTime& start, BasicDateTime& end);  //does not work
	/**
	 *@param str (string) input from processor
	 *@param title (string reference) will have the value of the extracted quoted string
	 *@param status (bool reference) will set the value of status: true--done; false--pending
	 *@return int status code--0: success; -1: failure
	 */
	int interpretMark(string str, string& title, bool& status);
	/**
	 *@param str (string) input from processor
	 *@param title (string reference) will have the value of the extracted quoted string
	 *@return int status code--0: success; -1: failure
	 */
	int interpretRemove(string str, string& title);
	/**
	 *@param str (string) input string
	 *@return try to parse the string to int, if failure then return -1
	 */
	int stringToInt(string str);
	/**
	 * 1, 3, 4, 5--return <1, 3, 4, 5>;  1-5--return <1, 2, 3, 4, 5>
	 *@param str (string) input string
	 *@return a vector of integers
	 */
	vector<int> stringToIntVec(string str);  //does not work
	/**
	 *@param input (string)
	 *@return string of the input string 
	 */
	string toLowerCase(string input);
	///destructor
	~Interpreter();

private:
	bool extractTitle(const string& str, string& title, int& pos1, int& pos2);
	bool extractComment(const string& str, string& comment, int& pos);
	bool fromToCheck(string str);
	bool byCheck(string str);
	bool translateDateTime(string str1, string str2, int either);  //will take in more strings as we progress
	int extractDateTimeForReschdule(string str);
	bool translateDate(string str1, int either);  //will take in more strings as we progress
	bool translateTime(string str1, int either);
	bool dateStandardInput(string str, int either);
	bool dateTodayOrTomorrow(string str, int either);
	bool dateNextDateFormat(string str1, string str2, int either);  //not allowed for now
	bool timeStandardInput(string str, char delim, int either);
	bool timeSpecialNumsOnly(string str, int either);
	vector<string> breakStringWithDelim(string str, char delim);
	void setDateParams(int yearValue, int monthValue, int dayValue, int either);
	void setTimeParams(int hourValue, int minuteValue, int secondValue, int either);
	string removeLeadingSpaces(string str);
	string removeTailSpaces(string str);
	string removeSpacesFromBothEnds(string str);
	int findFirstOfWord(const string& source, const string& word);
	int findLastOfWord(const string& source, const string& word);
};

#endif
