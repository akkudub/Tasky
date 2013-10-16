
#include <string>
#include <fstream>
#include <vector>

namespace LogLibrary{	

	class Log {
	private :
		static bool emptyFile(std::string logName);
	public:
		/**
		* Purpose: writes a log 
		*
		* @param data the things to be logged down
		* @param logName the name you want your file to be
		*/
		static void writeLog(std::string data, std::string logName);
		
	};
}