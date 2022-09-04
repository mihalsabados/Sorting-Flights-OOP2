//============================================================================
// Name        : MyTable.h
// Author      : Mihal Sabados
// Date        : 09.01.2021.
// Copyright   :
// Description : Definition of MyTable class for managment of the table.
//============================================================================
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Table.H>
#include <FL/fl_draw.H>

#pragma once
#define MAX_ROWS 10
#define MAX_COLS 4	
class MyTable : public Fl_Table {

    char* data[MAX_ROWS][MAX_COLS];		// data array for cells

    // Draw the row/col headings
    //    Make this a dark thin upbox with the text inside.
    //
public:
    void DrawHeader(const char* s, int X, int Y, int W, int H);
    // Draw the cell data
    //    Dark gray text on white background with subtle border
    //
    void DrawData(const char* s, int X, int Y, int W, int H);
    // Handle drawing table's cells
    //     Fl_Table calls this function to draw each visible cell in the table.
    //     It's up to us to use FLTK's drawing functions to draw the cells the way we want.
    //
    void draw_cell(TableContext context, int ROW = 0, int COL = 0, int X = 0, int Y = 0, int W = 0, int H = 0);
    // Constructor
    //     Make data array, and initialize the table options.
    //
    MyTable(int X, int Y, int W, int H, const char* L = 0);
    ~MyTable();
    //sets new data in the table and
    //overwrites the old data
    void setData(char*** new_data, int rows, int cols);
    //returns data from the table in char* matrix
    char*** getData();
    //free the memory allocated for data
    friend void deleteData(char*** data, int rows, int cols);
};