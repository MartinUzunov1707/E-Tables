#pragma once
class Cell
{
protected:
	char xValue;
	int yValue;
public:
	virtual ~Cell() = default;
	virtual double evaluate() = 0;
};

