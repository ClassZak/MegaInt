#include "MegaInt_Definetion.h"
#ifndef MEGAINT_STRUCTORS_H
#define MEGAINT_STRUCTORS_H
MegaInt::MegaInt()
{
    #ifdef MEGAINT_DEBUG
    std::cout<<"construction "<<this<<std::endl;
    #endif
    length=0;
    numbers=NULL;
    negative=false;
    constructed++;
    Exponential=false;
    IsPrefix=false;
}
MegaInt::MegaInt(const MegaInt &other)
{
    this->negative=other.negative;
    this->length=other.length;
    numbers=new short[length];
    for(unsigned long long i=0;i<length;i++)
    this->numbers[i]=other.numbers[i];
    #ifdef MEGAINT_DEBUG
    std::cout<<"copyright construction "<<this<<std::endl;
    #endif
    constructed++;
    Exponential=false;
    IsPrefix=false;
}

MegaInt::MegaInt(long long n)
{
    (n>=0) ? negative=false : negative=true;
    n=modyl(n);
    length=IntSize(n);
    numbers=new short[length];
    for(unsigned long long i=0;i<length;i++)
    numbers[i]=short(GetDigitRate(n, length-i-1));
    #ifdef MEGAINT_DEBUG
    std::cout<<"construction with number"<<this<<std::endl;
    #endif
    constructed++;
    Exponential=false;
    IsPrefix=false;
}

MegaInt::MegaInt(std::string &InputString):MegaInt()
{
	*this=StringToMegaInt(InputString);
}
MegaInt::MegaInt(std::string InputString):MegaInt()
{
	*this=StringToMegaInt(InputString);
}
//Destructor
MegaInt::~MegaInt()
{
    #ifdef MEGAINT_DEBUG
    std::cout<<"destruction "<<this<<std::endl;
    #endif
//  this->Print(1);    
    if(numbers!=NULL)
    delete [] numbers;
    numbers=NULL;
	length=0;
    destructed++;
}
#endif
