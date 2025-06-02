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
	void concat(char* other, int length);
	void concat(const MyString& other);
	char* getString() const;
};

