#ifndef FILE_IO_H_
#define FILE_IO_H_

enum class CellContent
{
    dot,x,X,o,O
};

bool saveBoard(std::string fileName,char board[12][12],const int &SIZE,int &playerReturn,const int &gameMode,int &counter);
bool saveBoard(std::string fileName,char board[12][12],const int &SIZE,int &playerReturn,const int &gameMode,int &counter,int moveList[72][2]);
bool loadBoard(std::string fileName,char board[12][12],int &counter,int &gameMode,int &size,int nums[12],char letters[12],int moveList[72][2]);

#endif
