#include"HexAdapter.h"
using namespace AtakanHex;
template<template<class...>class T>
HexAdapter<T>::HexAdapter() : AbstractHex()
{
    createBoard();
}
template<template<class...>class T>
HexAdapter<T>::HexAdapter(int width, int height): AbstractHex(width,height)
{
    createBoard();
}
template<template<class...>class T>
void HexAdapter<T>::createBoard()
{
    int i,j;
    hexCell.resize(getHeight());
    for (i = 0; i < getHeight(); i++)
    {
        hexCell[i].resize(getWidth());
    }
    for (i = 0; i < getHeight(); i++)
    {
        for (j = 0; j < getWidth(); j++)
        {
            hexCell[i][j]=Cell(i,j);
        }
    }
}
template<template<class...>class T>
Cell& HexAdapter<T>::operator()(int x,int y) 
{
    if ((x<0 || x>getWidth()) && (y<0 || y>getHeight()))
    {
        throw CellException();
    }
    return hexCell[x][y];
}
template<template<class...>class T>
Cell HexAdapter<T>::operator()(int x,int y) const
{
    if ((x<0 || x>getWidth()) && (y<0 || y>getHeight()))
    {
        throw CellException();
    }
    return hexCell[x][y];
}
template<template<class...>class T>
void HexAdapter<T>::reset()
{
    setcompCounter(0);
    setCounter(0);
    setMarkedCells(0);
    hexCell.clear();
    setLastX(-1);
    setLastY(-1);
    createBoard();
}
