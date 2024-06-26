#ifndef MEGAINT_OPERATORS_H
#define MEGAINT_OPERATORS_H
#include <iostream>
template <typename T>
MegaInt& MegaInt::operator=(T n)
{
	(n>=0) ? negative=false : negative=true;
	n=modyl(n);
	#ifdef MEGAINT_DEBUG
	std::cout<<"reset "<<this<<std::endl;
	#endif
	if(numbers!=NULL)
	delete [] numbers;
	length=IntSize(n);
	numbers=new short[length];
	for(T i=0;i<length;i++)
	numbers[i]=GetDigitRate(n, length-i-1);
	
	return *this;
}
MegaInt& MegaInt::operator=(const MegaInt &other)
{
	this->negative=other.negative;
	#ifdef MEGAINT_DEBUG
	std::cout<<"copyright "<<this<<std::endl;
	#endif
	this->length=other.length;
	if(numbers!=NULL)
	delete [] numbers;
	numbers=new short[length];
	for(unsigned long long i=0;i<length;i++)
	this->numbers[i]=other.numbers[i];
	
	return *this;
}

MegaInt MegaInt::operator +(const MegaInt& other)
{
	MegaInt m = other;

	MegaInt result;
	if(this->MegaIntModyl()< m.MegaIntModyl())
	{
		#ifdef MEGAINT_DEBUG
		std::cout<<"\nSMALLER!\n\n";
		#endif
		MegaInt result;result= m +*this;
		return(result);
	}
	
	result.negative=this->negative;
	(this->length>=other.length)?(result.length=this->length):(result.length=other.length);
	result.numbers=new short[result.length];
	for(unsigned long long i=0;i<result.length;i++)
	result.numbers[i]=0;
	#ifdef MEGAINT_DEBUG
	std::cout<<"before\n";
	for(unsigned long long i=0;i<result.length;i++)
	{
		std::cout<<result.numbers[i];
		std::cout<<std::endl;        	
	}
	#endif
	for(unsigned long long i=0;i<length;i++)
	result.numbers[result.length-1-i]=this->numbers[length-1-i];
	if(this->negative==other.negative)
	{
		for(unsigned long long i=0;i<other.length;i++)
		result.numbers[result.length-1-i]+=other.numbers[other.length-1-i];
		for(unsigned long long i=result.length-1;i>0;i--)
		if(result.numbers[i]>=10)
		{
			result.numbers[i-1]+=1;
			result.numbers[i]-=10;
		}
		if(result.numbers[0]>=10)
		{
			result.SetNewDigitRate();
			result.numbers[1]-=10;
			result.numbers[0]=1;
		}
	}
	else
	{
		#ifdef MEGAINT_DEBUG
		std::cout<<"subtraction\n";
		#endif
		for(unsigned long long i=0;i<other.length;i++)
		{
			#ifdef MEGAINT_DEBUG
			std::cout<<result.numbers[result.length-1-i]<<' '<<other.numbers[other.length-1-i]<<"  ";
			#endif           	
			result.numbers[result.length-1-i]-=other.numbers[other.length-1-i];
			if(result.numbers[result.length-1-i]<0)
			{
				#ifdef MEGAINT_DEBUG
				std::cout<<"result.length-1-i = "<<result.length-2-i<<std::endl;
				#endif
				if((result.length-2-i)>=0 and (result.length-2-i)!=MAX_UNSIGNED_LONG_LONG)
				result.numbers[result.length-2-i]--;
				if(result.length-1-i!=0)
				result.numbers[result.length-1-i]+=10;
			}
			#ifdef MEGAINT_DEBUG
			std::cout<<result.numbers[result.length-1-i]<<' '<<other.numbers[other.length-1-i]<<std::endl;
			#endif   
		}
		#ifdef MEGAINT_DEBUG
		std::cout<<"sub is such\n";
		#endif
		for(unsigned long long i=result.length-1;i>0;i--)
		{
			if(result.numbers[i]<0 and i)
			{
				result.numbers[i]+=10;
				result.numbers[i-1]--;
			}
			#ifdef MEGAINT_DEBUG
			std::cout<<"i = "<<i<<std::endl;
			#endif
		}
		if(result.numbers[0]<0)
		{
			result.numbers[0]*=-1;
			result.negative=!result.negative;
		}
		while(result.numbers[0]==0)
		if(result.length!=1)
		result.EareseDigitRate();
		else
		{
			if(result.numbers[0]==0)
			result.negative=false;
			break;
		}
	}

	#ifdef MEGAINT_DEBUG
	std::cout<<"after\n";
	for(unsigned long long i=0;i<result.length;i++)
	{
		std::cout<<result.numbers[i];
		std::cout<<std::endl;
	}
	#endif
	return result;
}
MegaInt MegaInt::operator-(const MegaInt &other)
{
	MegaInt result,result2=other;
	result2.negative=!result2.negative;
	result=*this+result2;
	return result;
}
MegaInt MegaInt::operator*(const MegaInt &other)
{
	MegaInt result=0,sum=0;
	for(unsigned long long i=0;i<other.length;i++)
	{
		MegaInt CurrSum=sum;
		#ifdef MEGAINT_DEBUG
		std::cout<<"last - "<<other.numbers[other.length-i-1]<<std::endl;
		#endif
		for(short j=1;j<=other.numbers[other.length-i-1];j++)
		{
			sum=sum+MegaIntModyl();
			#ifdef MEGAINT_DEBUG
			std::cout<<"j="<<j<<" sum:";sum.Print();std::cout<<std::endl;
			#endif
		}
		CurrSum=sum;
		for(unsigned long long k=0;k<i;k++)
		{
			sum.SetUpDigitRate(1);
			#ifdef MEGAINT_DEBUG
			std::cout<<"sum:";sum.Print(1);
			#endif
		}
		
		result=result+sum;
		#ifdef MEGAINT_DEBUG
		std::cout<<"result:";result.Print(1);
		#endif
		sum=0;
	}
	
	if(this->negative and other.negative)
	result.negative=false;
	else if((this->negative and !other.negative) or (!this->negative and other.negative))
	result.negative=true;
	
	if(*this==0 or (MegaInt&)other==0)
	{
		result=0;
		result.negative=false;
	}
	
//	if(result.length==1 and result.numbers[0]==0)
	
	#ifdef MEGAINT_DEBUG
	std::cout<<"result:";result.Print(1);
	#endif
	sum=0;
	return result;
}

MegaInt MegaInt::operator/(const MegaInt &other)
{
	MegaInt m = other;
	MegaInt result=0,dividend=0;
	dividend.negative=false;
	if(*this==0 or (MegaInt&)other==0)
	return result;
	
	#ifdef MEGAINT_DEBUG
	std::cout<<"dividend = ";dividend.Print();std::cout<<" other = ";other.Print();std::cout<<" res: ";
	result.Print(1);
	#endif
	while(dividend<this->MegaIntModyl())
	{
		dividend=dividend+ m.MegaIntModyl();
		result=result+1;
		#ifdef MEGAINT_DEBUG
		std::cout<<std::endl<<"dividend = ";dividend.Print();std::cout<<" other = ";other.Print();std::cout<<" res: ";result.Print(1);
		#endif
	}
	if(dividend>this->MegaIntModyl())
	result=result-1;
	
	if(negative!=other.negative)
	if(((negative and !other.negative) or (!negative and other.negative))and result!=0)
	result.negative=true;
	
	return result;
}
MegaInt MegaInt::operator%(const MegaInt &other)
{
	MegaInt result;
	#ifdef MEGAINT_DEBUG
	std::cout<<"\nthis negative: "<<negative<<std::endl;
	#endif
	result=*this-((*this/other)*other);
	return result;
}
template <typename T>
MegaInt	MegaInt::operator+(const T n)
{
	MegaInt result,other=n;
	result=*this+other;
	return result;
}
template <typename T>
MegaInt	MegaInt::operator-(const T n)
{
	MegaInt result,other=n;
	result=*this-other;
	return result;
}
template <typename T>
MegaInt	MegaInt::operator*(const T n)
{
	MegaInt result,other=n;
	result=*this*other;
	return result;
}
template <typename T>
MegaInt	MegaInt::operator/(const T n)
{
	MegaInt result,other=n;
	result=*this/other;
	return result;
}
template <typename T>
MegaInt	MegaInt::operator%(const T n)
{
	MegaInt result,other=n;
	result=*this%other;
	return result;
}

bool MegaInt::operator==(const MegaInt &other)
{
	bool biggerModyl=false;
	bool biggerSign =false;
	bool equalModyl=true;
	bool equalSign =false;
	bool equal=false;
	
	if(negative==other.negative)
	equalSign=true;
	if(length==other.length)
	{
		equalModyl=true;
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

	equal=equalModyl*equalSign;
	return equal;
}
template <typename T>
bool MegaInt::operator==(const T n)
{
	MegaInt other=n;
	return *this==other;
}
bool MegaInt::operator >(const MegaInt &other)
{
	#ifdef MEGAINT_DEBUG
	std::cout<<"\nCOMPARE\nthis l:"<<length<<" other l:"<<other.length<<std::endl;
	Print(1);std::cout<<std::endl;
	other.Print(1);std::cout<<std::endl;
	#endif
	bool biggerModyl=false;
	bool equalModyl=true;
	bool equalSign =false;
	bool equal=false;
	
	
	if(length>other.length)
	{
		biggerModyl=true;
	}
	else if (length==other.length)
	{
		biggerModyl=false;
		for(unsigned long long i=0;i<length;i++)
		{
			#ifdef MEGAINT_DEBUG
			std::cout<<numbers[i]<<" and "<<other.numbers[i]<<"  ";
			#endif
			if(numbers[i]!=other.numbers[i])
			{
				if(numbers[i]>other.numbers[i])
				biggerModyl=true;
				else if(numbers[i]<other.numbers[i])
				biggerModyl=false;
				
				#ifdef MEGAINT_DEBUG
				std::cout<<std::endl<<numbers[i]<<" and "<<other.numbers[i]<<" are triggers\n";
				#endif
				break;
			}       		
		}
		#ifdef MEGAINT_DEBUG
		std::cout<<std::endl;
		#endif
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
		if(negative and !(*this==other))
		biggerModyl=!biggerModyl;
	}
	
	return biggerModyl;
}
template <typename T>
bool MegaInt::operator >(const T n)
{
	MegaInt other=n;
	return *this>other;
}
bool MegaInt::operator <(const MegaInt &other)
{
	#ifdef MEGAINT_DEBUG
	std::cout<<"\nCOMPARE\nthis l:"<<length<<" other l:"<<other.length<<std::endl;
	Print(1);std::cout<<std::endl;
	other.Print(1);std::cout<<std::endl;
	#endif
	bool smallerModyl=false;
	bool smallerSign =false;
	bool equalModyl=true;
	bool equalSign =false;
	bool equal=false;
	
	
	if(length<other.length)
	{
		smallerModyl=true;
	}
	else if (length==other.length)
	{
		smallerModyl=false;
		for(unsigned long long i=0;i<length;i++)
		{
			#ifdef MEGAINT_DEBUG
			std::cout<<numbers[i]<<" and "<<other.numbers[i]<<"  ";
			#endif
			if(numbers[i]!=other.numbers[i])
			{
				if(numbers[i]<other.numbers[i])
				smallerModyl=true;
				else if(numbers[i]>other.numbers[i])
				smallerModyl=false;
				
				#ifdef MEGAINT_DEBUG
				std::cout<<std::endl<<numbers[i]<<" and "<<other.numbers[i]<<" are triggers\n";
				#endif
				break;
			}       		
		}
		#ifdef MEGAINT_DEBUG
		std::cout<<std::endl;
		#endif
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

	//return smallerModyl*(*this!=other);
	return smallerModyl;
}
template <typename T>
bool MegaInt::operator <(const T n)
{
	MegaInt other=n;
	return *this<other;
}
bool MegaInt::operator <=(const MegaInt &other)
{
	#ifdef MEGAINT_DEBUG
	std::cout<<"\nCOMPARE\nthis l:"<<length<<" other l:"<<other.length<<std::endl;
	Print(1);std::cout<<std::endl;
	other.Print(1);std::cout<<std::endl;
	#endif
	bool smallerModyl=false;
	bool equalModyl=true;
	bool equalSign=false;
	
	if(length<other.length)
	{
		smallerModyl=true;
	}
	else if (length==other.length)
	{
		smallerModyl=false;
		for(unsigned long long i=0;i<length;i++)
		{
			#ifdef MEGAINT_DEBUG
			std::cout<<numbers[i]<<" and "<<other.numbers[i]<<"  ";
			#endif
			if(numbers[i]!=other.numbers[i])
			{
				if(numbers[i]<other.numbers[i])
				smallerModyl=true;
				else if(numbers[i]>other.numbers[i])
				smallerModyl=false;
				
				#ifdef MEGAINT_DEBUG
				std::cout<<std::endl<<numbers[i]<<" and "<<other.numbers[i]<<" are triggers\n";
				#endif
				break;
			}       		
		}
		#ifdef MEGAINT_DEBUG
		std::cout<<std::endl;
		#endif
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
	
	
	if(negative==other.negative)
	equalSign=true;
	if(length==other.length)
	{
		equalModyl=true;
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

	bool equal=equalModyl*equalSign;
	return equal+smallerModyl;
}
template <typename T>
bool MegaInt::operator <=(const T n)
{
	MegaInt other=n;
	return *this<=other;
}
bool MegaInt::operator >=(const MegaInt &other)
{
	#ifdef MEGAINT_DEBUG
	std::cout<<"\nCOMPARE\nthis l:"<<length<<" other l:"<<other.length<<std::endl;
	Print(1);std::cout<<std::endl;
	other.Print(1);std::cout<<std::endl;
	#endif
	bool biggerModyl=false;
	bool equalModyl=true;
	bool equalSign=false;
	
	if(length>other.length)
	{
		biggerModyl=true;
	}
	else if (length==other.length)
	{
		biggerModyl=false;
		for(unsigned long long i=0;i<length;i++)
		{
			#ifdef MEGAINT_DEBUG
			std::cout<<numbers[i]<<" and "<<other.numbers[i]<<"  ";
			#endif
			if(numbers[i]!=other.numbers[i])
			{
				if(numbers[i]>other.numbers[i])
				biggerModyl=true;
				else if(numbers[i]<other.numbers[i])
				biggerModyl=false;
				
				#ifdef MEGAINT_DEBUG
				std::cout<<std::endl<<numbers[i]<<" and "<<other.numbers[i]<<" are triggers\n";
				#endif
				break;
			}       		
		}
		#ifdef MEGAINT_DEBUG
		std::cout<<std::endl;
		#endif
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
		if(negative and !(*this==other))
		biggerModyl=!biggerModyl;
	}
	
	
	if(negative==other.negative)
	equalSign=true;
	if(length==other.length)
	{
		equalModyl=true;
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

	bool equal=equalModyl*equalSign;
	return equal+biggerModyl;
}
template <typename T>
bool MegaInt::operator >=(const T n)
{
	MegaInt other=n;
	return *this>=other;
}
bool MegaInt::operator!=(const MegaInt &other)
{
	bool biggerModyl=false;
	bool biggerSign =false;
	bool equalModyl=true;
	bool equalSign =false;
	bool equal=false;
	
	if(negative==other.negative)
	equalSign=true;
	if(length==other.length)
	{
		equalModyl=true;
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

	equal=equalModyl*equalSign;
	return !equal;
}
template <typename T>
bool MegaInt::operator!=(const T n)
{
	MegaInt other=n;
	return *this!=other;
}

MegaInt MegaInt::operator-()
{
	MegaInt result=*this;
	result.negative=!negative;
	return result;
}
MegaInt MegaInt::operator+()
{
	MegaInt result=*this;
	result.negative=false;
	return result;
}


MegaInt MegaInt::operator++()
{
	MegaInt prev=*this;
	*this=prev+1;
	return *this;
}
MegaInt MegaInt::operator++(int value)
{
	MegaInt old=*this,prev=*this;
	*this=prev+1;
	return old;
}

MegaInt MegaInt::operator--()
{
	*this=*this-1;
	return *this;
}
MegaInt MegaInt::operator--(int value)
{
	MegaInt old=*this;
	*this=*this-1;
	return old;
}




MegaInt MegaInt::operator+=(const MegaInt &other)
{
	*this=*this+other;
	return *this;
}
MegaInt MegaInt::operator-=(const MegaInt &other)
{
	*this=*this-other;
	return *this;
}
MegaInt MegaInt::operator/=(const MegaInt &other)
{
	*this=*this/other;
	return *this;
}
MegaInt MegaInt::operator*=(const MegaInt &other)
{
	*this=*this*other;
	return *this;
}
MegaInt MegaInt::operator%=(const MegaInt &other)
{
	*this=*this%other;
	return *this;
}



template <typename T>
MegaInt MegaInt::operator+=(const T n)
{
	MegaInt other=n;
	*this=*this+other;
	return *this;
}
template <typename T>
MegaInt MegaInt::operator-=(const T n)
{
	MegaInt other=n;
	*this=*this-other;
	return *this;
}
template <typename T>
MegaInt MegaInt::operator/=(const T n)
{
	MegaInt other=n;
	*this=*this/other;
	return *this;
}
template <typename T>
MegaInt MegaInt::operator*=(const T n)
{
	MegaInt other=n;
	*this=*this*other;
	return *this;
}
template <typename T>
MegaInt MegaInt::operator%=(const T n)
{
	MegaInt other=n;
	*this=*this%other;
	return *this;
}

template <typename T>
short MegaInt::operator[](T n)
{
	return numbers[n];
}


std::ostream& operator<<(std::ostream &os,MegaInt &MI)
{
	return os<<MI.GetStringRecord();
}
std::istream& operator>>(std::istream &in,MegaInt &MI)
{
	std::string InputString;
	in>>InputString;
	MI=MegaInt::StringToMegaInt(InputString);
	return in;
}

#endif
