#pragma once
class Cell
{
protected:
	int xValue;
	char yValue;
public:
	virtual ~Cell() = default;
	virtual double evaluate() = 0;
};

