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

	static void parseDoubleToString(double value, char* buffer) {
		//limits to 3 decimal places
		int integerPart = (int)value;
		int decimalPart = (int)((value - integerPart)*pow(10,3));
		//decimal part is always 3 digits long
		int integerDigitCounter = 0;
		int integerPartCopy = integerPart;
		while (integerPart != 0) {
			integerPart /= 10;
			integerDigitCounter++;
		}
		int lastIndex = integerDigitCounter + 4; // 3 digits for decimal part + 1 for dot
		int reverseIndex = lastIndex - 1;
		while (decimalPart != 0) {
			buffer[reverseIndex] = (decimalPart % 10) + '0';
			decimalPart /= 10;
			reverseIndex--;
		}
		buffer[reverseIndex--] = '.';

		while (integerPartCopy != 0) {
			buffer[reverseIndex] = (integerPartCopy % 10) + '0';
			integerPartCopy /= 10;
			reverseIndex--;
		}

		buffer[lastIndex] = '\0';
	}
	static bool validateCellCoordinates(int xVal, int yVal, int maxXVal, int maxYVal) {
		return xVal > 0 && xVal < maxXVal && yVal > 0 && yVal < maxYVal;
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
	static bool tryConvertToDouble(char* value, double& tryResult) {
		int intResult = 0;
		int decimalResult = 0;
		int length = 0;
		int decimalPointIndex = -1;
		bool isAfterDecimalPoint = false;
		while (value[length] != '\0') {
			if (value[length] == '.') {
				decimalPointIndex = length;
			}
			length++;
		}

		int reverseIndex = length - 1;
		for (int i = 0; i < length;i++) {
			if (value[i] == '.') {
				isAfterDecimalPoint = true;
			}
			if (value[i] < '0' || value[i] > '9') {
				return false;
			}
			if (isAfterDecimalPoint) {
				decimalResult += (value[i] - '0') * pow(10, reverseIndex);
			}
			else {
				intResult += (value[i] - '0') * pow(10, reverseIndex);
			}
			reverseIndex--;
		}

		tryResult = intResult + (decimalResult / pow(10,length-decimalPointIndex - 1));
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

	static char** splitValuesByDelimiter(char* line, char delimiter) {
		char** result = new char*[countDelimiter(line,delimiter) + 1];
		for (int a = 0; a <=countDelimiter(line, delimiter);a++) {
			result[a] = new char[Utils::BUFFER_SIZE];
		}
		int stringIndex = 0;
		int currentStringIndex = 0;
		int i = 0;
		int lineLength = getStringLength(line);

		while (true) {
			if (line[i] == '\0') {
				result[stringIndex][currentStringIndex] = '\0';
				break;
			}
			else if (line[i] == delimiter) {
				result[stringIndex][currentStringIndex] = '\0';
				stringIndex++;
				currentStringIndex = 0;
				i++;
			}
			else {
				result[stringIndex][currentStringIndex] = line[i];
				i++;
				currentStringIndex++;
			}
		}
		return result;
	}
	static int countDelimiter(char* line, char delimiter) {
		int res = 0;
		for (int i = 0; i < getStringLength(line); i++) {
			if (line[i] == delimiter) {
				res++;
			}
		}
		return res;
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
