#include "HelpUser.h"

const string HelpUser::HELP_GENERAL_MSG      = "Welcome to Tasky Help."
											   "\nFor full definition of user commands please refer to the user manual.";
const string HelpUser::HELP_ADD_MSG          = "To add a task, enter one of the following:"
											   "\nadd '[Task] from [StartDate] to [EndDate] or"
											   "\nadd '[Task]' by [Deadline] or"
											   "\nadd '[Task]'";
const string HelpUser::HELP_REMOVE_MSG       = "To remove a task, enter the following:"
											   "\nremove '[Task]'"
											   "\nIf prompted for selection of task to remove, enter the number only.";
const string HelpUser::HELP_SEARCH_MSG       = "To search for a task, enter the following:"
											   "\nsearch '[keyword1] [keyword2]'"
											   "\nTo search for a task within a time range, enter the following:"
											   "\nsearch '[keyword1] [keyword2]' from [StartDate] to [EndDate]";
const string HelpUser::HELP_MARK_MSG         = "To mark a task as Done/Pending, enter the following:"
											   "\nmark '[Task]' done/pending";
const string HelpUser::HELP_RESCHEDULE_MSG   = "To reschedule a task, enter one of the following:"
											   "\nreschedule '[Task]' from [NewStartDate] to [NewEndDate]"
											   "\nreschedule '[Task]' by [Deadline]"
											   "\nreschedule '[Task]'";
const string HelpUser::HELP_RENAME_MSG       = "To rename a task, enter the following:"
											   "\nrename '[Task]' to '[NewTaskName]'";
const string HelpUser::HELP_DISPLAY_MSG      = "To display all tasks: display all"
											   "\nTo display pending tasks: display pending"
											   "\nTo display today's task: display today";
const string HelpUser::HELP_TITLE_MSG        = "";
const string HelpUser::HELP_DATE_MSG         = "Please enter the date in DD/MM/YYYY format.";
const string HelpUser::HELP_TIME_MSG         = "Please enter the time in HH.MM format.";
const string HelpUser::HELP_COMMENT_MSG      = "To add a comment behind a task, use -m after the add command."
												"\nFor example: add 'Shopping For XMas Gifts' by 25/12/2013 -m bring recepient list";
const string HelpUser::HELP_OTHERS_MSG       = "For more information, please refer to Tasky User Manual.";
const string HelpUser::HELP_ABOUT_MSG        = "Developed by AY2013 Semester1 CS2103 F09-2C Team.";

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
