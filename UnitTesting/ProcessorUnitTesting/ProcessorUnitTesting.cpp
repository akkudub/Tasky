// TaskyTest.cpp : Defines the entry point for the console application.
#include "gtest/gtest.h"
#include "Processor.h"

string message;
vector<string> outStrings;
int statusCode;

/*add a normal task with all parameters*/
TEST(message_addSingleNormal, add){
	Processor tempProcessor;
	outStrings.clear();
	statusCode = tempProcessor.UImainProcessor("add 'testing case 1' from 21/11/2013 08.00 to 22/11/2013 09.00", message, outStrings);
	EXPECT_EQ("Success! Task added",message);
}

TEST(outStrings_addSingleNormal, add){
	Processor tempProcessor;
	outStrings.clear();
	statusCode = tempProcessor.UImainProcessor("add 'testing case 1' from 21/11/2013 08.00 to 22/11/2013 09.00", message, outStrings);
	EXPECT_EQ("Type: Timed task\nTitle: testing case 1\nStatus: Pending\nStart time: 21/11/2013 08:00:00\nEnd time: 22/11/2013 09:00:00\nComment: ", outStrings[0]);
}

/*add a normal task which clashes*/
TEST(message_addClash, add){
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'testing case 1' from 21/11/2013 08.00 to 22/11/2013 09.00", message, outStrings);
	outStrings.clear();
	statusCode = tempProcessor.UImainProcessor("add 'testing case 2' from 21/11/2013 to 22/11/2013", message, outStrings);
	EXPECT_EQ("Warning! Task clashes with existing ones",message);
}

TEST(outStrings_addClash, add){
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'testing case 1' from 21/11/2013 08.00 to 22/11/2013 09.00", message, outStrings);
	outStrings.clear();
	statusCode = tempProcessor.UImainProcessor("add 'testing case 2' from 21/11/2013 to 22/11/2013", message, outStrings);
	EXPECT_EQ("Type: Timed task\nTitle: testing case 1\nStatus: Pending\nStart time: 21/11/2013 08:00:00\nEnd time: 22/11/2013 09:00:00\nComment: ",outStrings[0]);
}

/*border case for task clash, SHOULD be identified as clashing*/
TEST(message_addBorderClash, add){
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'testing case 1' from 21/11/2013 to 22/11/2013 12.00", message, outStrings);
	outStrings.clear();
	statusCode = tempProcessor.UImainProcessor("add 'testing case 2' from 22/11/2013 11.59 to 24/11/2013", message, outStrings);
	EXPECT_EQ("Warning! Task clashes with existing ones",message);
}

TEST(outStrings_addBorderClash, add){
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'testing case 1' from 21/11/2013 to 22/11/2013 12.00", message, outStrings);
	outStrings.clear();
	statusCode = tempProcessor.UImainProcessor("add 'testing case 2' from 22/11/2013 11.59 to 24/11/2013", message, outStrings);
	EXPECT_EQ("Type: Timed task\nTitle: testing case 1\nStatus: Pending\nStart time: 21/11/2013 00:00:00\nEnd time: 22/11/2013 12:00:00\nComment: ",outStrings[0]);
}

/*border case for task clash, SHOULD NOT be identified as clashing*/
TEST(message_addBorderNoClash, add){
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'testing case 1' from 21/11/2013 to 22/11/2013", message, outStrings);
	outStrings.clear();
	statusCode = tempProcessor.UImainProcessor("add 'testing case 2' from 22/11/2013 to 24/11/2013", message, outStrings);
	EXPECT_EQ("Success! Task added",message);
}

TEST(outStrings_addBorderNoClash, add){
	Processor tempProcessor;
	statusCode = tempProcessor.UImainProcessor("add 'testing case 1' from 21/11/2013 to 22/11/2013", message, outStrings);
	outStrings.clear();
	statusCode = tempProcessor.UImainProcessor("add 'testing case 2' from 22/11/2013 to 24/11/2013", message, outStrings);
	EXPECT_EQ("Type: Timed task\nTitle: testing case 2\nStatus: Pending\nStart time: 22/11/2013 00:00:00\nEnd time: 24/11/2013 00:00:00\nComment: ",outStrings[0]);
}
//
//int main(int argc, char **argv) {
//	::testing::InitGoogleTest(&argc, argv);
//	return RUN_ALL_TESTS();
//}
