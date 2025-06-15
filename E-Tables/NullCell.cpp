#include "NullCell.h"

NullCell::NullCell(int x, char y)
{
	this->xValue = x;
	this->yValue = y;
}


double NullCell::evaluate()
{
	return -1;
}

const char* NullCell::toString() const
{
	return "";
}

Cell* NullCell::clone()
{
	return new NullCell(this->xValue, this->yValue);
}

void NullCell::clear()
{
	//NullCell does not hold data, so no action needed
}
