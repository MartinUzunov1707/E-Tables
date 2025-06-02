// E-Tables.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <fstream>
#include <iostream>
#include "Config.h"



int main()
{
	try {
		Config cfg("test.txt");
	}
	catch (std::invalid_argument exc) {
		std::cout << exc.what() << std::endl;
	}
	
}

