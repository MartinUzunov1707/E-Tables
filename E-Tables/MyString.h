#pragma once

class MyString
{
private:
	char* data;
	int length;
	void copyDynamicMemory(const MyString& other);
	void free();
public:
	MyString();
	MyString(const char* data);
	MyString(char* data, int length);
	MyString(const MyString& other);
	~MyString();
	MyString& operator=(const MyString& other);
	MyString& append(const char* other);
	MyString& append(char other);
	MyString& append(char* other, int length);
	MyString substr(int startIndex, int length) const;
	
	//MyString & append(const MyString & other);
	char* getString() const;
};

