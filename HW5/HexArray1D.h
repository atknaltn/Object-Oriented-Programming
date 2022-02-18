#if !defined(HEXARRAY1D_H_)
#define HEXARRAY1D_H_
/*
    THIS CLASS REPRESENTS HEXCELLS WITH STANDART 1D C ARRAY AND INCLUDES COMPATIBLE VIRTUAL FUNCTIONS
    WITH 1D C ARRAYS. IT ALSO INCLUDES BIG THREE
*/
#include"AbstractHex.h"
namespace AtakanHex
{
    class HexArray1D : public AbstractHex
    {
    public:
        HexArray1D();
        HexArray1D(int width,int height);
        HexArray1D(const HexArray1D &otherGame); //Copy Constructor
        HexArray1D& operator=(const HexArray1D &otherGame); //Assigment operator overloading
        virtual ~HexArray1D();//Destructor
        virtual Cell &operator()(int x,int y) override;
        virtual Cell operator()(int x,int y) const override;
        virtual void reset() override;
        virtual void createBoard() override;
    private:
        Cell *hexCell;
    };
} // namespace AtakanHex
#endif // HEXARRAY1D_H_
