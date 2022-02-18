#include<iostream>
#include"hex.h"
#include<vector>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<string>
using namespace std;

int Hex::allMarkedCells=0; 
int Hex::gameCount=0;
//3 CONSCRUCTORS ARE HERE
//IT CREATES A THE DEFAULT OBJECT WHICH SIZE IS 5x5
Hex::Hex() : colSize(5),rowSize(5)
{
    gameCount++;
    createBoard();
}
//IT CREATES AN OBJECT WITH SIZE PARAMATERS
Hex::Hex(int width,int height)
{
    gameCount++;
    rowSize=height;
    colSize=width;
    createBoard();
}
//COPY CONSTRUCTOR
Hex::Hex(const Hex &other):
unsuitCount(other.unsuitCount),moveCount(other.moveCount),score_x(other.score_x),score_o(other.score_o),
tempScoreX(other.tempScoreX),tempScoreO(other.tempScoreO),gameName(other.gameName),fName(other.fName),
gameMode(other.gameMode),rowSize(other.rowSize),colSize(other.colSize),counter(other.counter),
compCounter(other.compCounter),compX(other.compX),compY(other.compY),gameEnd(other.gameEnd),markedCells(other.markedCells)
{
    int i,j;
    hexCell = new Cell*[getHeight()];
    for (i = 0; i < getHeight();i++)
    {
        hexCell[i]=new Cell[getWidth()];
    }
    for (i = 0; i < getHeight(); i++)
    {
        for (j = 0; j < getWidth(); j++)
        {
            hexCell[i][j]=other.hexCell[i][j];
        }
    }
    moves=new Cell[getCapacity()];
    for (i = 0; i < getCapacity(); i++)
        moves[i]=other.moves[i];
    unsuitCells=new Cell[getUnsuitCellCount()];
    for (i = 0; i < getUnsuitCellCount(); i++)
        unsuitCells[i]=other.unsuitCells[i];
}
//DESTRUCTOR
Hex::~Hex()
{
    int i;
    for (i = 0; i < getWidth(); i++)
    {
        delete[] hexCell[i];
    }
    delete[] hexCell;
    delete[] moves;
    delete[] unsuitCells;
}
//ASSIGMENT OPERATOR OVERLOADING
Hex& Hex::operator=(const Hex &rightSide)
{
    int i,j;
    if (getHeight() != rightSide.getHeight())
    {
        for (i = 0; i < getWidth(); i++)
        {
            delete[] hexCell[i];
        }
        delete [] hexCell;
        hexCell = new Cell*[rightSide.getHeight()];
        for (i = 0; i < rightSide.getHeight(); ++i)
        {
            hexCell[i]=new Cell[rightSide.getWidth()];
        }
    }
    if (getCapacity()!=rightSide.getCapacity())
    {
        delete[] moves;
        moves=new Cell[rightSide.getCapacity()];
    }
    if (getUnsuitCellCount()!=rightSide.getUnsuitCellCount())
    {
        delete[] unsuitCells;
        unsuitCells = new Cell[rightSide.getUnsuitCellCount()];
    }
    unsuitCount=rightSide.unsuitCount;
    moveCount=rightSide.moveCount;
    score_x=rightSide.score_x;
    score_o=rightSide.score_o;
    tempScoreX=rightSide.tempScoreX;
    tempScoreO=rightSide.tempScoreO;
    gameName=rightSide.gameName;
    fName=rightSide.fName;
    gameMode=rightSide.gameMode;
    rowSize=rightSide.rowSize;
    colSize=rightSide.colSize;
    counter=rightSide.counter;
    compCounter=rightSide.compCounter;
    compX=rightSide.compX;
    compY=rightSide.compY;
    gameEnd=rightSide.gameEnd;
    markedCells=rightSide.markedCells;
    for (i = 0; i <getHeight(); i++)
    {
        for (j = 0; j < getWidth(); j++)
        {
            hexCell[i][j]=rightSide.hexCell[i][j];
        }
    }
    for (i = 0; i < getCapacity(); i++)
        moves[i]=rightSide.moves[i];
    for (i = 0; i < getUnsuitCellCount(); i++)
        unsuitCells[i]=rightSide.unsuitCells[i];
    return *this;
}
//IT CREATES A DEFAULT CELL OBJECT
Hex::Cell::Cell()
{
    state=CellContent::empty;
}
Hex::Cell::Cell(int nRow,int nCol)
{
    row=nRow;
    column=nCol;
    state=CellContent::empty;
}
//IT CREATES THE 2D HEXCELL ARRAY AND FILLS THE HEX OBJECT'S CELLS
void Hex::createBoard()
{
    int i,j;
    hexCell = new Cell*[rowSize];
    for (i = 0; i < rowSize; ++i)
    {
        hexCell[i]=new Cell[colSize];
    }
    for (i = 0; i < rowSize; i++)
    {
        for (j = 0; j <colSize; j++)
        {
            hexCell[i][j].setRow(i);
            hexCell[i][j].setColumn(j);
        }
    }
}
//THIS FUNCTION ADDS THE GIVEN MOVES INTO MOVES ARRAY TO REMEMEBER ALL MOVES ORDER
void Hex::addMove(Cell move)
{
    int i;
    Cell *tempMove;
    tempMove=new Cell[moveCount];
    if (moveCount==1)
    {
        moves = new Cell[moveCount];
        moves[moveCount-1]=move;
    }
    else
    {
        for (i = 0; i < moveCount-1; i++)
        {
            tempMove[i]=moves[i];
        }
        delete[] moves;
        moves = new Cell[moveCount];
        for (i = 0; i < moveCount; i++)
        {
            moves[i]=tempMove[i];
        }
        moves[moveCount-1]=move;
        delete[] tempMove;
    }
}
//THIS FUNCTION DELETES LAST ELEMENT OF MOVES ARRAY TO UNDO
void Hex::delMove()
{   
    if (isEmpty())
    {
        delete[] moves;
        moves=nullptr;
        cout << "No more moves to undo !" << endl;
    }
    else
    {
        int i;
        Cell *tempMove;
        tempMove=new Cell[getCapacity()-1];   
        for (i = 0; i < getCapacity()-1; i++)
        {
            tempMove[i]=moves[i];
        }
        delete[] moves;
        decreaseCapacity();
        moves = new Cell[getCapacity()];
        for (i = 0; i < getCapacity(); i++)
        {
            moves[i]=tempMove[i];
        }
        delete[] tempMove;
    }
}
//THIS FUNCTION RETURNS LAST ELEMENT OF ARRAY
Hex::Cell Hex::topMove() const
{
    return moves[getCapacity()-1];
}
//THIS FUNCTION CHECKS IF THE MOVES ARRAY IS EMPTY OR NOT. IT RETURNS TRUE IF THERE IS NO MOVE ON THE BOARD
bool Hex::isEmpty() const
{
    if (getCapacity()==0)
    {
        return true;
    }
    return false;
}
//THIS FUNCTION PROVIDES USER TO UNDO ONE MOVE. THIS FUNCTION CALLED IN PvP GAME
Hex& Hex::operator--()
{
    if (!isEmpty())
    {
        counter--;
        markedCells--;
        hexCell[topMove().getRow()][topMove().getColumn()].setState(Cell::CellContent::empty);
        delMove();
    }
    return *this;
}
//THIS FUNCTION PROVIDES USER TO UNDO ONE MOVE. IT ALSO UNDO ONE COMPUTER MOVE.
//THIS FUNCTION CALLED IN PvC GAME
Hex& Hex::operator--(int fooInt)
{
    if (!isEmpty())
    {
        compCounter-=2;
        markedCells-=2;
        hexCell[topMove().getRow()][topMove().getColumn()].setState(Cell::CellContent::empty);
        delMove();
        hexCell[topMove().getRow()][topMove().getColumn()].setState(Cell::CellContent::empty);
        delMove();
        compX=topMove().getRow();
        compY=topMove().getColumn();
    }
    return *this;
}
//THIS FUNCTION COMPARE TWO GAMES IF THEY HAVE EQUAL MARKED CELLS OR NOT.
bool Hex::operator==(const Hex &otherGame) const
{
    if (getMarkedCells()==otherGame.getMarkedCells())
        return true;
    else 
        return false;
}
//THIS FUNCTION PRINTS GAME BOARD,SCORE ETC.
//IT CALCULATES PLAYER'S SCORE BEFORE IT PRINT,SO IT DOESN'T TAKE A CONST OBJECT.
ostream& operator<<(ostream &outputStream,const Hex &object)
{
    int i,j,k;
    outputStream << "GAME NAME: " <<object.getGameName() << endl;
    outputStream << "PLAYER 1 SCORE: " << object.getScoreX() * (100.0/(double)(object.getHeight()-1)) << "\t";
    if (object.getGameMode()==2)
        outputStream << "COMPUTER SCORE: " << object.getScoreO() * (100.0/(double)(object.getHeight()-1)) << endl << endl;
    else
        outputStream << "PLAYER 2 SCORE: " << object.getScoreO() * (100.0/(double)(object.getHeight()-1))<< endl << endl;
    outputStream << "  ";
    for (i = 0; i < object.getHeight(); i++)
    {
        outputStream << static_cast<char>('A'+i)<< "  ";
    }
    outputStream << endl;
    for (i = 0; i < object.getWidth(); i++)
    {
        outputStream << 1+i << " ";
        for (k = 0; k < i; k++)
        {
            outputStream << "  ";
        }
        for (j = 0; j < object.getWidth(); j++)
        {
            outputStream << static_cast<char> (object.hexCell[i][j].getState()) <<"  ";
        }
        outputStream << endl;
    }
    if (object.isEnd()==false)
    {
        outputStream << "ENTER \"EXIT\" TO BACK TO MAIN MENU" << endl;
        if(!(object.isEmpty()))
            outputStream << "Enter \"UNDO\" to back to the previous move. " << endl;
    }
    return outputStream;
}
//THIS FUNCTION READS ALL GAME DATA FROM A FILE. AND RETURNS A FSTREAM OBJECT.
fstream& operator>>(fstream &inputFStream,Hex& object)
{
    int i,j;
    decltype(i) input;
    Hex::Cell tempCell;
    inputFStream >> input;
    if (input==1)
        object.setEnd(true);
    else 
        object.setEnd(false);
    inputFStream >> input;
    object.setHeight(input);
    object.setWidth(input);
    inputFStream >> input;
    object.setGameMode(input);
    if (object.getGameMode()==1)
    {
        inputFStream >> input;
        object.setCounter(input);
        object.setMarkedCells(object.getCounter());
    }
    else
    {
        inputFStream >> input;
        object.setcompCounter(input);
        object.setMarkedCells(object.getcompCounter());
        inputFStream >> input;
        object.setCompX(input);
        inputFStream >> input;
        object.setCompY(input);    
    }
    object.createBoard();
    for ( i = 0; i < object.getHeight(); i++)
    {

        for ( j = 0; j < object.getWidth(); j++)
        {
            inputFStream >> input;
            object.hexCell[i][j].setState(static_cast<Hex::Cell::CellContent>(input));
        }       
    }
    inputFStream >> input;
    object.setCapacity(input);
    delete[] object.moves;
    object.moves = new Hex::Cell[object.getCapacity()];
    for (i = 0; i < object.getCapacity(); i++)
    {
        inputFStream>>input;
        tempCell.setRow(input);
        inputFStream >> input;
        tempCell.setColumn(input);
        inputFStream >> input;
        tempCell.setState(static_cast<Hex::Cell::CellContent>(input));
        object.moves[i]=tempCell;
    }
    inputFStream >> input;
    object.setScoreX(input);
    inputFStream >> input;
    object.setScoreO(input);
    return inputFStream;
}
//THIS FUNCTION PRINTS ALL GAME DATA INTO A FILE. AND RETURNS A FSTREAM OBJECT.
fstream& operator<<(fstream& outputFStream,const Hex& object)
{
    int i,j;
    outputFStream <<  object.isEnd()<< endl;
    outputFStream << object.getWidth() << endl;
    outputFStream << object.getGameMode() << endl;

    if (object.getGameMode()==1)
        outputFStream << object.getCounter() << endl;
    else
    {
        outputFStream << object.getcompCounter() << endl;
        outputFStream << object.getCompX() << ' ' << object.getCompY() << endl;
    }  
    for (i = 0; i < object.getHeight(); i++)
    {
        for (j = 0; j <object.getWidth(); j++)
        {
            outputFStream << static_cast<int>(object.hexCell[i][j].getState()) << ' ';
        }
    }
    outputFStream << endl;
    outputFStream << object.getCapacity();
    outputFStream << endl;
    for (i = 0; i <object.getCapacity(); i++)
    {
        outputFStream << object.moves[i].getRow() << ' ' << object.moves[i].getColumn() << ' ' << static_cast<int>(object.moves[i].getState()) << ' ';
    }
    outputFStream << endl;
    outputFStream << object.getScoreX() << endl;
    outputFStream << object.getScoreO();
    return outputFStream;
}
//THIS FUNCTION CALCULATES TOTAL X SCORES. SCORE WILL BE INCREASED ONLY IF IT IS CORRECT DIRECTION
void Hex::findScoreX(int x,int y)
{
    int i;
    int move_row[]={-1,-1,0,0,1,1};//These are the 6 different direction in the game
	int move_col[]={0,1,-1,1,-1,0};
    int coordinate[2];
    unsuitCount++;
    addUnsuit(Cell(x,y));
    for (i = 0; i < 6; i++)
    {
        coordinate[0] = x + move_row[i];
        coordinate[1] = y + move_col[i];
        if (checkSuitability(coordinate,Hex::Cell::CellContent::x))
        {   
            if (isUnsuit(coordinate[0],coordinate[1]))
            {
                if (i==1 || i==3)
                {
                    tempScoreX++;
                }
                findScoreX(coordinate[0],coordinate[1]);
            }
        }
    }
}
//THIS FUNCTION SENDS ALL MOVES AND SAVES THE CALCULATED SCORE FOR X
void Hex::scoreX()
{
    int i;
    for (i = 0; i <getCapacity(); i+=2)
    {
        unsuitCount=0;
        delete[] unsuitCells;
        unsuitCells=nullptr;
        tempScoreX=0;
        findScoreX(moves[i].getRow(),moves[i].getColumn());
        if (tempScoreX>score_x)
            score_x=tempScoreX;
    }
}
//THIS FUNCTION CALCULATES TOTAL O SCORES. SCORE WILL BE INCREASED ONLY IF IT IS CORRECT DIRECTION
void Hex::findScoreO(int x,int y)
{
    int i;
    int move_row[]={-1,-1,0,0,1,1};//These are the 6 different direction in the game
	int move_col[]={0,1,-1,1,-1,0};
    int coordinate[2];
    unsuitCount++;
    addUnsuit(Cell(x,y));
    for (i = 0; i < 6; i++)
    {
        coordinate[0] = x + move_row[i];
        coordinate[1] = y + move_col[i];
        if (checkSuitability(coordinate,Hex::Cell::CellContent::o))
        {   
            if (isUnsuit(coordinate[0],coordinate[1]))
            {
                if (i==4 || i==5)
                {
                    tempScoreO++;
                }
                findScoreO(coordinate[0],coordinate[1]);
            }
        }
    }
}
//THIS FUNCTION SENDS ALL MOVES AND SAVES THE CALCULATED SCORE FOR O
void Hex::scoreO()
{
    int i;
    for (i = 1; i <getCapacity(); i+=2)
    {
        unsuitCount=0;
        delete[] unsuitCells;
        unsuitCells=nullptr;
        tempScoreO=0;
        findScoreO(moves[i].getRow(),moves[i].getColumn());
        if (tempScoreO>score_o)
            score_o=tempScoreO;
    }
}
//THIS FUNCTION CHECKS THE GIVEN MOVE IS SUIT OR UNSUIT FOR SCORE CALCULATION
bool Hex::isUnsuit(int x,int y)
{
    int i;
    for (i = 0; i < unsuitCount; i++)
    {
        if (unsuitCells[i].getRow()==x && unsuitCells[i].getColumn()==y)
        {
            return false;
        }
    }
    return true;
}
//THIS FUNCTION MARKS THE VISITED CELLS AND STORE IN AN ARRAY
void Hex::addUnsuit(Cell unsuit)
{
    int i;
    Cell *tempCell;
    if (unsuitCount==1)
    {
        unsuitCells = new Cell[unsuitCount];
        unsuitCells[unsuitCount-1]=unsuit;
    }
    else
    {
        tempCell=new Cell[unsuitCount];
        for (i = 0; i < unsuitCount-1; i++)
        {
            tempCell[i]=unsuitCells[i];
        }
        delete[] unsuitCells;
        unsuitCells = new Cell[unsuitCount];
        for (i = 0; i < unsuitCount; i++)
        {
            unsuitCells[i]=tempCell[i];
        }
        unsuitCells[unsuitCount-1]=unsuit;
        delete[] tempCell;
    }
}
//-----------------------REST OF THE CODE ALMOST THE SAME WITH HW3----------------------

//IT FINDS THE MARKED CELLS OF AN OBJECT
void Hex::findMarkedCells()
{
    int i,j,num=0;
    for (i = 0; i <rowSize; i++)
    {
        for (j = 0; j < colSize; j++)
        {
            if (hexCell[i][j].getState()!=Cell::CellContent::empty)
                num++;
        }
    }
    Hex::allMarkedCells+=num;
}
//THIS FUNCTION STARTS THE GAME
void Hex::playGame()
{
    bool exitFirst=true,exitSecond=true;
    int selection;
    cout << "\033[2J\033[1;1H";
    cout << "<<<<<<<<Welcome To The Hex Game>>>>>>>>" << endl;
    while (exitFirst)
    {
        cout << "Please enter the board size (Min 5x5): ";
        cin >> colSize;
        rowSize=colSize;
        if (colSize<5)
        {
            cout << "Size cannot be smaller than 5 !" << endl; 
        }
        else
        {
            exitFirst=false;
            createBoard();
            while (exitSecond)
            {
                cout << "1-) Play with User" << endl;
                cout << "2-) Play with Computer" << endl;
                cout << "3-) Exit" << endl;
                cout << "Make your choice: " ;
                cin >> selection;
                if (selection==1)
                {
                    exitSecond=false;
                    setGameMode(selection);
                    playWPlayer();
                }
                else if (selection==2)
                {
                    exitSecond=false;
                    setGameMode(selection);
                    playWComp();
                }
                else if (selection==3)
                {
                    cout << "GoodByee <3" << endl;
                    exitSecond = false;
                }
                else
                {
                    cout << "Wrong Choice! Try again." << endl;
                }
            }
        }
    }
}
//THIS FUNCTION MAKES COMPUTER MOVES
Hex::Cell Hex::play()
{
    Cell tempCell;
    markedCells++;
    int move_up[2][2]={{-1,0},{-1,1}};
    int move_down[2][2]={{1,-1},{1,0}};
    int left_rigt[2][2]={{0,-1},{0,1}};
    allMoves(move_up,move_down,left_rigt); 
    tempCell.setColumn(compY);
    tempCell.setRow(compX);
    tempCell.setState(Cell::CellContent::o);
    return tempCell;
}
//THIS FUNCTION MAKES PLAYER MOVES
Hex::Cell Hex::play(const int &r,const int &c)
{
    markedCells++;
    Cell tempCell;
    if(getCounter()%2==0)
    {
        hexCell[r-1][c-1].setState(Cell::CellContent::x);
        tempCell=hexCell[r-1][c-1];
    }
    else
    {
        hexCell[r-1][c-1].setState(Cell::CellContent::o);
        tempCell=hexCell[r-1][c-1];
    }
    return tempCell;
}
//THIS FUNCTION MANAGES THE COMPUTER VS PLAYER GAME
bool Hex::playWComp()
{
    bool exitFirst=true,exitSecond=true;
    int r;
    char c;
    int flag;
    string wholeLine,command,fileName;
    Cell tempCell;
    while (exitFirst!=false)
    {
        if (isWin(Cell::CellContent::x,Cell::CellContent::o))
        {
            cout << "\033[2J\033[1;1H";//Clears the screen.
            cout << *this;
            cout << "Player 1 Wins !!" << endl;
            gameEnd=true;
            return true;
        }
        else if (isWin(Cell::CellContent::o,Cell::CellContent::x))
        {
            cout << "\033[2J\033[1;1H";
            cout << *this;
            cout << "Computer Wins !!" << endl;
            gameEnd=true;
            return true;
        }
        else
        {
            exitSecond=true;
            cout << "\033[2J\033[1;1H";
            cout << *this;
            if (compCounter!=0)
            {
                cout << "Computer Move: " << static_cast<char>(compY+65) << " " << compX+1<< endl;
            }
            while (exitSecond!=false)
            {
                flag=-1;
                cout << "Make your move(Ex: A1) : " ;
                getline(cin>>ws,wholeLine);
                flag=wholeLine.find(" ");
                if (wholeLine=="EXIT")
                {
                    return false;
                }
                else if (wholeLine=="UNDO")
                {
                    cout << "\033[2J\033[1;1H";
                    (*this)--;
                    score_o=0;
                    score_x=0;
                    scoreX();
                    scoreO();
                    cout << *this;  
                    if (isEmpty())
                        cout << "No more moves to undo !" << endl;
                    else
                    {
                        cout << "Computer Move: " << static_cast<char>(compY+65) << " " << compX+1<< endl;
                    }
                }              
                else
                {
                    c=wholeLine[0];
                    r=stoi(wholeLine.substr(1));
                    if (c>96 && c<123)
                    {
                        c-=96;
                    }
                    else if (c>64 && c<90)
                    {
                        c-=64;
                    }
                    if(r>0 && r<=rowSize && c>0 && c<=colSize && hexCell[r-1][c-1].getState()==Hex::Cell::CellContent::empty)
                    {
                        exitSecond = false;
                        tempCell=play(r,c);
                        increaseCapacity();
                        addMove(tempCell);
                        if (tempCell.getState()==Hex::Cell::CellContent::x)
                            scoreX();
                        else if (tempCell.getState()==Hex::Cell::CellContent::o)
                            scoreO();
                        tempCell=play();
                        increaseCapacity();
                        addMove(tempCell);
                        scoreO();
                        compCounter+=2;
                    }
                    else 
                        cout << "->>>>Please make a valid move !!!" << endl;
                }
            }
        }
    }
    return false;
}
//FOLLOWING FUNCTIONS ARE AI FUNCTIONS
void Hex::randomMove()
{
    srand(time(0));
    bool exit=true;
    int rand_coord[2];
    while (exit)
    {
        rand_coord[0]=rand()%colSize;
        rand_coord[1]=rand()%colSize;
        if (checkComputerMove(rand_coord))
        {
            hexCell[rand_coord[0]][rand_coord[1]].setState(Cell::CellContent::o);
            compX=rand_coord[0];
            compY=rand_coord[1];
            exit=false;
        }
    }
}
/*This function manages first move,other moves and random moves.*/
void Hex::allMoves(int move_up[2][2],int move_down[2][2],int left_rigt[2][2])
{
    if (!compMove(move_down))
    {
        if (!compMove(left_rigt))
        {
            randomMove();
        }
    }   
}
bool Hex::compMove(int moves[2][2])
{
    if (compCounter==0)
    {
        if (hexCell[0][colSize/2].getState()==Cell::CellContent::empty)
        {
            compX=0;
            compY=colSize/2;
            hexCell[compX][compY].setState(Cell::CellContent::o);
        }
        else
        {
            compX=0;
            compY=(colSize/2)-1;
            hexCell[compX][compY].setState(Cell::CellContent::o);
        }
        return true;
    }
    else
    {
        int i;
        int temp_coord[2];
        temp_coord[0]=compX;
        temp_coord[1]=compY;
        for (i = 0; i <2; i++)
        {
            temp_coord[0]+=moves[i][0];
            temp_coord[1]+=moves[i][1];
            if (checkComputerMove(temp_coord))
            {
                compX+=moves[i][0];
                compY+=moves[i][1];
                hexCell[compX][compY].setState(Cell::CellContent::o);
                return true;
            }
            else
            {
                temp_coord[0]-=moves[i][0];
                temp_coord[1]-=moves[i][1];
            }      
        }
    }
    return false;
}
bool Hex::checkComputerMove(int coord[2])
{
    return (coord[0] >= 0 && coord[0] < colSize && coord[1] >= 0 && coord[1] < colSize && 
    hexCell[coord[0]][coord[1]].getState() == Cell::CellContent::empty);
}
//THIS FUNCTION MANAGES THE PLAYER VS PLAYER GAME
bool Hex::playWPlayer()
{
    bool exitFirst=true,exitSecond=true;
    int r;
    char c,temp;
    int flag;
    string wholeLine,command,fileName;
    Cell tempCell;
    while (true)
    {
        if (isWin(Cell::CellContent::x,Cell::CellContent::o))
        {
            cout << "\033[2J\033[1;1H";//Clears the screen.
            cout << *this;
            cout << "Player 1 Wins !!" << endl;
            gameEnd = true;
            return true;
        }
        else if (isWin(Cell::CellContent::o,Cell::CellContent::x))
        {
            cout << "\033[2J\033[1;1H";
            cout << *this;
            cout << "Player 2 Wins !!" << endl;
            gameEnd=true;
            return true;
        }
        else
        {
            exitSecond=true;
            cout << "\033[2J\033[1;1H";
            cout << *this;
            while (exitSecond)
            {
                flag=-1;
                if(counter%2==0)
                    cout << "(Player 1) Make Your Move(Ex: A1) :  ";
                else 
                    cout << "(Player 2) Make Your Move(Ex: A1) :  ";
                getline(cin>>ws,wholeLine);
                flag=wholeLine.find(" ");
                if (wholeLine=="EXIT")
                {   
                    return false;
                } 
                else if (wholeLine=="UNDO")
                {
                    cout << "\033[2J\033[1;1H";
                    --(*this);
                    score_o=0;
                    score_x=0;
                    scoreX();
                    scoreO();
                    cout << *this;   
                }                
                else
                {
                    c=wholeLine[0];
                    r=stoi(wholeLine.substr(1));
                    if (c>96 && c<123)
                    {
                        c-=96;
                    }
                    else if (c>64 && c<90)
                    {
                        c-=64;
                    }
                    if(r>0 && r<=rowSize && c>0 && c<=colSize && hexCell[r-1][c-1].getState()==Hex::Cell::CellContent::empty)
                    {
                        exitSecond = false;
                        tempCell=play(r,c);
                        increaseCapacity();
                        addMove(tempCell);
                        if (tempCell.getState()==Hex::Cell::CellContent::x)
                            scoreX();
                        else if (tempCell.getState()==Hex::Cell::CellContent::o)
                            scoreO();
                        counter++;
                    }
                    else 
                        cout << "->>>>Please make a valid move !!!" << endl;   
                }
            } 
        }
    }
}
//THIS FUNCTION DETERMINES THE WHICH USER IS WINNER. 
bool Hex::isWin(const Cell::CellContent &safe_ch,const Cell::CellContent &forb_ch)
{
    int i,j;
    int move_row[]={-1,-1,0,0,1,1};//These are the 6 different direction in the game
	int move_col[]={0,1,-1,1,-1,0};
    int coordinate[2];
    for (i = 0; i < colSize; i++)
    {
        if (safe_ch == Cell::CellContent::x)
        {
            if (hexCell[i][0].getState()!=Cell::CellContent::empty && hexCell[i][0].getState()!=forb_ch)
            {
                coordinate[0]=i;
                coordinate[1]=0;
                if (winControl(coordinate,move_row,move_col,0,safe_ch))
                {
                    if (safe_ch==Cell::CellContent::x)
                    {
                        hexCell[i][0].setState(Cell::CellContent::X);
                    }
                    else if (safe_ch==Cell::CellContent::o)
                    {
                        hexCell[i][0].setState(Cell::CellContent::O);
                    }                    
                    return true;
                }
            }
        }
        else
        {
            if (hexCell[0][i].getState()!=Cell::CellContent::empty && hexCell[0][i].getState()!=forb_ch)
            {
                coordinate[0]=0;
                coordinate[1]=i;
                if (winControl(coordinate,move_row,move_col,0,safe_ch))
                {
                    if (safe_ch==Cell::CellContent::x)
                    {
                        hexCell[0][i].setState(Cell::CellContent::X);
                    }
                    else if (safe_ch==Cell::CellContent::o)
                    {
                        hexCell[0][i].setState(Cell::CellContent::O);
                    }  
                    return true;
                }
            }
        }
    }
    return false; 
}
//THIS FUNCTION DETERMINES THE GAME IS FINISH OR NOT WITH USING BACKTRACKING ALGORITHM. 
bool Hex::winControl(const int coordinate[2],const int move_row[6],const int move_col[6],int count,const Cell::CellContent &usr_ch)
{
    int k, next_coord[2];
    if (usr_ch==Hex::Cell::CellContent::x && coordinate[1]==colSize-1)
        return true;
    else if (usr_ch==Hex::Cell::CellContent::o && coordinate[0]==colSize-1)
        return true;
    for (k = 0; k < 6; k++) 
    {
        next_coord[0] = coordinate[0] + move_row[k];
        next_coord[1] = coordinate[1] + move_col[k];
        if (checkSuitability(next_coord,usr_ch)) 
        {
            if (usr_ch==Cell::CellContent::x)
                hexCell[next_coord[0]][next_coord[1]].setState(Cell::CellContent::X);
            else if (usr_ch==Cell::CellContent::o)
                hexCell[next_coord[0]][next_coord[1]].setState(Cell::CellContent::O);
            if (winControl(next_coord,move_row,move_col,count + 1,usr_ch)==true)
                return true;
            else
                hexCell[next_coord[0]][next_coord[1]].setState(usr_ch); 
        }
    }
    return false;
}
/*This function controls the next move of player valid or not*/
bool Hex::checkSuitability(const int coordinate[2],const Cell::CellContent &usr_ch)
{
    Cell::CellContent forb_ch;
    if (usr_ch==Cell::CellContent::x)
        forb_ch=Cell::CellContent::o;
    else
        forb_ch=Cell::CellContent::x;     
    return (coordinate[0] >= 0 && coordinate[0] < rowSize && coordinate[1] >= 0 && coordinate[1] < colSize && 
    hexCell[coordinate[0]][coordinate[1]].getState() == usr_ch);
}
/*
This function saves the essential game datas such as game board,board size etc. into a file with using c++11
enum types which is enum classes.If the file cannot created the function returns false.
*/
bool Hex::saveBoard(string fileName) const
{
    fstream file(fileName,ios::out);
    if (file.fail())
        return false;
    file << *this;
    file.close();
    return true;
}
/*
    This function reads the essential game datas such as game board,board size etc. from a file with using c++11
enum types.If the file cannot be opened the function returns false.
*/
int Hex::loadBoard(string fileName) 
{
    fstream file;
    file.open(fileName,ios::in);
    if (file.fail())
        return false;
    file >> *this;
    file.close();
    if (gameMode==2 && gameEnd!=1)
        playWComp();
    else if(gameEnd!=1 && gameMode==1)
        playWPlayer();
    if (gameEnd==1)
        return -1;
    return true;
} 
//THIS FUNCTION IS OVERLOADED VERSION OF UPPER FUNCTION.IT READS THE GAME DATAS BUT WILL NOT DISPLAY THE GAME BOARD.
int Hex::loadBoard(string fileName,int foo) 
{
    fstream file;
    file.open(fileName,ios::in);
    Cell tempCell;
    if (!file.is_open())
        return false;
    file >> *this;
    file.close();
    return true;
} 
