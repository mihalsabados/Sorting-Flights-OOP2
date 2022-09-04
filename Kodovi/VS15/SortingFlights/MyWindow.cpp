//============================================================================
// Name        : MyWindow.cpp
// Author      : Mihal Sabados
// Date        : 09.01.2021.
// Copyright   :
// Description : Implementation of MyWindow class for GUI.
//============================================================================
#include "MyWindow.h"

MyWindow* MyWindow::mw_this = NULL;			//set static attribute to NULL


MyWindow::MyWindow(Point xy, int w, int h, const string& title) :
	Window(xy, w, h, title),
	table1(10, 50, 400, 220),
	table2(910, 50, 400, 220),
	cmp_number(Point(470, 300), 30, 30, "Compares:"),
	subs_number(Point(650, 300), 30, 30, "Substitutions:"),
	nextButton(Point(800, 300), 120, 40, "Next Iteration", cb_nextButton),
	openButton(Point(10, 300), 120, 40, "Open", cb_openButton),
	saveButton(Point(150, 300), 120, 40, "Save", cb_saveButton),
	nextButtonPushed(false)
{

	MyWindow::mw_this = this;						//sets static pointer attribute to this.
	Window::add(table1);							//adds both tables
	Window::add(table2);

	createCriteriaRadioButtons();					//creates two groups of radio buttons
	createSortRadioButtons();

	attach(nextButton);								//attaches all buttons and outBoxes
	attach(openButton);
	attach(saveButton);
	attach(cmp_number);
	attach(subs_number);
	
	draw_lines();									//draws lines between tables
	iteration = 0;									//sets default values for attributes
	sort_criteria = 1;
	sort_type = 1;
	compares = 0;
	subs = 0;
}

MyWindow::~MyWindow(void)
{
	delete flightNo_btn;
	delete destination_btn;
	delete departure_btn;
	delete gateNo_btn;
	delete selectionSort_btn;
	delete mergeSort_btn;
}


bool MyWindow::wait_for_button()
{
	Window::show();
	Fl::run();
	return true;
}


void MyWindow::setTableData(vector<Flight> flights, int rows, int cols, int table)
{
	
	char*** new_data = new char**[10];				//creates char* matrix for storing data
	for (int i = 0; i < 10; i++)
	{
		new_data[i] = new char*[4];
		for (int j = 0; j < 4; j++)
		{
			new_data[i][j] = new char[20];
		}
	}

	for (int i = 0; i < 10; i++)
	{	
		strcpy(new_data[i][0], flights[i].getFlightNo().c_str());				//sets values from Flight vector to char* matrix
		strcpy(new_data[i][1], flights[i].getDestination().c_str());
		strcpy(new_data[i][2], flights[i].getDeparture().c_str());
		strcpy(new_data[i][3], flights[i].getGateNo().c_str());
	}

	if (table == 1)table1.setData((char ***)new_data, rows, cols);						//sets data for table1
	else if (table == 2)table2.setData((char***)new_data, rows, cols);					//sets data for table2
}


void MyWindow::createCriteriaRadioButtons()
{
	criteria_group = new Fl_Group(10, 10, 400, 30);							//creates new group of radio buttons
	criteria_group->box(FL_UP_FRAME);		
	{
		flightNo_btn = new Fl_Round_Button(20, 12, 70, 30, "&Flight No.");				//adds radio buttons to new group
		flightNo_btn->type(102);
		flightNo_btn->down_box(FL_ROUND_DOWN_BOX);
		flightNo_btn->callback(cb_radio, (void*)1);
	}
	{
		destination_btn = new Fl_Round_Button(120, 12, 70, 30, "&Destination");
		destination_btn->type(102);
		destination_btn->down_box(FL_ROUND_DOWN_BOX);
		destination_btn->callback(cb_radio, (void*)2);
	}
	{
		departure_btn = new Fl_Round_Button(220, 12, 70, 30, "&Departure");
		departure_btn->type(102);
		departure_btn->down_box(FL_ROUND_DOWN_BOX);
		departure_btn->callback(cb_radio, (void*)3);
	}
	{
		gateNo_btn = new Fl_Round_Button(320, 12, 70, 30, "&Gate No.");
		gateNo_btn->type(102);
		gateNo_btn->down_box(FL_ROUND_DOWN_BOX);
		gateNo_btn->callback(cb_radio, (void*)4);
	}
	criteria_group->end();
	Window::add(*criteria_group);									//adds group to the window
	flightNo_btn->set();											//sets flightNo radio button to default 
	flightNo_btn->activate();
}

void MyWindow::createSortRadioButtons()
{
	sort_group = new Fl_Group(450, 10, 300, 30);				//creates new radio button group
	sort_group->box(FL_UP_FRAME);
	{
		selectionSort_btn = new Fl_Round_Button(460, 12, 70, 30, "&Selection Sort.");				//adds two radio buttons to new group
		selectionSort_btn->type(FL_RADIO_BUTTON);
		selectionSort_btn->down_box(FL_ROUND_DOWN_BOX);
		selectionSort_btn->callback(cb_sort, (void*)1);
	}
	{
		mergeSort_btn = new Fl_Round_Button(620, 12, 70, 30, "&Merge Sort");
		mergeSort_btn->type(FL_RADIO_BUTTON);
		mergeSort_btn->down_box(FL_ROUND_DOWN_BOX);
		mergeSort_btn->callback(cb_sort, (void*)2);
	}
	sort_group->end();
	Window::add(*sort_group);								//adds new gruop to the window
	selectionSort_btn->set();								//sets selectionSort radio button to default
	selectionSort_btn->activate();
}


void MyWindow::draw_lines()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			lines[i][j] = new Line(Point(410 + i * 50, 80 + j * 20), Point(460 + i * 50, 80 + j * 20));
			lines[i][j]->set_color(Color::red);
			lines[i][j]->set_style(FL_CAP_FLAT);
			redraw();
			attach(*lines[i][j]);
		}
	}

}


void MyWindow::move_lines(vector<Flight> old_flights, vector<Flight> new_flights) {
	for (int i = 0; i < 10; i++)
	{
		if (!(old_flights[i] == new_flights[i])) {					//if element position in both vectors don't match
			for (int j = 0; j < 10; j++)
			{
				if (old_flights[i]==new_flights[j])
				{
					detach(*lines[iteration][i]);												//detaches and deteles lines
					delete[] lines[iteration][i];
					lines[iteration][i] = new Line(Point(410 + iteration * 50, 80 + i * 20), Point(460 + iteration * 50, 80 + j * 20));		//creates new lines
					lines[iteration][i]->set_color(Color::green);																	//set color to green
					lines[iteration][i]->set_style(FL_CAP_FLAT);
					redraw();												//refresh window
					attach(*lines[iteration][i]);							//atach them to window
					break;
				}
			}
			subs++;															//counts number of substitution
		}

	}

}


void MyWindow::delete_lines()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			detach(*lines[i][j]);		//delete lines
			delete[] lines[i][j];
		}
		if (iteration > 0) {			//delete number of iterations labels
			detach(*iter[i]);
			delete[] iter[i];
			iteration--;
		}
	}
}


vector<Flight> MyWindow::getTableData(int table)
{
	char*** data;
	if (table == 1)data = table1.getData();					//get data from table 1
	else data = table2.getData();;							//get data from table 2
	vector<Flight> flights;

	for (int i = 0; i < 10; i++)
	{
		Flight fl(data[i][0], data[i][1], data[i][2], data[i][3]);			//convert from char* matrix to vector of Flights
		flights.push_back(fl);
	}
	deleteData(data, 10, 4);									//free allocated memory

	return flights;
}


void MyWindow::cb_nextButton(Address, Address pw)
{
	reference_to<MyWindow>(pw).nextButtonHandler();
}

void MyWindow::cb_openButton(Address, Address pw)
{
	reference_to<MyWindow>(pw).openButtonHandler();
}

void MyWindow::cb_saveButton(Address, Address pw)
{
	reference_to<MyWindow>(pw).saveButtonHandler();
}


void MyWindow::nextButtonHandler()
{
	if (iteration < 10) {										//only take action if there is less than 10 iterations
		vector<Flight> new_flights = getTableData(2);			//get vector of flights from table 2
		vector<Flight> old_flights = new_flights;
		switch (sort_type) {									//take action based on sorting type
		case 1: {
			SelectionSort ss(iteration, sort_criteria);
			ss.sort(new_flights, 10);							//sort by selection sort and sort_criteria
			compares += ss.getNumCmps();						//accumulate number of compares
			cmp_number.put(compares);							//and put them in outBox
			break;
		}
		case 2:
			new_flights = getTableData(1);						//
			MergeSort ms(iteration+1, sort_criteria);			//sort by merge sort and sort_criteria
			ms.sort(new_flights, 10);
			cmp_number.put(ms.getNumCmps());					//put number of compares in outBox
			break;
		}
		setTableData(new_flights, 10, 4, 2);					//sets sorted table data in table 2
		move_lines(old_flights, new_flights);					//moves lines for visualization
		subs_number.put(subs);																		//put number of substitutions in outBox
		iter[iteration] = new Text(Point(430+iteration*50, 290), to_string(iteration+1));			//add iteration label
		redraw();																				//refresh window
		attach(*iter[iteration]);
		iteration++;
	}
}

//opens file chooser for opening file
void MyWindow::openButtonHandler()
{
	Fl_Native_File_Chooser* chooser = new Fl_Native_File_Chooser();
	chooser->type(Fl_Native_File_Chooser::BROWSE_FILE);   // let user browse a single file
	chooser->title("Open a file");                        // optional title
	chooser->preset_file("/var/tmp/somefile.txt");        // optional filename preset
	chooser->filter("Text Files\t*.txt");                 // optional filter
	switch (chooser->show()) {
	case -1:    // ERROR
		fprintf(stderr, "*** ERROR show() failed:%s\n", chooser->errmsg());
		break;
	case 1:     // CANCEL
		fprintf(stderr, "*** CANCEL\n");
		break;
	default:    // USER PICKED A FILE
		string file_path = chooser->filename();
		if (file_path.substr(file_path.size() - 4, 4).compare(".txt") == 0) {				//only if file ends with .txt
			FileManager fm(file_path);													//create file manager for that file
			vector<Flight> flights = fm.readFlights();									//read flight from file
			int n = flights.size();
			if (n != 10)error("There must be exactly 10 Flights!!!");
			else {
				reset();														//refreshes the window, sets new table data and draw lines between tables
				setTableData(flights, 10, 4, 1);
				setTableData(flights, 10, 4, 2);
				draw_lines();
			}
		}
		else error("File must be .txt!!!");
		break;
	}

}


void MyWindow::saveButtonHandler()
{
	Fl_Native_File_Chooser* chooser = new Fl_Native_File_Chooser();
	chooser->type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);   // 'saveas' browser
	chooser->title("Save As..");                               // optional title for chooser window
	chooser->directory("/var/tmp");                            // optional starting directory
	chooser->preset_file("untitled.txt");                      // optional default filename
	chooser->filter("Text Files\t*.txt");                      // optional filter
	switch (chooser->show()) {
	case -1:    // ERROR
		fprintf(stderr, "*** ERROR show() failed:%s\n", chooser->errmsg());
		break;
	case 1:     // CANCEL
		fprintf(stderr, "*** CANCEL\n");
		break;
	default:    // USER PICKED A FILE
		fprintf(stderr, "Filename was '%s'\n", chooser->filename());
		FileManager fm(chooser->filename());								//save flights from table 2 to file
		fm.saveFlights(getTableData(2));
		break;
	}
}


void MyWindow::cb_radio(Fl_Widget* b, void* d) {
	int criteria = (int)d;
	mw_this->sort_criteria = criteria;
	mw_this->reset();
	vector<Flight> flights= mw_this->getTableData(1);
	mw_this->setTableData(flights, 10, 4, 2);
	mw_this->draw_lines();
}


void MyWindow::cb_sort(Fl_Widget* b, void* d)
{
	int sort = (int)d;
	mw_this->sort_type = sort;
	mw_this->reset();
	vector<Flight> flights = mw_this->getTableData(1);
	mw_this->setTableData(flights, 10, 4, 2);
	mw_this->draw_lines();
}


void MyWindow::reset() {
	mw_this->delete_lines();
	mw_this->iteration = 0;
	mw_this->cmp_number.put(0);
	mw_this->subs_number.put(0);
	mw_this->compares = 0;
	mw_this->subs = 0;
}