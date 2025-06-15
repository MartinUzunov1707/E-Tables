#include "MyString.h"
#include <stdexcept>

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

int getCharLength(const char* data) {
	int i = 0;
	while (data[i] != '\0') {
		i++;
	}
	i++;
	return i;
}

MyString::MyString(const char* data)
{
	this->length = getCharLength(data);
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

MyString MyString::substr(int startIndex, int length) const
{
	char* temp = new char[length + 1];
	if (startIndex < 0 || startIndex >= this->length) {
		throw std::invalid_argument("startIndex out of bounds!");
	}
	else if (length == 0 || length >= this->length) {
		throw std::invalid_argument("Length cannot be 0 or bigger than current length!");
	}
	int i = 0;
	while(i < length) {
		temp[i] = this->data[i + startIndex];
		i++;
	}
	temp[i] = '\0';
	return MyString(temp);
}

bool MyString::contains(char symbol) const
{
	for (int i = 0; i < this->length;i++) {
		if (this->data[i] == symbol) {
			return true;
		}
	}
	return false;
}

MyString& MyString::append(const char* other)
{
	int length = getCharLength(other);
	this->append((char*)other, length);
	return *this;
}

MyString& MyString::append(char other)
{
	this->append(&other, 1);
	return *this;
}


int MyString::getLength() const
{
	return getCharLength(data);
}

char* MyString::getString() const
{
	return this->data;
}
