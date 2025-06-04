#include "BooleanCell.h"

BooleanCell::BooleanCell(char x, int y, bool value)
{
	this->xValue = x;
	this->yValue = y;
	setValue(value);
}

void BooleanCell::setValue(bool value)
{
	this->value = value;
}

double BooleanCell::evaluate()
{
	return value;
}

