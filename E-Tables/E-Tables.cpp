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
	/*char* data = new char[5] {"data"};
	char* data2 = new char[5] {"brat"};
	MyString str(data, 5);
	str.concat(data2,5);*/
	
}

