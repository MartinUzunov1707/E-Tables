#pragma once
#include "Cell.h"
#include "Engine.h"
class ReferenceCell : public Cell
{
private:
    int targetX;
    int targetY;
public:
    ReferenceCell(int x, char y,int targetX, int targetY);
    void setValue(int targetX, int targetY);
    double evaluate() override;
    const char* toString() const override;
    virtual Cell* clone() override;
    virtual void clear() override;
};

