#include <iostream>
#include <windows.h>

#include "MegaInt.h"
#include <thread>
#include <mutex>
#include <functional>


std::mutex allocationLock;
int main()
{
	MegaInt a("12676506002282294014967032053761267650600228229401496703205376126765060022822940149670320537612676506002282294014967032053761267650600228229401496703205376126765060022822940149670320537612676506002282294014967032053761267650600228229401496703205376126765060022822940149670320537612676506002282294014967032053761267650600228229401496703205376126765060022822940149670320537612676506002282294014967032053761267650600228229401496703205376126765060022822940149670320537612676506002282294014967032053761267650600228229401496703205376126765060022822940149670320537612676506002282294014967032053761267650600228229401496703205376126765060022822940149670320537612676506002282294014967032053761267650600228229401496703205376126765060022822940149670320537612676506002282294014967032053761267650600228229401496703205376");
	for(unsigned int it=0;;++it)
	{
		std::function<void()> allocF([a,&allocationLock]() -> void
		{
			MegaInt* b;
			allocationLock.lock();
			b=new MegaInt[100];
			allocationLock.unlock();
			for(unsigned int j=0;j!=100;++j)
			*(b+j)=a;
		});
		std::thread alloc[20]=
		{
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF),
			std::thread::thread(allocF)
		};
		
		for(unsigned char i=0;i<20;++i)
		alloc[i].join();
	}
	
	system("pause");
	return 0;
}
