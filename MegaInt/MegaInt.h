#ifndef MEGAINT_H
#define MEGAINT_H
#include <string>
#include <iostream>
#include <typeinfo>
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
#ifndef MAX_CHAR
#define MAX_CHAR 255
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
class MegaInt;
#include "MegaInt_Definetion.h"
template <typename T>
T modyl(T n)
{
    return (n*(-1*(n<0)+(n>=0)));
}
unsigned long long len(MegaInt &n)
{
	return n.GetSize();
}
char NumberToChar(const int n)
{
	char RetunChar=' ';
	
	if(n>=0 and n<10)
	RetunChar='0'+n;
	else
	RetunChar='0'+n%10;
	return RetunChar;
}

unsigned long long IntSize(unsigned long long n)
{
	unsigned long long length=1;
    while(n>=10)
    {
        length++;
        n=n/10;
    }
    return length;
}
template <typename T>
T PowerTen(T n)
{
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

#include "MegaInt_Structors.h"
#include "MegaInt_Operators.h"
#include "MegaInt_Methods.h"



#endif
