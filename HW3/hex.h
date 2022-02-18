#ifndef HEX_H_
#define HEX_H_

#include<iostream>
#include<vector>

using namespace std;
/*
    THIS HEADER FILE CONTAINS THE HEX AND CELL CLASSES. THERE ARE MANY GETTERS,SETTERS,MEMBER VARIABLES,MEMBER FUNCTIONS
STATIC VARIABLE AND FUNCTIONS AND INLINE FUNCTIONS WHICH MAKE THE GAME PLAYABLE.
*/
class Hex
{
private:
    string gameName="Nameless";
    string fName;
    int gameMode=1;
    int rowSize;
    int colSize;
    int counter=0;
    int compCounter=0;
    int compX=0;
    int compY=0;
    bool gameEnd=false;
    int markedCells=0;
    static int allMarkedCells;
    static int gameCount;
    void createVectorBoard();
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
        Cell(int nRow,int nCol);
    private:
        int column;
        int row;
        CellContent state;
    };
    vector< vector <Cell> > hexCell;
    void play();
    void play(const int &r,const int &c);
    bool playWComp();
    bool playWPlayer();
    void setGameMode(int gM){gameMode=gM;}
    bool isWin(const Cell::CellContent &safe_ch,const Cell::CellContent &forb_ch);
    bool winControl(const int coordinate[2],const int move_row[6],const int move_col[6],int count,const Cell::CellContent &usr_ch);
    bool checkSuitability(const int coordinate[2],const Cell::CellContent &usr_ch);
    void allMoves(int move_up[2][2],int move_down[2][2],int left_rigt[2][2]);
    void randomMove();
    bool compMove(int moves[2][2]);
    bool checkComputerMove(int coord[2]);
    void setCompX(int x){compX=x;}
    void setCompY(int y){compY=y;}
public:
    Hex();
    Hex(int row,int col);
    void setGameName(string name){gameName=name;}
    void setGameName(string name,int foo){gameName=name;}
    string getGameName(){return gameName;}
    int getWidth() const{return colSize;}
    int getHeight() const{return rowSize;}
    void setWidth(int width){rowSize=width;}
    void setHeight(int height){colSize=height;}
    void playGame();
    void display() const;
    bool isEnd() const {return gameEnd;}
    int getMarkedCells() const {return markedCells;}
    void setMarkedCells(int set) {markedCells=set;}
    void findMarkedCells();
    static int numMarkedCells(){return allMarkedCells;}
    static void setNumMarkedCells(int num){allMarkedCells=num;}
    static int numGames(){return gameCount;}
    static void setNumGames(int num){gameCount=num;}
    bool compareGames(Hex otherGame) const;
    int loadBoard(string fileName);
    int loadBoard(string fileName,int foo);
    bool saveBoard(string fileName) const ;
    int getCounter(){return counter;}
    int getcompCounter(){return compCounter;}
    int getGameMode(){return gameMode;}
    void setEnd(bool end) {gameEnd=end;}
    void setFName(string name){fName=name;}
    string getFName() const{return fName;}
};
#endif
