#include "FileProcessing.h"


int FileProcessing::load(vector<string>& data){
	ifstream input(_LOGNAME);
	if(!input.is_open()) {
		return STATUS_CODE_SET_ERROR::ERROR_LOAD_OPENFILE;
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
				return STATUS_CODE_SET_WARNING::WARNING_LOAD_EMPTY_FILE;	
			}
		} else {
			return STATUS_CODE_SET_ERROR::ERROR_LOAD_OPENFILE;
		}
	}
	input.close();
	return STATUS_CODE_SET_SUCCESS::SUCCESS_LOAD;
}


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
		return STATUS_CODE_SET_ERROR::ERROR_SAVE_SAVEFILE;
	}
	output.close();
	return STATUS_CODE_SET_SUCCESS::SUCCESS_SAVE;
}


bool FileProcessing::emptyFile() {
	bool isEmpty = false;
	ifstream inf;
	inf.open(_LOGNAME);
	if(inf.peek() == ifstream::traits_type::eof())
		isEmpty = true;
	inf.close();
	return isEmpty;
}