#include "StringCell.h"

StringCell::StringCell(int x, char y, MyString value)
{
	this->xValue = x;
	this->yValue = y;
	setValue(value);
}

void StringCell::setValue(MyString value)
{
	this->value = value;
}

double StringCell::evaluate()
{
	return 0.0;
}
