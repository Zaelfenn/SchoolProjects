#pragma once
#include <ostream>
using std::ostream;
class String
{
public:
	String();
	String(char str);
	String(char* str);
	String(const char* str);

	~String();

	String(const String& original);
	String(String&& original) noexcept;

	String& operator = (const String& rhs);
	String& operator = (String&& rhs) noexcept;

	bool operator < (const String& rhs);
	bool operator < (String&& rhs);
	bool operator < (const String& rhs) const;

	bool operator > (const String& rhs);
	bool operator > (String&& rhs);
	bool operator > (const String& rhs) const;

	bool operator <= (const String& rhs);
	bool operator <= (String&& rhs);
	bool operator <= (const String& rhs) const;

	bool operator == (const String& rhs);
	bool operator == (String&& rhs);
	bool operator == (const String& rhs) const;

	bool operator >= (const String& rhs);
	bool operator >= (String&& rhs);
	bool operator >= (const String& rhs) const;


	bool operator != (const String& rhs);
	bool operator != (String&& rhs);
	bool operator != (const String& rhs) const;


	String& operator ++();
	String operator ++(int);

	String& operator --();
	String operator --(int);

	String operator + (const String& rhs);
	String operator +(String&& rhs);

	void operator += (const String& rhs);
	void operator += (String&& rhs);

	char& operator[](int index);
	char operator[](int index) const;

	int getLength();
	const char* getStr();
	const char* getStr()const;

	friend ostream& operator << (ostream& str, const String& rhs);

private:

	char* m_str;
	int m_length;

};

