#include "HelpUser.h"

const string HelpUser::HELP_GENERAL_MSG      = "";
const string HelpUser::HELP_ADD_MSG          = "";
const string HelpUser::HELP_REMOVE_MSG       = "";
const string HelpUser::HELP_SEARCH_MSG       = "";
const string HelpUser::HELP_MARK_MSG         = "";
const string HelpUser::HELP_RESCHEDULE_MSG   = "";
const string HelpUser::HELP_RENAME_MSG       = "";
const string HelpUser::HELP_DISPLAY_MSG      = "";
const string HelpUser::HELP_TITLE_MSG        = "";
const string HelpUser::HELP_DATE_MSG         = "";
const string HelpUser::HELP_TIME_MSG         = "";
const string HelpUser::HELP_COMMENT_MSG      = "";
const string HelpUser::HELP_OTHERS_MSG       = "";
const string HelpUser::HELP_ABOUT_MSG        = "";

const string HelpUser::GENERAL_STR           = "";
const string HelpUser::ADD_STR               = "add";
const string HelpUser::REMOVE_STR            = "remove";
const string HelpUser::SEARCH_STR            = "search";
const string HelpUser::MARK_STR              = "mark";
const string HelpUser::RESCHEDULE_STR        = "reschedule";
const string HelpUser::RENAME_STR            = "rename";
const string HelpUser::DISPLAY_STR           = "display";
const string HelpUser::TITLE_STR             = "title";
const string HelpUser::DATE_STR              = "date";
const string HelpUser::TIME_STR              = "time";
const string HelpUser::COMMENT_STR           = "comment";
const string HelpUser::OTHERS_STR            = "others";
const string HelpUser::ABOUT_STR             = "about";

string HelpUser::getHelpMsg(string input){
	int type=determineHelpType(input);
	return getMsg(type);
}

int HelpUser::determineHelpType(const string& input){
	return 0;
}

string HelpUser::getMsg(int type){
	return ABOUT_STR;
}

bool HelpUser::equalWithoutCase(const string& input, const string& keyword){
	return false;
}
