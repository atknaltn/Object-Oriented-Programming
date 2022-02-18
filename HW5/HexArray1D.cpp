#include"HexArray1D.h"
using namespace AtakanHex;
HexArray1D::HexArray1D(): AbstractHex()
{
    createBoard();
}
HexArray1D::HexArray1D(int width,int height):AbstractHex(width,height) 
{
    createBoard();
}
HexArray1D::~HexArray1D()
{
    delete[] hexCell;
}
HexArray1D::HexArray1D(const HexArray1D &otherGame)
{
    setGameName(otherGame.getGameName());
    setFName(otherGame.getFName());
    setGameMode(otherGame.getGameMode());
    setWidth(otherGame.getWidth());
    setHeight(otherGame.getHeight());
    setCounter(otherGame.getCounter());
    setcompCounter(otherGame.getcompCounter());
    setCompX(otherGame.getCompX());
    setCompY(otherGame.getCompY());
    setEnd(otherGame.isEnd());
    setMarkedCells(otherGame.numberOfMoves());
    setLastX(otherGame.getLastX());
    setLastY(otherGame.getLastY());
    hexCell=(Cell*)calloc(getWidth()*getHeight(),sizeof(Cell));
    int i,j;
    for (i = 0; i < getHeight(); i++)
    {
        for (j = 0; j <getWidth(); j++)
        {
            hexCell[i*getWidth()+j]=otherGame.hexCell[i*getWidth()+j];
        } 
    } 
}
HexArray1D& HexArray1D::operator=(const HexArray1D &otherGame)
{
    int i,j;
    if (getHeight()!=otherGame.getHeight())
    {
        delete[] hexCell;
        hexCell=(Cell*)calloc((otherGame.getHeight())*(otherGame.getWidth()),sizeof(Cell));
    }
    setGameName(otherGame.getGameName());
    setFName(otherGame.getFName());
    setGameMode(otherGame.getGameMode());
    setWidth(otherGame.getWidth());
    setHeight(otherGame.getHeight());
    setCounter(otherGame.getCounter());
    setcompCounter(otherGame.getcompCounter());
    setCompX(otherGame.getCompX());
    setCompY(otherGame.getCompY());
    setEnd(otherGame.isEnd());
    setMarkedCells(otherGame.numberOfMoves());
    setLastX(otherGame.getLastX());
    setLastY(otherGame.getLastY());
    for (i = 0; i < getHeight(); i++)
    {
         hexCell[i*getWidth()+j]=otherGame.hexCell[i*getWidth()+j];
    }
    return *this;
}
void HexArray1D::createBoard()
{
    int i,j;
    hexCell=(Cell*)calloc(getWidth()*getHeight(),sizeof(Cell));
    for (i = 0; i < getWidth(); i++)
    {
        for (j = 0; j < getHeight(); j++)
        {
            hexCell[i*getWidth()+j]=Cell(i,j);
        }
    }
}
Cell HexArray1D::operator()(int x,int y)const
{
    if ((x<0 || x>getWidth()) && (y<0 || y>getHeight()))
    {
        throw CellException();
    }
    return hexCell[x*getWidth()+y]; //Throws an exception
}
Cell &HexArray1D::operator()(int x,int y)
{
    if ((x<0 || x>getWidth()) && (y<0 || y>getHeight()))
    {
        throw CellException();
    }
    return hexCell[x*getWidth()+y]; //Throws an exception
}
void HexArray1D::reset()
{
    setcompCounter(0);
    setCounter(0);
    setMarkedCells(0);
    delete[] hexCell;
    setLastX(-1);
    setLastY(-1);
    createBoard();
}
