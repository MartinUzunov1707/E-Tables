#include "Table.h"
#include "BooleanCell.h"
#include "StringCell.h"
#include "NumCell.h"
#include "NullCell.h"
#include <iostream>


void assignValuesFromRow(const char* row, int rowIndex,Cell*** table) {
	int currentCol = 0;
	int valueCursor = 0;
	char value[Utils::BUFFER_SIZE];
	int i = 0;
	Cell* currentCell = nullptr;
	while (row[i] != '\0') {
		if (row[i] == 't' || row[i] == 'f') {		
			currentCell = new BooleanCell(currentCol, rowIndex + 'A', (row[i] == 't'));
		}
		else if (row[i] == '"') {
			value[valueCursor++] = row[i++];
			while (row[i] != '"') {
				value[valueCursor] = row[i];
				valueCursor++;
				i++;
			}
			value[valueCursor++] = row[i];
			value[valueCursor] = '\0';
			currentCell = new StringCell(currentCol, rowIndex + 'A',value);
			valueCursor = 0;
		}
		else if (row[i] >= '0' && row[i] <= '9') {
			value[valueCursor++] = row[i++];
			while (row[i] != '|') {
				value[valueCursor] = row[i];
				valueCursor++;
				i++;
			}
			value[valueCursor] = '\0';
			int res = 0;
			if (!Utils::tryConvertToInt(value, res)) {
				throw std::invalid_argument("There has been an error, please check the save file for the current table!");
			}
			currentCell = new NumCell(currentCol, rowIndex + 'A', res);  
			valueCursor = 0;
			i--;
		}
		else if (row[i] == '|') {
			if (currentCell == nullptr) {
				table[rowIndex][currentCol] = new NullCell(currentCol, rowIndex + 'A');
			}
			else{
				table[rowIndex][currentCol] = currentCell;
			}
			currentCell = nullptr;
			currentCol++;
		}
		i++;
	}
}


void Table::free()
{
	for (int i = 0; i < this->currentRow;i++) {
		delete[] table[i];
	}
	delete[] table;
}

void Table::copyDynamicMemory(const Table& other)
{
	this->currentCol = other.currentCol;
	this->currentRow = other.currentRow;
	this->cfg = other.cfg;

	table = new Cell * *[currentRow] {0};
	for (int a = 0; a < currentRow;a++) {
		table[a] = new Cell * [currentCol];
	}

	for (int i = 0; i < this->currentRow;i++) {
		for (int a = 0; a < this->currentCol;a++) {
			this->table[i][a] = other.table[i][a]->clone();
		}
	}
	
}

Table::Table()
{

}

Table::Table(MyString configFileName, MyString fileName) : cfg(configFileName.getString())
{
	readTableFromFile(fileName);
}

Table::Table(MyString configFileName) : cfg(configFileName.getString())
{
	this->currentCol = cfg.getInitialCols();
	this->currentRow = cfg.getInitialRows();
	table = new Cell * *[cfg.getMaxRows()] {0};
	for (int a = 0; a < cfg.getMaxRows();a++) {
		table[a] = new Cell * [cfg.getMaxCols()];
	}
}

void Table::readTableFromFile(MyString fileName)
{
	std::ifstream ifs(fileName.getString(), std::ifstream::in);
	char buffer[Utils::BUFFER_SIZE];
	char maxRow[Utils::BUFFER_SIZE];
	char maxCol[Utils::BUFFER_SIZE];
	
	ifs.getline(buffer,Utils::BUFFER_SIZE);
	Utils::splitValuesByDelimiter(buffer, maxRow, maxCol, ';');
	int maxRowInt, maxColInt;
	if (!Utils::tryConvertToInt(maxRow, maxRowInt) || !Utils::tryConvertToInt(maxCol, maxColInt)) {
		throw std::invalid_argument("There has been an error, please check the save file for the current table!");
	}
	this->currentCol = maxColInt;
	this->currentRow = maxRowInt;
	/*this->table = new Cell*[this->currentRow];*/

	table = new Cell * *[currentRow] {0};
	for (int a = 0; a < currentRow;a++) {
		table[a] = new Cell * [currentCol];
	}

	for (int i = 0; i < this->currentRow;i++) {
		ifs.getline(buffer, Utils::BUFFER_SIZE);
		assignValuesFromRow(buffer,i, this->table);
	}
}

void Table::writeTableToFile(MyString fileName) const
{
	std::ofstream ofs(fileName.getString()); 
	ofs << this->currentRow << ';' << this->currentCol << std::endl;
	for (int i = 0; i < this->currentRow; i++) {
		for (int a = 0; a < this->currentCol; a++) {
			ofs << this->table[i][a]->toString() << '|';
		}
		ofs << std::endl;
	}
}

int Table::getCurrentCol() const
{
	return this->currentCol;
}

int Table::getCurrentRow() const
{
	return this->currentRow;
}

void Table::setCurrentCol(int val)
{
	if (val < this->cfg.getInitialCols() || val > this->cfg.getMaxCols()) {
		throw std::invalid_argument("Cannot set columns out of bounds!");
	}
	this->currentCol = val;
}

void Table::setCurrentRow(int val)
{
	if (val < this->cfg.getInitialRows() || val > this->cfg.getMaxRows()) {
		throw std::invalid_argument("Cannot set rows out of bounds!");
	}
	this->currentRow = val;
}

int Table::getMaxCellLength()
{
	int res = INT_MIN;
	for (int i = 0; i < this->currentRow; i++) {
		for (int a = 0; a < this->currentCol; a++) {
			int currentLength = Utils::getStringLength(this->table[i][a]->toString());
			if (res < currentLength) {
				res = currentLength;
			}
		}
	}
	return res;
}

Cell& Table::getByIndex(int x, int y)
{
	return *(this->table[y][x]);
}

Cell* Table::getPointerByIndex(int x, int y)
{
	return this->table[y][x];
}

void Table::setPointerByIndex(int x, int y, Cell* value)
{
	this->table[y][x] = value;
}
void Table::setPointerCloneByIndex(int x, int y, Cell* value)
{
	this->table[y][x] = value->clone();
}

Table& Table::operator=(const Table& other)
{
	if (this != &other) {
		free();
		copyDynamicMemory(other);
	}
	return *this;
}

Config Table::getConfig() const
{
	return this->cfg;
}

Table::~Table()
{
	free();
}

