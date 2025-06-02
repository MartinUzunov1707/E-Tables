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
	i++;
	return i;
}

MyString::MyString(const char* data)
{
	this->length = getLength(data);
	this->data = new char[this->length];
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

MyString& MyString::append(char* other, int length)
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
	this->length += length - 1;
	this->data = temp;

	return *this;
}

MyString& MyString::append(const char* other)
{
	int length = getLength(other);
	this->append((char*)other, length);
	return *this;
}

//MyString& MyString::append(const MyString& other)
//{
//	this->append(other.data, other.length);
//return *this;
//}

char* MyString::getString() const
{
	return this->data;
}
