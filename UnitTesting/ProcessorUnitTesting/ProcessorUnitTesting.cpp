// TaskyTest.cpp : Defines the entry point for the console application.
#include "gtest/gtest.h"
#include "Processor.h"
#include <string>

const string NEWLINE = "\n";

string message, expected, actual;
vector<string> outStrings;
int statusCode;

/*add a normal task with all parameters*/
TEST(message_addSingle, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2013 08.00 to 22/11/2013 09.00", message, outStrings);
	EXPECT_EQ("Success! Task added",message);
}

TEST(outStrings_addSingleNormal, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2013 08.00 to 22/11/2013 09.00 -m Adding comment", message, outStrings);
	expected = "Task Added:"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2013 08:00:00\n"
		"End time:   22/11/2013 09:00:00\n"
		"Comment:    Adding comment";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

TEST(outStrings_addSingleDeadline, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' by 21/11/2013 08.00", message, outStrings);
	expected = "Task Added:"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: None\n"
		"End time:   21/11/2013 08:00:00\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

TEST(outStrings_addSingleFloating, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1'", message, outStrings);
	expected = "Task Added:"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: None\n"
		"End time:   None\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

/* add existing task */
TEST(message_addExisting, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2013 08.00 to 22/11/2013 09.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2013 08.00 to 22/11/2013 09.00", message, outStrings);
	EXPECT_EQ("Error! Task already exists. Task not added",message);
}

/*add a normal task which clashes*/
TEST(message_addClash, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2013 08.00 to 22/11/2013 09.00", message, outStrings);

	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 21/11/2013 to 22/11/2013", message, outStrings);
	EXPECT_EQ("Warning! Task clashes with existing ones",message);
}

TEST(outStrings_addClash1, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2013 08.00 to 22/11/2013 09.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 21/11/2013 08.00 to 22/11/2013 12.00", message, outStrings);
	expected = "Task Added:"
		"Title:      test case 2\n"
		"Status:     Pending\n"
		"Start time: 21/11/2013 08:00:00\n"
		"End time:   22/11/2013 12:00:00\n"
		"Comment:    "
		"Clashes:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2013 08:00:00\n"
		"End time:   22/11/2013 09:00:00\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3];
	EXPECT_EQ(expected,actual);
}

TEST(outStrings_addClash2, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2013 08.00 to 22/11/2013 09.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 21/11/2013 08.00 to 22/11/2013 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 3' from 20/11/2013 to 23/11/2013", message, outStrings);
	expected = "Task Added:"
		"Title:      test case 3\n"
		"Status:     Pending\n"
		"Start time: 20/11/2013 00:00:00\n"
		"End time:   23/11/2013 00:00:00\n"
		"Comment:    "
		"Clashes:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2013 08:00:00\n"
		"End time:   22/11/2013 09:00:00\n"
		"Comment:    "
		"Task no:    2\n"
		"Title:      test case 2\n"
		"Status:     Pending\n"
		"Start time: 21/11/2013 08:00:00\n"
		"End time:   22/11/2013 12:00:00\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3]+outStrings[4];
	EXPECT_EQ(expected, actual);
}

/*border case for task clash, SHOULD be identified as clashing*/

TEST(outStrings_addBorderClashPlus, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2013 to 22/11/2013 12.00", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2013 11.59 to 24/11/2013", message, outStrings);
	expected = "Task Added:"
		"Title:      test case 2\n"
		"Status:     Pending\n"
		"Start time: 22/11/2013 11:59:00\n"
		"End time:   24/11/2013 00:00:00\n"
		"Comment:    "
		"Clashes:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2013 00:00:00\n"
		"End time:   22/11/2013 12:00:00\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3];
	EXPECT_EQ(expected, actual);
}

TEST(outStrings_addBorderClashMinus, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2013 16.00 to 22/11/2013", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 20/11/2013 to 21/11/2013 16.01", message, outStrings);
	expected = "Task Added:"
		"Title:      test case 2\n"
		"Status:     Pending\n"
		"Start time: 20/11/2013 00:00:00\n"
		"End time:   21/11/2013 16:01:00\n"
		"Comment:    "
		"Clashes:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2013 16:00:00\n"
		"End time:   22/11/2013 00:00:00\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1]+outStrings[2]+outStrings[3];
	EXPECT_EQ(expected, actual);}

/*border case for task clash, SHOULD NOT be identified as clashing*/
TEST(message_addBorderNoClash, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2013 to 22/11/2013", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2013 to 24/11/2013", message, outStrings);
	EXPECT_EQ("Success! Task added",message);
}

TEST(outStrings_addBorderNoClash, add){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2013 to 22/11/2013", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2013 to 24/11/2013", message, outStrings);
	expected = "Task Added:"
		"Title:      test case 2\n"
		"Status:     Pending\n"
		"Start time: 22/11/2013 00:00:00\n"
		"End time:   24/11/2013 00:00:00\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}
/* single remove*/
TEST(message_remove, remove){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2013 to 22/11/2013", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2013 to 24/11/2013", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("remove 'test case 1'", message, outStrings);
	EXPECT_EQ("Success! Task removed",message);
}

TEST(outStrings_remove, remove){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2013 to 22/11/2013", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2013 to 24/11/2013", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("remove 'test case 1'", message, outStrings);
	expected = "Tasks removed:"
		"Task no:    1\n"
		"Title:      test case 1\n"
		"Status:     Pending\n"
		"Start time: 21/11/2013 00:00:00\n"
		"End time:   22/11/2013 00:00:00\n"
		"Comment:    ";
	actual = outStrings[0]+outStrings[1];
	EXPECT_EQ(expected, actual);
}

TEST(message_removeInvalid, remove){
	remove("Tasky.txt");
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'test case 1' from 21/11/2013 to 22/11/2013", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("add 'test case 2' from 22/11/2013 to 24/11/2013", message, outStrings);
	statusCode = tempProcessor.UImainProcessor("remove 'test case 3'", message, outStrings);
	EXPECT_EQ("Warning! No such task",message);
}
