#include"AbstractHex.h"
using namespace std;
using namespace AtakanHex;
AbstractHex::AbstractHex() : colSize(5),rowSize(5)
{/*INTENTIONALLY EMPTY*/}

//IT CREATES AN OBJECT WITH SIZE PARAMATERS
AbstractHex::AbstractHex(int width,int height)
{
    rowSize=height;
    colSize=width;
}
AbstractHex::~AbstractHex()
{/*INTENTIONALLY EMPTY*/}
void AbstractHex::print() const
{
    int i,j,k;
    cout << "GAME NAME: " <<getGameName() << endl;
    cout << "  ";
    for (i = 0; i < getHeight(); i++)
    {
        cout << static_cast<char>('A'+i)<< "  ";
    }
    cout << endl;
    for (i = 0; i < getWidth(); i++)
    {
        cout << 1+i << " ";
        for (k = 0; k < i; k++)
        {
            cout << "  ";
        }
        for (j = 0; j < getWidth(); j++)
        {
            cout << static_cast<char> ((*this)(i,j).getState()) <<"  ";
        }
        cout << endl;
    }
    if (gameEnd==false)
    {
        cout << "ENTER \"EXIT\" TO BACK TO MAIN MENU" << endl; 
    }
}
//THIS FUNCTION MAKES COMPUTER MOVES
void AbstractHex::play()
{
    markedCells++;
    int move_up[2][2]={{-1,0},{-1,1}};
    int move_down[2][2]={{1,-1},{1,0}};
    int left_rigt[2][2]={{0,-1},{0,1}};
    allMoves(move_up,move_down,left_rigt);
    setLastX(compX);
    setLastY(compY);
}
//THIS FUNCTION MAKES PLAYER MOVES
void AbstractHex::play(Cell cell)
{
    markedCells++;
    if(counter%2==0)
    {
        (*this)(cell.getRow(),cell.getColumn()).setState(Cell::CellContent::x);
    }
    else
    {
        (*this)(cell.getRow(),cell.getColumn()).setState(Cell::CellContent::o);
    }
    setLastX(cell.getRow());
    setLastY(cell.getColumn());
}
void AbstractHex::setSize(int width,int height)
{
    if (width!=height)
    {
        throw SquareException();
    }
    if (width<5 || height<5)
    {
        throw SizeException();
    }
    setWidth(width);
    setHeight(height);
    reset();
}
bool AbstractHex::operator==(const AbstractHex& otherGame)const
{
    if (getWidth()!=otherGame.getWidth() || getHeight()!=otherGame.getHeight()){
        return false; 
    }
    int i,j;
    for (i = 0; i < getWidth(); i++)
    {
        for (j = 0; j < getHeight(); j++)
        {
            if ((*this)(i,j).getState()!=otherGame(i,j).getState())
            {
                return false;
            }
        }
    }
    return true;
}
Cell AbstractHex::lastMove()const
{
    if (getLastX()==-1 || getLastY()==-1)
    {
        throw LastMoveException();
    }
    return (*this)(getLastX(),getLastY());
}
int AbstractHex::readFromFile(string fileName) 
{
    fstream file;
    file.open(fileName,ios::in);
    if (file.fail())
    {
        throw FileOpenException();
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
    setWidth(input);
    setHeight(input);
    file >> input;
    setGameMode(input);
    if (getGameMode()==1)
    {
        file >> counter;
        file >> input;
        setLastX(input);
        file >> input;
        setLastY(input);
        setMarkedCells(counter);
    }
    else
    {
        file >> input;
        setcompCounter(input);
        setMarkedCells(compCounter);
        file >> input;
        setCompX(input);
        setLastX(input);
        file >> input;  
        setCompY(input);  
        setLastY(input);
    }
    createBoard();
    for ( i = 0; i < getHeight(); i++)
    {
        for ( j = 0; j < getWidth(); j++)
        {
            file >> input;
            (*this)(i,j).setState(static_cast<Cell::CellContent>(input));
        }       
    }    
    file.close();
    if (getGameMode()==2 && isEnd()!=1)
    {
        playWComp();
    }
    else if(isEnd()!=1 && getGameMode()==1)
    {
        playWPlayer();
    }
    if (isEnd()==1)
    {
        return -1;
    }
    return true;
} 
//THIS FUNCTION IS OVERLOADED VERSION OF UPPER FUNCTION.IT READS THE GAME DATAS BUT WILL NOT DISPLAY THE GAME BOARD.
int AbstractHex::readFromFile(string fileName,int foo) 
{
    fstream file;
    file.open(fileName,ios::in);
    if (!file.is_open())
    {
        throw FileOpenException();
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
    setWidth(input);
    setHeight(input);
    file >> input;
    setGameMode(input);
    if (getGameMode()==1)
    {
        file >> counter;
        file >> input;
        setLastX(input);
        file >> input;
        setLastY(input);
        setMarkedCells(counter);
    }
    else
    {
        file >> input;
        setcompCounter(input);
        setMarkedCells(compCounter);
        file >> input;
        setCompX(input);
        setLastX(input);
        file >> input;  
        setCompY(input);  
        setLastY(input);
    }
    createBoard();
    for ( i = 0; i < rowSize; i++)
    {
        for ( j = 0; j < colSize; j++)
        {
            file >> input;
            (*this)(i,j).setState(static_cast<Cell::CellContent>(input));
        }       
    }    
    file.close();
    return true;
}
bool AbstractHex::writeToFile(string fileName) const
{
    fstream file;
    file.open(fileName,ios::out);
    int i,j;
    if (file.fail())
    { 
        throw FileCreateException();
        return false;
    } 
    file << isEnd() << endl;
    file << getWidth() << endl;
    file << getGameMode() << endl;

    if (getGameMode()==1)
    {
        file << getCounter() << endl;
        file << getLastX() << endl;
        file << getLastY() << endl;
    }
    else
    {
        file << getcompCounter() << endl;
        file << getCompX() << ' ' << getCompY() << endl;
    }  
    for (i = 0; i < getHeight(); i++)
    {
        for (j = 0; j < getHeight(); j++)
        {
            file << static_cast<int>((*this)(i,j).getState()) << ' ';
        }
    }
    file.close();
    return true;
}
void AbstractHex::playGame()
{
    bool exitFirst=true,exitSecond=true;
    int selection;
    cout << "\033[2J\033[1;1H";
    cout << "<<<<<<<<Welcome To The Hex Game>>>>>>>>" << endl;
    int input;
    while (exitFirst)
    {
        cout << "Please enter the board size (Min 5x5): ";
        cin >> input;
        setWidth(input);
        setHeight(input);
        if (getWidth()<5)
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
//THIS FUNCTION MANAGES THE COMPUTER VS PLAYER GAME
bool AbstractHex::playWComp()
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
            print();
            cout << "Player 1 Wins !!" << endl;
            setEnd(true);
            return true;
        }
        else if (isWin(Cell::CellContent::o,Cell::CellContent::x))
        {
            cout << "\033[2J\033[1;1H";
            print();
            cout << "Computer Wins !!" << endl;
            setEnd(true);
            return true;
        }
        else
        {
            exitSecond=true;
            cout << "\033[2J\033[1;1H";
            print();
            if (getcompCounter()!=0)
            {
                cout << "Computer Move: " << static_cast<char>(getCompY()+65) << " " << getCompX()+1<< endl;
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
                        try
                        {
                            readFromFile(fileName);
                        }
                        catch(const FileOpenException& e)
                        {
                            cerr << e.what() << '\n';
                        }
                        counter -=2;
                        return 0; 
                    }
                    else if (command=="SAVE")
                    {
                        try
                        {
                            writeToFile(fileName);
                        }
                        catch(const FileCreateException& e)
                        {
                            std::cerr << e.what() << '\n';
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
                    try
                    {
                        r=stoi(wholeLine.substr(1));
                    }
                    catch(const std::exception& e)
                    {
                        cerr << "Wrong Command" << endl;
                    }
                    if (c>96 && c<123)
                    {
                        c-=96;
                    }
                    else if (c>64 && c<90)
                    {
                        c-=64;
                    }
                    if(r>0 && r<=rowSize && c>0 && c<=colSize && (*this)(r-1,c-1).getState()==Cell::CellContent::empty)
                    {
                        exitSecond = false;
                        Cell tempCell;
                        tempCell.setRow(r-1);
                        tempCell.setColumn(c-1);
                        play(tempCell);
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
bool AbstractHex::playWPlayer()
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
            print();
            cout << "Player 1 Wins !!" << endl;
            setEnd(true);
            return true;
        }
        else if (isWin(Cell::CellContent::o,Cell::CellContent::x))
        {
            cout << "\033[2J\033[1;1H";
            print();
            cout << "Player 2 Wins !!" << endl;
            setEnd(true);
            return true;
        }
        else
        {
            exitSecond=true;
            cout << "\033[2J\033[1;1H";
            print();
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
                        try
                        {
                            readFromFile(fileName);
                        }
                        catch(const FileOpenException& e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                        counter -=2;
                        return false; 
                    }
                    else if (command=="SAVE")
                    {
                        try
                        {
                            writeToFile(fileName);
                        }
                        catch(const FileCreateException& e)
                        {
                            std::cerr << e.what() << '\n';
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
                    try
                    {
                        r=stoi(wholeLine.substr(1));
                    }
                    catch(const std::exception& e)
                    {
                        cerr << "Wrong Command" << endl;
                    }
                    if (c>96 && c<123)
                    {
                        c-=96;
                    }
                    else if (c>64 && c<90)
                    {
                        c-=64;
                    }
                    if(r>0 && r<=rowSize && c>0 && c<=colSize && (*this)(r-1,c-1).getState()==Cell::CellContent::empty)
                    {
                        exitSecond = false;
                        Cell tempCell;
                        tempCell.setRow(r-1);
                        tempCell.setColumn(c-1);
                        play(tempCell);
                        counter++;
                    }
                    else 
                        cout << "->>>>Please make a valid move !!!" << endl;   
                }
            } 
        }
    }
}
//FOLLOWING FUNCTIONS ARE AI FUNCTIONS
void AbstractHex::randomMove()
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
            (*this)(rand_coord[0],rand_coord[1]).setState(Cell::CellContent::o);
            setCompX(rand_coord[0]);
            setCompY(rand_coord[1]);
            exit=false;
        }
    }
}
/*This function manages first move,other moves and random moves.*/
void AbstractHex::allMoves(int move_up[2][2],int move_down[2][2],int left_rigt[2][2])
{
    if (!compMove(move_down))
    {
        if (!compMove(left_rigt))
        {
            randomMove();
        }
    }   
}
bool AbstractHex::compMove(int moves[2][2])
{
    if (compCounter==0)
    {
        if ((*this)(0,getWidth()/2).getState()==Cell::CellContent::empty)
        {
            setCompX(0);
            setCompY(colSize/2);
            (*this)(getCompX(),getCompY()).setState(Cell::CellContent::o);
        }
        else
        {
            setCompX(0);
            setCompY((colSize/2)-1);
            (*this)(getCompX(),getCompY()).setState(Cell::CellContent::o);
        }
        return true;
    }
    else
    {
        int i;
        int temp_coord[2];
        temp_coord[0]=getCompX();
        temp_coord[1]=getCompY();
        for (i = 0; i <2; i++)
        {
            temp_coord[0]+=moves[i][0];
            temp_coord[1]+=moves[i][1];
            if (checkComputerMove(temp_coord))
            {
                setCompX(getCompX()+moves[i][0]);
                setCompY(getCompY()+moves[i][1]);
                (*this)(getCompX(),getCompY()).setState(Cell::CellContent::o);
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
bool AbstractHex::checkComputerMove(int coord[2])
{
    return (coord[0] >= 0 && coord[0] < colSize && coord[1] >= 0 && coord[1] < colSize && 
    (*this)(coord[0],coord[1]).getState() == Cell::CellContent::empty);
}
//THIS FUNCTION DETERMINES THE WHICH USER IS WINNER. 
bool AbstractHex::isWin(const Cell::CellContent &safe_ch,const Cell::CellContent &forb_ch)
{
    int i,j;
    int move_row[]={-1,-1,0,0,1,1};//These are the 6 different direction in the game
	int move_col[]={0,1,-1,1,-1,0};
    int coordinate[2];
    for (i = 0; i < getWidth(); i++)
    {
        if (safe_ch == Cell::CellContent::x)
        {
            if ((*this)(i,0).getState()!=Cell::CellContent::empty && (*this)(i,0).getState()!=forb_ch)
            {
                coordinate[0]=i;
                coordinate[1]=0;
                if (winControl(coordinate,move_row,move_col,0,safe_ch))
                {
                    if (safe_ch==Cell::CellContent::x)
                    {
                        (*this)(i,0).setState(Cell::CellContent::X);
                    }
                    else if (safe_ch==Cell::CellContent::o)
                    {
                        (*this)(i,0).setState(Cell::CellContent::O);
                    }                    
                    return true;
                }
            }
        }
        else
        {
            if ((*this)(0,i).getState()!=Cell::CellContent::empty && (*this)(0,i).getState()!=forb_ch)
            {
                coordinate[0]=0;
                coordinate[1]=i;
                if (winControl(coordinate,move_row,move_col,0,safe_ch))
                {
                    if (safe_ch==Cell::CellContent::x)
                    {
                        (*this)(0,i).setState(Cell::CellContent::X);
                    }
                    else if (safe_ch==Cell::CellContent::o)
                    {
                        (*this)(0,i).setState(Cell::CellContent::O);
                    }  
                    return true;
                }
            }
        }
    }
    return false; 
}
//THIS FUNCTION DETERMINES THE GAME IS FINISH OR NOT WITH USING BACKTRACKING ALGORITHM. 
bool AbstractHex::winControl(const int coordinate[2],const int move_row[6],const int move_col[6],int count,const Cell::CellContent &usr_ch)
{
    int k, next_coord[2];
    if (usr_ch==Cell::CellContent::x && coordinate[1]==colSize-1)
    {
        return true;
    }
    else if (usr_ch==Cell::CellContent::o && coordinate[0]==colSize-1)
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
                (*this)(next_coord[0],next_coord[1]).setState(Cell::CellContent::X);
            }
            else if (usr_ch==Cell::CellContent::o)
            {
                (*this)(next_coord[0],next_coord[1]).setState(Cell::CellContent::O);
            }
            if (winControl(next_coord,move_row,move_col,count + 1,usr_ch)==true)
                return true;
            else
                (*this)(next_coord[0],next_coord[1]).setState(usr_ch); 
        }
    }
    return false;
}
/*This function controls the next move of player valid or not*/
bool AbstractHex::checkSuitability(const int coordinate[2],const Cell::CellContent &usr_ch)
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
    (*this)(coordinate[0],coordinate[1]).getState() == usr_ch);
}
