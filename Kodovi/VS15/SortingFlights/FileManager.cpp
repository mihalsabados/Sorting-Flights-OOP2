//============================================================================
// Name        : FileManager.cpp
// Author      : Mihal Sabados
// Date        : 09.01.2021.
// Copyright   :
// Description : Implementation of FileManager class for I/O of a file.
//============================================================================

#include "FileManager.h"
#include <std_lib_facilities.h>

FileManager::FileManager()
{
}

FileManager::FileManager(string filepath):file_path(filepath)
{
}

FileManager::~FileManager()
{
}


void FileManager::setFilePath(string filePath)
{
	this->file_path = filePath;
}


string FileManager::getFilePath()
{
	return file_path;
}


vector<Flight> FileManager::readFlights()
{
	vector<Flight> flights;			//creates vector for storing Flights.
	try {
		ifstream file(file_path);		//opens file for reading
		string line;
		int n = 0;
		while (getline(file, line)) {			//get line from file
			if (n++ == 0)continue;
			string* words = splitLine(line);										//split values
			Flight cur_flight(words[2], words[0], words[1], words[3]);				//create object
			flights.push_back(cur_flight);											//push back to vector
			delete[] words;
		}
		file.close();
	}
	catch (...) {
		cout<<"Loading file gone wrong!!!"<<endl;
	}
	return flights;
}


void FileManager::saveFlights(vector<Flight> flights)
{
	try {
		ofstream file(file_path);
		file << "Destination Departure Flight No. Gate No." << endl;
		for (int i = 0; i < flights.size(); i++)
		{
			file << flights[i];
		}
		file.close();
	}
	catch (...) {
		error("Saving file gone wrong!!!");
	}
}


string* FileManager::splitLine(string line) {
	int last = 0;
	int plast = 0;
	int i = 0;
	string* words = new string[4];
	while ((last = line.find(";", plast + 1)) != -1) {
		if (i == 0) words[i++] = line.substr(plast, last - plast);
		else words[i++] = line.substr(plast + 2, last - plast - 2);
		plast = last;
	}
	return words;
};
