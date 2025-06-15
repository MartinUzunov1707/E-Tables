#pragma once
#include "Table.h"
#include "Utils.h"
#include "Command.h"
class Engine
{
private:
	static Table table;
	static void run();
	static void printTable();
	static void printHeader(int vcs);
	static void printHorizontalBorder(int vcs);
	static void printMatrix(int vcs);
	static Command* commandFactory(char* cell, char* command);
public:
	static void initialize();
	static Table& getTable() { return table; }
};

