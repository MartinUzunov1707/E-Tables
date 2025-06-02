#include "Config.h"
#include "MyString.h"

namespace Constants {
	const int BUFFER_SIZE = 1024;
	const int ZERO_ASCII = '0';
}
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

Allignment getAlignmentByString(char* value) {
	if (value == "left") {
		return Allignment::LEFT;
	}
	else if (value == "right") {
		return Allignment::RIGHT;
	}
	else if (value == "center") {
		return Allignment::CENTER;
	}
	else {
		return Allignment::INIT;
	}
}

Config::Config(char* fileName)
{
	readConfigFromFileName(fileName);
}

void Config::readConfigFromFileName(char* fileName)
{
	std::ifstream ifs(fileName,std::ifstream::in);
	readConfigFromFile(ifs);
}

void getPropertyNameFromLine(char* line, char* nameDestination, char* valueDestination) {
	int i = 0;
	int a = 0;
	while (line[i] != ':') {
		nameDestination[i] = line[i];
		i++;
	}
	nameDestination[i] = '\0';
	i++; // skips delimeter
	while (line[i] != '\0') {
		valueDestination[a] = line[i];
		i++;
		a++;
	}
	valueDestination[a] = '\0';
}

int convertToInt(char* value) {
	int result = 0;
	int length = 0;
	while (value[length] != '\0') {
		length++;
	}
	int reverseIndex = length - 1;
	for (int i = 0; i < length;i++) {
		result += (value[i] - '0') * pow(10, reverseIndex);
		reverseIndex--;
	}

	return result;
}

void Config::assignValueToProperty(char* propertyName, char* propertyValue)
{
	ConfigProperties cfp;
	if (propertyName == "initialTableRows") {
		this->initialTableRows = convertToInt(propertyValue);
		cfp.initialTableRowsFlag = true;
	}
	else if (propertyName == "initialTableCols") {
		this->initialTableCols = convertToInt(propertyValue);
		cfp.initialTableColsFlag = true;
	}
	else if (propertyName == "maxTableRows") {
		this->maxTableRows = convertToInt(propertyValue);
		cfp.maxTableRowsFlag = true;
	}
	else if (propertyName == "maxTableCols") {
		this->maxTableCols = convertToInt(propertyValue);
		cfp.maxTableColsFlag = true;
	}
	else if (propertyName == "autoFit") {
		if (propertyValue == "true") {
			this->autoFit = true;
		}
		else if (propertyValue == "false") {
			this->autoFit = false;
		}
		else {
			//TODO
			//MyString exceptionMessage("ABORTING!")
		}
		
		cfp.autoFitFlag = true;
	}
	else if (propertyName == "visibleCellSymbols") {
		this->visibleCellSymbols = convertToInt(propertyValue);
		cfp.visibleCellSymbolsFlag = true;
	}
	else if (propertyName == "initialAllignment") {
		this->initialAllignment = getAlignmentByString(propertyValue);
		cfp.initialAllignmentFlag = true;
	} 
	else if (propertyName == "clearConsoleAfterCommand") {
		//
		this->clearConsoleAfterCommand = convertToInt(propertyValue);
		cfp.clearConsoleAfterCommandFlag = true;
	}
}

void Config::readConfigFromFile(std::ifstream& ifs)
{
	ConfigProperties cfp;
	if (ifs.is_open()) {
		while (ifs.peek() != EOF) {
			char buffer[Constants::BUFFER_SIZE];
			ifs.getline(buffer, Constants::BUFFER_SIZE);
			char propertyName[Constants::BUFFER_SIZE];
			char propertyValue[Constants::BUFFER_SIZE];
			getPropertyNameFromLine(buffer, propertyName, propertyValue);
			assignValueToProperty(propertyName, propertyValue);
		}
	}
}


