#ifndef MEGAINT_METHODS_H
#define MEGAINT_METHODS_H
#include <cstddef>
#include <iostream>
#include <windows.h>
MegaInt MegaInt::CutMegaIntNumber(MegaInt &n,const unsigned long long newlength,const short pos)
{
	//pos=[1;17]
	MegaInt DigitNumber=((MegaInt)(newlength)-1)* (MegaInt&)((MegaInt)MAX_LIMIT_RATE_MEGAINT)+pos;
	MegaInt result=0;
	
	if(DigitNumber> (MegaInt&)n.DigitNumberMegaInt())
	{
		throw MegaInt::MegaIntException("Digit number is very big to cut into <MegaInt> object");
		return result;
	}
	if(DigitNumber==n.DigitNumberMegaInt())
	{
		result=n;
		return result;
	}
	
	result=n;
	while(result.length>newlength+2)
	{
		result/=MAX_LIMIT_MEGAINT;
	}
	while(result.DigitNumberMegaInt()>DigitNumber)
	{
		result/=10;
	}
	return result;
}
char* MegaInt::CutMegaIntNumberInCharPointer
(MegaInt &n,const unsigned long long newlength,const short pos,const bool GetLeftHalf)
{
	MegaInt DigitNumber=((MegaInt)(newlength)-1)*(MegaInt&)((MegaInt)MAX_LIMIT_RATE_MEGAINT)+pos;
	if(pos==0 and newlength==1)
	{
		n.GetCharArrayRecord();
	}
	if(DigitNumber> (MegaInt&)n.DigitNumberMegaInt())
	{
		throw MegaInt::MegaIntException("Digit number is very big to cut into <char*&> object");
		return n.GetCharArrayRecord();
	}
	char* Pointer=n.GetCharArrayRecord();
	char* CurrPointer=Pointer;
	
	#ifdef DIGIT_SELECTION
	bool cell=false;
	for(char* iterator=Pointer;iterator!=CurrPointer+1+pos;++iterator)
	{
		if(*iterator=='|' and (*iterator)+1!='\0')
		{
			cell=true;
			break;
		}
	}
	if(cell)
	++CurrPointer;
	#endif
	CurrPointer+=pos;
	
	for(unsigned long long i=1;i<newlength;++i)
	{
		CurrPointer+=MAX_LIMIT_RATE_MEGAINT;
		#ifdef DIGIT_SELECTION
		++CurrPointer;
		#endif
	}
	char* result= (char*)"";
	
	if(GetLeftHalf)
	{
		for(char* iterator=Pointer;iterator!=CurrPointer;++iterator)
		CharArrayPushBack(result,*iterator);
		CharArrayPushBack(result,'\0');
	}
	else
	{
		for(char* iterator=CurrPointer;*iterator!='\0';++iterator)
		CharArrayPushBack(result,*iterator);
		CharArrayPushBack(result,'\0');
	}

	
	CurrPointer=NULL;
	delete [] Pointer;
	return result;
}




MegaInt MegaInt::AddNulls(MegaInt &n,const unsigned long long length,const short pos)
{
	//pos=[0;17]
	MegaInt DigitNumber=((MegaInt)((unsigned long long)length))
	* (MegaInt&)(MegaInt)((unsigned long long)MAX_LIMIT_RATE_MEGAINT)+pos;
	MegaInt result=n;
	
	if(n.DigitNumberMegaInt()+DigitNumber>= (MegaInt&)((MegaInt)(unsigned long long)MAX_UNSIGNED_LONG_LONG*17))
	{
		throw MegaInt::MegaIntException("<MegaInt> object will very long");
		return result=(long long)0;
	}
	if(DigitNumber<=0)
	{
		return result;
	}
	for(unsigned long long i=0;i<length;++i)
	result*=(unsigned long long)MAX_LIMIT_MEGAINT;
	for(short i=0;i<pos;++i)
	result*=10;
	return result;
}



MegaInt* MegaInt::GetPointer()
{
	return this;
}
unsigned long long MegaInt::GetSize()const
{
	return length;
}
MegaInt MegaInt::DigitNumberMegaInt()
{
	return ((MegaInt)(length)-1)* (MegaInt&)((MegaInt)MAX_LIMIT_RATE_MEGAINT)+IntSize(numbers[0]);
}
unsigned long long MegaInt::DigitNumber() const
{
	if(length<=(unsigned long long)MAX_UNSIGNED_LONG_LONG/MAX_LIMIT_RATE_MEGAINT)
	return length*MAX_LIMIT_RATE_MEGAINT;
	else
	{
		throw MegaInt::MegaIntException("Length is very long to show digit number in <unsigned long int> type");
		return 0;
	}
}
MegaInt MegaInt::MegaIntModyl() const
{
	MegaInt n=*this;
	if(negative)
	n.negative=false;
	return n;
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
char*& MegaInt::GetCharArrayRecord()const
{
	char* returnarray= (char*)"-\0";
	(negative) ? returnarray=(char*)"-\0" : returnarray= (char*)"\0";
	
	for(unsigned long long i=0;i<length;++i)
	{
		if((numbers[i]<=MAX_LIMIT_MEGAINT-1)and(i))
		{
			char* nulls=(char*)"";
			for(short j=0;j<MAX_LIMIT_RATE_MEGAINT-IntSize(numbers[i]);++j)
			CharArrayPushBack(nulls,'0');
			
			if(returnarray[0] == '\0')
			returnarray=nulls;
			else
			returnarray=CharConcat(returnarray,nulls);
		}
		if(returnarray[0] == '\0')
		returnarray=to_char_pointer(numbers[i]);
		else
		returnarray=CharConcat(returnarray,to_char_pointer(numbers[i]));
		#ifdef DIGIT_SELECTION
		CharArrayPushBack(returnarray,'|');
		#endif
	}
	CharArrayPushBack(returnarray,'\0');
	return returnarray;
}
MegaInt MegaInt::CharPointerToMegaInt(const char* InputString)
{
	MegaInt result=0;
	char *array= (char*)"";
	unsigned long long newlength=0;
	for(unsigned long long i=0;i<GetCharArrayLength(InputString);++i)
	{
		if((InputString[i]>='0' and InputString[i]<='9') or ((!newlength)and(InputString[i]=='-')))
		{
			if(InputString[i]=='0')
			{
				if(newlength>2)
				{
					CharArrayPushBack(array,'0');
					++newlength;
				}
				else
				{
					if((newlength-(array[0]=='-'))>=1)
					{
						CharArrayPushBack(array,'0');
						++newlength;
					}	
				}
			}
			else
			{
				CharArrayPushBack(array,InputString[i]);
				++newlength;
			}
		}
	}
	unsigned long long lastlength=newlength;
	if(array[0]=='-')
	{
		result.negative=true;
		--lastlength;
		char *newarray=new char[lastlength+1];
		for(unsigned long long i=0;i<lastlength;++i)
		newarray[i]=array[i+1];
		newarray[lastlength]='\0';
		
		delete[]array;
		array=newarray;
	}
	if(array=="")
	{
		result.negative=false;
		return result;
	}
	newlength=(unsigned long long)lastlength/(unsigned long long)(MAX_LIMIT_RATE_MEGAINT)
	+bool(bool((lastlength%(MAX_LIMIT_RATE_MEGAINT))!=0)+bool(lastlength<MAX_LIMIT_RATE_MEGAINT));
	if(!(newlength))
	return result;
	else
	{
		unsigned long long *newnumbers=new unsigned long long[newlength-(array[0]=='-')];
		for(unsigned long long i=0;i<newlength;++i)
		{
			unsigned long long curr=0;
			for(unsigned long long j=0;j<MAX_LIMIT_RATE_MEGAINT;++j)
			{
				if((lastlength-i*MAX_LIMIT_RATE_MEGAINT-j+i)==MAX_UNSIGNED_LONG_LONG)
				break;
				curr+=(unsigned long long)((short)(array[lastlength-i*MAX_LIMIT_RATE_MEGAINT-j+i]-'0'))*PowerTen(j);
			}
			newnumbers[newlength-i-1]=curr;
		}
		result.length=newlength;
		delete [] result.numbers;
		result.numbers=newnumbers;
		return result;
	}
}
MegaInt MegaInt::StringToMegaInt(const std::string &InputString)
{
	char* array=new char[InputString.size()+1];
	for(unsigned long long i=0;i<InputString.size();++i)
	array[i]=InputString[i];
	array[InputString.size()]='\0';
	
	return CharPointerToMegaInt(array);
}
unsigned long long MegaInt::GetConstructedTimes()
{
	return MegaInt::constructed;
}
unsigned long long MegaInt::GetDestructedTimes()
{
	return MegaInt::destructed;
}
#endif
