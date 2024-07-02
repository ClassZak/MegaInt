#ifndef MEGAINT_STRUCTORS_H
#define MEGAINT_STRUCTORS_H
MegaInt::MegaInt()
{
	length=1;
	numbers=new unsigned long long[1];
	numbers[0]=0;
	negative=false;
	++constructed;
}
MegaInt::MegaInt(const MegaInt &other)
{
	this->negative=other.negative;
	this->length=other.length;
	numbers=new unsigned long long[length];
	for(unsigned long long i=0;i<length;i++)
	this->numbers[i]=other.numbers[i];
	++constructed;
}
#pragma region Constructors for scalar types
MegaInt::MegaInt(long long n)
{
	long long nmodyl=modyl(n);
	
	(n<0) ? negative=true : negative=false;
	length=1;
	numbers=new unsigned long long[length];
	numbers[0]=nmodyl;
	
	if(nmodyl>=MAX_LIMIT_MEGAINT)
	{
		length=2;
		unsigned long long *newnumbers=new unsigned long long[length];
		newnumbers[1]=CutNumber((unsigned long long)nmodyl,MAX_LIMIT_RATE_MEGAINT);
		newnumbers[0]=(nmodyl)/PowerTen(MAX_LIMIT_RATE_MEGAINT);
		delete [] numbers;
		numbers=newnumbers;
	}
	++constructed;
}
MegaInt::MegaInt(unsigned long long n)
{
	length = 1;
	negative = false;
	numbers = new unsigned long long[length];
	numbers[0] = n;

	if (n >= MAX_LIMIT_MEGAINT)
	{
		++length;
		unsigned long long* newnumbers = new unsigned long long[length];
		newnumbers[1] = CutNumber(n, MAX_LIMIT_RATE_MEGAINT);
		newnumbers[0] = (n) / PowerTen(MAX_LIMIT_RATE_MEGAINT);
		delete[] numbers;
		numbers = newnumbers;
	}
	++constructed;
}


MegaInt::MegaInt(long n)
	: MegaInt::MegaInt((long long)n)
{
}
MegaInt::MegaInt(short n)
	: MegaInt::MegaInt((long long)n)
{
}
MegaInt::MegaInt(int n)
	: MegaInt::MegaInt((long long)n)
{
}
MegaInt::MegaInt(char n)
	: MegaInt::MegaInt((long long)n)
{
}


MegaInt::MegaInt(unsigned long n)
	: MegaInt::MegaInt((unsigned long long)n)
{
}
MegaInt::MegaInt(unsigned short n)
	: MegaInt::MegaInt((unsigned long long)n)
{
}
MegaInt::MegaInt(unsigned int n)
	: MegaInt::MegaInt((unsigned long long)n)
{
}
MegaInt::MegaInt(unsigned char n)
	: MegaInt::MegaInt((unsigned long long)n)
{
}


MegaInt::MegaInt(double n)
	: MegaInt::MegaInt((long long)trunc(n))
{
}
#pragma endregion
MegaInt::MegaInt(const char* InputString) : MegaInt::MegaInt()
{
	*this=CharPointerToMegaInt(InputString);
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
	++destructed;
}
#endif
