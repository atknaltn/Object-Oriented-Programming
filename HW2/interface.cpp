#include<iostream>
#include<string>
#include"ai.h"
#include<cstdlib>
#include<ctime>
#include"game_control_unit.h"
#include"game_board.h"
#include"interface.h"
#include"file_io.h"

using namespace std;
/*This function starts or finishes the game.*/
void start_game()
{
    bool exit_first=true;
    int choice;
    char board[12][12];
    int nums[]={1,2,3,4,5,6,7,8,9,10,11,12};
    char letters[]={'a','b','c','d','e','f','g','h','j','k','l','m'};
    while (exit_first)
    {
        player_input(board,nums,letters);
        cout << "Do you want to play again ? (yes:1/no:0)" << endl;
        cin >> choice;
        if (choice==0)
        {
            exit_first=false;
        }
    }
}
/*This function handles player inputs*/
void player_input(char board[12][12],int nums[12],char letters[12])
{
    cout << "-------------------- WELCOME TO HEX GAME ------------------------" << endl;
    int SIZE;
    bool exit_first=true;
    decltype(exit_first) exit_second=true;
    decltype(SIZE) choice;
    int move_list[72][2];
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
                    play_with_computer(board,move_list,nums,letters,SIZE,choice);
                }
                else if (choice==2)
                {
                    exit_second=false;
                    play_with_user(board,move_list,nums,letters,SIZE,choice);
                }
                else
                {
                    cout << "->>>>Please make a valid choice !!!" << endl;
                }
            }
        }
    }
}
/*
    This function provides the user to play the game with another user and if the user want to save the current game
it saves the whole game data.
*/
bool play_with_user(char board[12][12],int move_list[72][2],int nums[12],char letters[12],int SIZE,const int &choice,int counter)
{
    bool exit_first=true,exit_second=true;
    int row,gameMode;
    string wholeLine,command,fileName;
    char column;
    bool flag;
    while (exit_first!=false)
    {
        if (is_win(board,SIZE,'x','o'))
        {
            cout << "\033[2J\033[1;1H";//Clears the screen.
            print_board(board,nums,letters,SIZE);
            cout << "Player 1 Wins !!" << endl;
            return true;
        }
        else if (is_win(board,SIZE,'o','x'))
        {
            cout << "\033[2J\033[1;1H";
            print_board(board,nums,letters,SIZE);
            cout << "Player 2 Wins !!" << endl;
            return true;
        }
        else
        {
            exit_second=true;
            cout << "\033[2J\033[1;1H";
            print_board(board,nums,letters,SIZE);
            while (exit_second!=false)
            {
                flag=true;
                if (counter % 2 == 0)
                {
                    cout << "(Player 1) Make your move: " ;
                }
                else
                {
                    cout << "(Player 2) Make your move: " ;
                }
                cin >> column;
                if (column=='L')
                {
                    getline(cin,wholeLine);
                    wholeLine=column+wholeLine;
                    auto lPos = wholeLine.find("LOAD");
                    if (lPos != string::npos)
                    {
                        command = wholeLine.substr(lPos,4);
                        fileName = wholeLine.substr(lPos+5);
                        if (!loadBoard(fileName,board,counter,gameMode,SIZE,nums,letters,move_list))
                        {
                            cerr << "The file cannot be opened !!!" << endl;
                        }
                        counter --;
                        return 0;   
                    }
                    else
                    {
                        lPos=wholeLine.find("L");
                        string temp;
                        temp=wholeLine.substr(lPos+1);
                        /*
                            Since the stoi function when gets the invalid input,it ends the program; i have to use 
                        try catch structure to prevent the program to end. 
                        */
                        try
                        {
                            row=stoi(temp);
                        }
                        catch(const std::exception& e)
                        {
                            cerr << "Wrong Command !!!";
                        }  
                    }
                }
                else if (column=='S')
                {
                    getline(cin,wholeLine);
                    wholeLine=column+wholeLine;
                    auto lPos = wholeLine.find("SAVE");
                    if (lPos != string::npos)
                    {
                        command = wholeLine.substr(lPos,4);
                        fileName = wholeLine.substr(lPos+5);
                        if(!saveBoard(fileName,board,SIZE,counter,choice,counter))
                        {
                            cerr << "The file cannot be created." << endl;
                        }
                        counter--;
                        flag=false;
                        break;
                    }
                }
                else
                {
                    cin >> row;
                }
                if ((check_move_letter(letters,SIZE,column) && check_move_num(nums,SIZE,row)) && board[row-1][find_index(letters,column,SIZE)] == '.' && flag!=false)
                {
                    exit_second = false;
                }
                else if(flag!=false)
                {
                    cout << "->>>>Please make a valid move !!!" << endl;
                }
            }
            if (counter%2==0 && flag!=false)
            {
                board[row-1][find_index(letters,column,SIZE)]='x';
            }
            else if(counter%2!=0 && flag!=false)
            {
                board[row-1][find_index(letters,column,SIZE)]='o';
            }
            counter++; 
        }
    }
    return false;
}
/*This function provides the user to play the game with computer and if the user want to save the current game
it saves the whole game data*/
bool play_with_computer(char board[12][12],int move_list[72][2],int nums[12],char letters[12],int SIZE,const int &choice,int counter)
{
    bool exit_first=true,exit_second=true;
    int row;
    decltype(row) gameMode;
    char column;
    string wholeLine,command,fileName;
    int move_up[2][2]={{-1,0},{-1,1}};
    int move_down[2][2]={{1,-1},{1,0}};
    int left_rigt[2][2]={{0,-1},{0,1}};
    bool flag;
    while (exit_first!=false)
    {
        flag=true;
        if (is_win(board,SIZE,'x','o'))
        {
            cout << "\033[2J\033[1;1H";
            print_board(board,nums,letters,SIZE);
            cout << "Player 1 Wins !!" << endl;
            return true;
        }
        else if (is_win(board,SIZE,'o','x'))
        {
            cout << "\033[2J\033[1;1H";
            print_board(board,nums,letters,SIZE);
            cout << "Computer Wins !!" << endl;
            cout << "You should improve your skills !!" << endl;
            return true;
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
                cout << "Make your move: ";
                cin >> column;
                if (column=='L')
                {
                    getline(cin, wholeLine);
                    wholeLine = column + wholeLine;
                    auto lPos = wholeLine.find("LOAD");
                    if (lPos != string::npos)
                    {
                        flag=false;
                        command = wholeLine.substr(lPos,4);
                        fileName = wholeLine.substr(lPos+5);
                        auto flag2 = loadBoard(fileName,board,counter,gameMode,SIZE,nums,letters,move_list);
                        if(flag2==false)
                        {
                            cerr << "The file cannot be opened !!!" << endl;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        lPos=wholeLine.find("L");
                        string temp;
                        temp=wholeLine.substr(lPos+1);
                        /*
                            Since the stoi function when gets the invalid input,it ends the program; i have to use 
                        try catch structure to prevent the program to end. 
                        */
                        try
                        {
                            row=stoi(temp);
                        }
                        catch(const std::exception& e)
                        {
                            cerr << "Wrong Command !!!";
                        }
                    }
                }
                else if (column=='S')
                {
                    getline(cin, wholeLine);
                    wholeLine = column + wholeLine;
                    auto lPos = wholeLine.find("SAVE");
                    if (lPos != string::npos)
                    {
                        flag=false;
                        command = wholeLine.substr(lPos,4);
                        fileName = wholeLine.substr(lPos+5);
                        if(!saveBoard(fileName,board,SIZE,counter,choice,counter,move_list))
                        {
                            cerr << "The file cannot be created." << endl;
                        }
                        break;
                    }
                }
                else
                {
                    cin >> row;
                }
                if ((check_move_letter(letters,SIZE,column) && check_move_num(nums,SIZE,row)) && board[row-1][find_index(letters,column,SIZE)] == '.')
                {
                    exit_second = false;
                }
                else 
                {
                    cout << "->>>>Please make a valid move !!!" << endl;
                }
            }
            if (flag)
            {
                board[row-1][find_index(letters,column,SIZE)]='x';
                computer_move(board,counter,SIZE,move_list,move_up,move_down,left_rigt);
                counter++;
            }
        }
    }
    return false;
}
