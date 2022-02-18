#include<iostream>
#include"ai.h"
#include<cstdlib>
#include<ctime>
#include"game_control_unit.h"
#include"game_board.h"
#include"interface.h"


using namespace std;

/*This function provides the computer to make random move when it has no other place to go.*/
void random_move(char board[12][12],int SIZE,int move_list[72][2],int counter)
{
    srand(time(0));
    bool exit=true;
    int rand_coord[2];
    while (exit)
    {
        rand_coord[0]=rand()%SIZE;
        rand_coord[1]=rand()%SIZE;
        if (check_computer_move(board,rand_coord,SIZE))
        {
            board[rand_coord[0]][rand_coord[1]]='o';
            move_list[counter][0]=rand_coord[0];
            move_list[counter][1]=rand_coord[1];
            exit=false;
        }
    }
}
/*This function manages first move,other moves and random moves.*/
void computer_move(char board[12][12],int counter,int SIZE,int move_list[72][2],int move_up[2][2],int move_down[2][2],int left_rigt[2][2])
{
    if (counter==0)
    {
        first_move(board,SIZE,move_list[counter]);
    }
    else
    {
        if (!other_moves(board,move_list[counter-1],move_list[counter],move_down,SIZE))
        {
            if (!other_moves(board,move_list[counter-1],move_list[counter],left_rigt,SIZE))
            {
                random_move(board,SIZE,move_list,counter);
            }
        }
        
    }
}
/*This function provides the computer to make the first move.First move makes it easy to win*/
void first_move(char board[12][12],int SIZE,int coord[2])
{
    if (board[0][SIZE/2]=='.')
    {
        board[0][SIZE/2]='o';
        coord[0]=0;
        coord[1]=SIZE/2;
    }
    else
    {
        board[0][(SIZE/2)-1]='o';  
        coord[0]=0;
        coord[1]=(SIZE/2)-1;
    }
}
/*This function handles the moves after the first move. If this function is blocked random function is activated*/
bool other_moves(char board[12][12],int last_coord[2],int current_coord[2],int moves[2][2],int SIZE)
{
    int i;
    int temp_coord[2];
    temp_coord[0]=last_coord[0];
    temp_coord[1]=last_coord[1];
    for (i = 0; i <2; i++)
    {
        temp_coord[0]+=moves[i][0];
        temp_coord[1]+=moves[i][1];
        if (check_computer_move(board,temp_coord,SIZE))
        {
            current_coord[0]=last_coord[0]+moves[i][0];
            current_coord[1]=last_coord[1]+moves[i][1];
            board[current_coord[0]][current_coord[1]]='o';
            return true;
        }
        else
        {
            temp_coord[0]-=moves[i][0];
            temp_coord[1]-=moves[i][1];
        }      
    }
    return false;
}
