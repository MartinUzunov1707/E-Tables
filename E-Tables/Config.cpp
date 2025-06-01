#include "Config.h"

namespace Constants {
	const int BUFFER_SIZE = 1024;
}
struct ConfigProperties {
	bool initialTableRowsFlag = 0;
	bool initialTableColsFlag = 0;
	bool maxTableRowsFlag = 0;
	bool maxTableColsFlag = 0;
	bool autoFitFlag = 0;
	bool visibleCellSymbolsFlag = 0;
	bool initialAllignementFlag = 0;
	bool clearConsoleAfterCommandFlag = 0;

	bool validateConfigProperties() {
		return initialTableRowsFlag && initialTableColsFlag
			&& maxTableRowsFlag && maxTableColsFlag
			&& autoFitFlag && visibleCellSymbolsFlag
			&& initialAllignementFlag && clearConsoleAfterCommandFlag;
	}

	
};
Config::Config(char* fileName)
{
	readConfigFromFileName(fileName);
}

void Config::readConfigFromFileName(char* fileName)
{
	std::ifstream ifs(fileName,std::ifstream::in);
	readConfigFromFile(ifs);
}

void Config::readConfigFromFile(std::ifstream& ifs)
{
	if (ifs.is_open()) {
		while (ifs.peek() != EOF) {
			char propertyName[Constants::BUFFER_SIZE];
			char propertyValue[Constants::BUFFER_SIZE];
			ifs.getline(propertyName, Constants::BUFFER_SIZE, ':');
			ifs.getline(propertyValue, Constants::BUFFER_SIZE);
			if(propertyName == "initialTableRows"){
				
			}
		}
	}
}

