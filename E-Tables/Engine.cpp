#include "Engine.h"
#include "EqualsCommand.h"
#include "InsertCommand.h"
#include "DeleteCommand.h"
#include <iostream> 

Table Engine::table;

void Engine::initialize()
{
	std::cout << "Welcome to E-tables!\n1.Open existing table\n2.Create new table\n3.Exit" << std::endl;
	char command[Utils::BUFFER_SIZE];
	std::cin >> command;
	//Utils::splitValuesByDelimiter(buffer, command, param1, ' ');
	while (true) {
		if (strcmp(command, "open") == 0) {
			char tableName[Utils::BUFFER_SIZE];
			char configName[Utils::BUFFER_SIZE];
			std::cin >> tableName;
			std::cin >> configName;
			//Utils::splitValuesByDelimiter(param1, tableName, configName, ' ');
			Engine::table = Table(configName, tableName);
			break;
		}
		else if (strcmp(command, "new") == 0) {
			char param1[Utils::BUFFER_SIZE];
			std::cin >> param1;
			Engine::table = Table(param1);
			break;
		}
		else if (strcmp(command, "exit") == 0) {
			exit(EXIT_SUCCESS);
		}
		else {
			std::cout << "Invalid command! Please try again!" << std::endl;
		}
	}
	run();
}

Command* Engine::commandFactory(char* cell, char* command)
{
	
	Cell* target = &Engine::getTable().getByIndex(cell[1] - '1', cell[0] - 'A');
	if (command[0] == '=') {
		return new EqualsCommand(target, command);
	}
	else if (strcmp(command, "insert") == 0) {
		char insertArgs[Utils::BUFFER_SIZE];
		std::cin >> insertArgs;
		return new InsertCommand(target, insertArgs);
	}
	else if ((strcmp(command, "delete") == 0)) {
		return new DeleteCommand(target);
	}
}

void Engine::run()
{
	while (true) {
		if (Engine::table.getConfig().getClearConsoleAfterCommand()) {
			system("cls");
		}
		printTable();
		char cell[Utils::BUFFER_SIZE];
		char commandString[Utils::BUFFER_SIZE];
		std::cin >> cell;
		std::cin >> commandString;
		Command* command = commandFactory(cell, commandString);
		command->execute();
	}
}

void Engine::printTable()
{
	int visibleCellSymbols = 0;
	if (Engine::table.getConfig().getAutoFit()) {
		visibleCellSymbols = Engine::table.getMaxCellLength();
	}
	else {
		visibleCellSymbols = Engine::table.getConfig().getVisibleCellSymbols();
	}
	printHeader(visibleCellSymbols);
	printMatrix(visibleCellSymbols);
}

void Engine::printHeader(int vcs)
{
	printHorizontalBorder(vcs);
	std::cout << "|   |";
	for (int i = 0; i < Engine::table.getCurrentCol();i++) {
		for (int a = 0; a < vcs;a++) {
			if (vcs / 2 == a) {
				std::cout << i+1;
			}
			else {
				std::cout << ' ';
			}
			
		}
		std::cout << "|";
	}
	std::cout << std::endl;
	printHorizontalBorder(vcs);
}
void Engine::printHorizontalBorder(int vcs) {
	std::cout << "|---|";
	for (int i = 0; i < Engine::table.getCurrentCol();i++) {
		for (int a = 0; a < vcs;a++) {
			std::cout << '-';
		}
		std::cout << "|";
	}
	std::cout << std::endl;
}

void Engine::printMatrix(int vcs)
{
	MyString cellValue;
	for (int i = 0; i < Engine::table.getCurrentRow();i++) {
		std::cout << "| " << (char)(i + 'A') << " |";
		for (int a = 0; a < Engine::table.getCurrentCol();a++) {
			int currentCellLength = 0;
			if (strcmp(Engine::table.getByIndex(a, i).toString(), "t") == 0) {
				cellValue = "TRUE";
				currentCellLength = 4;
			} else if(strcmp(Engine::table.getByIndex(a, i).toString(), "f") == 0){
				cellValue = "FALSE";
				currentCellLength = 5;
			}
			else {
				cellValue = Engine::table.getByIndex(a, i).toString();
				currentCellLength = Utils::getStringLength(cellValue.getString()) - 1;
			}
			int startIndex;
			if (currentCellLength >= vcs) {
				startIndex = 0;
			}
			else {
				startIndex = (vcs - currentCellLength) % 2 == 0 ? (vcs - currentCellLength) / 2 : ((vcs - currentCellLength) / 2) + 1; //(vcs - currentCellLength) / 2;
			}
			for (int x = 0; x < vcs; x++) {
				if (x == startIndex && currentCellLength != 0) {
					for (int c = 0; x < vcs && c < currentCellLength; c++) {
						std::cout << cellValue.getString()[c];
						x++;
					}
					x--;
				}
				else {
					std::cout << ' ';
				}
			}
			std::cout << '|';
		}
		std::cout << std::endl;
		printHorizontalBorder(vcs);
	}
}




