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
	virtual void clear() = 0;
	int getXValue() const { return xValue; }
	char getYValue() const { return yValue; }
};

