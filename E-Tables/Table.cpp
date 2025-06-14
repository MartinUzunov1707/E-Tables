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
			currentCell = new BooleanCell(rowIndex, currentCol + 'A', (row[i] == 't'));
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
			currentCell = new StringCell(rowIndex, currentCol + 'A',value);
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
			currentCell = new NumCell(rowIndex, currentCol + 'A', res);  
			valueCursor = 0;
			i--;
		}
		else if (row[i] == '|') {
			if (currentCell == nullptr) {
				table[rowIndex][currentCol] = new NullCell(rowIndex, currentCol + 'A');
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


Table::Table(MyString configFileName, MyString fileName) : cfg(configFileName.getString())
{
	readTableFromFile(fileName);
}

Table::Table(MyString configFileName) : cfg(configFileName.getString())
{
	this->currentMaxCol = cfg.getInitialCols();
	this->currentMaxRow = cfg.getInitialRows();
	table = new Cell * *[currentMaxRow] {0};
	for (int a = 0; a < currentMaxRow;a++) {
		table[a] = new Cell * [currentMaxCol];
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
	this->currentMaxCol = maxColInt;
	this->currentMaxRow = maxRowInt;
	/*this->table = new Cell*[this->currentMaxRow];*/

	table = new Cell * *[currentMaxRow] {0};
	for (int a = 0; a < currentMaxRow;a++) {
		table[a] = new Cell * [currentMaxCol];
	}

	for (int i = 0; i < this->currentMaxRow;i++) {
		ifs.getline(buffer, Utils::BUFFER_SIZE);
		assignValuesFromRow(buffer,i, this->table);
	}
}

void Table::writeTableToFile(MyString fileName) const
{
	std::ofstream ofs(fileName.getString()); 
	ofs << this->currentMaxRow << ';' << this->currentMaxCol << std::endl;
	for (int i = 0; i < this->currentMaxRow; i++) {
		for (int a = 0; a < this->currentMaxCol; a++) {
			ofs << this->table[i][a]->print() << '|';
		}
		ofs << std::endl;
	}
}

Table::~Table()
{
	for (int i = 0; i < cfg.getMaxRows();i++) {
		delete[] table[i];
	}
	delete[] table;
}

