#pragma once
#include "Config.h"
#include "Cell.h"


class Table
{
private:
	Cell*** table;
	Config cfg;
	unsigned int currentMaxCol;
	unsigned int currentMaxRow;
public:
	Table(MyString configFileName, MyString fileName);
	Table(MyString configFileName);
	void readTableFromFile(MyString fileName);
	void writeTableToFile(MyString fileName) const;
	friend void assignValuesFromRow(const char* row, int rowIndex, Table& table);
	~Table();
};

