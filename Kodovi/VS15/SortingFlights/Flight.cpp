//============================================================================
// Name        : Flight.cpp
// Author      : Mihal Sabados
// Date        : 09.01.2021.
// Copyright   : 
// Description : Implementation of Flight class which stores Flight values.
//============================================================================
#include "Flight.h"


Flight::Flight() :flightNo("None"), destination("None"), departure("None"), gateNo("None") {
};


Flight::Flight(string flightNo, string destination, string departure, string gateNo) {
	this->flightNo = flightNo;
	this->destination = destination;
	this->departure = departure;
	this->gateNo = gateNo;
};

Flight::~Flight() {};

string Flight::getFlightNo() {
	return this->flightNo;
};

string Flight::getDestination() {
	return this->destination;
};

string Flight::getDeparture() {
	return this->departure;
};

string Flight::getGateNo() {
	return this->gateNo;
};

void Flight::setFlightNo(string flightNo) {
	this->flightNo = flightNo;
}

void Flight::setDestination(string destination) {
	this->destination = destination;
}

void Flight::setDeparture(string departure) {
	this->departure = departure;
}

void Flight::setGateNo(string gateNo) {
	this->gateNo = gateNo;
}


int Flight::compare(Flight other, int criteria)
{
	string cmp1;
	string cmp2;
	switch (criteria) {
	case 1:cmp1 = this->flightNo; cmp2 = other.getFlightNo(); break;		//comparing by flight No.
	case 2:cmp1 = this->destination; cmp2 = other.getDestination(); break;	//comparing by Destination
	case 3: {											//for comparing departures we need to convert string values to time values
		time_t t1, t2, timenow=time(0);
		struct tm* timeptr, *tm1=localtime(&timenow), tm2=*tm1;
		int f = departure.find(":");
		int hour1, min1, hour2, min2;
		hour1 = atoi(departure.substr(0, f).c_str());
		min1 = atoi(departure.substr(f+1).c_str());
		f = other.getDeparture().find(":");
		hour2 = atoi(other.getDeparture().substr(0, f).c_str());
		min2 = atoi(other.getDeparture().substr(f + 1).c_str());
		tm1->tm_hour = hour1;
		tm1->tm_min = min1;
		tm1->tm_sec = 0;
		tm2.tm_hour = hour2;
		tm2.tm_min = min2;
		tm2.tm_sec = 0;
		t1 = mktime(tm1);
		t2 = mktime(&tm2);
		return difftime(t1, t2) > 0.0 ? 1 : -1;
		 break; }
	case 4:cmp1 = this->gateNo; cmp2 = other.getGateNo(); break;			//comparing by gate No.
	default:cmp1 = ""; cmp2 = "";
	}
	return cmp1.compare(cmp2);
}


ostream& operator<<(ostream& os, Flight& flight)
{
	os <<flight.getDestination()  << "; " << flight.getDeparture() << "; " << flight.getFlightNo() << "; " << flight.getGateNo()<<";" << endl;
	return os;
}


bool operator==(Flight& this_flight, Flight& other_flight)
{
	if (this_flight.flightNo.compare(other_flight.flightNo) == 0 && this_flight.destination.compare(other_flight.destination) == 0 &&
		this_flight.departure.compare(other_flight.departure) == 0 && this_flight.gateNo.compare(other_flight.gateNo) == 0)return true;
	else return false;
}
