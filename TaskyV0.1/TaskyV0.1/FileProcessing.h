#ifndef _FILEPROCESSING_H_
#define _FILEPROCESSING_H_

/*
 *This class is mainly for file-related operations. At the starting phase of the program, it will load existing 
 *tasks to processor and when the save method is being called, it will save the content in logic list to local file
 *
 *Main author: Joan
*/

#include <fstream>
#include "Essential.h"

class FileProcessing{
public:
	int load(vector<string>&); //reads text file, push into vector
	int save(vector<string>&); //reads vector, writes to text file
};

#endif