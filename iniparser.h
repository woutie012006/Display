#pragma once

#include <stdio>
#include <string>

class INIparser
{
public:
	int createFile(string filename);
	int deleteFile(string filename);

	int createVariable(string filename, string data, string value);
	int deleteVariable(string filename, string data);

	int setData(string filename, string data, string value, bool createIfNotExist = true);
	int getData(string filename, string data, string *output);

	int addSection(string filename, string sectionName);
};

extern INIparser iniparser;
