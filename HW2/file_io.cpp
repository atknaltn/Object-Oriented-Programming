#include<iostream>
#include<string>
#include<fstream>
#include"file_io.h"
#include"game_board.h"
#include"interface.h"

using namespace std;

/*
This function saves the essential game datas such as game board,board size etc. into a file with using c++11
enum types which is enum classes.Under the this function there is overloaded version which takes moveList which
stores the computer's moves. If the file cannot created the function returns false.
*/
bool saveBoard(string fileName,char board[12][12],const int &SIZE,int &playerReturn,const int &gameMode,int &counter)
{
    fstream file;
    file.open(fileName,ios::out);
    if (file.fail())
    { 
        return false;
    }  
    file << SIZE << endl;
    file << gameMode << endl;
    file << playerReturn << endl;
    int i,j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (board[i][j]=='.')
            {
                file <<static_cast<int>(CellContent::dot) << ' ';
            }
            else if (board[i][j]=='x')
            {
                file <<static_cast<int>(CellContent::x)<< ' ';
            }
            else if (board[i][j]=='X')
            {
                file <<static_cast<int>(CellContent::X)<< ' ';
            }
            else if (board[i][j]=='o')
            {
                file <<static_cast<int>(CellContent::o)<< ' ';
            }
            else
            {
                file <<static_cast<int>(CellContent::O)<< ' ';
            }
        }
    }
    file.close();
    return true;
}
bool saveBoard(string fileName,char board[12][12],const int &SIZE,int &playerReturn,const int &gameMode,int &counter,int moveList[72][2])
{
    fstream file;
    file.open(fileName,ios::out);
    if (file.fail())
    {
        return false;
    }  
    file << SIZE << endl;
    file << gameMode << endl;
    file << playerReturn << endl;
    int i,j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (board[i][j]=='.')
            {
                file <<static_cast<int>(CellContent::dot) << ' ';
            }
            else if (board[i][j]=='x')
            {
                file <<static_cast<int>(CellContent::x)<< ' ';
            }
            else if (board[i][j]=='X')
            {
                file <<static_cast<int>(CellContent::X)<< ' ';
            }
            else if (board[i][j]=='o')
            {
                file <<static_cast<int>(CellContent::o)<< ' ';
            }
            else
            {
                file <<static_cast<int>(CellContent::O)<< ' ';
            }
        }
    }
    file << endl;
    if (gameMode==1)
    {
        for (i = 0; i < counter; i++)
        {
            file << moveList[i][0] << ' ' << moveList[i][1] << ' ';
        }
    }
    file.close();
    return true;
}
/*
    This function reads the essential game datas such as game board,board size etc. from a file with using c++11
enum types which is enum classes then put them into variables which are taken from another function with their
references.If the file cannot be opened the function returns false.
*/
bool loadBoard(string fileName,char board[12][12],int &counter,int &gameMode,int &size,int nums[12],char letters[12],int moveList[72][2])
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
    size=input;
    file >> input;
    gameMode=input;
    file >> input;
    counter = input;
    for ( i = 0; i < size; i++)
    {
        for ( j = 0; j < size; j++)
        {
            file >> input;
            if (input==static_cast<int>(CellContent::dot))
            {
                board[i][j]='.';
            }
            else if (input==static_cast<int>(CellContent::x))
            {
                board[i][j]='x';
            }
            else if (input==static_cast<int>(CellContent::X))
            {
                board[i][j]='X';
            }
            else if (input==static_cast<int>(CellContent::o))
            {
                board[i][j]='o';
            }
            else if (input==static_cast<int>(CellContent::O))
            {
                board[i][j]='O';
            }
            else
            {
                cerr << "FILE CONTENT ERROR" << endl;
            }    
        }       
    }
    for (i = 0; i <72; i++)
    {
        moveList[i][0]=0;
        moveList[i][1]=0;
    }
    for (i = 0; i < counter; i++)
    {
        file >> moveList[i][0] >> moveList[i][1];
    }        
    file.close();
    if (gameMode==2)
    {
        play_with_user(board,moveList,nums,letters,size,gameMode,counter);
    }
    else
    {
        play_with_computer(board,moveList,nums,letters,size,gameMode,counter);
    }
    return true;
}  
