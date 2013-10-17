#include "Log.h"

using namespace std;

namespace LogLibrary{

	void Log::writeLog(int logType, std::string data, std::string logName){

		vector<string> storage;
		ifstream input(logName);
		if(input.is_open()) {
			if (!emptyFile(logName)) {
				while(input) {
					string line;
					getline(input, line);
					storage.push_back(line);
				}
			}
		}

		ofstream output(logName);
		//check if file exist
		if (!output.is_open()) {
			output.clear();
			output.open(logName, ofstream::out|ofstream::trunc);
		}
		//check if file is created, ready for writing
		if (output.good()) {
			for (std::string str:storage){
				output << str << endl;
			}
			switch(logType) {
			case STATUS_CODE_SET_LOG::INFO:
				output << "Info: ";
				break;
			case STATUS_CODE_SET_LOG::DEBUG:
				output << "Debug: ";
				break;
			case STATUS_CODE_SET_LOG::WARNING:
				output << "Warning: ";
				break;
			case STATUS_CODE_SET_LOG::ERROR:
				output << "Error: ";
				break;
			default:
				break;
			}
			output << data << endl;
		}
		output.close();

	}

	bool Log::emptyFile(std::string logName) {
		bool isEmpty = false;
		ifstream inf;
		inf.open(logName);
		if(inf.peek() == ifstream::traits_type::eof())
			isEmpty = true;
		inf.close();
		return isEmpty;
	}

}