#if !defined(ABSTRACTHEX_H_)
#define ABSTRACTHEX_H_
#include<iostream>
#include"Cell.h"
#include<string>
#include<fstream>
#include"HexExceptions.h"
/*
    THIS IS THE ABSTRACT BASE CLASS. IT INCLUDES SOME ESSENTIAL FUNCTIONS AND SOME PURE VIRTUAL FUNCTIONS 
    THAT CANNOT BE IMPLEMENTED WITHOUT KNOWING HEXCELL REPRESENTATION
*/
using namespace std;
namespace AtakanHex
{
    class AbstractHex
    {
    public:
        AbstractHex();
        AbstractHex(int width, int height);
        virtual ~AbstractHex();
        void print() const;
        int readFromFile(const string fileName);
        int readFromFile(const string fileName,int foo);
        bool writeToFile(const string fileName) const;
        virtual void reset()=0;
        void setSize(int width,int height);
        void play();
        void play(Cell cell);
        bool isEnd()const{return gameEnd;}
        virtual Cell &operator()(int x,int y)=0;
        virtual Cell operator()(int x,int y) const=0;
        bool operator==(const AbstractHex& otherGame)const;
        Cell lastMove()const;
        int numberOfMoves()const{return markedCells;}
        void playGame();
        void setGameName(string name){gameName=name;}
        void setGameName(string name,int foo){gameName=name;}
        const string getGameName() const {return gameName;}
        void setFName(string name){fName=name;}
        string getFName() const{return fName;}
        void setEnd(bool end) {gameEnd=end;} // getter is isEnd.
        int getWidth() const{return rowSize;}
        int getHeight() const{return colSize;}
        void setWidth(int width){colSize=width;}
        void setHeight(int height){rowSize=height;}
        int getGameMode()const{return gameMode;}
        void setGameMode(int gM){gameMode=gM;}
    protected:
        int getLastX()const{return lastX;}
        int getLastY()const{return lastY;}
        void setLastX(int x){lastX=x;}
        void setLastY(int y){lastY=y;}
        void setMarkedCells(int set) {markedCells=set;} //getter is numberOfMoves.
        int getCounter()const{return counter;}
        void setCounter(int count){counter=count;}
        int getcompCounter()const{return compCounter;}
        void setcompCounter(int compCount){compCounter=compCount;}
        void setCompX(int x){compX=x;}
        void setCompY(int y){compY=y;}
        int getCompX()const{return compX;}
        int getCompY()const{return compY;}
        virtual void createBoard()=0;
        bool playWComp();
        bool playWPlayer();
        bool isWin(const Cell::CellContent &safe_ch,const Cell::CellContent &forb_ch);
        bool winControl(const int coordinate[2],const int move_row[6],const int move_col[6],int count,const Cell::CellContent &usr_ch);
        bool checkSuitability(const int coordinate[2],const Cell::CellContent &usr_ch);
        void allMoves(int move_up[2][2],int move_down[2][2],int left_rigt[2][2]);
        void randomMove();
        bool compMove(int moves[2][2]);
        bool checkComputerMove(int coord[2]);
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
        int lastX=-1;
        int lastY=-1;
    };
} // namespace AtakanHex

#endif // ABSTRACTHEX_H_
