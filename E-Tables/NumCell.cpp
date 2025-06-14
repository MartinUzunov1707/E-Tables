#include "NumCell.h"
#include "Utils.h"

NumCell::NumCell(int x, char y, double value)
{
	this->xValue = x;
	this->yValue = y;
	setValue(value);
}

void NumCell::setValue(double value)
{
	this->value = value;
}

double NumCell::evaluate()
{
	return value;
}

const char* NumCell::print() const
{
	return Utils::parseIntToString(this->value);
}

Cell* NumCell::clone()
{
	return new NumCell(this->xValue, this->yValue, this->value);
}

