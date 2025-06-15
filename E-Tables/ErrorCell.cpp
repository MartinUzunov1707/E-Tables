#include "ErrorCell.h"

ErrorCell::ErrorCell(int x, char y)
{
	this->xValue = x;
	this->yValue = y;
}

double ErrorCell::evaluate()
{
	return 0.0;
}

const char* ErrorCell::toString() const
{
	return "#VALUE!";
}

Cell* ErrorCell::clone()
{
	return new ErrorCell(this->xValue, this->yValue);
}

void ErrorCell::clear()
{
	//there is no value in errorcell, so no value to clear
}
