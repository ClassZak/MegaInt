#ifndef MEGAINT_OPERATORS_H
#define MEGAINT_OPERATORS_H
#include <iostream>
#include <string>
#include "MegaInt_Definetion.h"
MegaInt& MegaInt::operator=(const MegaInt &other)
{
	if (numbers != nullptr)
	{
		delete [] numbers;
		numbers = nullptr;
	}

	
	this->negative=other.negative;
	this->length=other.length;
	numbers=new unsigned long long[length];
	for(unsigned long long i=0;i<length;i++)
	this->numbers[i]=other.numbers[i];
	
	return *this;
}
MegaInt& MegaInt::operator=(const char* InputString)
{
	*this=CharPointerToMegaInt(InputString);
	return *this;
}

MegaInt& MegaInt::operator=(long long n)
{
	long long nmodyl=modyl(n);
	if (numbers != nullptr)
	{
		delete [] numbers;
		numbers = nullptr;
	}
	length=1;
	(n<0) ? negative=true : negative=false;
	numbers=new unsigned long long[length];
	numbers[0]=nmodyl;
	if(nmodyl>=MAX_LIMIT_MEGAINT)
	{
		++length;
		unsigned long long *newnumbers=new unsigned long long[length];
		newnumbers[1]=0;
		newnumbers[1]=CutNumber((unsigned long long)nmodyl,MAX_LIMIT_RATE_MEGAINT);
		newnumbers[0]=(nmodyl)/PowerTen(MAX_LIMIT_RATE_MEGAINT);
		delete [] numbers;
		numbers=newnumbers;
	}
	if(numbers[0]==0 and length==1)
	negative=false;
	return *this;
}


MegaInt MegaInt::operator+()
{
	MegaInt result=*this;
	result.negative=false;
	if(result.numbers[0]==0 and result.length==1)
	result.negative=false;
	return result;
}
MegaInt MegaInt::operator+(MegaInt& other)
{
	if(*this==0)
	{
		MegaInt result(other);
		if(result.numbers[0]==0 and result.length==1)
		result.negative=false;
		return result;
	}
	if(other==0)
	{
		MegaInt result(*this);
		if(result.numbers[0]==0 and result.length==1)
		result.negative=false;
		return result;
	}
	
	if(this->MegaIntModyl()<(MegaInt&)other.MegaIntModyl())
	{
		return other+*this;
	}
	if((negative==other.negative))
	{
		MegaInt result=*this;
		for(unsigned long long i=0;i<other.length;++i)
		{
			result.numbers[length-i-1]+=other.numbers[other.length-i-1];
			
			if(i<other.length-1)
			if(result.numbers[length-i-1]>=MAX_LIMIT_MEGAINT)
			{
				result.numbers[length-i-2]+=
				(result.numbers[length-i-1]/((unsigned long long)MAX_LIMIT_MEGAINT));
				
				result.numbers[length-i-1]=
				result.numbers[length-i-1]-
				(result.numbers[length-i-1]/
				((unsigned long long)MAX_LIMIT_MEGAINT))*(unsigned long long)MAX_LIMIT_MEGAINT;
			}
		}
		
		if(result.numbers[0]>=MAX_LIMIT_MEGAINT)
		{
			unsigned long long *newnumbers=new unsigned long long[length+1];
			newnumbers[0]=result.numbers[0]/(MAX_LIMIT_MEGAINT);
			newnumbers[1]=result.numbers[0]%(MAX_LIMIT_MEGAINT);
			if(length>=2)
			for(unsigned long long i=1;i<length;++i)
			newnumbers[1+i]=result.numbers[i];
			
			++result.length;
			
			if(result.numbers!=nullptr)
			delete [] result.numbers;
			result.numbers=newnumbers;
		}
		if(result.numbers[0]==0 and result.length==1)
		result.negative=false;
		return result;
	}
	else
	{
		MegaInt result=*this;
		for(unsigned long long i=0;i<other.length;++i)
		{
			if(i+1==length)
			break;
			if(result.numbers[length-i-1]==MAX_UNSIGNED_LONG_LONG)
			{
				--result.numbers[length-i-2];
				result.numbers[length-i-1]=MAX_LIMIT_MEGAINT-1;
			}
			
			if(result.numbers[length-i-1]>=other.numbers[other.length-i-1])
			result.numbers[length-i-1]-=other.numbers[other.length-i-1];
			else
			{
				result.numbers[length-i-1]=
				MAX_LIMIT_MEGAINT-(other.numbers[other.length-i-1]-result.numbers[length-i-1]);
				--result.numbers[length-i-2];
			}
		}
		if(length==other.length)
		result.numbers[0]-=other.numbers[0];
		
		if(result.length>1)
		{
			unsigned long long nulls=0;
			for(unsigned long long i=0;i<result.length-1;++i)
			{
				if(result.numbers[i])
				break;
				else
				++nulls;
			}
			
			if(nulls)
			{
				unsigned long long *newnumbers=new unsigned long long[result.length-nulls];
				for(unsigned long long i=nulls;i<result.length;++i)
				newnumbers[i-nulls]=result.numbers[i];
				
				result.length-=nulls;
				
				if(result.numbers!=nullptr)
				delete [] result.numbers;
				result.numbers=newnumbers;
			}
		}
		
		if(result.numbers[0]==0 and result.length==1)
		result.negative=false;
		if(result.numbers[0]==0 and result.length==1)
		result.negative=false;
		return result;
	}
}

MegaInt MegaInt::operator-(MegaInt& other)
{
	return *this+ (MegaInt&)other.operator-();
}

MegaInt MegaInt::operator+(long long n)
{
	if(*this==0)
	{
		MegaInt result(n);
		if(result.numbers[0]==0 and result.length==1)
		result.negative=false;
		return result;
	}
	if(n==0)
	{
		MegaInt result(*this);
		if(result.numbers[0]==0 and result.length==1)
		result.negative=false;
		return result;
	}
	
	if(n>=MAX_LIMIT_MEGAINT)
	return *this+ (MegaInt&)(MegaInt)n;
	else
	{
		if(this->MegaIntModyl()<modyl(n))
		{
			MegaInt other(n);
			return other+*this;
		}
		if(negative==(n<0))
		{
			MegaInt result=*this;
			
			result.numbers[length-1]+=modyl(n);
			for(unsigned long long i=0;i<result.length-1;++i)
			{
				if(result.numbers[length-i-1]>=MAX_LIMIT_MEGAINT)
				{
					result.numbers[length-i-2]+=(result.numbers[length-i-1]/((unsigned long long)MAX_LIMIT_MEGAINT));
					result.numbers[length-i-1]=
					result.numbers[length-i-1]-(result.numbers[length-i-1]/((unsigned long long)MAX_LIMIT_MEGAINT))
					*MAX_LIMIT_MEGAINT;
				}
			}
			
			if(result.numbers[0]>=MAX_LIMIT_MEGAINT)
			{
				unsigned long long *newnumbers=new unsigned long long[length+1];
				newnumbers[0]=result.numbers[0]/(MAX_LIMIT_MEGAINT);
				newnumbers[1]=result.numbers[0]%(MAX_LIMIT_MEGAINT);
				if(length>=2)
					for(unsigned long long i=1;i<length;++i)
						newnumbers[1+i]=result.numbers[i];
				
				++result.length;
				
				if(result.numbers!=nullptr)
					delete [] result.numbers;

				result.numbers=newnumbers;
			}
			if(result.numbers[0]==0 and result.length==1)
			result.negative=false;
			return result;
		}
		else
		{
			MegaInt result=*this;
			
			if(result.numbers[length-1]>=modyl(n))
			result.numbers[length-1]-=modyl(n);
			else
			{
				result.numbers[length-1]=
				MAX_LIMIT_MEGAINT-(modyl(n)-result.numbers[length-1]);
				if(length>1)
				--result.numbers[length-2];
				else
				result.negative=!result.negative;
			}
			
			for(unsigned long long i=0;i<length-1;++i)
			{
				if(result.numbers[length-i-1]==MAX_UNSIGNED_LONG_LONG)
				{
					--result.numbers[length-i-2];
					if(result.numbers[length-i-1]==MAX_UNSIGNED_LONG_LONG)
					result.numbers[length-i-1]=MAX_LIMIT_MEGAINT-1;
				}
			}
			if(result.length>1)
			{
				unsigned long long nulls=0;
				for(unsigned long long i=0;i<result.length-1;++i)
				{
					if(result.numbers[i])
					break;
					else
					++nulls;
				}
				
				if(nulls)
				{
					unsigned long long *newnumbers=new unsigned long long[result.length-nulls];
					for(unsigned long long i=nulls;i<result.length;++i)
					newnumbers[i-nulls]=result.numbers[i];
					
					result.length-=nulls;
					
					if(result.numbers!=nullptr)
					delete [] result.numbers;
					result.numbers=newnumbers;
				}
			}
			if(result.numbers[0]==0 and result.length==1)
				result.negative=false;

			return result;
		}	
	}
}

MegaInt MegaInt::operator-(long long n)
{
	return *this+(-n);
}

MegaInt MegaInt::operator*(MegaInt &other)
{
	MegaInt result=0;
	if(*this==0 or other==0)
	return result;
	
	if(*this==-1 or *this==1)
	{
		result=other;
		result.negative=(negative!=other.negative);
		return result;
	}
	if(other==-1 or other==1)
	{
		result=*this;
		result.negative=(negative!=other.negative);
		return result;
	}
	
	if(MegaIntModyl()<(MegaInt&)other.MegaIntModyl())
	{
		return other*(*this);
	}
	for(unsigned long long i=0;i<other.length;++i)
	{
		MegaInt curr=0;
		for(short j=0;j<IntSize(other.numbers[other.length-i-1]);++j)
		{
			MegaInt curr2=0;
			short currnumber;
			currnumber=(short)(unsigned long long)(((other.numbers[other.length-i-1]/PowerTen(j))%10));
			for(short k=0;k<currnumber;++k)
			curr2=curr2+*this;
			curr2*=PowerTen(j);
			
			if(currnumber!=0)
			{
				curr=curr+curr2;
			}
		}
		
		for(unsigned long long j=1;j<=i;++j)
		{
			curr*=(unsigned long long)MAX_LIMIT_MEGAINT;
		}
		result=result+curr;
	}
	result.negative=(negative!=other.negative);
	if(result.numbers[0]==0 and result.length==1)
	result.negative=false;
	return result;
}

MegaInt MegaInt::operator*(long long n)
{
	long long nmodyl=modyl(n);
	MegaInt result=0;
	if(*this==0 or n==0)
	return result;
	
	if(*this==-1 or *this==1)
	{
		result=nmodyl;
		result.negative=(negative!=(n<0));
		return result;
	}
	if(nmodyl==1)
	{
		result=*this;
		result.negative=(negative!=(n<0));
		return result;
	}
	
	if((MegaIntModyl()<nmodyl)or(n>=MAX_LIMIT_MEGAINT))
	{
		MegaInt other(n);
		return other*(*this);
	}
	
	for(short j=0;j<IntSize(nmodyl);++j)
	{
		MegaInt curr2=0;
		short currnumber;
		currnumber=(short)(unsigned long long)(((nmodyl/PowerTen(j))%10));
		for(short k=0;k<currnumber;++k)
		curr2=curr2+*this;
		curr2*=PowerTen(j);
		
		if(currnumber)
		result=result+curr2;
	}

	result.negative=(negative!=(n<0));
	if(result.numbers[0]==0 and result.length==1)
	result.negative=false;
	return result;
}
MegaInt& MegaInt::operator*=(MegaInt &other)
{
	*this=*this*(MegaInt&)other;
	return *this;
}



MegaInt& MegaInt::operator*=(long long n)
{
	if(*this==0)
	return *this;
	else
	if((IsRound(n))and(n!=0))
	{
		if(n==MAX_LIMIT_MEGAINT)
		{
			++length;
			unsigned long long *newnumbers=new unsigned long long[length];
			for(unsigned long long i=0;i<length-1;i++)
			newnumbers[i]=numbers[i];
			newnumbers[length-1]=0;
			
			
			if(numbers!=nullptr)
			delete [] numbers;
			numbers=new unsigned long long[length];
			for(unsigned long long i=0;i<length;i++)
			numbers[i]=newnumbers[i];
			
			if(newnumbers!=nullptr)
			delete [] newnumbers;
			newnumbers=nullptr;
		}
		else
		{
			for(short i=0;i<IntSize(n)-1;++i)
			{
				
				for(unsigned long long j=0;j<length;j++)
				{
					numbers[j]*=10;
				}
				for(unsigned long long j=0;j<length-1;j++)
				{
					
					if(numbers[length-j-1]>=MAX_LIMIT_MEGAINT)
					{
						numbers[length-j-2]+=
						(numbers[length-j-1]/((unsigned long long)MAX_LIMIT_MEGAINT));
						
						numbers[length-j-1]=
						numbers[length-j-1]-
						(numbers[length-j-1]/((unsigned long long)MAX_LIMIT_MEGAINT))*MAX_LIMIT_MEGAINT;
					}
				}
				if(numbers[0]>=MAX_LIMIT_MEGAINT)
				{
					unsigned long long *newnumbers=new unsigned long long[length+1];
					newnumbers[0]=numbers[0]/(MAX_LIMIT_MEGAINT);
					newnumbers[1]=numbers[0]%(MAX_LIMIT_MEGAINT);
					if(length>=2)
					for(unsigned long long j=1;j<length;++j)
					newnumbers[1+j]=numbers[j];
					
					++length;
					
					if(numbers!=nullptr)
					delete [] numbers;
					numbers=new unsigned long long[length];
					for(unsigned long long i=0;i<length;++i)
					numbers[i]=newnumbers[i];
					if(newnumbers!=nullptr)
					delete [] newnumbers;
					newnumbers=nullptr;
				}
			}
		}
		if((n<0)and(!(length==1 and numbers[0]==0)))
		negative=true;
	}
	else
	{
		if(n<MAX_UNSIGNED_LONG_LONG)
		*this=*this*n;
		else
		*this=*this*(MegaInt&)(MegaInt)n;
	}
	return *this;
}

unsigned long long MegaInt::operator[](unsigned long long n)
{
	return numbers[n];
}

bool MegaInt::operator==(long long n)
{
	if (n >= MAX_LIMIT_MEGAINT)
	{
		MegaInt other = n;
		return *this == other;
	}
	else
	{
		if (length > 1)
			return false;
		else
			return (numbers[0] == modyl(n)) * (negative == (n < 0));
	}
}
bool MegaInt::operator==(const MegaInt &other)
{
	bool equalModyl=true;
	bool equalSign =false;
	
	if(negative==other.negative)
	equalSign=true;
	if(length==other.length)
	{
		for(unsigned long long i=0;i<length;i++)
		{
			if(numbers[i]!=other.numbers[i])
			{
				equalModyl=false;
				break;
			}
		}
	}
	else
	equalModyl=false;
	return equalModyl*equalSign;
}

bool MegaInt::operator!=(long long n)
{
	if (n>=MAX_LIMIT_MEGAINT)
	{
		MegaInt other=n;
		return *this!=other;		
	}
	else
	{
		if(length>1)
		return true;
		else
		return (numbers[0]!=modyl(n))+(negative!=(n<0));
	}
}
bool MegaInt::operator!=(MegaInt &other)
{
	bool equalModyl=true;
	bool equalSign =false;
	if(negative==other.negative)
	equalSign=true;
	if(length==other.length)
	{
		for(unsigned long long i=0;i<length;i++)
		{
			if(numbers[i]!=other.numbers[i])
			{
				equalModyl=false;
				break;
			}
		}
	}
	else
	equalModyl=false;
	return !(equalModyl*equalSign);
}
bool MegaInt::operator>(long long n)
{
	if (n>=MAX_LIMIT_MEGAINT)
	{
		MegaInt other=n;
		return *this>other;		
	}
	else
	{
		if(length>1)
		return !negative;
		else
		{
			if(n==0)
			return !negative-(numbers[0]==0);
			
			if((!negative)and(n<0))
			return true;
			else if(negative and (n>0))
			return false;
			
			if(negative==(n<0))
			{
				if(negative)
				return (numbers[0]<modyl(n));
				else
				return (numbers[0]>modyl(n));
			}
		}
	}
}
bool MegaInt::operator>(MegaInt& other)
{
	bool biggerModyl;

	if (length > other.length)
		biggerModyl = true;
	else if (length < other.length)
		biggerModyl = false;
	else if (length == other.length)
	{
		biggerModyl = true;
		for (unsigned long long i = 0; i < length; i++)
		{
			if (numbers[i] < other.numbers[i])
			{
				biggerModyl = false;
				break;
			}
			if (numbers[i] > other.numbers[i])
			{
				biggerModyl = true;
				break;
			}
		}
		if (MegaIntModyl() == other.MegaIntModyl())
		{
			biggerModyl = false;
		}
	}

	if (negative != other.negative)
	{
		if (negative)
			biggerModyl = false;
		if (!negative and other.negative)
			biggerModyl = true;
	}
	else
	{
		if (negative and !(*this == other))
			biggerModyl = !biggerModyl;
	}

	return biggerModyl;
}
bool MegaInt::operator<(long long n)
{
	if (n>=MAX_LIMIT_MEGAINT)
	{
		MegaInt other=n;
		return *this<other;		
	}
	else
	{
		if(length>1)
		return negative;
		else
		{
			if(n==0)
			return negative and(numbers[0]!=0);
			
			if((!negative)and(n<0))
			return false;
			else if(negative and (n>0))
			return true;
			
			if(negative==(n<0))
			{
				if(negative)
				return (numbers[0]>modyl(n));
				else
				return (numbers[0]<modyl(n));
			}
		}
	}
}
bool MegaInt::operator<( MegaInt &other)
{
	bool smallerModyl=true;
	
	if(length>other.length)
	smallerModyl=false;
	else if(length<other.length)
	smallerModyl=true;
	else if(length==other.length)
	{
		smallerModyl=true;
		for(unsigned long long i=0;i<length;i++)
		{
			if(numbers[i]>other.numbers[i])
			{
				smallerModyl=false;
				break;
			}
			if(numbers[i]<other.numbers[i])
			{
				smallerModyl=true;
				break;
			}
		}
		if(MegaIntModyl()==other.MegaIntModyl())
		{
			smallerModyl=false;
		}
	}
	
	if(negative!=other.negative)
	{
		if(negative)
		smallerModyl=true;
		if(!negative and other.negative)
		smallerModyl=false;
	}
	else
	{
		if(negative and !(*this==other))
		smallerModyl=!smallerModyl;
	}
	return smallerModyl;
}
bool MegaInt::operator>=(long long n)
{
	if (n>=MAX_LIMIT_MEGAINT)
	{
		MegaInt other=n;
		return *this>=other;	
	}
	else
	{
		return (*this>n) + (*this==n);
	}
}
bool MegaInt::operator>=(MegaInt &other)
{
	bool biggerModyl=false;
	bool biggerSign =false;
	bool equal;
	
	if((length!=other.length)or(negative!=other.negative))
	equal=false;
	else
	{
		equal=true;
		for(unsigned long long i=0;i<length;i++)
		{
			if(numbers[i]!=other.numbers[i])
			{
				equal=false;
				break;
			}
		}
	}
	
	if(!negative and other.negative)
	biggerSign=true;
	
	if(length>other.length)
	biggerModyl=true;
	else if(length==other.length)
	{
		biggerModyl=true;
		for(unsigned long long i=0;i<length;i++)
		{
			if(numbers[i]<other.numbers[i])
			{
				biggerModyl=false;
				break;
			}
			if(numbers[i]>other.numbers[i])
			{
				biggerModyl=true;
				break;
			}
		}
		if(MegaIntModyl()==other.MegaIntModyl())
		{
			biggerModyl=false;
		}
	}
	
	if(negative!=other.negative)
	{
		if(negative)
		biggerModyl=false;
		if(!negative and other.negative)
		biggerModyl=true;
	}
	else
	{
		if(negative and !equal)
		biggerModyl=!biggerModyl;
	}
	
	return biggerModyl+equal;
}/*
bool MegaInt::operator>=(MegaInt other)
{
	bool biggerModyl=false;
	bool biggerSign =false;
	bool equal;
	
	if((length!=other.length)or(negative!=other.negative))
	equal=false;
	else
	{
		equal=true;
		for(unsigned long long i=0;i<length;i++)
		{
			if(numbers[i]!=other.numbers[i])
			{
				equal=false;
				break;
			}
		}
	}
	
	if(!negative and other.negative)
	biggerSign=true;
	
	if(length>other.length)
	biggerModyl=true;
	else if(length==other.length)
	{
		biggerModyl=true;
		for(unsigned long long i=0;i<length;i++)
		{
			if(numbers[i]<other.numbers[i])
			{
				biggerModyl=false;
				break;
			}
			if(numbers[i]>other.numbers[i])
			{
				biggerModyl=true;
				break;
			}
		}
		if(MegaIntModyl()==other.MegaIntModyl())
		{
			biggerModyl=false;
		}
	}
	
	if(negative!=other.negative)
	{
		if(negative)
		biggerModyl=false;
		if(!negative and other.negative)
		biggerModyl=true;
	}
	else
	{
		if(negative and !equal)
		biggerModyl=!biggerModyl;
	}
	
	return biggerModyl+equal;
}*/
bool MegaInt::operator<=(long long n)
{
	if (n>=MAX_LIMIT_MEGAINT)
	{
		MegaInt other=n;
		return *this<=other;		
	}
	else
	{
		return (*this<n) + (*this==n);
	}
}
bool MegaInt::operator<=(MegaInt &other)
{
	bool smallerModyl=false;
	bool smallerSign =false;
	bool equal=false;
	
	if((length!=other.length)or(negative!=other.negative))
	{
	}
	else
	{
		equal=true;
		for(unsigned long long i=0;i<length;i++)
		{
			if(numbers[i]!=other.numbers[i])
			{
				equal=false;
				break;
			}
		}
	}
	
	if(length<other.length)
	smallerModyl=true;
	else if(length==other.length)
	{
		smallerModyl=true;
		for(unsigned long long i=0;i<length;i++)
		{
			if(numbers[i]>other.numbers[i])
			{
				smallerModyl=false;
				break;
			}
			if(numbers[i]<other.numbers[i])
			{
				smallerModyl=true;
				break;
			}
		}
		if(MegaIntModyl()==other.MegaIntModyl())
		{
			smallerModyl=false;
		}
	}
	
	if(negative!=other.negative)
	{
		if(negative)
		smallerModyl=true;
		if(!negative and other.negative)
		smallerModyl=false;
	}
	else
	{
		if(negative and !equal)
		smallerModyl=!smallerModyl;
	}
	
	return smallerModyl+equal;
}
MegaInt MegaInt::operator --()
{
	if(negative)
	{
		++numbers[length-1];
		for(unsigned long long i=0;i<length-1;++i)
		if(numbers[length-1-i]>=MAX_LIMIT_MEGAINT)
		{
			numbers[length-2-i]+=numbers[length-1-i]/MAX_LIMIT_MEGAINT;
			numbers[length-1-i]%=MAX_LIMIT_MEGAINT;
		}
		if(numbers[0]>=MAX_LIMIT_MEGAINT)
		{
			unsigned long long *newnumbers=new unsigned long long[length+1];
			newnumbers[0]=numbers[0]/(MAX_LIMIT_MEGAINT);
			newnumbers[1]=numbers[0]%(MAX_LIMIT_MEGAINT);
			if(length>=2)
			for(unsigned long long i=1;i<length;++i)
			newnumbers[1+i]=numbers[i];
			
			++length;
			
			if(numbers!=nullptr)
			delete [] numbers;
			numbers=newnumbers;
		}		
	}
	else
	{
		--numbers[length-1];
		for(unsigned long long i=0;i<length-1;++i)
		if(numbers[length-1-i]>=MAX_UNSIGNED_LONG_LONG)
		{
			--numbers[length-2-i];
			numbers[length-1-i]=MAX_LIMIT_MEGAINT-1;
		}
		if(length>1)
		{
			unsigned long long nulls=0;
			for(unsigned long long i=0;i<length-1;++i)
			{
				if(numbers[i])
				break;
				else
				++nulls;
			}
			if(nulls)
			{
				unsigned long long *newnumbers=new unsigned long long[length-nulls];
				for(unsigned long long i=nulls;i<length;++i)
				newnumbers[i-nulls]=numbers[i];
				
				length-=nulls;
				
				if(numbers!=nullptr)
				delete [] numbers;
				numbers=newnumbers;
			}
		}
		if(numbers[0]==0 and length==1)
		negative=false;
		if(numbers[0]==MAX_UNSIGNED_LONG_LONG and length==1)
		{
			numbers[0]=1;
			negative=true;			
		}
	}
	return *this;
}
MegaInt MegaInt::operator --(int value)
{
	MegaInt old=*this;
	if(negative)
	{
		++numbers[length-1];
		for(unsigned long long i=0;i<length-1;++i)
		if(numbers[length-1-i]>=MAX_LIMIT_MEGAINT)
		{
			numbers[length-2-i]+=numbers[length-1-i]/MAX_LIMIT_MEGAINT;
			numbers[length-1-i]%=MAX_LIMIT_MEGAINT;
		}
		if(numbers[0]>=MAX_LIMIT_MEGAINT)
		{
			unsigned long long *newnumbers=new unsigned long long[length+1];
			newnumbers[0]=numbers[0]/(MAX_LIMIT_MEGAINT);
			newnumbers[1]=numbers[0]%(MAX_LIMIT_MEGAINT);
			if(length>=2)
			for(unsigned long long i=1;i<length;++i)
			newnumbers[1+i]=numbers[i];
			
			++length;
			
			if(numbers!=nullptr)
			delete [] numbers;
			numbers=newnumbers;
		}		
	}
	else
	{
		--numbers[length-1];
		for(unsigned long long i=0;i<length-1;++i)
		if(numbers[length-1-i]>=MAX_UNSIGNED_LONG_LONG)
		{
			--numbers[length-2-i];
			numbers[length-1-i]=MAX_LIMIT_MEGAINT-1;
		}
		if(length>1)
		{
			unsigned long long nulls=0;
			for(unsigned long long i=0;i<length-1;++i)
			{
				if(numbers[i])
				break;
				else
				++nulls;
			}
			if(nulls)
			{
				unsigned long long *newnumbers=new unsigned long long[length-nulls];
				for(unsigned long long i=nulls;i<length;++i)
				newnumbers[i-nulls]=numbers[i];
				
				length-=nulls;
				
				if(numbers!=nullptr)
				delete [] numbers;
				numbers=newnumbers;
			}
		}
		if(numbers[0]==0 and length==1)
		negative=false;
		if(numbers[0]==MAX_UNSIGNED_LONG_LONG and length==1)
		{
			numbers[0]=1;
			negative=true;			
		}
	}
	return old;
}
MegaInt MegaInt::operator ++(int value)
{
	MegaInt old=*this;
	if(!negative)
	{
		++numbers[length-1];
		for(unsigned long long i=0;i<length-1;++i)
		if(numbers[length-1-i]>=MAX_LIMIT_MEGAINT)
		{
			numbers[length-2-i]+=numbers[length-1-i]/MAX_LIMIT_MEGAINT;
			numbers[length-1-i]%=MAX_LIMIT_MEGAINT;
		}
		if(numbers[0]>=MAX_LIMIT_MEGAINT)
		{
			unsigned long long *newnumbers=new unsigned long long[length+1];
			newnumbers[0]=numbers[0]/(MAX_LIMIT_MEGAINT);
			newnumbers[1]=numbers[0]%(MAX_LIMIT_MEGAINT);
			if(length>=2)
			for(unsigned long long i=1;i<length;++i)
			newnumbers[1+i]=numbers[i];
			
			++length;
			
			if(numbers!=nullptr)
			delete [] numbers;
			numbers=newnumbers;
		}		
	}
	else
	{
		--numbers[length-1];
		for(unsigned long long i=0;i<length-1;++i)
		if(numbers[length-1-i]>=MAX_UNSIGNED_LONG_LONG)
		{
			--numbers[length-2-i];
			numbers[length-1-i]=MAX_LIMIT_MEGAINT-1;
		}
		if(length>1)
		{
			unsigned long long nulls=0;
			for(unsigned long long i=0;i<length-1;++i)
			{
				if(numbers[i])
				break;
				else
				++nulls;
			}
			if(nulls)
			{
				unsigned long long *newnumbers=new unsigned long long[length-nulls];
				for(unsigned long long i=nulls;i<length;++i)
				newnumbers[i-nulls]=numbers[i];
				
				length-=nulls;
				
				if(numbers!=nullptr)
				delete [] numbers;
				numbers=newnumbers;
			}
		}
		if(numbers[0]==0 and length==1)
		negative=false;
		if(numbers[0]==MAX_UNSIGNED_LONG_LONG and length==1)
		{
			numbers[0]=1;
			negative=true;			
		}
	}
	return old;
}
MegaInt MegaInt::operator ++()
{
	if(!negative)
	{
		++numbers[length-1];
		for(unsigned long long i=0;i<length-1;++i)
		if(numbers[length-1-i]>=MAX_LIMIT_MEGAINT)
		{
			numbers[length-2-i]+=numbers[length-1-i]/MAX_LIMIT_MEGAINT;
			numbers[length-1-i]%=MAX_LIMIT_MEGAINT;
		}
		if(numbers[0]>=MAX_LIMIT_MEGAINT)
		{
			unsigned long long *newnumbers=new unsigned long long[length+1];
			newnumbers[0]=numbers[0]/(MAX_LIMIT_MEGAINT);
			newnumbers[1]=numbers[0]%(MAX_LIMIT_MEGAINT);
			if(length>=2)
			for(unsigned long long i=1;i<length;++i)
			newnumbers[1+i]=numbers[i];
			
			++length;
			
			if(numbers!=nullptr)
			delete [] numbers;
			numbers=newnumbers;
		}		
	}
	else
	{
		--numbers[length-1];
		for(unsigned long long i=0;i<length-1;++i)
		if(numbers[length-1-i]>=MAX_UNSIGNED_LONG_LONG)
		{
			--numbers[length-2-i];
			numbers[length-1-i]=MAX_LIMIT_MEGAINT-1;
		}
		if(length>1)
		{
			unsigned long long nulls=0;
			for(unsigned long long i=0;i<length-1;++i)
			{
				if(numbers[i])
				break;
				else
				++nulls;
			}
			if(nulls)
			{
				unsigned long long *newnumbers=new unsigned long long[length-nulls];
				for(unsigned long long i=nulls;i<length;++i)
				newnumbers[i-nulls]=numbers[i];
				
				length-=nulls;
				
				if(numbers!=nullptr)
				delete [] numbers;
				numbers=newnumbers;
			}
		}
		if(numbers[0]==0 and length==1)
		negative=false;
		if(numbers[0]==MAX_UNSIGNED_LONG_LONG and length==1)
		{
			numbers[0]=1;
			negative=true;			
		}
	}
	return *this;
}


MegaInt& MegaInt::operator+=(MegaInt& other)
{
	if(*this==0)
	{
		*this=other;
		return *this;
	}
	if(other==0)
	return *this;
	
	if(this->MegaIntModyl()<(MegaInt&)other.MegaIntModyl())
	{
		*this=other+*this;
		return *this;
	}
	if(negative==other.negative)
	{
		for(unsigned long long i=0;i<other.length;++i)
		{
			numbers[length-i-1]+=other.numbers[other.length-i-1];
			
			if(i<other.length-1)
			if(numbers[length-i-1]>=MAX_LIMIT_MEGAINT)
			{
				numbers[length-i-2]+=(numbers[length-i-1]/((unsigned long long)MAX_LIMIT_MEGAINT));
				
				numbers[length-i-1]=numbers[length-i-1]-
				(numbers[length-i-1]/((unsigned long long)MAX_LIMIT_MEGAINT))
				*(unsigned long long)MAX_LIMIT_MEGAINT;
			}
		}
		
		if(numbers[0]>=MAX_LIMIT_MEGAINT)
		{
			unsigned long long *newnumbers=new unsigned long long[length+1];
			newnumbers[0]=numbers[0]/(MAX_LIMIT_MEGAINT);
			newnumbers[1]=numbers[0]%(MAX_LIMIT_MEGAINT);
			if(length>=2)
			for(unsigned long long i=1;i<length;++i)
			newnumbers[1+i]=numbers[i];
			
			++length;
			
			if(numbers!=nullptr)
			delete [] numbers;
			numbers=newnumbers;
		}
		if(numbers[0]==0 and length==1)
		negative=false;
		return *this;
	}
	else
	{
		for(unsigned long long i=0;i<other.length;++i)
		{
			if(i+1==length)
			break;
			if(numbers[length-i-1]==MAX_UNSIGNED_LONG_LONG)
			{
				--numbers[length-i-2];
				numbers[length-i-1]=MAX_LIMIT_MEGAINT-1;
			}
			
			if(numbers[length-i-1]>=other.numbers[other.length-i-1])
			numbers[length-i-1]-=other.numbers[other.length-i-1];
			else
			{
				numbers[length-i-1]=
				MAX_LIMIT_MEGAINT-(other.numbers[other.length-i-1]-numbers[length-i-1]);
				--numbers[length-i-2];
			}
		}
		if(length==other.length)
		numbers[0]-=other.numbers[0];
		
		if(length>1)
		{
			unsigned long long nulls=0;
			for(unsigned long long i=0;i<length-1;++i)
			{
				if(numbers[i])
				break;
				else
				++nulls;
			}
			
			if(nulls)
			{
				unsigned long long *newnumbers=new unsigned long long[length-nulls];
				for(unsigned long long i=nulls;i<length;++i)
				newnumbers[i-nulls]=numbers[i];
				
				length-=nulls;
				
				if(numbers!=nullptr)
				delete [] numbers;
				numbers=newnumbers;
			}
		}
		if(numbers[0]==0 and length==1)
		negative=false;
		
		if(numbers[0]==0 and length==1)
		negative=false;
		return *this;
	}
}

MegaInt& MegaInt::operator+=(long long n)
{
	if(*this==0)
	{
		*this=n;
		return *this;
	}
	if(n==0)
	{
		return *this;
	}
	
	if(n>=MAX_LIMIT_MEGAINT)
	{
		*this=*this+(MegaInt&)(MegaInt)n;
		return *this;
	}
	else
	{
		if(this->MegaIntModyl()<modyl(n))
		{
			*this=(MegaInt)n+*this;
			return *this;
		}
		if(negative==(n<0))
		{
			numbers[length-1]+=modyl(n);
			for(unsigned long long i=0;i<length-1;++i)
			{
				if(numbers[length-i-1]>=MAX_LIMIT_MEGAINT)
				{
					numbers[length-i-2]+=(numbers[length-i-1]/((unsigned long long)MAX_LIMIT_MEGAINT));
					numbers[length-i-1]=
					numbers[length-i-1]-(numbers[length-i-1]/((unsigned long long)MAX_LIMIT_MEGAINT))
					*MAX_LIMIT_MEGAINT;
				}
			}
			
			if(numbers[0]>=MAX_LIMIT_MEGAINT)
			{
				unsigned long long *newnumbers=new unsigned long long[length+1];
				newnumbers[0]=numbers[0]/(MAX_LIMIT_MEGAINT);
				newnumbers[1]=numbers[0]%(MAX_LIMIT_MEGAINT);
				if(length>=2)
				for(unsigned long long i=1;i<length;++i)
				newnumbers[1+i]=numbers[i];
				
				++length;
				
				if(numbers!=nullptr)
				delete [] numbers;
				numbers=newnumbers;
			}
			if(numbers[0]==0 and length==1)
			negative=false;
			return *this;
		}
		else
		{
			if(numbers[length-1]>=modyl(n))
			numbers[length-1]-=modyl(n);
			else
			{
				numbers[length-1]=
				MAX_LIMIT_MEGAINT-(modyl(n)-numbers[length-1]);
				if(length>1)
				--numbers[length-2];
				else
				negative=!negative;
			}
			
			for(unsigned long long i=0;i<length-1;++i)
			{
				if(numbers[length-i-1]==MAX_UNSIGNED_LONG_LONG)
				{
					--numbers[length-i-2];
					if(numbers[length-i-1]==MAX_UNSIGNED_LONG_LONG)
					numbers[length-i-1]=MAX_LIMIT_MEGAINT-1;
				}
			}
			if(length>1)
			{
				unsigned long long nulls=0;
				for(unsigned long long i=0;i<length-1;++i)
				{
					if(numbers[i])
					break;
					else
					++nulls;
				}
				
				if(nulls)
				{
					unsigned long long *newnumbers=new unsigned long long[length-nulls];
					for(unsigned long long i=nulls;i<length;++i)
					newnumbers[i-nulls]=numbers[i];
					
					length-=nulls;
					
					if(numbers!=nullptr)
					delete [] numbers;
					numbers=newnumbers;
				}
			}
			if(numbers[0]==0 and length==1)
				negative=false;
			return *this;
		}	
	}
}
MegaInt& MegaInt::operator-=(MegaInt& other)
{
	*this+=(MegaInt&)other.operator-();
	return *this;
}


MegaInt& MegaInt::operator-=(long long n)
{
	if(n<MAX_LONG_LONG)
	*this+=-n;
	else
	*this+=(MegaInt&) - (MegaInt)n;
	return *this;
}

MegaInt MegaInt::operator/(MegaInt& other)
{
	try
	{
		MegaInt result=0;
	
		if(*this==0)
			return result;
		if(other==0)
		{
			throw MegaInt::MegaIntException("Division by zero");
			return result;
		}
		if(other==1)
		{
			result=*this;
			return result;
		}
		if(MegaIntModyl()< (MegaInt&)other.MegaIntModyl())
			return result;
	//			делимое  делитель частное
	//	MegaInt dividend,divisor, quotient;
	
		MegaInt Divisor,Dividend=MegaIntModyl(),SmallDividend=0,AdditionalLength,Difference=0,
		GlobalDifference=0,DifferenceLength,LastNulls=0,BiggerDivisior=other.MegaIntModyl();
	
		while
		(
			(Dividend.numbers[Dividend.length-1]%10==0) and 
			(BiggerDivisior.numbers[BiggerDivisior.length-1]%10==0)
		)
		{
			BiggerDivisior/=10;
			Dividend/=10;
		}
	
		unsigned long long CurrQuotient=0;
		unsigned long long CutedPos=IntSize(BiggerDivisior.numbers[0])-1;

		unsigned long long CutedLength=BiggerDivisior.length;

		char* DividendCharPointer=nullptr;
		char* SmallDividendCharPointer=nullptr;

		while(Dividend>=BiggerDivisior)
		{
			CurrQuotient=0;
			SmallDividend=MegaInt::CutMegaIntNumber(Dividend,1,1);
			Divisor=BiggerDivisior;
			if(SmallDividend<Divisor)
			{
				CutedPos=IntSize(Difference.numbers[0]);
				CutedLength=BiggerDivisior.length;
				short ChangedRate=0;
				while(SmallDividend<Divisor)
				{
					if(CutedPos>MAX_LIMIT_RATE_MEGAINT)
					{
						CutedPos=1;
						++CutedLength;
					}
					if
					(
						((MegaInt)(CutedLength)-1)*(MegaInt&)
						((MegaInt)MAX_LIMIT_RATE_MEGAINT)+CutedPos<= (MegaInt&)Dividend.DigitNumberMegaInt()
					)
					{
						SmallDividend=MegaInt::CutMegaIntNumber(Dividend,CutedLength,CutedPos);


						if (DividendCharPointer != nullptr)
							delete[] DividendCharPointer;
						if (SmallDividendCharPointer != nullptr)
							delete[] SmallDividendCharPointer;

						DividendCharPointer=Dividend.GetCharArrayRecord();
						SmallDividendCharPointer=SmallDividend.GetCharArrayRecord();
						if
						(
							SmallDividend.DigitNumberMegaInt()> (MegaInt&)Difference.DigitNumberMegaInt()
							and(ChangedRate==2 or Difference==0)
						)
							result*=10;
						else
						if(ChangedRate<2)
							++ChangedRate;
						++CutedPos;
					}
					else
					{
						if (DividendCharPointer != nullptr)
							delete[] DividendCharPointer;
						if (SmallDividendCharPointer != nullptr)
							delete[] SmallDividendCharPointer;

						return result;
					}
				}
			}
			if (SmallDividend == 0)
			{
				if (DividendCharPointer != nullptr)
					delete[] DividendCharPointer;
				if (SmallDividendCharPointer != nullptr)
					delete[] SmallDividendCharPointer;

				return result;
			}
		
			AdditionalLength=Dividend.DigitNumberMegaInt()-(MegaInt&)SmallDividend.DigitNumberMegaInt();
		
			while(!(BiggerDivisior*CurrQuotient>SmallDividend))
			++CurrQuotient;
			--CurrQuotient;
		
			result*=10;
			result+=CurrQuotient;
			Divisor=BiggerDivisior*CurrQuotient;
			Difference=SmallDividend-Divisor;
			DifferenceLength=Divisor.DigitNumberMegaInt()-(MegaInt&)SmallDividend.DigitNumberMegaInt();
			AdditionalLength=Dividend.DigitNumberMegaInt()-DifferenceLength;
			if(Divisor!=0)
			{
				while(Divisor.DigitNumberMegaInt()<AdditionalLength)
				Divisor*=MAX_LIMIT_MEGAINT;
				if(Divisor.DigitNumberMegaInt()>AdditionalLength)
				Divisor/=MAX_LIMIT_MEGAINT;
				while(Divisor.DigitNumberMegaInt()<AdditionalLength)
				Divisor*=10;
				while(Divisor>Dividend)
				Divisor/=10;
			}
			MegaInt LostNulls=0;
			MegaInt currcuted;
			if(SmallDividend.DigitNumberMegaInt()+1<= (MegaInt&)Dividend.DigitNumberMegaInt() and Difference==0
			and(((MegaInt)(SmallDividend.length)-1)* (MegaInt&)((MegaInt)MAX_LIMIT_RATE_MEGAINT)
			+IntSize(SmallDividend.numbers[SmallDividend.length-1])+1
			<= (MegaInt&)Dividend.DigitNumberMegaInt()))
			{
				currcuted=MegaInt::CutMegaIntNumber
				(
					Dividend,SmallDividend.length,IntSize(SmallDividend.numbers[SmallDividend.length-1])+1
				);
				if(currcuted.numbers[currcuted.length-1]%10==0)
				{
					unsigned long long clength=SmallDividend.length;
					short cpos=IntSize(SmallDividend.numbers[SmallDividend.length-1])+1;
					if(cpos>MAX_LIMIT_RATE_MEGAINT)
					{
						cpos=1;
						++clength;
					}
					while(currcuted.numbers[currcuted.length-1]%10==0)
					{
						++LostNulls;
						++cpos;
						if(cpos>MAX_LIMIT_RATE_MEGAINT)
						{
							cpos=1;
							++clength;
						}
						if(currcuted.DigitNumberMegaInt()+1<= (MegaInt&)Dividend.DigitNumberMegaInt())
						currcuted=MegaInt::CutMegaIntNumber(Dividend,clength,cpos);
						if(Dividend.DigitNumberMegaInt()==currcuted.DigitNumberMegaInt())
						break;
					}
					for(MegaInt i=0;i<LostNulls;++i)
					result*=10;
				}
			}
			Dividend-=Divisor;
		}
		while(result* (MegaInt&)other.MegaIntModyl()<=(MegaInt&)MegaIntModyl())
		result*=10;
		while(result* (MegaInt&)other.MegaIntModyl()> (MegaInt&) MegaIntModyl())
		result/=10;
	
		if(other.negative!=negative)
		result.negative=true;


		if (DividendCharPointer != nullptr)
			delete[] DividendCharPointer;
		if (SmallDividendCharPointer != nullptr)
			delete[] SmallDividendCharPointer;


		return result;
	}
	catch(MegaInt::MegaIntException &ex)
	{
		std::cout<<ex.what();
		system("pause");
	}
}
MegaInt& MegaInt::operator/=(MegaInt &other)
{
	*this=*this/other;
	return *this;
}

MegaInt MegaInt::operator/(long long n)
{
	MegaInt number(n);

	return *this/number;
}

MegaInt& MegaInt::operator/=(long long n)
{
	if(n==0)
	{
		throw MegaInt::MegaIntException("Division by zero");
		*this=(long long)0;
		return *this;
	}
	if(n==1)
	{
		return *this;
	}
	if(*this<n)
	{
		*this=(long long)0;
		return *this;
	}
	if(IsRound(n))
	{
		if(n==MAX_LIMIT_MEGAINT)
		{
			--length;
			unsigned long long *newnumbers=new unsigned long long[length];
			for(unsigned long long i=0;i<length;++i)
			newnumbers[i]=numbers[i];
			
			if(numbers!=nullptr)
			delete [] numbers;
			numbers = nullptr;
			
			numbers=new unsigned long long[length];
			for(unsigned long long i=0;i<length;++i)
			numbers[i]=newnumbers[i];
			
			delete [] newnumbers;
		}
		else
		{
			for(short i=0;i<IntSize(n)-1;++i)
			{
				for(unsigned long long i=0;i<length;++i)
				{
					if(i<length-1)
					numbers[i+1]+=(unsigned long long)MAX_LIMIT_MEGAINT*(numbers[i]%10);
					numbers[i]/=10;
				}
			}
			if(length>1)
			{
				unsigned long long nulls=0;
				for(unsigned long long i=0;i<length-1;++i)
				{
					if(numbers[i])
					break;
					else
					++nulls;
				}
				
				if(nulls)
				{
					unsigned long long *newnumbers=new unsigned long long[length-nulls];
					for(unsigned long long i=nulls;i<length;++i)
					newnumbers[i-nulls]=numbers[i];
					
					length-=nulls;
					
					if(numbers!=nullptr)
					delete [] numbers;
					numbers=newnumbers;
				}
			}
		}
	}
	else
	{
		*this=*this/(MegaInt&)(MegaInt)n;
	}
	return *this;
}

MegaInt MegaInt::operator%(MegaInt &other)
{
	MegaInt result=*this-(MegaInt&)((*this/(MegaInt&)other)* (MegaInt&)other);
	return result;
}
MegaInt& MegaInt::operator%=(MegaInt &other)
{
	*this=*this%other;
	return *this;
}

MegaInt MegaInt::operator%(long long n)
{
	if(n==10)
	{
		if(numbers[length-1]%10==0)
		return (MegaInt)0;
	}
	else
	{
		MegaInt result=*this-(MegaInt&)((*this/(MegaInt&)(MegaInt)n)*(MegaInt&)(MegaInt)n);
		return result;
	}
}

MegaInt& MegaInt::operator%=(long long n)
{
	*this=*this%n;
	return *this;
}

MegaInt* MegaInt::operator*()
{
	return this;
}
#endif
