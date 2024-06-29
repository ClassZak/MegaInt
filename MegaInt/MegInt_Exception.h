#ifndef MEGAINT_EXCEPTION_H
#define MEGAINT_EXCEPTION_H

MegaInt::MegaIntException::MegaIntException(char* reason)
{
	this->reason=reason;
	this->numbers=NULL;
	this->count=0;
}
MegaInt::MegaIntException::MegaIntException(const char* reason)
{
	this->reason=(char*)reason;
	this->numbers=NULL;
	this->count=0;
}

MegaInt::MegaIntException::MegaIntException(MegaInt* m,char* reason,const unsigned long long count)
{
	this->reason=reason;
	this->numbers=m;
	this->count=count;
}
MegaInt::MegaIntException::MegaIntException(MegaInt* m,const char* reason,const unsigned long long count)
{
	this->reason=(char*)reason;
	this->numbers=m;
	this->count=count;
}
int MegaInt::MegaIntException::what()
{
	std::cout<<reason<<std::endl;
	if(numbers!=NULL)
	{
		std::cout<<"Operands are:\n";
		for(unsigned long long i=0;i<count;i++)
		std::cout<<numbers[i].GetPointer()<<":\n"<<numbers[i]<<std::endl;
	}

	return EXIT_SUCCESS;
}


#endif
