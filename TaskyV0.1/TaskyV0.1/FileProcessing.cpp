#include "FileProcessing.h"

/*Purpose:
* Checks if file Log exists
* If it exists, reads and load the tasks from file Log into vector<string> data
* 
* Param:
* data - vector to be loaded with tasks from Log
*
* Returns:
* Success in loading file; File Log does not exist; File Log is empty
*/
int FileProcessing::load(vector<string>& data){
	ifstream input(_LOGNAME);
	if(!input.is_open()) {
		return LOAD_FAILURE_OPENFILE;
	} else {
		if (input.good()) {
			if (!emptyFile()) {
				data.clear();
				while(input) {
					string line;
					getline(input, line);
					data.push_back(line);
				}
			} else {
				input.close();
				return LOAD_WARNING_EMPTYFILE;	
			}
		} else {
			return LOAD_FAILURE_OPENFILE;
		}
	}
	input.close();
	return SUCCESS;
}

/*Purpose:
* Checks if file Log exist
* If it exists, writes the task from vector<string> data into file Log
* If it does not exist, create a file Log
* 
* Param:
* data - vector containing all the tasks to be written
*
* Returns:
* Success in writing file; failure in writing file
*/
int FileProcessing::save(vector<string>& data){
	ofstream output(_LOGNAME);
	//check if file exist
	if (!output.is_open()) {
		output.clear();
		output.open(_LOGNAME, ofstream::out|ofstream::trunc);
	}
	//check if file is created, ready for writing
	if (output.good()) {
		for(string s:data) {
			output << s << endl;
		}
	} else {
		output.close();
		return SAVE_FAILURE_SAVEFILE;
	}
	output.close();
	return SUCCESS;
}

/*Purpose:
* Checks if the file Log is empty
*
* Return:
* True - File Log is empty, False - File Log not empty
*/
bool FileProcessing::emptyFile() {
	bool isEmpty = false;
	ifstream inf;
	inf.open(_LOGNAME);
	if(inf.peek() == ifstream::traits_type::eof())
		isEmpty = true;
	inf.close();
	return isEmpty;
}