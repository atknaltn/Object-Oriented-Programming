#ifndef INTERFACE_H_
#define INTERFACE_H_

/*This header file includes functions that make the game playable*/
void start_game();
void player_input(char board[12][12],int nums[12],char letters[12]);
void play_with_user(char board[12][12],int nums[12],char letters[12],int SIZE);
void play_with_computer(char board[12][12],int nums[12],char letters[12],int SIZE);

#endif