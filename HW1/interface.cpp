#include<iostream>
#include"ai.h"
#include<cstdlib>
#include<ctime>
#include"game_control_unit.h"
#include"game_board.h"
#include"interface.h"

using namespace std;
/*This function starts or finishes the game.*/
void start_game()
{
    int exit=true;
    int choice;
    char board[12][12];
    int nums[]={1,2,3,4,5,6,7,8,9,10,11,12};
    char letters[]={'a','b','c','d','e','f','g','h','j','k','l','m'};
    while (exit)
    {
        player_input(board,nums,letters);
        cout << "Do you want to play again ? (yes:1/no:0)" << endl;
        cin >> choice;
        if (choice==0)
        {
            exit=false;
        }
    }
}
/*This function handles player inputs*/
void player_input(char board[12][12],int nums[12],char letters[12])
{
    cout << "-------------------- WELCOME TO HEX GAME ------------------------" << endl;
    int SIZE;
    bool exit_first=true,exit_second=true;
    int choice;
    while (exit_first!=false)
    {
        cout << "Please enter the board size (Min : 6, Max: 12): ";
        cin >> SIZE;
        if (SIZE<6 || SIZE>12)
        {
            cout<< "->>>>Please enter a valid board size !!!"<<endl;
        }
        else
        {
            exit_first=false;
            fill_board(board,SIZE);
            cout << "To play with a computer : 1" << endl << "To play with user2 : 2"<<endl;
            while (exit_second!=false)
            {
                cout << "Make your choice: ";
                cin >> choice;
                if (choice==1)
                {
                    exit_second=false;
                    play_with_computer(board,nums,letters,SIZE);
                }
                else if (choice==2)
                {
                    exit_second=false;
                    play_with_user(board,nums,letters,SIZE);
                }
                else
                {
                    cout << "->>>>Please make a valid choice !!!" << endl;
                }
            }
        }
    }
}
/*This function provides the user to play the game with another user*/
void play_with_user(char board[12][12],int nums[12],char letters[12],int SIZE)
{
    int count=0;
    bool exit_first=true,exit_second=true;
    int row;
    char column; 
    while (exit_first!=false)
    {
        if (is_win(board,SIZE,'x','o'))
        {
            cout << "\033[2J\033[1;1H";//Clears the screen.
            print_board(board,nums,letters,SIZE);
            cout << "Player 1 Wins !!" << endl;
            break;
        }
        else if (is_win(board,SIZE,'o','x'))
        {
            cout << "\033[2J\033[1;1H";
            print_board(board,nums,letters,SIZE);
            cout << "Player 2 Wins !!" << endl;
            break;
        }
        else
        {
            exit_second=true;
            cout << "\033[2J\033[1;1H";
            print_board(board,nums,letters,SIZE);
            while (exit_second!=false)
            {
                if (count % 2 == 0)
                {
                    cout << "(Player 1) Make your move: " ;
                }
                else
                {
                    cout << "(Player 2) Make your move: " ;
                }
                cin >> column;
                cin >> row;
                if ((check_move_letter(letters,SIZE,column) && check_move_num(nums,SIZE,row)) && board[row-1][find_index(letters,column,SIZE)] == '.')
                {
                    exit_second = false;
                }
                else
                {
                    cout << "->>>>Please make a valid move !!!" << endl;
                }
            }
            if (count%2==0)
            {
                board[row-1][find_index(letters,column,SIZE)]='x';
            }
            else
            {
                board[row-1][find_index(letters,column,SIZE)]='o';
            }
            count++; 
        }
    }
}
/*This function provides the user to play the game with computer*/
void play_with_computer(char board[12][12],int nums[12],char letters[12],int SIZE)
{
    bool exit_first=true,exit_second=true;
    int row;
    char column;
    int counter=0;
    int move_up[2][2]={{-1,0},{-1,1}};
    int move_down[2][2]={{1,-1},{1,0}};
    int left_rigt[2][2]={{0,-1},{0,1}};
    int move_list[72][2];
    
    while (exit_first!=false)
    {
        if (is_win(board,SIZE,'x','o'))
        {
            cout << "\033[2J\033[1;1H";
            print_board(board,nums,letters,SIZE);
            cout << "Player 1 Wins !!" << endl;
            exit_first=false;
        }
        else if (is_win(board,SIZE,'o','x'))
        {
            cout << "\033[2J\033[1;1H";
            print_board(board,nums,letters,SIZE);
            cout << "Computer Wins !!" << endl;
            cout << "You should improve your skills !!" << endl;
            exit_first=false;
        }
        else
        {
            exit_second=true;
            cout << "\033[2J\033[1;1H";
            print_board(board,nums,letters,SIZE);
            if (counter!=0)
            {
                cout << "Computer Move: " <<letters[move_list[counter-1][1]]<<" "<< move_list[counter-1][0]+1 << endl;
            }
            while (exit_second!=false)
            {
                cout << "Make your move: " ;
                cin >> column;
                cin >> row;
                if ((check_move_letter(letters,SIZE,column) && check_move_num(nums,SIZE,row)) && board[row-1][find_index(letters,column,SIZE)] == '.')
                {
                    exit_second = false;
                }
                else
                {
                    cout << "->>>>Please make a valid move !!!" << endl;
                }
            }
            board[row-1][find_index(letters,column,SIZE)]='x';
            computer_move(board,counter,SIZE,move_list,move_up,move_down,left_rigt);
            counter++;
        }
    }
}