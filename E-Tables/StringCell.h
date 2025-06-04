#pragma once
#include "Cell.h"
#include "MyString.h"

class StringCell :
    public Cell
{

private:
   MyString value;
public:
    StringCell(int x, char y, MyString value);
    void setValue(MyString value);
    double evaluate() override;
};

