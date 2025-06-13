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

const char* NullCell::print() const
{
	return "";
}
