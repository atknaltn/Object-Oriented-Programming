#ifndef GAME_CONTROL_UNIT_H_
#define GAME_CONTROL_UNIT_H_

/*This header file contains the functions which control many different situations.*/
bool check_move_letter(char letters[12],int SIZE,char move);
bool check_move_num(int nums[12],int SIZE,int move);
bool check_computer_move(char board[12][12],int coord[2],int SIZE);
int find_index(char letters[12],char move,int SIZE);
bool win_control(char board[12][12],int coordinate[2],int SIZE,int move_row[6],int move_col[6],int count,char usr_ch);
bool check_suitability(char board[12][12],int coordinate[2],int SIZE,char usr_ch);
bool is_win(char board[12][12],int SIZE,char safe_ch,char forb_ch);

#endif
