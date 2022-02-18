#include<exception>
#include<iostream>
#include<stdexcept>
/*
    THIS CLASS INCLUDES SOME SPECIFIC EXCEPTIONS
*/
using namespace std;
namespace AtakanHex
{
    class LastMoveException : public runtime_error
    {
    public:
        LastMoveException():runtime_error("There is no move on the board"){} 
    };
    class SizeException:public runtime_error
    {
    public:
        SizeException():runtime_error("Size should be larger than 5"){}
    };
    class SquareException:public runtime_error
    {
    public:
        SquareException():runtime_error("Board should be square"){}
    };
    class CellException:public runtime_error
    {
    public:
        CellException():runtime_error("Corresponding cell does not exist"){};
    };
    class FileOpenException:public runtime_error
    {
    public:
        FileOpenException():runtime_error("File cannot be opened"){}
    };
    class FileCreateException:public runtime_error
    {
    public:
        FileCreateException():runtime_error("File cannot be created"){}
    };
} // namespace AtakanHex


