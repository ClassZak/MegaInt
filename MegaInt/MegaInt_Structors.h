#ifndef MEGAINT_STRUCTORS_H
#define MEGAINT_STRUCTORS_H
MegaInt::MegaInt()
{
	length=1;
	numbers=new unsigned long long[1];
	numbers[0]=0;
	negative=false;
	constructed++;
}
MegaInt::MegaInt(const MegaInt &other)
{
	this->negative=other.negative;
	this->length=other.length;
	numbers=new unsigned long long[length];
	for(unsigned long long i=0;i<length;i++)
	this->numbers[i]=other.numbers[i];
	constructed++;
}
template <typename T>
MegaInt::MegaInt(const T n)
{
	T nmodyl=modyl(n);
	
	(n<0) ? negative=true : negative=false;
	length=1;
	numbers=new unsigned long long[length];
	numbers[0]=nmodyl;
	
	if(nmodyl>=MAX_LIMIT_MEGAINT)
	{
		++length;
		unsigned long long *newnumbers=new unsigned long long[length];
		newnumbers[1]=CutNumber((unsigned long long)nmodyl,MAX_LIMIT_RATE_MEGAINT);
		newnumbers[0]=(nmodyl)/PowerTen(MAX_LIMIT_RATE_MEGAINT);
		delete [] numbers;
		numbers=newnumbers;
	}
	constructed++;
}
MegaInt::MegaInt(char* InputString) : MegaInt::MegaInt()
{
	*this=(long long)0;
	char* array = (char*)"";
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
		negative=true;
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
		negative=false;
	}
	else
	{
		newlength=(unsigned long long)lastlength/(unsigned long long)(MAX_LIMIT_RATE_MEGAINT)
		+bool(((lastlength%(MAX_LIMIT_RATE_MEGAINT))!=0)or(lastlength<MAX_LIMIT_RATE_MEGAINT));
		if(!(newlength))
		{
		}
		else
		{
			unsigned long long *newnumbers=new unsigned long long[newlength];
			for(unsigned long long i=0;i<newlength;++i)
			{
				unsigned long long curr=0;
				for(unsigned long long j=0;j<MAX_LIMIT_RATE_MEGAINT;++j)
				{
					if((lastlength-i*MAX_LIMIT_RATE_MEGAINT-j+i)==MAX_UNSIGNED_LONG_LONG)
					break;
					curr+=(unsigned long long)((short)(array[lastlength-i*MAX_LIMIT_RATE_MEGAINT-j+i]-'0'))
					*PowerTen(j);
				}
				newnumbers[newlength-i-1]=curr;
			}
			length=newlength;
			delete numbers;
			numbers=newnumbers;
		}
	}
}
MegaInt::MegaInt(const char* InputString) : MegaInt::MegaInt()
{
	*this=(long long)0;
	char* array = (char*)"";
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
		negative=true;
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
		negative=false;
	}
	else
	{
		newlength=(unsigned long long)lastlength/(unsigned long long)(MAX_LIMIT_RATE_MEGAINT)
		+bool(((lastlength%(MAX_LIMIT_RATE_MEGAINT))!=0)or(lastlength<MAX_LIMIT_RATE_MEGAINT));
		if(!(newlength))
		{
		}
		else
		{
			unsigned long long *newnumbers=new unsigned long long[newlength];
			for(unsigned long long i=0;i<newlength;++i)
			{
				unsigned long long curr=0;
				for(unsigned long long j=0;j<MAX_LIMIT_RATE_MEGAINT;++j)
				{
					if((lastlength-i*MAX_LIMIT_RATE_MEGAINT-j+i)==MAX_UNSIGNED_LONG_LONG)
					break;
					curr+=(unsigned long long)((short)(array[lastlength-i*MAX_LIMIT_RATE_MEGAINT-j+i]-'0'))
					*PowerTen(j);
				}
				newnumbers[newlength-i-1]=curr;
			}
			length=newlength;
			delete numbers;
			numbers=newnumbers;
		}
	}
}
//Destructor
MegaInt::~MegaInt()
{	
	if (numbers != nullptr)
	{
		delete [] numbers;
		numbers= nullptr;
	}

	length=0;
	destructed++;
}
#endif
