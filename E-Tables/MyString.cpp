#include "MyString.h"

void MyString::copyDynamicMemory(const MyString& other)
{
	this->length = other.length;
	this->data = new char[length + 1];

	for (int i = 0; i < length; i++) {
		this->data[i] = other.data[i];
	}

	data[length] = '\0';
}

void MyString::free()
{
	delete[] this->data;
}

MyString::MyString()
{
	this->data = nullptr;
	this->length = 0;
}

int getLength(const char* data) {
	int i = 0;
	while (data[i] != '\0') {
		i++;
	}
	return i;
}

MyString::MyString(const char* data)
{
	this->length = getLength(data);
	for (int i = 0; i < this->length; i++) {
		this->data[i] = data[i];
	}
}	

MyString::MyString(char* data, int length)
{
	this->data = data;
	this->length = length;
}

MyString::MyString(const MyString& other)
{
	copyDynamicMemory(other);
}

MyString::~MyString()
{
	free();
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other) {
		free();
		copyDynamicMemory(other);
	}
	return *this;
}

void MyString::concat(char* other, int length)
{
	char* temp = new char[length + this->length - 1];
	int i = 0;
	while(i < this->length) {
		if (this->data[i] == '\0') {
			break;
		}
		temp[i] = this->data[i];
		i++;
	}
	for (int a = 0; a < length; a++) {
		temp[i] = other[a];
		i++;
	}

	free();
	this->data = temp;
}

void MyString::concat(const MyString& other)
{
	this->concat(other.data, other.length);
}

char* MyString::getString() const
{
	return this->data;
}
