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
public:
    explicit Hex();
    explicit Hex(int row,int col);
    ~Hex();
    Hex(const Hex &other);
    Hex& operator=(const Hex &rightSide);
    Hex& operator--();//Prefix Version
    Hex& operator--(int);//Postfix version
    friend ostream& operator<<(ostream &outputStream,const Hex &object);
    friend fstream& operator>>(fstream &inputFStream,Hex& object);
    friend fstream& operator<<(fstream &outputFStream,const Hex& object);
    bool operator==(const Hex &otherGame)const;
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
    void setGameName(string name){gameName=name;}
    void setGameName(string name,int foo){gameName=name;}
    string getGameName() const {return gameName;}
    int getWidth() const{return rowSize;}
    int getHeight() const{return colSize;}
    void setWidth(int width){colSize=width;}
    void setHeight(int height){rowSize=height;}
    void playGame();
    bool isEnd() const {return gameEnd;}
    int getMarkedCells() const {return markedCells;}
    void setMarkedCells(int set) {markedCells=set;}
    void findMarkedCells();
    static int numMarkedCells(){return allMarkedCells;}
    static void setNumMarkedCells(int num){allMarkedCells=num;}
    static int numGames(){return gameCount;}
    static void setNumGames(int num){gameCount=num;}
    int loadBoard(string fileName);
    int loadBoard(string fileName,int foo);
    bool saveBoard(string fileName) const ;
    int getCounter()const{return counter;}
    void setCounter(int count){counter=count;}
    int getcompCounter()const{return compCounter;}
    void setcompCounter(int compCount){compCounter=compCount;}
    int getGameMode()const{return gameMode;}
    void setGameMode(int gM){gameMode=gM;}
    void setEnd(bool end) {gameEnd=end;}
    void setFName(string name){fName=name;}
    string getFName() const{return fName;}
    void increaseCapacity(){moveCount++;}
    void decreaseCapacity(){moveCount--;}
    int getCapacity()const{return moveCount;}
    void setCapacity(int size){moveCount=size;}
    int getCompX()const{return compX;}
    int getCompY()const{return compY;}
    void setCompX(int x){compX=x;}
    void setCompY(int y){compY=y;} 
    void findScoreX(int x,int y);
    void scoreX();
    void findScoreO(int x,int y);
    void scoreO();
    void setTempScoreX(int x){tempScoreX=x;}
    void setTempScoreO(int o){tempScoreO=o;}
    void setScoreX(int x){score_x=x;}
    void setScoreO(int o){score_o=o;}
    double getScoreX()const {return score_x;}
    double getScoreO()const {return score_o;}
    int getConnectedX(){return tempScoreX;}
    int getConnectedO(){return tempScoreO;}
    bool isUnsuit(int x,int y);
    void addUnsuit(Cell unsuit);
    int getUnsuitCellCount() const {return unsuitCount;}
    void setUnsuitCellCount(int count){unsuitCount=count;}
private:
    Cell ** hexCell=nullptr;
    Cell *moves=nullptr;
    Cell * unsuitCells=nullptr;
    int unsuitCount=0;
    int moveCount=0;
    double score_x=0;
    double score_o=0;
    int tempScoreX=0;
    int tempScoreO=0;
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
    void createBoard();
    Cell play();
    Cell play(const int &r,const int &c);
    bool playWComp();
    bool playWPlayer();
    bool isWin(const Cell::CellContent &safe_ch,const Cell::CellContent &forb_ch);
    bool winControl(const int coordinate[2],const int move_row[6],const int move_col[6],int count,const Cell::CellContent &usr_ch);
    bool checkSuitability(const int coordinate[2],const Cell::CellContent &usr_ch);
    void allMoves(int move_up[2][2],int move_down[2][2],int left_rigt[2][2]);
    void randomMove();
    bool compMove(int moves[2][2]);
    bool checkComputerMove(int coord[2]);
    void addMove(Cell move);
    void delMove();
    Cell topMove() const;
    bool isEmpty() const;
};
#endif
