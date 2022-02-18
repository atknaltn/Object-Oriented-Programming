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
    createVectorBoard();
}
//IT CREATES AN OBJECT WITH SIZE PARAMATERS
Hex::Hex(int width,int height)
{
    gameCount++;
    rowSize=height;
    colSize=width;
    createVectorBoard();
}
//IT CREATES A DEFAULT CELL OBJECT
Hex::Cell::Cell(int nRow,int nCol)
{
    row=nRow;
    column=nCol;
    state=CellContent::empty;
}
//IT FILLS THE HEX OBJECT'S CELLS
void Hex::createVectorBoard()
{
    int i,j;
    for (i = 0; i < colSize; i++)
    {
        hexCell.push_back(vector<Hex::Cell>());
        for (j = 0; j < colSize; j++)
        {
            hexCell[i].push_back(Hex::Cell(i,j));
        }
    }
}
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
//PRINTS THE GAME TABLE ON TERMINAL
void Hex::display() const
{
    int i,j,k;
    cout << "GAME NAME: " <<gameName << endl;
    cout << "  ";
    for (i = 0; i < rowSize; i++)
    {
        cout << static_cast<char>('A'+i)<< "  ";
    }
    cout << endl;
    for (i = 0; i < colSize; i++)
    {
        cout << 1+i << " ";
        for (k = 0; k < i; k++)
        {
            cout << "  ";
        }
        for (j = 0; j < colSize; j++)
        {
            cout << static_cast<char> (hexCell[i][j].getState()) <<"  ";
        }
        cout << endl;
    }
    if (gameEnd==false)
    {
        cout << "ENTER \"EXIT\" TO BACK TO MAIN MENU" << endl; 
    }
}
//COMPARE 2 GAMES AND IF THE FIRST OBJECT HAS MORE MARKED CELLS THEN IT WILL TRUE
bool Hex::compareGames(Hex otherGame) const
{
    if (getMarkedCells()>otherGame.getMarkedCells())
        return true;
    else 
        return false;
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
            createVectorBoard();
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
void Hex::play()
{
    markedCells++;
    cout << getMarkedCells() << endl;
    int move_up[2][2]={{-1,0},{-1,1}};
    int move_down[2][2]={{1,-1},{1,0}};
    int left_rigt[2][2]={{0,-1},{0,1}};
    allMoves(move_up,move_down,left_rigt);
}
//THIS FUNCTION MAKES PLAYER MOVES
void Hex::play(const int &r,const int &c)
{
    markedCells++;
    if(counter%2==0)
    {
        hexCell[r-1][c-1].setState(Cell::CellContent::x);
    }
    else
    {
        hexCell[r-1][c-1].setState(Cell::CellContent::o);
    }
}
//THIS FUNCTION MANAGES THE COMPUTER VS PLAYER GAME
bool Hex::playWComp()
{
    bool exitFirst=true,exitSecond=true;
    int r;
    char c;
    int flag;
    string wholeLine,command,fileName;
    while (exitFirst!=false)
    {
        if (isWin(Cell::CellContent::x,Cell::CellContent::o))
        {
            cout << "\033[2J\033[1;1H";//Clears the screen.
            display();
            cout << "Player 1 Wins !!" << endl;
            gameEnd=true;
            return true;
        }
        else if (isWin(Cell::CellContent::o,Cell::CellContent::x))
        {
            cout << "\033[2J\033[1;1H";
            display();
            cout << "Computer Wins !!" << endl;
            gameEnd=true;
            return true;
        }
        else
        {
            exitSecond=true;
            cout << "\033[2J\033[1;1H";
            display();
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
                else if (flag>-1)
                {
                    string temp1,temp2;
                    command=wholeLine.substr(0,4);
                    fileName=wholeLine.substr(flag+1);
                    if (command=="LOAD")
                    {
                       if (!loadBoard(fileName))
                        {
                            cerr << "The file cannot be opened !!!" << endl;
                        }
                        counter -=2;
                        return 0; 
                    }
                    else if (command=="SAVE")
                    {
                        if(!saveBoard(fileName))
                        {
                            cerr << "The file cannot be created." << endl;
                        }
                        counter-=2;
                        break;
                    }
                    else
                    {
                        cerr << "Wrong Command !!!" << endl;
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
                        play(r,c);
                        play();
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
    while (true)
    {
        if (isWin(Cell::CellContent::x,Cell::CellContent::o))
        {
            cout << "\033[2J\033[1;1H";//Clears the screen.
            display();
            cout << "Player 1 Wins !!" << endl;
            gameEnd = true;
            return true;
        }
        else if (isWin(Cell::CellContent::o,Cell::CellContent::x))
        {
            cout << "\033[2J\033[1;1H";
            display();
            cout << "Player 2 Wins !!" << endl;
            gameEnd=true;
            return true;
        }
        else
        {
            exitSecond=true;
            cout << "\033[2J\033[1;1H";
            display();
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
                else if (flag>-1)
                {
                    string temp1,temp2;
                    command=wholeLine.substr(0,4);
                    fileName=wholeLine.substr(flag+1);
                    if (command=="LOAD")
                    {
                       if (!loadBoard(fileName))
                        {
                            cerr << "The file cannot be opened !!!" << endl;
                        }
                        counter -=2;
                        return false; 
                    }
                    else if (command=="SAVE")
                    {
                        if(!saveBoard(fileName))
                        {
                            cerr << "The file cannot be created." << endl;
                        }
                        counter-=2;
                        break;
                    }
                    else
                    {
                        cerr << "Wrong Command !!!" << endl;
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
                        play(r,c);
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
    {
        return true;
    }
    else if (usr_ch==Hex::Cell::CellContent::o && coordinate[0]==colSize-1)
    {
        return true;
    }
    for (k = 0; k < 6; k++) 
    {
        next_coord[0] = coordinate[0] + move_row[k];
        next_coord[1] = coordinate[1] + move_col[k];
        if (checkSuitability(next_coord,usr_ch)) 
        {
            if (usr_ch==Cell::CellContent::x)
            {
                hexCell[next_coord[0]][next_coord[1]].setState(Cell::CellContent::X);
            }
            else if (usr_ch==Cell::CellContent::o)
            {
                hexCell[next_coord[0]][next_coord[1]].setState(Cell::CellContent::O);
            }
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
    {
        forb_ch=Cell::CellContent::o;
    }
    else
    {
        forb_ch=Cell::CellContent::x;
    }       
    return (coordinate[0] >= 0 && coordinate[0] < rowSize && coordinate[1] >= 0 && coordinate[1] < colSize && 
    hexCell[coordinate[0]][coordinate[1]].getState() == usr_ch);
}
/*
This function saves the essential game datas such as game board,board size etc. into a file with using c++11
enum types which is enum classes.If the file cannot created the function returns false.
*/
bool Hex::saveBoard(string fileName) const
{
    fstream file;
    file.open(fileName,ios::out);
    int i,j;
    if (file.fail())
    { 
        return false;
    } 
    file << gameEnd << endl;
    file << colSize << endl;
    file << gameMode << endl;

    if (gameMode==1)
        file << counter << endl;
    else
    {
        file << compCounter << endl;
        file << compX << ' ' << compY << endl;
    }  
    for (i = 0; i < rowSize; i++)
    {
        for (j = 0; j < colSize; j++)
        {
            file << static_cast<int>(hexCell[i][j].getState()) << ' ';
        }
    }
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
    {
        return false;
    }
    int i,j;
    decltype(i) input;
    file >> input;
    if (input==1)
        setEnd(true);
    else 
        setEnd(false);
    file >> input;
    rowSize=input;
    colSize=input;
    file >> gameMode;
    if (gameMode==1)
    {
        file >> counter;
        setMarkedCells(counter);
    }
    else
    {
        file >> compCounter;
        setMarkedCells(compCounter);
        file >> compX;
        file >> compY;    
    }
    createVectorBoard();
    for ( i = 0; i < rowSize; i++)
    {
        for ( j = 0; j < colSize; j++)
        {
            file >> input;
            hexCell[i][j].setState(static_cast<Hex::Cell::CellContent>(input));
        }       
    }    
    file.close();
    if (gameMode==2 && gameEnd!=1)
    {
        playWComp();
    }
    else if(gameEnd!=1 && gameMode==1)
    {
        playWPlayer();
    }
    if (gameEnd==1)
    {
        return -1;
    }
    return true;
} 
//THIS FUNCTION IS OVERLOADED VERSION OF UPPER FUNCTION.IT READS THE GAME DATAS BUT WILL NOT DISPLAY THE GAME BOARD.
int Hex::loadBoard(string fileName,int foo) 
{
    fstream file;
    file.open(fileName,ios::in);
    if (!file.is_open())
    {
        return false;
    }
    int i,j;
    decltype(i) input;
    file >> input;
    if (input==1)
        setEnd(true);
    else 
        setEnd(false);
    file >> input;
    rowSize=input;
    colSize=input;
    file >> gameMode;
    if (gameMode==1)
    {
        file >> counter;
        setMarkedCells(counter);
    }
    else
    {
        file >> compCounter;
        setMarkedCells(compCounter);
        file >> compX;
        file >> compY;    
    }
    createVectorBoard();
    for ( i = 0; i < rowSize; i++)
    {
        for ( j = 0; j < colSize; j++)
        {
            file >> input;
            hexCell[i][j].setState(static_cast<Hex::Cell::CellContent>(input));
        }       
    }    
    file.close();
    return true;
} 
