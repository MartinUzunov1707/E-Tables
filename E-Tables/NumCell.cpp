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

const char* NumCell::toString() const
{
	char buffer[Utils::BUFFER_SIZE];
	if (floor(this->value) == this->value) {
		Utils::parseIntToString(this->value, buffer);
	}
	else {
		Utils::parseDoubleToString(this->value, buffer);
	}
	
	return buffer;
}

Cell* NumCell::clone()
{
	return new NumCell(this->xValue, this->yValue, this->value);
}

void NumCell::clear()
{
	this->value = 0.0;
}

