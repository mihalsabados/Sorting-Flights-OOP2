//============================================================================
// Name        : MyWindow.h
// Author      : Mihal Sabados
// Date        : 09.01.2021.
// Copyright   :
// Description : Definition of MyWindow class which is used for GUI.
//============================================================================
#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Table.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Native_File_Chooser.H>
#include "Window.h"
#include "GUI.h"
#include "MyTable.h"
#include "Flight.h"
#include "Sort.h"
#include "FileManager.h"

using namespace Graph_lib;


class MyWindow :public Window{
public:
	//Constructor
	//	Creates window on Points with width w, height h and title.
	//	Creates 2 tables, 2 outboxes, 3 buttons and 2 groups of radio buttons.
	MyWindow(Point xy, int w, int h, const string& title);
	//Destructor
	//	Frees all allocated memory
	~MyWindow(void);
	//keeps window showing
	bool wait_for_button();
	//sets data for one table from Flight vector.
	void setTableData(vector<Flight> flights, int rows, int cols, int table);
	//Creates Radio Button group for sorting criteria.
	void createCriteriaRadioButtons();
	//Creates Radio Button group for sorting type.
	void createSortRadioButtons();
	//draws lines between two tables for sorting visualization
	void draw_lines();
	//moves lines between two tables when some elements in old_flights and new_flights are in different positions
	void move_lines(vector<Flight> old_flights, vector<Flight> new_flights);
	//delete lines between two tables and number of iterations labels
	void delete_lines();
	//resets all attributes to default
	void reset();
	//returns vector of Flights from one of the table
	vector<Flight> getTableData(int table);
	static MyWindow* mw_this;
	

private:
	int iteration;
	int sort_criteria;
	int sort_type;
	int compares;
	int subs;
	Button nextButton;
	Button openButton;
	Button saveButton;
	MyTable table1;
	MyTable table2;
	Fl_Round_Button* flightNo_btn;
	Fl_Round_Button* destination_btn;
	Fl_Round_Button* departure_btn;
	Fl_Round_Button* gateNo_btn;
	
	Fl_Round_Button* selectionSort_btn;
	Fl_Round_Button* mergeSort_btn;
	Fl_Group* criteria_group;
	Fl_Group* sort_group;
	Line* lines[10][10];
	Text* iter[10];

	Out_box cmp_number;
	Out_box subs_number;
	bool nextButtonPushed;
	static void cb_nextButton(Address, Address);
	static void cb_openButton(Address, Address);
	static void cb_saveButton(Address, Address);
	//action for sort criteria radio buttons
	static void cb_radio(Fl_Widget* b, void* d);
	//action for sort type radio buttons
	static void cb_sort(Fl_Widget* b, void* d);
	//Next Button click
	void nextButtonHandler();
	//opens file chooser for opening file
	void openButtonHandler();
	//opens file chooser for saving file
	void saveButtonHandler();
};