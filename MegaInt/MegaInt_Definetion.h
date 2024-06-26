#ifndef MEGAINT_DEFINETION_H
#define MEGAINT_DEFINETION_H
#include <string>
#include <iostream>
#include <ostream>
class MegaInt
{
//Friend functions and methods
public:
	friend unsigned long long len(MegaInt &n);
	friend std::ostream& operator<<(std::ostream &os,const MegaInt &MI);
	friend std::istream& operator>>(std::istream &in,const MegaInt &MI);
//Static field
private:
    unsigned long long length,ExpPos,ExpLength,NumbersAreVisible;
    short *numbers;
    bool negative,Exponential,IsPrefix;
//Constructors
public:
    MegaInt();
    MegaInt(const MegaInt &other);
    template <typename T>
    MegaInt(T n);
//Destructor
    ~MegaInt();
//Operators
	MegaInt operator - ();
	MegaInt operator + ();
	MegaInt operator --();
	MegaInt operator --(int value);
	MegaInt operator ++();
	MegaInt operator ++(int value);
	template <typename T>
	short  operator[](T n);
	
	
	
    MegaInt&operator=(const MegaInt &other);
    MegaInt operator+(const MegaInt &other);
    MegaInt operator-(const MegaInt &other);
    MegaInt operator*(const MegaInt &other);
    MegaInt operator/(const MegaInt &other);
    MegaInt operator%(const MegaInt &other);
    MegaInt operator+=(const MegaInt &other);
    MegaInt operator-=(const MegaInt &other);
    MegaInt operator*=(const MegaInt &other);
    MegaInt operator/=(const MegaInt &other);
    MegaInt operator%=(const MegaInt &other);
    
    template <typename T>
    MegaInt &operator=(T n);
    template <typename T>
    MegaInt operator+(const T n);
    template <typename T>
    MegaInt operator-(const T n);
    template <typename T>
    MegaInt operator*(const T n);
    template <typename T>
    MegaInt operator/(const T n);
    template <typename T>
    MegaInt operator%(const T n);
    template <typename T>
    MegaInt operator+=(const T n);
    template <typename T>
    MegaInt operator-=(const T n);
    template <typename T>
    MegaInt operator*=(const T n);
    template <typename T>
    MegaInt operator/=(const T n);
    template <typename T>
    MegaInt operator%=(const T n);
    
    
	bool operator ==(const MegaInt &other);
	bool operator > (const MegaInt &other);
	bool operator < (const MegaInt &other);
	bool operator <=(const MegaInt &other);
	bool operator >=(const MegaInt &other);
	bool operator !=(const MegaInt &other);
	
    template <typename T>
    bool operator==(const T n);
    template <typename T>
    bool operator >(const T n);
	template <typename T>
	bool operator <(const T n);
	template <typename T>
	bool operator <=(const T n);
	template <typename T>
	bool operator >=(const T n);
    template <typename T>
    bool operator!=(const T n);
//Methods
/* TODO (#1#): 
ƒобавить методы и аналогичные 
дружественные функции:
”далить 
последний, добавить последний, вырезать 
€чейку, добавить €чейку, 
експоненциальность, количество видимых 
знаков; словесное описание разр€дов, 
перевод по разр€дам. 
*/
/* TODO (#2#): Take MegaInt:: structures into static fields */

public:
    void Print(const bool linePrint=false);
    MegaInt MegaIntModyl();
    std::string GetStringRecord();
	
	unsigned long long GetSize();
	unsigned long long GetWeight();
	//////////////////////////////////////////////////////////////
	void PushBack(const short n);
	void PopBack();
	void Remove(const unsigned long long pos);
	void Insert(const short n,const unsigned long long pos=0);
	void SwitchExponential(const unsigned long long ExpLength,const unsigned long long ExpPos=0);
	void MakeExponential(const unsigned long long ExpPos=1);
	void MakeUnExponential();
	void ExpRound(const unsigned long long NumbersAreVisible);
	unsigned long long NumberOfLastNulls();
	
	void MakePrefix();
	void MakeUnPrefix();
	
	template <typename T>
    friend void SetUpDigitRate (T n=1);
	template <typename T>
    void SetUpDigitRate (T n=1);
//Static methods

	//Static methods
	static unsigned long long GetConstructedTimes()
	{
		return constructed;
	}
	static unsigned long long GetDestructedTimes()
	{
		return destructed;
	}
	static unsigned long long GetThousandPowers()
	{
		return NumberThousandPowers;
	}
	static MegaInt StringToMegaInt(const std::string& InputString)
	{
		MegaInt result;
		std::string String = "";
		for (unsigned long long i = 0; i < InputString.length(); i++)
			if ((InputString[i] >= '0' and InputString[i] <= '9') or (InputString[i] == '-' and !String.find('-')))
				String += InputString[i];


		result.negative = false;
		if (String == "")
			result = 0;
		else
		{
			if (String.length() > 1 and String[0] == '-')
				result.negative = true;
			else if (String.length() == 1 and String[0] == '-')
				return result;

			result.length = String.length() - result.negative;
			result.numbers = new short[result.length];
#ifdef DEBUG
			std::cout << "numbers:" << String << '|' << std::endl;
#endif
			for (unsigned long long i = 0 + result.negative; i < String.length(); i++)
			{
				result.numbers[i - result.negative] = short(String[i]) - short('0');
#ifdef DEBUG
				std::cout << "n[i]=" << result.numbers[i - result.negative] << " must be:" << short(String[i]) << " negative:" << result.negative << std::endl;
#endif
			}
		}
		return result;
	}
private:
//Friend methods
	friend void SetNewDigitRate();
    friend void EareseDigitRate();
	friend MegaInt StringToMegaInt(const std::string &InputString);
//Static variables
	static unsigned long long constructed;
	static unsigned long long destructed;
	static const unsigned long long NumberThousandPowers=29;
	static std::string ThousandPowers[NumberThousandPowers];
//Private Methods
	void SetNewDigitRate();
    void EareseDigitRate();

    void ExpUpDate();
    void PrefixUpDate();
	bool IsRoundDigit(const unsigned long long StartPos=0);
	
    short GetDigitRate(unsigned long long n,unsigned long long i);
	template <typename T>
    T IntSize(T n);
    template <typename T>
    T PowerTen(T n);
};
unsigned long long MegaInt::constructed=0;
unsigned long long MegaInt::destructed=0;
std::string MegaInt::ThousandPowers[NumberThousandPowers]=
{
"","K","M","B","T","Q","Sx","Sp","O","No","D","U","Duod","Tred","Quat","Quin"
,"Sexdec","Septendecillions","Octodecillions","Novemdecillions","Vigintillions"
,"Unvigintillions","Duovigintillions","Trevigintillion","Quattuorvigintillions"
,"Quinvigintillions","Sexvigintillions","Septenvigintillions","Octovigintillions"
};	
//Stream operators
std::ostream& operator<<(std::ostream &os, MegaInt &MI);
std::istream& operator>>(std::istream &in,const MegaInt &MI);
//Variables
#endif
