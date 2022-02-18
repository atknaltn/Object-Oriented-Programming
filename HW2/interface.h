#ifndef INTERFACE_H_
#define INTERFACE_H_

/*This header file includes functions that make the game playable. Some Functions uses default arguments*/
void start_game();
void player_input(char board[12][12],int nums[12],char letters[12]);
bool play_with_user(char board[12][12],int move_list[72][2],int nums[12],char letters[12],int SIZE,const int &choice,int counter=0);
bool play_with_computer(char board[12][12],int move_list[72][2],int nums[12],char letters[12],int SIZE,const int &choice,int counter=0);

#endif
