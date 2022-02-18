public class Cell {

    private int column;
    private int row;
    private CellContent state;
    int getColumn(){return column;}
    int getRow(){return row;}
    CellContent getState(){return state;}
    void setColumn(int newColumn){column=newColumn;}
    void setRow(int newRow){row=newRow;}
    void setState(CellContent newState){state=newState;}
    Cell(){
        state=CellContent.empty;
    }
    Cell(int nRow,int nCol){
        row=nRow;
        column=nCol;
        state=CellContent.empty;
    }
}