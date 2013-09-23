#ifndef _FILEPROCESSING_H_
#define _FILEPROCESSING_H_

#include <fstream>
#include "Essential.h"

class FileProcessing{
public:
	int load(vector<string>&); //reads text file, push into vector
	int save(vector<string>&); //reads vector, writes to text file
};

#endif