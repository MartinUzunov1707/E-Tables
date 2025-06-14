#include "Engine.h"
Table Engine::table;

void Engine::initialize()
{
	std::cout << "Welcome to E-tables!\n1.Open existing table\n2.Create new table\n3.Exit" << std::endl;
	char buffer[Utils::BUFFER_SIZE];
	char command[Utils::BUFFER_SIZE];
	char param1[Utils::BUFFER_SIZE];
	std::cin >> command;
	//Utils::splitValuesByDelimiter(buffer, command, param1, ' ');
	while (true) {
		if (strcmp(command, "open") == 0) {
			char tableName[Utils::BUFFER_SIZE];
			char configName[Utils::BUFFER_SIZE];
			std::cin >> tableName;
			std::cin >> configName;
			//Utils::splitValuesByDelimiter(param1, tableName, configName, ' ');
			Engine::table  = Table(configName, tableName);
			break;
		}
		else if (strcmp(command, "new") == 0) {
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

void Engine::run()
{
	while (true) {
		if (Engine::table.getConfig().getClearConsoleAfterCommand()) {
			system("cls");
		}
		printTable();
		char buffer[Utils::BUFFER_SIZE];
		std::cin >> buffer;
		//todo
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
	printHorizontalBorder(visibleCellSymbols);
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
	for (int i = 0; i < Engine::table.getCurrentRow();i++) {
		std::cout << "| " << (char)(i + 'A') << " |";
		for (int a = 0; a < Engine::table.getCurrentCol();a++) {
			int currentCellLength = Utils::getStringLength(Engine::table.getByIndex(i, a).print()) - 1;
			int startIndex;
			if (currentCellLength >= vcs-1) {
				startIndex = 0;
			}
			else {
				startIndex = (vcs - currentCellLength) / 2;
			}
			for (int x = 0; x < vcs; x++) {
				if (x == startIndex) {
					const char* cellValue = Engine::table.getByIndex(i, a).print();
					for (int c = 0; c < currentCellLength; c++) {
						if (c + currentCellLength == vcs) {
							break;
						}
						std::cout << cellValue[c];
						x++;
					}
				}
				else {
					std::cout << ' ';
				}
			}
			std::cout << '|';
		}
		std::cout << std::endl;
	}
}


