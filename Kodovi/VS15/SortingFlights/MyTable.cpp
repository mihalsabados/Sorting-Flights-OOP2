//============================================================================
// Name        : MyTable.cpp
// Author      : Mihal Sabados
// Date        : 09.01.2021.
// Copyright   :
// Description : Implementation of MyTable class which is used for table managment.
//============================================================================
#include "MyTable.h"
#include <string>


using namespace std;
void MyTable::DrawHeader(const char* s, int X, int Y, int W, int H) {
    fl_push_clip(X, Y, W, H);
    fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, row_header_color());
    fl_color(FL_BLACK);
    fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
    fl_pop_clip();
}


void MyTable::DrawData(const char* s, int X, int Y, int W, int H) {
    fl_push_clip(X, Y, W, H);
    // Draw cell bg
    fl_color(FL_WHITE); fl_rectf(X, Y, W, H);
    // Draw cell data
    fl_color(FL_GRAY0); fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
    // Draw box border
    fl_color(color()); fl_rect(X, Y, W, H);
    fl_pop_clip();
}


void MyTable::draw_cell(TableContext context, int ROW, int COL, int X, int Y, int W, int H) {
    static char s[40];
    static char* col_name;
    switch (context) {
    case CONTEXT_STARTPAGE:                   // before page is drawn..
        fl_font(FL_HELVETICA, 16);              // set the font for our drawing operations
        return;
    case CONTEXT_COL_HEADER:                  // Draw column headers
        switch (COL) {
        case 0:col_name = "Flight No."; break;
        case 1:col_name = "Destination"; break;
        case 2:col_name = "Departure"; break;
        case 3:col_name = "Gate No."; break;
        default:col_name = "b.";
        };
        sprintf(s, "%s", col_name);                // "A", "B", "C", etc.
        DrawHeader(s, X, Y, W, H);
        return;
    case CONTEXT_ROW_HEADER:                  // Draw row headers
        sprintf(s, "%d:", ROW+1);                 // "001:", "002:", etc
        DrawHeader(s, X, Y, W, H);
        return;
    case CONTEXT_CELL:                        // Draw data in cells
        //sprintf(s, "%s", data[ROW][COL]);
        DrawData(data[ROW][COL], X, Y, W, H);
        return;
    default:
        return;
    }
}


void MyTable::setData(char*** new_data, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            strcpy(this->data[i][j],new_data[i][j]);    //copy new data element into table data

    deleteData(new_data,rows,cols);

    redraw();   // refreshes the table
}


char*** MyTable::getData()
{
    char*** new_data = new char** [10];         //creates char* matrix
    for (int i = 0; i < 10; i++)
    {
        new_data[i] = new char* [4];
        for (int j = 0; j < 4; j++)
        {
            new_data[i][j] = new char[20];
            strcpy(new_data[i][j], data[i][j]);         //copy element from table to new char* matrix
        }
    }
    return (char***)new_data;
}


MyTable::MyTable(int X, int Y, int W, int H, const char* L) : Fl_Table(X, Y, W, H, L) {
    // Fill data array
    for (int r = 0; r < MAX_ROWS; r++)
        for (int c = 0; c < MAX_COLS; c++) {
            data[r][c] = new char[20];
            //data[r][c] = "None";
        }
    // Rows
    rows(MAX_ROWS);             // how many rows
    row_header(1);              // enable row headers (along left)
    row_height_all(20);         // default height of rows
    row_resize(0);              // disable row resizing
    // Cols
    cols(MAX_COLS);             // how many columns
    col_header(1);              // enable column headers (along top)
    col_width_all(80);          // default width of columns
    col_resize(1);              // enable column resizing
    end();			// end the Fl_Table group
}


MyTable::~MyTable() { }


void deleteData(char*** data, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            delete[] data[i][j];
        }
        delete[] data[i];
    }
    delete[] data;
}
