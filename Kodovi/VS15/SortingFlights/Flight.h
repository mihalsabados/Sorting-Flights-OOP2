//============================================================================
// Name        : Flight.h
// Author      : Mihal Sabados
// Date        : 09.01.2021.
// Copyright   :
// Description : Definition of Flight class for storing flight information.
//============================================================================
#include <string>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <ctime>
#pragma once

using namespace std;
class Flight
{
private:
	string flightNo;
	string destination;
	string departure;
	string gateNo;
public:
	//Default Constructor
	Flight();
	//Constructor with parameters
	Flight(string flightNo, string destination, string departure, string gateNo);
	~Flight();

	string getFlightNo();
	string getDestination();
	string getDeparture();
	string getGateNo();
	void setFlightNo(string flightNo);
	void setDestination(string destination);
	void setDeparture(string departure);
	void setGateNo(string gateNo);
	//Compares the Flights based on criteria
	int compare(Flight other, int criteria);
	//Overwrites the operator << for output.
	friend ostream& operator<<(ostream& os, Flight& flight);
	//Overwrites the operator == for equals.
	friend bool operator==(Flight& this_flight,Flight& other_flight);
};
