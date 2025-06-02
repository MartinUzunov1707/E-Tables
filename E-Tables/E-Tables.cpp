// E-Tables.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <fstream>
#include <iostream>
#include "MyString.h"

int convertToInts(char* value) {
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

void getPropertyNameFromLines(char* line, char* nameDestination, char* valueDestination) {
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
int getLengths(const char* data) {
	int i = 0;
	while (data[i] != '\0') {
		i++;
	}
	return i;
}

int main()
{
	std::ifstream ifs("test.txt");
	char propertyName[1024];
	char propertyValue[1024];
	char buffer[1024];

	if (ifs.is_open()) {
		ifs.getline(buffer,1024);
	}
	getPropertyNameFromLines(buffer, propertyName, propertyValue);
	MyString s("ABORTING! ");
	s.append((const char*)propertyName).append(":").append((const char*)propertyValue)
		.append(" - ").append("Property does not exist!");
	std::cout << s.getString() << std::endl;
}

