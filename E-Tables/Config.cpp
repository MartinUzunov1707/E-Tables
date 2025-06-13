#include "Config.h"
#include "MyString.h"

namespace Constants {
	const int BUFFER_SIZE = 1024;
	const int ZERO_ASCII = '0';
}

Allignment getAlignmentByString(char* value) {
	if (strcmp(value,"left")==0) {
		return Allignment::LEFT;
	}
	else if (strcmp(value, "right") == 0) {
		return Allignment::RIGHT;
	}
	else if (strcmp(value, "center") == 0) {
		return Allignment::CENTER;
	}
	else {
		return Allignment::INIT;
	}
}

Config::Config(const char* fileName)
{
	readConfigFromFileName(fileName);
}

void Config::readConfigFromFileName(const char* fileName)
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

bool tryConvertToInt(char* value, int& tryResult) {
	int result = 0;
	int length = 0;
	while (value[length] != '\0') {
		length++;
	}
	int reverseIndex = length - 1;
	for (int i = 0; i < length;i++) {
		if (value[i] < '0' || value[i] > '9') {
			return false;
		}
		result += (value[i] - '0') * pow(10, reverseIndex);
		reverseIndex--;
	}

	tryResult = result;
	return true;
}

void Config::assignValueToProperty(char* propertyName, char* propertyValue,ConfigProperties& cfp)
{
	if (strcmp(propertyName,"initialTableRows") == 0) {
		int value = 0;
		if (tryConvertToInt(propertyValue, value)) {
			this->initialTableRows = value;
		}
		else {
			const char* message = "ABORTING! ";
			MyString exceptionMessage(message);
			exceptionMessage.append((const char*)propertyName).append(":").append((const char*)propertyValue)
				.append(" - ").append("Invalid value!");
			throw std::invalid_argument(exceptionMessage.getString());
		}
		cfp.initialTableRowsFlag = true;
	}
	else if (strcmp(propertyName, "initialTableCols") == 0) {
		int value = 0;
		if (tryConvertToInt(propertyValue, value)) {
			this->initialTableCols = value;
		}
		else {
			const char* message = "ABORTING! ";
			MyString exceptionMessage(message);
			exceptionMessage.append((const char*)propertyName).append(":").append((const char*)propertyValue)
				.append(" - ").append("Invalid value!");
			throw std::invalid_argument(exceptionMessage.getString());
		}
		cfp.initialTableColsFlag = true;
	}
	else if (strcmp(propertyName, "maxTableRows") == 0) {
		int value = 0;
		if (tryConvertToInt(propertyValue, value)) {
			this->maxTableRows = value;
		}
		else {
			const char* message = "ABORTING! ";
			MyString exceptionMessage(message);
			exceptionMessage.append((const char*)propertyName).append(":").append((const char*)propertyValue)
				.append(" - ").append("Invalid value!");
			throw std::invalid_argument(exceptionMessage.getString());
		}
		cfp.maxTableRowsFlag = true;
	}
	else if (strcmp(propertyName, "maxTableCols") == 0) {
		int value = 0;
		if (tryConvertToInt(propertyValue, value)) {
			this->maxTableCols = value;
		}
		else {
			const char* message = "ABORTING! ";
			MyString exceptionMessage(message);
			exceptionMessage.append((const char*)propertyName).append(":").append((const char*)propertyValue)
				.append(" - ").append("Invalid value!");
			throw std::invalid_argument(exceptionMessage.getString());
		}
		cfp.maxTableColsFlag = true;
	}
	else if (strcmp(propertyName, "autoFit") == 0) {

		if (strcmp(propertyValue,"true") == 0) {
			this->autoFit = true;
		}
		else if (strcmp(propertyValue, "false") == 0) {
			this->autoFit = false;
		}
		else {
			const char* message = "ABORTING! ";
			MyString exceptionMessage(message);
			exceptionMessage.append((const char*) propertyName).append(":").append((const char*) propertyValue)
				.append(" - ").append("Invalid value!");
			throw std::invalid_argument(exceptionMessage.getString());
		}
		
		cfp.autoFitFlag = true;
	}
	else if (strcmp(propertyName, "visibleCellSymbols") == 0) {
		int value = 0;
		if (tryConvertToInt(propertyValue, value)) {
			this->visibleCellSymbols = value;
		}
		else {
			const char* message = "ABORTING! ";
			MyString exceptionMessage(message);
			exceptionMessage.append((const char*)propertyName).append(":").append((const char*)propertyValue)
				.append(" - ").append("Invalid value!");
			throw std::invalid_argument(exceptionMessage.getString());
		}
		cfp.visibleCellSymbolsFlag = true;
	}
	else if (strcmp(propertyName, "initialAllignment") == 0) {
		Allignment allignment = getAlignmentByString(propertyValue);
		if (allignment == Allignment::INIT) {
			const char* message = "ABORTING! ";
			MyString exceptionMessage(message);
			exceptionMessage.append((const char*)propertyName).append(":").append((const char*)propertyValue)
				.append(" - ").append("Invalid value!");
			throw std::invalid_argument(exceptionMessage.getString());
		}
		this->initialAllignment = allignment;
		cfp.initialAllignmentFlag = true;
	} 
	else if (strcmp(propertyName, "clearConsoleAfterCommand") == 0) {
		if (strcmp(propertyValue, "true") == 0) {
			this->clearConsoleAfterCommand = true;
		}
		else if (strcmp(propertyValue, "false") == 0) {
			this->clearConsoleAfterCommand = false;
		}
		else {
			const char* message = "ABORTING! ";
			MyString exceptionMessage(message);
			exceptionMessage.append((const char*)propertyName).append(":").append((const char*)propertyValue)
				.append(" - ").append("Invalid value!");
			throw std::invalid_argument(exceptionMessage.getString());
		}
		cfp.clearConsoleAfterCommandFlag = true;
	}
	else {
		const char* message = "ABORTING! ";
		MyString exceptionMessage(message);
		exceptionMessage.append((const char*)propertyName).append(":").append((const char*)propertyValue)
			.append(" - ").append("Property does not exist!");
		throw std::invalid_argument(exceptionMessage.getString());
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
			assignValueToProperty(propertyName, propertyValue,cfp);
		}
		if (!cfp.validateConfigProperties()) {
			throw std::invalid_argument("One or more configuration properties are missing!");
		}
	}
}

unsigned int Config::getInitialRows()
{
	return this->initialTableRows;
}

unsigned int Config::getInitialCols()
{
	return this->initialTableCols;
}

unsigned int Config::getMaxRows()
{
	return this->maxTableRows;
}

unsigned int Config::getMaxCols()
{
	return this->maxTableCols;
}

bool Config::getAutoFit()
{
	return this->autoFit;
}

unsigned int Config::getVisibleCellSymbols()
{
	return this->visibleCellSymbols;
}

Allignment Config::getinitialAllignment()
{
	return this->initialAllignment;
}

bool Config::getClearConsoleAfterCommand()
{
	return this->clearConsoleAfterCommand;
}


