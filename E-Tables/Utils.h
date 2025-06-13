#pragma once
static class Utils {
public:
	static const int BUFFER_SIZE = 1024;
	static const int ZERO_ASCII = '0';
	

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

	static void splitValuesByDelimiter(char* line, char* lhs, char* rhs, char delimiter) {
		int i = 0;
		int a = 0;
		while (line[i] != delimiter) {
			lhs[i] = line[i];
			i++;
		}
		lhs[i] = '\0';
		i++; // skips delimeter
		while (line[i] != '\0') {
			rhs[a] = line[i];
			i++;
			a++;
		}
		rhs[a] = '\0';
	}

};
