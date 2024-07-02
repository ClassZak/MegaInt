#ifndef MEGAINT_H
#define MEGAINT_H


#include <string>
#include <iostream>
#include <typeinfo>
#include <windows.h>
//#define MEGAINT_DEBUG
#ifndef MAX_SIGNED_CHAR
#define MAX_SIGNED_CHAR 127
#endif
#ifndef MIN_SIGNED_CHAR
#define MIN_SIGNED_CHAR -128
#endif
#ifndef MAX_UNSIGNED_CHAR
#define MAX_UNSIGNED_CHAR 255
#endif
#ifndef MIN_CHAR
#define MIN_CHAR -128
#endif
#ifndef MAX_CHAR
#define MAX_CHAR 127
#endif
#ifndef MAX_SHORT
#define MAX_SHORT 32767
#endif
#ifndef MIN_SHORT
#define MIN_SHORT -32768
#endif
#ifndef MAX_UNSIGNED_SHORT
#define MAX_UNSIGNED_SHORT 65535
#endif
#ifndef MAX_INT
#define MAX_INT 2147483647
#endif
#ifndef MIN_INT
#define MIN_INT -2147483648
#endif
#ifndef MAX_UNSIGNED_INT
#define MAX_UNSIGNED_INT 4294967295
#endif
#ifndef MAX_LONG
#define MAX_LONG 2147483647
#endif
#ifndef MIN_LONG
#define MIN_LONG -2147483648
#endif
#ifndef MAX_UNSIGNED_LONG
#define MAX_UNSIGNED_LONG 4294967295
#endif
#ifndef MAX_LONG_LONG
#define MAX_LONG_LONG 9223372036854775807
#endif
#ifndef MIN_LONG_LONG
#define MIN_LONG_LONG -9223372036854775808
#endif
#ifndef MAX_UNSIGNED_LONG_LONG
#define MAX_UNSIGNED_LONG_LONG 18446744073709551615
#endif

#ifndef MAX_LIMIT_MEGAINT 
#define MAX_LIMIT_MEGAINT		1000000000000000000
#endif
#ifndef MAX_LIMIT_RATE_MEGAINT 
#define MAX_LIMIT_RATE_MEGAINT IntSize(MAX_LIMIT_MEGAINT)-1
#endif

class MegaInt;

unsigned long long IntSize(unsigned long long n);

#include "MegaInt_Definetion.h"
#include "MegInt_Exception.h"
unsigned long long CutNumber(unsigned long long n,const short newsize);


long long modyl(long long n);

unsigned long long len(const MegaInt &n);

char NumberToChar(const int n);

unsigned long long GetCharArrayLength(const char* array);

void CharArrayPushBack(char*& array,char last);

char* CharConcat(char* first,char *second);

void CharArrayPushBack(const char*& array,char last);

char* CharConcat(const char* first,char *second);

char* CharConcat(const char* first,const char *second);

char* CharConcat(char* first,const char *second);

unsigned long long find_in_chars(char* array,char element);

unsigned long long find_in_chars(char* array,unsigned long long length,char element);

unsigned long long PowerTen(unsigned long long n);

short GetDigitRate(unsigned long long n,unsigned long long i);

template <typename T>
std::string to_string(T n);

template <typename T>
void to_char_pointer(char*& array,T n);

char* StringToCharPoint(const std::string &String);

template <typename T>
bool IsRound(const T n);





unsigned long long CutNumber(unsigned long long n,const short newsize)
{
	unsigned long long returnnumber=0;
	for(short i=0;i<newsize;i++)
	{
		unsigned long long curr=((n/PowerTen(i))%10);
		if(!i)
		returnnumber=n%10;
		else
		returnnumber+=((n/PowerTen(i))%10)*PowerTen(i);
	}
	return returnnumber;
}

long long modyl(long long n)
{
	return (n < 0) ? -n : n;
}
unsigned long long len(const MegaInt &n)
{
	return n.GetSize();
}
char NumberToChar(const int n)
{
	char RetunChar='0';
	if(n>=0 and n<10)
	RetunChar+=n;
	else
	RetunChar+=n%10;
	return RetunChar;
}

unsigned long long GetCharArrayLength(const char* array)
{
	if(array==NULL)
	{
		throw std::exception();
		return 0;
	}
	else
	{
		unsigned long long length=0;
		for(unsigned long long i=0;array[i]!='\0';++i)
		++length;
		#ifdef DEBUG
		std::cout<<"len="<<length<<std::endl;
		#endif
		return length;
	}
}
void CharArrayPushBack(char*& array, char last)
{
	if (last == '\0')
		return;

	size_t arrayLength = (array != nullptr) ? strlen(array) : 0;

	char* result = new char[arrayLength + 2];
	result[arrayLength] = last;
	result[arrayLength + 1] = '\0';

	if (array != nullptr)
	{
		for (std::size_t i = 0; i < arrayLength - 1; ++i)
			result[i] = array[i];

		delete[] array;
	}
	array = result;
}

char* CharConcat(const char* first, const char* second)
{
	if (!first && !second)
		throw std::exception();
	else if (!first)
		return _strdup(second);
	else if (!second)
		return _strdup(first);
	else
	{
		std::size_t firstLength = strlen(first);
		std::size_t secondLength = strlen(second);
		char* result = new char[firstLength + secondLength + 1];
		strcpy_s(result, firstLength + 1, first);
		strcpy_s(result + firstLength, secondLength + 1, second);
		return result;
	}
}
unsigned long long find_in_chars(char* array,char element)
{
	unsigned long long length=GetCharArrayLength(array);
	for(unsigned long long i=0;i<length;++i)
	if(array[i]==element)
	return i;
	return 0;
}
unsigned long long find_in_chars(char* array,unsigned long long length,char element)
{
	for(unsigned long long i=0;i<length;++i)
	if(array[i]==element)
	return i;
	return 0;
}

unsigned long long IntSize(unsigned long long n)
{
	unsigned long long length=1;
	while(n>=10)
	{
		if(length==MAX_UNSIGNED_LONG_LONG)
			throw MegaInt::MegaIntException("Length is more then max");

		++length;
		n/=10;
	}
	return length;
}
unsigned long long PowerTen(unsigned long long n)
{
	if(n==MAX_LIMIT_RATE_MEGAINT-1)
	return (unsigned long long)MAX_LIMIT_MEGAINT/10;
	if(n==MAX_LIMIT_RATE_MEGAINT)
	return (unsigned long long)MAX_LIMIT_MEGAINT;
	if(n==0)
	return 1;
	else if(n==1)
	return 10;
	else
	return 10*PowerTen(n-1);
}
short GetDigitRate(unsigned long long n,unsigned long long i)
{
	short result=((n/PowerTen(i))%10);
	return result;
}
template <typename T>
std::string to_string(T n)
{
	std::string OutputString;
	int size=IntSize(n);
	
	for(int i=0;i<size;i++)
	OutputString+=(NumberToChar(GetDigitRate(n,size-i-1)));
	
	return OutputString;
}
template <typename T>
void to_char_pointer(char*& array,T n)
{
	char* OutputString=nullptr;
	unsigned long long size=IntSize(n);
	
	OutputString=(char*)malloc(sizeof(char)*(size+1));
	OutputString[size]='\0';

	for(int i=0;i<size;i++)
		OutputString[i]=NumberToChar(GetDigitRate(n,size-i-1));
	
	if (OutputString != nullptr)
	{
		if (array != nullptr)
			delete[] array;

		array = OutputString;
	}
}
char* StringToCharPoint(const std::string &String)
{
	unsigned long long newlength=String.length()+1;
	char *array=new char[newlength];
	
	for(unsigned long long i=0;i<newlength-1;i++)
	{
		array[i]=String[i];
	}
	array[newlength-1]='\0';
	
	return array;
}

template <typename T>
bool IsRound(const T n)
{
	bool round=false;
	for(short i=0;i<=19;++i)
	{
		if(modyl(n)==PowerTen(i))
		{
			round=true;
			break;
		}
		if(PowerTen(i)>modyl(n))
		break;
	}
	return round;
}

#include "MegaInt_Structors.h"
#include "MegaInt_Operators.h"
#include "MegaInt_Methods.h"



#endif
