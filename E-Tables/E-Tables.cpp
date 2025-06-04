// E-Tables.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <fstream>
#include <iostream>
#include "Config.h"
#include "MyString.h"



int main()
{
	MyString str("012345");

	std::cout << str.substr(1, 3).getString();
	
}

