#pragma once
class Formula
{
protected:
	char** args;
	int lengthOfArgs;
public:
	virtual double calculate() const = 0;
	virtual char* evaluate() const = 0;
};

