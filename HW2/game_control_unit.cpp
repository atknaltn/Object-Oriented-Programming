#include<iostream>
#include"ai.h"
#include<cstdlib>
#include<ctime>
#include"game_control_unit.h"
#include"game_board.h"
#include"interface.h"

using namespace std;

/*This function checks if the computer's move is valid or not*/
bool check_computer_move(char board[12][12],int coord[2],int SIZE)
{
    return (coord[0] >= 0 && coord[0] < SIZE && coord[1] >= 0 && coord[1] < SIZE && 
    board[coord[0]][coord[1]] == '.');
}
/*This function checks the letter which was inputted by user is valid or not. And also handles captital letters*/
bool check_move_letter(char letters[12],int SIZE,char move)
{
    int i,flag=0;
    if (move>64 && move<91)
    {
        move+=32;
    }
    for (i = 0; i < SIZE; i++)
    {
        if (move == letters[i])
        {
            flag=1;
        }
    }
    if (flag==1)
    {
        return true;
    }
    return false;
}
/*This function checks the number which was inputted by user is valid or not*/
bool check_move_num(int nums[12],int SIZE,int move)
{
    int i,flag=0;
    for (i = 0; i < SIZE; i++)
    {
        if (move == nums[i])
        {
            flag=1;
        }
    }
    if (flag==1)
    {
        return true;
    }
    return false;
}
/*This function finds the char's index which was inputted*/
int find_index(char letters[12],char move,int SIZE)
{
    int i,flag;
    if (move>64 && move<91)
    {
        move+=32;
    }
    for (i = 0; i < SIZE; i++)
    {
        if (move == letters[i])
        {
            flag=i;
        }
    }
    return flag;
}
/*
    This function checks if there is a x move on the far left because if this situation is not provided winning is not 
    possible. Then, if there is a x on the far left, function will send the coordinates of each x on the left side to 
    a bactracking algorithm.Backtracking algorithm decides the user win or not.The same goes for 'o'
*/
bool is_win(char board[12][12],int SIZE,char safe_ch,char forb_ch)
{
    int i,j;
    int move_row[]={-1,-1,0,0,1,1};//These are the 6 different direction in the game
	int move_col[]={0,1,-1,1,-1,0};
    int coordinate[2];
    
    for (i = 0; i < SIZE; i++)
    {
        if (safe_ch == 'x')
        {
            if (board[i][0]!='.' && board[i][0]!=forb_ch)
            {
                coordinate[0]=i;
                coordinate[1]=0;
                if (win_control(board,coordinate,SIZE,move_row,move_col,0,safe_ch))
                {
                    board[i][0]=safe_ch-32;
                    return true;
                }
            }
        }
        else
        {
            if (board[0][i]!='.' && board[0][i]!=forb_ch)
            {
                coordinate[0]=0;
                coordinate[1]=i;
                if (win_control(board,coordinate,SIZE,move_row,move_col,0,safe_ch))
                {
                    board[0][i]=safe_ch-32;
                    return true;
                }
            }
        }
    }
    return false; 
}
/*
    This algorithm checks the 'x' moves reach the far right or not and also checks 
    if the 'o' moves reach the far bottom or not with using game rules properly.
*/
bool win_control(char board[12][12],int coordinate[2],int SIZE,int move_row[6],int move_col[6],int count,char usr_ch)
{
    int k, next_coord[2];
    if (usr_ch=='x' && coordinate[1]==SIZE-1)
    {
        return true;
    }
    else if (usr_ch=='o' && coordinate[0]==SIZE-1)
    {
        return true;
    }
    for (k = 0; k < 6; k++) 
    {
        next_coord[0] = coordinate[0] + move_row[k];
        next_coord[1] = coordinate[1] + move_col[k];
        if (check_suitability(board,next_coord,SIZE,usr_ch)) 
        {
            board[next_coord[0]][next_coord[1]] = usr_ch-32;
            if (win_control(board,next_coord,SIZE,move_row,move_col,count + 1,usr_ch)==true)
                return true;
            else
                board[next_coord[0]][next_coord[1]] = usr_ch;
        }
    }
    return false;
}
/*This function controls the next move of player valid or not*/
bool check_suitability(char board[12][12],int coordinate[2],int SIZE,char usr_ch)
{
    char forb_ch;
    if (usr_ch=='x')
    {
        forb_ch='o';
    }
    else
    {
        forb_ch='x';
    }       
    return (coordinate[0] >= 0 && coordinate[0] < SIZE && coordinate[1] >= 0 && coordinate[1] < SIZE && 
    board[coordinate[0]][coordinate[1]] == usr_ch);
}
