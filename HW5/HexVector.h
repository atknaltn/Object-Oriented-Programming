#if !defined(HEXVECTOR_H_)
#define HEXVECTOR_H_
#include"AbstractHex.h"
#include<vector>
/*
    THIS CLASS REPRESENTS HEXCELLS WITH STL VECTOR AND INCLUDES COMPATIBLE VIRTUAL FUNCTIONS
    WITH VECTOR CELLS
*/
namespace AtakanHex
{
    class HexVector : public AbstractHex
    {
    public:
        HexVector();
        HexVector(int width,int height);
        virtual Cell &operator()(int x,int y) override;
        virtual Cell operator()(int x,int y) const override;
        virtual void reset() override;
        virtual void createBoard() override;
    private:
        vector<vector<Cell>> hexCell;
    };
} // namespace AtakanHex

#endif // HEXVECTOR_H_
