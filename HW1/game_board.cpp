#include<iostream>
#include"ai.h"
#include<cstdlib>
#include<ctime>
#include"game_control_unit.h"
#include"game_board.h"
#include"interface.h"

using namespace std;

/*This function fills the board with '.'*/
void fill_board(char arr[12][12],int SIZE)
{
    int i,j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            arr[i][j]='.';
        }
    }
}
/*This function prints the game board on the screen*/
void print_board(char board[12][12],int nums[12],char letters[12],int SIZE)
{
    int i,j,k;
    cout << "  ";
    for (i = 0; i < SIZE; i++)
    {
        cout << letters[i] << "  ";
    }
    cout << endl;
    for (i = 0; i < SIZE; i++)
    {
        cout << nums[i] << " ";
        for (k = 0; k < i; k++)
        {
            cout << "  ";
        }
        for (j = 0; j < SIZE; j++)
        {
            cout << board[i][j] <<"  ";
        }
        cout << endl;
    }
}