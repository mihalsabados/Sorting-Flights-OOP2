//============================================================================
// Name        : FileManager.h
// Author      : Mihal Sabados
// Date        : 09.01.2021.
// Copyright   :
// Description : Definition of FileManager class for I/O with file.
//============================================================================
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Flight.h"

using namespace std;
class FileManager {
private:
	string file_path;

public:
	FileManager();
	FileManager(string filepath);
	~FileManager();

	//Sets file path so that FileManager uses it.
	void setFilePath(string filePath);
	//returns file path which has been used.
	string getFilePath();

	//reads flights from the file_path file and catches issues while reading
	vector<Flight> readFlights();
	//writes vector of Flights to the file and catches issues while writing
	void saveFlights(vector<Flight> flights);
	//splits line on values by separator ';'
	string* splitLine(string line);
};