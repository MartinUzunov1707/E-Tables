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

const char* StringCell::print() const
{
	return this->value.getString();
}

Cell* StringCell::clone()
{
	return new StringCell(this->xValue, this->yValue, this->value);
}
