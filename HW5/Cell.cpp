#include"Cell.h"

Cell::Cell()
{
    state=CellContent::empty;
}
Cell::Cell(int nRow,int nCol)
{
    row=nRow;
    column=nCol;
    state=CellContent::empty;
}
