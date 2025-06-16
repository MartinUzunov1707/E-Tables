#pragma once
class Formula
{
protected:
	char** args;
	int lengthOfArgs;
public:
	virtual double calculate() const = 0;
	virtual const char* evaluate() const = 0;
	virtual ~Formula() = default;
};

