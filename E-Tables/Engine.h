#pragma once
#include "Table.h"
#include <iostream>
#include "Utils.h"
class Engine
{
private:
	static Table table;
	static void run();
	static void printTable();
	static void printHeader(int vcs);
	static void printHorizontalBorder(int vcs);
	static void printMatrix(int vcs);
public:
	static void initialize();
};

