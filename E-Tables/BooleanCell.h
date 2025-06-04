#pragma once
#include "Cell.h"

class BooleanCell :
    public Cell
{
private:
    bool value;
public:
    BooleanCell(char x, int y, bool value);
    void setValue(bool value);
    double evaluate() override;
};

