#pragma once
#include "Config.h"
#include "Cell.h"


class Table
{
private:
	Cell*** table;
	Config cfg;
	unsigned int currentCol;
	unsigned int currentRow;
	void free();
	void copyDynamicMemory(const Table& other);
public:
	Table();
	Table(MyString configFileName, MyString fileName);
	Table(MyString configFileName);
	void readTableFromFile(MyString fileName);
	void writeTableToFile(MyString fileName) const;
	Config getConfig() const;
	int getCurrentCol() const;
	int getCurrentRow() const;
	void setCurrentCol(int val);
	void setCurrentRow(int val);
	int getMaxCellLength();
	Cell& getByIndex(int x, int y);
	Cell* getPointerByIndex(int x, int y);
	void setPointerCloneByIndex(int x, int y, Cell* value);
	void setPointerByIndex(int x, int y, Cell* value);
	Table& operator=(const Table& other);
	~Table();
};

