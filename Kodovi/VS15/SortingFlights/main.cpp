//============================================================================
// Name        : main.cpp
// Author      : Mihal Sabados
// Date        : 08.01.2021.
// Copyright   :
// Description : Main file for starting and running project.
//============================================================================

#include <vector>
#include <iostream>
#include <fstream>
#include "Graph.h"
#include "Flight.h"
#include "MyWindow.h"
#include "MyTable.h"
#include "FileManager.h";

using namespace std;

int main(int argc, char **argv)
{
	string path;
	if (argc > 1) {
		path = argv[1];									//gets file path from argument line
	}

	FileManager fm(path);								//creates I/O file manager
	vector<Flight> flights = fm.readFlights();			//reads vector of flights from file manager
	int n = flights.size();
	for (int i = 0; i < n; i++) {
		cout << flights[i];								//prints all flights in vector
	}

	if (n != 10)cout << "There must be exactly 10 Flights!!!" << endl;
	else {
		MyWindow win(Point(10, 10), 1350, 400, "London Airport");				//if there are exactly 10 flights create MyWindow object for GUI
		win.setTableData(flights, 10, 4, 1);									//set both tables data from vector
		win.setTableData(flights, 10, 4, 2);
		win.wait_for_button();
	}
	return 0;
};
