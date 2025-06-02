#pragma once
#include <fstream>

struct ConfigProperties {
	bool initialTableRowsFlag = 0;
	bool initialTableColsFlag = 0;
	bool maxTableRowsFlag = 0;
	bool maxTableColsFlag = 0;
	bool autoFitFlag = 0;
	bool visibleCellSymbolsFlag = 0;
	bool initialAllignmentFlag = 0;
	bool clearConsoleAfterCommandFlag = 0;

	bool validateConfigProperties() {
		return initialTableRowsFlag && initialTableColsFlag
			&& maxTableRowsFlag && maxTableColsFlag
			&& autoFitFlag && visibleCellSymbolsFlag
			&& initialAllignmentFlag && clearConsoleAfterCommandFlag;
	}
};

enum Allignment {
	INIT,
	LEFT,
	CENTER,
	RIGHT
};

class Config
{
private:
	unsigned int initialTableRows = 0;
	unsigned int initialTableCols = 0;
	unsigned int maxTableRows = 0;
	unsigned int maxTableCols = 0;
	bool autoFit = false;
	unsigned int visibleCellSymbols = 0;
	Allignment initialAllignment = Allignment::INIT;
	bool clearConsoleAfterCommand = false;
	void assignValueToProperty(char* propertyName, char* propertyValue, ConfigProperties& cfp);
public:
	Config() = delete;
	Config(const char* fileName);
	void readConfigFromFileName(const char* fileName);
	void readConfigFromFile(std::ifstream& ifs);
	
};

