#ifndef CHAR_ARRAY_H
#define CHAR_ARRAY_H
#include <string>
class CharArray
{
public:
	char *String;
	unsigned long long *length;
	CharArray()
	{
		String=NULL;
		length=NULL;
	}
	CharArray(std::string String)
	{
		this->length=new unsigned long long;
	   *this->length=String.length()+1;
		this->String=new char[*length];
		for(unsigned long long i=0;i<*length-1;i++)
		this->String[i]=String[i];
		this->String[*length-1]='\0';
	}
	~CharArray()
	{
		if(String!=NULL)
		delete [] String;
		if(length!=NULL)
		delete length;
	}
	
	CharArray operator=(std::string String)
	{
		if(this->String!=NULL)
		delete [] this->String;
		if(this->length!=NULL)
		delete this->length;
		this->length=new unsigned long long;
	   *this->length=String.length()+1;
		this->String=new char[*length];
		for(unsigned long long i=0;i<*length-1;i++)
		this->String[i]=String[i];
		this->String[*length-1]='\0';
	}
	CharArray operator=(CharArray other)
	{
		if(this->String!=NULL)
		delete [] this->String;
		if(this->length!=NULL)
		delete this->length;
		this->length=new unsigned long long;
	   *this->length=other.length+1;
		this->String=new char[*length];
		for(unsigned long long i=0;i<*length;i++)
		this->String[i]=other.String[i];
	}
	static char* StringToCharPoint(const std::string &String)
	{
		unsigned long long newlength=String.length()+1;
		#ifdef DEBUG
		std::cout<<"length:"<<newlength<<std::endl;
		#endif
		char *array=new char[newlength];
		
		for(unsigned long long i=0;i<newlength-1;i++)
		{
			array[i]=String[i];
			#ifdef DEBUG
			std::cout<<"i="<<i<<" char:"<<array[i]<<std::endl;
			#endif
		}
		array[newlength-1]='\0';
		
		#ifdef DEBUG
		for(unsigned long long i=0;i<newlength;i++)
		std::cout<<array[i];
		std::cout<<'|'<<std::endl;
		#endif
		
		return array;
	}
};
#endif
