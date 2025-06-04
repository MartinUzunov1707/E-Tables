#pragma once
#include "Cell.h"

class BooleanCell :
    public Cell
{
private:
    bool value;
public:
    BooleanCell(int x, char y, bool value);
    void setValue(bool value);
    double evaluate() override;
};

