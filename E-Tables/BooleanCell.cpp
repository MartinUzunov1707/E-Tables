#include "BooleanCell.h"

BooleanCell::BooleanCell(int x, char y, bool value)
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

const char* BooleanCell::toString() const
{
	if (this->value) {
		return "t";
	}
	else {
		return "f";
	}
}

Cell* BooleanCell::clone()
{
	return new BooleanCell(this->xValue, this->yValue, this->value);
}

void BooleanCell::clear()
{
	this->value = false;
}


