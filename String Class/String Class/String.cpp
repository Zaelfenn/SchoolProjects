#include "String.h"
#include <exception>
using std::exception;
using std::invalid_argument;
#include <iostream>
using std::cerr;

String::String() : m_str(NULL), m_length(0) //default constructor
{}
String::String(char str) : m_str(&str), m_length(1) //constructor for a single character
{}

String::String(char* str) : m_str(nullptr), m_length(0) //constructor for a character pointer
{
	if (str != nullptr) { //if there is data to be copied
		m_str = new char[strlen(str) + 1]; //m_str size needs to be the same + 1 for null character
		strcpy(m_str, str); //copy the data
		m_length = static_cast<int>(strlen(str)); //find the size
	}
}

String::String(const char* str) : m_str(nullptr), m_length(0) //constructor for a string literal
{
	if (str != nullptr) { //if there is data to be copied
		m_str = new char[strlen(str) + 1]; //m_str size needs to be the same + 1 for null character
		strcpy(m_str, str); //copy the data
		m_length = static_cast<int>(strlen(str)); //find the size
	}
}

String::String(const String& original) : m_str(nullptr), m_length(original.m_length) //copy constructor
{
	if (m_length != 0) {
		m_str = new char[strlen(original.m_str) + 1];
		strcpy(m_str, original.m_str);
	}
}

String::String(String&& original) noexcept : m_str(original.m_str),  m_length(original.m_length)  //copy constructor
{}

String::~String() { //destructor
	if (m_str != nullptr && m_length != 0) //if there is a length to the string
		delete[] m_str; //deallocate the memory
	m_length = 0; //set the length to zero
}

String& String::operator = (const String& rhs) { //operator =
	if (this != &rhs) { //if they are not the same
		delete[] m_str; //deallocate the memory for m_str
		if (rhs.m_str != nullptr) { //if rhs has data
			m_str = new char[strlen(rhs.m_str) + 1]; //set the new size to the size of m_str + 1 for null char
			strcpy(m_str, rhs.m_str); //copy the string over
		}
	}
	m_length = rhs.m_length; //set the new length
	return *this;
}

String& String::operator = (String&& rhs) noexcept { //operator =
	if (this != &rhs) { //if they are not the same
		delete[] m_str; //deallocate the memory for m_str
		if (rhs.m_str != nullptr) { //if rhs has data
			m_str = new char[strlen(rhs.m_str) + 1]; //set the new size to the size of m_str + 1 for null char
			strcpy(m_str, rhs.m_str); //copy the string over
		}
	}
	m_length = rhs.m_length; //set the new length
	return *this;
}


bool String::operator < (const String& rhs) { //operator less than
	bool retVal = false; //assume false
	if (m_str != nullptr && rhs.m_str != nullptr) { //if both have data
		if (strcmp(m_str, rhs.m_str) < 0) //if the data in m_str is alphabetically after rhs.m_str
			retVal = true; //then m_str is less tha
	}
	else if (rhs.m_str != nullptr) //if only rhs.m_str has data
		retVal = true; //then m_str is less than 
	return retVal;
}

bool String::operator < (String&& rhs) { //operator less than
	bool retVal = false; //assume false
	if (m_str != nullptr && rhs.m_str != nullptr) { //if both have data
		if (strcmp(m_str, rhs.m_str) < 0) //if the data in m_str is alphabetically after rhs.m_str
			retVal = true; //then m_str is less tha
	}
	else if (rhs.m_str != nullptr) //if only rhs.m_str has data
		retVal = true; //then m_str is less than 
	return retVal;
}

bool String::operator < (const String& rhs) const {//operator less than
	bool retVal = false; //assume false
	if (m_str != nullptr && rhs.m_str != nullptr) { //if both have data
		if (strcmp(m_str, rhs.m_str) < 0) //if the data in m_str is alphabetically after rhs.m_str
			retVal = true; //then m_str is less tha
	}
	else if (rhs.m_str != nullptr) //if only rhs.m_str has data
		retVal = true; //then m_str is less than 
	//if neither has data than they are equal, and neither is less, therefore returning false.
	return retVal;
}

bool String::operator > (const String& rhs) { //operator greater than
	bool retVal = false; //assume false
	if (m_str != nullptr && rhs.m_str != nullptr) { //if both have data
		if (strcmp(m_str, rhs.m_str) > 0) //if the comparison shows that m_str comes before rhs.m_str
			retVal = true; //then it is greater
	}
	else if (m_str != nullptr) //if only m_str has data
		retVal = true; //it is more than nothing
	return retVal;
}

bool String::operator > (String&& rhs) { //operator greater than
	bool retVal = false; //assume false
	if (m_str != nullptr && rhs.m_str != nullptr) { //if both have data
		if (strcmp(m_str, rhs.m_str) > 0) //if the comparison shows that m_str comes before rhs.m_str
			retVal = true; //then it is greater
	}
	else if (m_str != nullptr) //if only m_str has data
		retVal = true; //it is more than nothing
	return retVal;
}

bool String::operator > (const String& rhs) const{ //operator greater than
	bool retVal = false; //assume false
	if (m_str != nullptr && rhs.m_str != nullptr) { //if both have data
		if (strcmp(m_str, rhs.m_str) > 0) //if the comparison shows that m_str comes before rhs.m_str
			retVal = true; //then it is greater
	}
	else if (m_str != nullptr) //if only m_str has data
		retVal = true; //it is more than nothing
	//if neither has data, then neither is greater, as they are both equal, which returns a false
	return retVal;
}

bool String::operator <= (const String& rhs) { //operator less than or equal to
	bool retVal = !(m_str > rhs.m_str); //return value is equal to the opposite of a greater than comparison
	return retVal; //return the bool
}

bool String::operator <= (String&& rhs) { //operator less than or equal to
	bool retVal = !(m_str > rhs.m_str); //return value is the same as not greater than
	return retVal; //return the bool
}

bool String::operator <= (const String& rhs) const{//operator less than or equal to
	bool retVal = !(m_str > rhs.m_str); //return value is equal to NOT (!) GREATER THAN (>)
	return retVal; //return the bool
}

bool String::operator == (const String& rhs) { //operator equal to
	bool retVal = false; //assume they are not equal
	if (rhs.m_str != nullptr && m_str != nullptr) //if both contain data
		retVal = (strcmp(m_str, rhs.m_str) == 0); //if both are the same, will return true
	else if (rhs.m_str == nullptr && m_str == nullptr)
		retVal = true; //they are technically the same if neither contains data
	return retVal;
}

bool String::operator == (String&& rhs) { //operator equal to
	bool retVal = false; //assume they are not equal
	if (rhs.m_str != nullptr && m_str != nullptr) //if both contain data
		retVal = (strcmp(m_str, rhs.m_str) == 0); //if both are the same, will return true
	else if (rhs.m_str == nullptr && m_str == nullptr)
		retVal = true; //they are technically the same if neither contains data
	return retVal; 
}

bool String::operator == (const String& rhs) const { //operator equal to
	bool retVal = false; //assume the value is false
	if (rhs.m_str != nullptr && m_str != nullptr) //if they both contain data
		retVal = (strcmp(m_str, rhs.m_str) == 0); //if the data is the same, strcmp will be true- otherwise, false
	else if (rhs.m_str == nullptr && m_str == nullptr) //if neither contains data
		retVal = true; //they are technically the same
	//if data is in one but not the other, they can't be the same- but writing that many if statements is redundant, so start with a false assumption
	return retVal;
}


bool String::operator >= (const String& rhs) { //operator greater than or equal to
	bool retVal = !(*this < rhs.m_str); //return value is equal to the opposite of a less than comparions
	return retVal; //return the bool
}

bool String::operator >= (String&& rhs) { //operator greater than or equal to
	bool retVal = !(*this < rhs.m_str); //return value is opposite of a less than comparison
	return retVal; //return bool
}

bool String::operator >= (const String& rhs) const {  //operator greater than or equal to
	bool retVal = !(*this < rhs.m_str); //return value is going to be the opposite of a less than comparison
	return retVal; //return bool
}


bool String::operator != (const String& rhs) { //operator not equal to
	bool retVal = !(*this == rhs.m_str); //return value is NOT (!) EQUAL TO (==)
	return retVal; //return bool
}

bool String::operator != (String&& rhs) { //operator not equal to
	bool retVal = !(*this == rhs); //return value is equal to the opposite of an equality 
	return retVal; //return the bool
}

bool String::operator != (const String& rhs) const{ //operator not equal to
	bool retVal = !(*this == rhs); //return value is the same as the opposite of an equal comparison
	return retVal; //return the boolean
}


String& String::operator ++() { //string uppercase operator, pre-increment
	if (m_str != nullptr) //if there is data
		_strupr(m_str); //uppercase the string
	return *this; //return the original value
}

String String::operator ++(int) { //string upppercase operator, post-increment
	String temp(*this); //create a new variable
	++(*this); //increment the original
	return temp; //return a temp value
}


String& String::operator --() { //string lowercase operator, pre-increment
	if (m_str != nullptr) //if there is data
		_strlwr(m_str); //lowercase the string
	return *this; //return new value
}

String String::operator --(int) { //string lowercase operator, post increment
	String temp(*this); //create a temporary variable
	--(*this); //lowercase the original
	return temp; //return a temporary value
}

void String::operator += (const String& rhs) { //concatenation operator
	if (m_str != nullptr && rhs.m_str != nullptr) { //if there is data to be copied on both sides
		char* temp = new char[strlen(m_str) + strlen(rhs.m_str) + 1]; //new variable with a size of both strings + 1 for null char
		strcpy(temp, m_str); //copy the first string over
		strcat(temp, rhs.m_str); //concatenate with second string
		delete[] m_str; //delete the original string
		m_str = temp; //set original string to new string
		m_length += rhs.m_length; //set the length
	}
	else if (m_str == nullptr && rhs.m_str != nullptr) { //if there is only data on the right side
		m_str = new char[strlen(rhs.m_str) + 1]; //set the size 
		strcpy(m_str, rhs.m_str); //copy the data
		m_length = rhs.m_length; //set the length
	}
}

void String::operator += (String&& rhs) { //concatenation operator
	if (m_str != nullptr && rhs.m_str != nullptr) { //if there is data to be added on both sides
		char* temp = new char[strlen(m_str) + strlen(rhs.m_str) + 1]; //new variable, the size of both strings + 1 for null character
		strcpy(temp, m_str); //copy the first string to new variable
		strcat(temp, rhs.m_str); //concatenate the 2nd string to the new variable
		delete[] m_str; //delete the old string
		m_str = temp; //set member variable to concatenated string
		m_length += rhs.m_length; //find the new length
	}
	else if (m_str == nullptr && rhs.m_str != nullptr) { //if original doesn't exist
		m_str = new char[strlen(rhs.m_str) + 1]; //set the size to the length of the other string + 1
		strcpy(m_str, rhs.m_str); //copy the string
		m_length = rhs.m_length; //find the length
	}//if there is no right side, nothing happens, as no changes would have to be made
}

String String::operator + (const String& rhs) { //concatenation operator
	String temp(*this); //initialize a new string, the old one will get deleted
	temp += rhs; //concatenate
	return temp; //return the new string
}

String String::operator + (String&& rhs) { //concatenation operator
	String temp(*this); //initialize a new string, old one gets deleted
	temp += rhs; //concatenate
	return temp; //return the new string
}





char& String::operator[](int index) { //index operator
	try {
		if (index > m_length || index < 0) { //index is out of bounds
			index = 0;
			throw invalid_argument("Error: Index out of bounds, returning first character"); //throw an error
		}
	}
	catch (invalid_argument& e) { //catch the error
		cerr << e.what() << std::endl; //display error
	}
	return m_str[index]; //return the correct character
}

char String::operator[](int index) const { //index operator
	try {
		if (index > m_length || index < 0) { //index is out of bounds
			index = 0;
			throw invalid_argument("Error: Index out of bounds, returning first character"); //throw an error	
		}
	}
	catch (invalid_argument& e) { //catch the error
		cerr << e.what() << std::endl; //display error
	}
	return m_str[index]; //return the correct character
}



int String::getLength() { //getter for length of string
	return m_length;
}

const char * String::getStr() const { //overloaded getter for string
	return m_str;
}

const char * String::getStr(){ //getter for string
	return m_str; 
}

ostream& operator << (ostream& str, const String& rhs) { //overloaded insertion operator
	if (rhs.getStr() != nullptr) //if there is data
		str << rhs.getStr(); //input the data
	else
		str << ""; //otherwise input a null string
	return str;
}