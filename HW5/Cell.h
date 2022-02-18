#if !defined(CELL_H_)
#define CELL_H_

class Cell
{
public:
    enum class CellContent
    {
        empty='.',x='x',o='o',X='X',O='O'
    };
    int getColumn() const {return column;}
    int getRow() const {return row;}
    CellContent getState() const {return state;}
    void setColumn(int newColumn){column=newColumn;}
    void setRow(int newRow){row=newRow;}
    void setState(CellContent newState){state=newState;}
    Cell();
    Cell(int nRow,int nCol);
private:
    int column;
    int row;
    CellContent state;
};


#endif // CELL_H_
