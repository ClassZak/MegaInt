#ifndef MEGAINT_METHODS_H
#define MEGAINT_METHODS_H
#include <cstddef>
#include <iostream>
#include <windows.h>
/*///////////////////////////////////////////////////////////*/
///////////////////////////////////////////////////////////////
//                     Public methods
///////////////////////////////////////////////////////////////
/*///////////////////////////////////////////////////////////*/

	
//Other methods

//std::string MegaInt::Print(const bool linePrint=false,const bool DoReturnThisSelfString=true)
void MegaInt::Print(const bool linePrint)
{
	ExpUpDate();
	if(!IsPrefix)
	{
		unsigned long long NumbersDisplayed=0;
		//ExpUpDate();
	    #ifdef MEGAINT_DEBUG
	    std::cout<<"length "<<length<<' ';
	    if(negative)std::cout<<"negative ";
	    for(unsigned long long i=0;i<length;i++)
	    std::cout<<numbers[i]<<' ';
	    std::cout<<':';
	    if(negative)std::cout<<'-';
	    for(unsigned long long i=0;i<length;i++)
	    std::cout<<numbers[i];
		#else
	    if(negative)std::cout<<'-';
	    if(!ExpPos and Exponential)std::cout<<"0.";
	    for(unsigned long long i=0;i<length;i++)
	    {
	    	if(i==ExpPos and Exponential and i and !IsRoundDigit(i) and NumbersAreVisible)
	    	std::cout<<'.';
	    	if(Exponential)
	    	{
		    	if(!IsRoundDigit(i)and NumbersDisplayed<=NumbersAreVisible)
		    	{
		    		std::cout<<numbers[i];
		    		NumbersDisplayed++;
				}
			}
	    	else
	    	std::cout<<numbers[i];
		}
		if(Exponential)
		std::cout<<"e+"<<ExpLength;
		#endif
		if(linePrint)std::cout<<std::endl;
	}
	else
	{
		unsigned long long NumbersDisplayed=0,PointPos;
		if(length/3<NumberThousandPowers)
		PointPos=(length%3);
		else if((length-1)/3<NumberThousandPowers)
		PointPos=(length%3);
		else
		PointPos=length-(3*NumberThousandPowers-3);
		
		if(length>3 and !PointPos)
		PointPos+=3;
		
		for(unsigned long long i=0;i<PointPos;i++)
		{
			if(i>=length)
			break;
			std::cout<<numbers[i];
		}
		
		for(unsigned long long i=PointPos;i<PointPos+3;i++)
		{
			
			
			if(i>=length)
			break;
			if(i==PointPos and !IsRoundDigit(i) and i)
			std::cout<<'.';
			if(!IsRoundDigit(i))
			std::cout<<numbers[i];
			else
			break;
		}
		if(((length-1)/3)<NumberThousandPowers)
		std::cout<<ThousandPowers[(length-1)/3];
		else
		std::cout<<ThousandPowers[NumberThousandPowers-1];
		if(linePrint)std::cout<<std::endl;
	}
}
std::string MegaInt::GetStringRecord()
{
	std::string ReturnString="";
	ExpUpDate();
	if(!IsPrefix)
	{
		unsigned long long NumbersDisplayed=0;
	    #ifdef MEGAINT_DEBUG
	    ReturnString.append("length ");ReturnString.append(to_string(length)+" ");
	    if(negative)std::cout<<"negative ";
	    for(unsigned long long i=0;i<length;i++)
	    ReturnString.append(to_string(numbers[i]));ReturnString.append(" ");
	    ReturnString.append(":");
	    if(negative)ReturnString.append("-");
	    for(unsigned long long i=0;i<length;i++)
	    std::cout<<numbers[i];
		#else
	    if(negative)ReturnString.append("-");
	    if(!ExpPos and Exponential)ReturnString.append("0.");
	    for(unsigned long long i=0;i<length;i++)
	    {
	    	if(i==ExpPos and Exponential and i and !IsRoundDigit(i) and NumbersAreVisible)
	    	ReturnString.append(".");
	    	if(Exponential)
	    	{
		    	if(!IsRoundDigit(i)and NumbersDisplayed<=NumbersAreVisible)
		    	{
		    		ReturnString.append(to_string(numbers[i]));
		    		NumbersDisplayed++;
				}
			}
	    	else
	    	ReturnString.append(to_string(numbers[i]));
		}
		if(Exponential)
		{
			ReturnString.append("e+");ReturnString.append(to_string(ExpLength));
		}
		#endif
	}
	else
	{
		unsigned long long NumbersDisplayed=0,PointPos;
		if(length/3<NumberThousandPowers)
		PointPos=(length%3);
		else if((length-1)/3<NumberThousandPowers)
		PointPos=(length%3);
		else
		PointPos=length-(3*NumberThousandPowers-3);
		
		if(length>3 and !PointPos)
		PointPos+=3;
		
		for(unsigned long long i=0;i<PointPos;i++)
		{
			if(i>=length)
			break;
			ReturnString.append(to_string(numbers[i]));
		}
		for(unsigned long long i=PointPos;i<PointPos+3;i++)
		{
			if(i>=length)
			break;
			if(i==PointPos and !IsRoundDigit(i) and i)
			ReturnString.append(".");
			if(!IsRoundDigit(i))
			ReturnString.append(to_string(numbers[i]));
			else
			break;
		}
		if(((length-1)/3)<NumberThousandPowers)
		ReturnString.append(ThousandPowers[(length-1)/3]);
		else
		ReturnString.append(ThousandPowers[NumberThousandPowers-1]);
	}
	return ReturnString;
}
//Длина экспоненты равна количеству ОБЫЧНЫХ чисел и 0 в конце 

MegaInt MegaInt::MegaIntModyl()
{
	if(!negative)
	return *this;
	else
	{
		MegaInt n;
		n=*this;
		n.negative=false;
		return n;
	}
}

unsigned long long MegaInt::GetSize() const
{
	return length;
}

unsigned long long MegaInt::GetWeight() const
{
	return length*sizeof(numbers[0])+sizeof(MegaInt);
}

void MegaInt::PushBack(const short n)
{
	length++;
	short *newnumbers=new short[length];
	for(unsigned long long i=0;i<length-1;i++)
	newnumbers[i]=numbers[i];
	newnumbers[length-1]=n;
	if(numbers!=NULL)
	delete [] numbers;
	numbers=newnumbers;
}
void MegaInt::PopBack()
{
	if(length>0)
	{
		length--;
		short *newnumbers=new short[length];
		for(unsigned long long i=0;i<length;i++)
		newnumbers[i]=numbers[i];
		if(numbers!=NULL)
		delete [] numbers;
		numbers=newnumbers;
	}
	else
	*this=0;
}
void MegaInt::Remove(const unsigned long long pos)
{
	unsigned long long i=0;
	length--;
	short *newnumbers=new short[length];
	for(;i<pos+1;i++)
	newnumbers[i]=numbers[i];
	for(;i<=length;i++)
	newnumbers[i-1]=numbers[i];
	if(numbers!=NULL)
	delete [] numbers;
	numbers=newnumbers;
}

void MegaInt::Insert(const short n,const unsigned long long pos)
{
	unsigned long long i=0;
	length++;
	short *newnumbers=new short[length];
	for(;i<pos;i++)
	newnumbers[i]=numbers[i];
	newnumbers[pos]=n;
	for(i=pos+1;i<length;i++)
	newnumbers[i]=numbers[i-1];
	if(numbers!=NULL)
	delete [] numbers;
	numbers=newnumbers;
}

void MegaInt::MakeExponential(const unsigned long long ExpPos)
{
	Exponential=true;
	this->ExpPos=ExpPos;
	this->ExpLength=length-ExpPos;
	ExpUpDate();
	
	IsPrefix=false;
}

void MegaInt::MakeUnExponential()
{
	Exponential=false;
}

void MegaInt::MakePrefix()
{
	Exponential=false;
	IsPrefix=true;
}
void MegaInt::MakeUnPrefix()
{
	IsPrefix=false;
}

template <typename T>
void MegaInt::SetUpDigitRate(T n)//This is *=10
{
	if(n>=1)
	{
		unsigned long long OldLength=length;
		length+=n;
		short *newnumbers=new short[length];
		unsigned long long i=0;
		for(i=0;i<OldLength;i++)
		newnumbers[i]=this->numbers[i];
		for(i=OldLength;i<length;i++)
		newnumbers[i]=0;
		if(numbers!=NULL)
		delete [] numbers;
		numbers=newnumbers;
	}
}
/*///////////////////////////////////////////////////////////*/
///////////////////////////////////////////////////////////////
//                     Private methods
///////////////////////////////////////////////////////////////
/*///////////////////////////////////////////////////////////*/
void MegaInt::SetNewDigitRate()
{
    length++;
    short *newnumbers=new short[length];
    for(unsigned long long i=1;i<length;i++)
    newnumbers[i]=numbers[i-1];
    delete [] numbers;
    numbers=newnumbers;
}
void MegaInt::EareseDigitRate()//First rate
{
	length--;
	short *newnumbers=new short[length];
	for(unsigned long long i=1;i<=length;i++)
	newnumbers[i-1]=numbers[i];
	delete [] numbers;
	numbers=newnumbers;
}
short MegaInt::GetDigitRate(unsigned long long n,unsigned long long i)//Uses in operator '='
{
	short result=((n/PowerTen(i))%10);
    return result;
}
unsigned long long MegaInt::IntSize(unsigned long long n)//Get size to allocate the memory
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
T MegaInt::PowerTen(T n)
{
    if(n==0)
    return 1;
    else if(n==1)
    return 10;
    else
    return 10*PowerTen(n-1);
}


bool MegaInt::IsRoundDigit(const unsigned long long StartPos)
{
	bool result=true;
	for(unsigned long long i=StartPos;i<length;i++)
	if(numbers[i]!=0)
	{
		result=false;
		break;
	}
	return result;
}
unsigned long long MegaInt::NumberOfLastNulls()
{
	if (!length)
		return 0;

	unsigned long long nulls=0;
	for(unsigned long long i=length-1;i!=0 or i!=0xFFFFFFFFFFFFFFFF;i--)
	{
		if(numbers[i]!=0)
		break;
		else
		nulls++;	
	}
	return nulls;
}

void MegaInt::ExpUpDate()
{
	if (!length)
		return;

	unsigned long long _ExpPos=0;
	for(unsigned long long i=length-1;i>=0;i++)
	{
		if(numbers[i]==0)
		{
			if(i>ExpLength)
			_ExpPos++;
			else
			break;
		}
		else
		break;
	}
	if(ExpLength<=length)
	ExpLength+=_ExpPos;
	else
	ExpLength=_ExpPos;
	
	if(*this==0)
	{
	    Exponential=false;
	    IsPrefix=false;
	}
}

void MegaInt::ExpRound(const unsigned long long NumbersAreVisible)
{
	this->NumbersAreVisible=NumbersAreVisible;
}
#endif
