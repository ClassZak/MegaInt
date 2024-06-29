#ifndef MEGAINT_DEFINETION_H
#define MEGAINT_DEFINETION_H
#include <string>
#include <iostream>
#include <ostream>
#include <exception>

#ifndef MAX_LIMIT_MEGAINT 
#define MAX_LIMIT_MEGAINT		 100000000000000000
#endif
#ifndef MAX_LIMIT_RATE_MEGAINT 
#define MAX_LIMIT_RATE_MEGAINT IntSize(MAX_LIMIT_MEGAINT)-1
#endif


class MegaInt
{
//Inner classes
public:
//Friend functions and methods
public:
	friend unsigned long long len(const MegaInt &n);
	friend std::ostream& operator<<(std::ostream &os,const MegaInt &MI);
	friend std::istream& operator>>(std::istream &in,const MegaInt &MI);
	
	class MegaIntException:public std::exception
	{
	public:
		MegaInt* numbers;
		unsigned long long count;
		char* reason;
		MegaIntException(MegaInt* m,char* reason,const unsigned long long count=1);
		MegaIntException(MegaInt* m,const char* reason,const unsigned long long count=1);
		MegaIntException(char* reason);
		MegaIntException(const char* reason);
		int what();
	};
//Private field
private:
	unsigned long long length;
	unsigned long long *numbers;
	bool negative;
//Constructors
public:
	MegaInt();
	MegaInt(const MegaInt &other);
	MegaInt(const char* InputString);
	MegaInt(char* InputString);
	template <typename T>
	MegaInt(const T n);
//Destructor
	~MegaInt();
//Operators
	MegaInt* operator*();
	
	MegaInt operator - ()
	{
		MegaInt result = *this;
		result.negative = !negative;
		if (result.numbers[0] == 0 and result.length == 1)
			result.negative = false;
		return result;
	}
	MegaInt operator + ();
	MegaInt operator --();
	MegaInt operator --(int value);
	MegaInt operator ++();
	MegaInt operator ++(int value);
	unsigned long long operator[](unsigned long long n);
	
	
	
	MegaInt&operator=(const char* InputString);
	
	MegaInt&operator=(const MegaInt &other);
	MegaInt operator+(MegaInt &other);
	MegaInt operator-(MegaInt &other);
	MegaInt operator*(MegaInt &other);
	MegaInt operator/(MegaInt &other);
	MegaInt operator%(const MegaInt &other);
	MegaInt operator+=(MegaInt &other);
	MegaInt operator-=(MegaInt &other);
	MegaInt operator*=(const MegaInt &other);
	MegaInt operator/=(const MegaInt &other);
	MegaInt operator%=(const MegaInt &other);
	
	
	MegaInt &operator=(long long n);
	MegaInt operator+(long long n);
	MegaInt operator-(long long n);
	MegaInt operator*(long long n);
	MegaInt operator/(long long n);
	MegaInt operator%(long long n);
	MegaInt operator+=(long long n);
	MegaInt operator-=(long long n);
	MegaInt operator*=(long long n);
	MegaInt operator/=(long long n);
	MegaInt operator%=(long long n);
	
	
	bool operator ==(const MegaInt &other);
	bool operator > (MegaInt &other);
	bool operator < ( MegaInt &other);
	bool operator <=( MegaInt &other);
	bool operator >=( MegaInt &other);
	bool operator !=( MegaInt &other);
	

	bool operator==(long long n);
	bool operator >(long long n);
	bool operator <(long long n);
	bool operator <=(long long n);
	bool operator >=(long long n);
	bool operator!=(long long n);
//Methods
public:
	MegaInt DigitNumberMegaInt();
	unsigned long long DigitNumber() const;
	MegaInt MegaIntModyl() const;
	char*& GetCharArrayRecord()const;
	MegaInt* GetPointer();
	unsigned long long GetSize()const;
//Static methods
	static unsigned long long GetConstructedTimes();
	static unsigned long long GetDestructedTimes();
	static MegaInt StringToMegaInt(const std::string &InputString);
	static MegaInt CharPointerToMegaInt(const char* InputString);
	static MegaInt CutMegaIntNumber(MegaInt &n,const unsigned long long newlength=1,const short pos=1);
	static char*   CutMegaIntNumberInCharPointer
	(
		MegaInt &n,
		const unsigned long long newlength=1,
		const short pos=1,
		const bool GetLeftHalf=true
	);
	static MegaInt AddNulls(MegaInt &n,const unsigned long long length=0,const short pos=0);
private:
//Friend methods
// 
//Static variables
public:
	static unsigned long long constructed;
	static unsigned long long destructed;
//Private Methods
private:
	bool IsRoundDigit(const unsigned long long StartPos=0);
};
unsigned long long MegaInt::constructed=0;
unsigned long long MegaInt::destructed=0;
//Stream operators
std::ostream& operator<<(std::ostream &os,const MegaInt &MI);
std::istream& operator>>(std::istream &in,const MegaInt &MI);
std::ostream& operator<<(std::ostream& os,const MegaInt& MI)
{
	char* returnchar = MI.GetCharArrayRecord();
	os << returnchar;
	if(returnchar != nullptr)
		delete[] returnchar;
	return os;
}
std::istream& operator>>(std::istream& in, MegaInt& MI)
{
	std::string InputString;
	in >> InputString;
	MI = MegaInt::StringToMegaInt(InputString);
	return in;
}
#endif
