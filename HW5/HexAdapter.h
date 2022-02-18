#if !defined(HEXADAPTER_H_)
#define HEXADAPTER_H_
/*
    THIS CLASS REPRESENTS HEXCELLS WITH TEMPLATED CONTAINERS AND INCLUDES COMPATIBLE VIRTUAL FUNCTIONS
    WITH ALL STL CLASSES WITH RANDOM ACCESS ITERATORS. 
*/
#include"AbstractHex.h"
namespace AtakanHex
{
    template<template<class...>class T>
    class HexAdapter: public AbstractHex
    {
    public:
        HexAdapter();
        HexAdapter(int width, int height);
        virtual Cell &operator()(int x,int y) override;
        virtual Cell operator()(int x,int y) const override;
        virtual void reset() override;
        virtual void createBoard() override;
    private:
        T<T<Cell>> hexCell;
    };  
} // namespace AtakanHex
#endif // HEXADAPTER_H_
