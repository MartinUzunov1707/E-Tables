#pragma once
#include <cmath>
static class Utils {
public:
	static const int BUFFER_SIZE = 1024;
	static const int ZERO_ASCII = '0';
	
	static int getStringLength(const char* data) {
		int i = 0;
		while (data[i] != '\0') {
			i++;
		}
		i++;
		return i;
	}

	static bool tryConvertToInt(char* value, int& tryResult) {
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

	static void parseIntToString(int num, char* buffer) {
		int digitCounter = 0;
		int numCopy = num;
		while (num != 0) {
			num /= 10;
			digitCounter++;
		}
		int lastIndex = digitCounter;
		while (numCopy != 0) {
			buffer[digitCounter-1] = numCopy % 10 + '0';
			numCopy /= 10;
			digitCounter--;
		}
		buffer[lastIndex] = '\0';
	}

	static void splitValuesByDelimiter(char* line, char* lhs, char* rhs, char delimiter) {
		int i = 0;
		int a = 0;
		int lineLength = getStringLength(line);
		while (line[i] != delimiter && i != lineLength) {
			lhs[i] = line[i];
			i++;
		}
		lhs[i] = '\0';
		if (i != lineLength) {
			i++; // skips delimeter
			while (line[i] != '\0') {
				rhs[a] = line[i];
				i++;
				a++;
			}
			rhs[a] = '\0';
		}
		else {
			rhs = nullptr;
		}
	}
};
