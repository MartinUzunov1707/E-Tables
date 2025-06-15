#pragma once
class Cell
{
protected:
	int xValue;
	char yValue;
public:
	virtual ~Cell() = default;
	virtual double evaluate() = 0;
	virtual const char* toString() const = 0;
	virtual Cell* clone() = 0;
};

