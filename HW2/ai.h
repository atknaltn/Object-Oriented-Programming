#ifndef AI_H_
#define AI_H_

/*This header file contains basic artificial intelligence functions*/

void computer_move(char board[12][12],int counter,int SIZE,int move_list[72][2],int move_up[2][2],int move_down[2][2],int left_rigt[2][2]);
bool other_moves(char board[12][12],int last_coord[2],int current_coord[2],int moves[2][2],int SIZE);
void first_move(char board[12][12],int SIZE,int coord[2]);
void random_move(char board[12][12],int SIZE,int move_list[72][2],int counter);


#endif
