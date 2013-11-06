#include "HelpUser.h"

const string HelpUser::HELP_GENERAL_MSG      = "Welcome to the help panel\n"
	                                           "Tasky is a text-based task management software. All you need to do is\n"
											   "type in the command following the right format and all the rest will\n"
											   "will be taken care of by the software. Have fun using it!\n"
											   "For additional help on a specific topic, you can try\n"
											   "help -add			for the help regarding to add operation\n"
											   "help -remove		for the help regarding to remove operation\n"
											   "help -search		for the help regarding to search operation\n"
											   "help -mark   		for the help regarding to mark operation\n"
											   "help -reschedule	for the help regarding to reschedule operation\n"
											   "help -rename		for the help regarding to rename operation\n"
											   "help -display		for the help regarding to display operation\n"
											   "help -title			for the help regarding to title\n"
											   "help -date			for the help regarding to date\n"
											   "help -time			for the help regarding to time\n"
											   "help -comment		for the help regarding to comment\n"
											   "help -others		for the help regarding to others\n"
											   "help -about			for the help regarding to about\n\n";
const string HelpUser::HELP_ADD_MSG          = "To add a task, enter one of the followings:\n"
	                                           "Format1: add '[Title]' from [StartDateTime] to [EndDateTime] -m [Comment]\n"
											   "Format2: add '[Title]' by [Deadline] -m [Comment]\n"
											   "Format3: add '[Title]' -m [Comment]\n"
											   "Note1: The title must be enclosed by two single quotes. Use help -title for more help\n"
											   "Note2: The various formats of date and time are explained in help -date and help -time\n"
											   "Note3: The comment is optional. Leave it blank if not applicable for you. help -comment for more help.\n";
const string HelpUser::HELP_REMOVE_MSG       = "To remove a task, enter the following:\n"
	                                           "Format: remove '[Title]'\n"
											   "If prompted for selection of task to remove, enter the number only."
											   "Note: The title must be enclosed by two single quotes. Use help -title for more help\n";
//this part is not yet done
const string HelpUser::HELP_SEARCH_MSG       = "To search for a task, enter the following:"
											   "\nsearch '[keyword1] [keyword2]'"
											   "\nTo search for a task within a time range, enter the following:"
											   "\nsearch '[keyword1] [keyword2]' from [StartDate] to [EndDate]";

const string HelpUser::HELP_MARK_MSG         = "To mark a task as Done/Pending, enter the following:\n"
											   "Format: mark '[Title]' done/pending\n"
											   "Note: The title must be enclosed by two single quotes. Use help -title for more help\n";
const string HelpUser::HELP_RESCHEDULE_MSG   = "To reschedule a task, enter one of the following:\n"
											   "Format1: reschedule '[Title]' from [NewStartDateTime] to [NewEndDateTime]\n"
											   "Format2: reschedule '[Title]' by [Deadline]\n"
											   "Format3: reschedule '[Title]'\n";
const string HelpUser::HELP_RENAME_MSG       = "To rename a task, enter the following:"
											   "\nrename '[Title]' to '[NewTaskName]'";
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
const string HelpUser::ADD_STR               = "-add";
const string HelpUser::REMOVE_STR            = "-remove";
const string HelpUser::SEARCH_STR            = "-search";
const string HelpUser::MARK_STR              = "-mark";
const string HelpUser::RESCHEDULE_STR        = "-reschedule";
const string HelpUser::RENAME_STR            = "-rename";
const string HelpUser::DISPLAY_STR           = "-display";
const string HelpUser::TITLE_STR             = "-title";
const string HelpUser::DATE_STR              = "-date";
const string HelpUser::TIME_STR              = "-time";
const string HelpUser::COMMENT_STR           = "-comment";
const string HelpUser::OTHERS_STR            = "-others";
const string HelpUser::ABOUT_STR             = "-about";

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
