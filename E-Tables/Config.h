#pragma once
#include <fstream>
enum Allignement {
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
	Allignement initialAllignement = Allignement::INIT;
	bool clearConsoleAfterCommand = false;
public:
	Config() = delete;
	Config(char* fileName);
	void readConfigFromFileName(char* fileName);
	void readConfigFromFile(std::ifstream& ifs);
};

