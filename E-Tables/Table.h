#pragma once
#include "Cell.h"
#include "Config.h"
#include "MyString.h";

class Table
{
private:
	Cell** table;
	Config cfg;
public:
	void readTableFromFile(MyString fileName);
	void writeTableToFile(MyString fileName) const;
	~Table();
};

