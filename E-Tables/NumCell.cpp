#include "NumCell.h"

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

