#include"HexVector.h"
using namespace AtakanHex;
HexVector::HexVector() : AbstractHex()
{
    createBoard();
}
HexVector::HexVector(int width,int height) : AbstractHex(width,height)
{
    createBoard();
}
void HexVector::createBoard()
{
    int i,j;
    for (i = 0; i < getWidth(); i++)
    {
        hexCell.push_back(vector<Cell>());
        for (j = 0; j < getHeight(); j++)
        {
            hexCell[i].push_back(Cell(i,j));
        }
    }
}
void HexVector::reset()
{
    setcompCounter(0);
    setCounter(0);
    setMarkedCells(0);
    hexCell.clear();
    setLastX(-1);
    setLastY(-1);
    createBoard();
}
Cell HexVector::operator()(int x,int y)const
{
    if ((x<0 || x>getWidth()) && (y<0 || y>getHeight()))
    {
        throw CellException();
    }
    return hexCell[x][y]; //Throws an exception
}
Cell &HexVector::operator()(int x,int y)
{
    if ((x<0 || x>getWidth()) && (y<0 || y>getHeight()))
    {
        throw CellException();
    }
    return hexCell[x][y]; //Throws an exception
}
