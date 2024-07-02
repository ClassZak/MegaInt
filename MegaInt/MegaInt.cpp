#include <cstddef>
#include <iostream>
#include <windows.h>
#include <conio.h>
//#define nullptr nullptr
#define MAX_UNSIGNED_LONG_LONG 18446744073709551615


#define BITNESS32

#ifdef BITNESS64
#define MIN_INT -2147483648
#define MAX_INT 2147483647
#else
#ifdef BITNESS32
#define MIN_INT -32768
#define MAX_INT 32767
#endif
#endif



#ifndef MAX_SIGNED_CHAR
#define MAX_SIGNED_CHAR 127
#endif
#ifndef MIN_SIGNED_CHAR
#define MIN_SIGNED_CHAR -128
#endif
#ifndef MAX_UNSIGNED_CHAR
#define MAX_UNSIGNED_CHAR 255
#endif
#ifndef MAX_CHAR
#define MAX_CHAR 255
#endif
#ifndef MAX_SHORT
#define MAX_SHORT 32767
#endif
#ifndef MIN_SHORT
#define MIN_SHORT -32768
#endif
#ifndef MAX_UNSIGNED_SHORT
#define MAX_UNSIGNED_SHORT 65535
#endif
#ifndef MAX_INT
#define MAX_INT 2147483647
#endif
#ifndef MIN_INT
#define MIN_INT -2147483648
#endif
#ifndef MAX_UNSIGNED_INT
#define MAX_UNSIGNED_INT 4294967295
#endif
#ifndef MAX_LONG
#define MAX_LONG 2147483647
#endif
#ifndef MIN_LONG
#define MIN_LONG -2147483648
#endif
#ifndef MAX_UNSIGNED_LONG
#define MAX_UNSIGNED_LONG 4294967295
#endif
#ifndef MAX_LONG_LONG
#define MAX_LONG_LONG 9223372036854775807
#endif
#ifndef MIN_LONG_LONG
#define MIN_LONG_LONG -9223372036854775808
#endif
#ifndef MAX_UNSIGNED_LONG_LONG
#define MAX_UNSIGNED_LONG_LONG 18446744073709551615
#endif
//#define MEGAINT_DEBUG
//#define DIVISION_DEBUG
#include "MegaInt.h"
#define BORDER 1000
#include <fstream>
#include <thread>
#include <mutex>
#include <functional>

std::mutex printLock;


static unsigned Progress = 0;

static void Threads100()
{

	std::string files[100];
	for (short i = 0; i < 100; ++i)
	{
		files[i] = "Tets";
		files[i] += to_string(i + 1);
		files[i] += ".txt";
	}

	//system("pause");

	std::function<void()> tests[100];
	for (short I_ = 0; I_ < 100; ++I_)
	{
		tests[I_] = [files, I_]()
			{
				std::ofstream file(files[I_]);

				for (long long i = BORDER / 100 * I_; i < BORDER / 100 * (I_ + 1); ++i)
				{
					printLock.lock();
					std::cout << "s=" << BORDER / 100 * I_ << '\n';
					std::cout << "i=" << -(BORDER / 100 * I_-i) <<'/'<< BORDER / 100
							  <<'\t' << round((double)-(BORDER / 100 * I_ - i) / (double)BORDER *100* 100.)<<'%'
							  << "\n\n";
					printLock.unlock();
					MegaInt m = i;
					for (long long j = -BORDER; j < BORDER; ++j)
					{
						if (j == 0)
							continue;
						MegaInt n = j;

						if ((m / n) != (i / j))
						try
						{
							file << std::string("m=\t") + m.GetCharArrayRecord() + "\tn=\t" +
								n.GetCharArrayRecord() +
								"\tm/n=\t" +
								(m / n).GetCharArrayRecord() +
								"\ti/j=\t" + std::to_string(i / j)<<'\n';
						}
						catch (const std::exception&)
						{
						}
					}
				}

				file.close();

				printLock.lock();
				std::cout << "s=" << BORDER / 100 * I_ << "\tfinished" << std::endl;
				std::cout << "Progress:\t" << ++Progress<<'%'<<std::endl<<std::endl;
				printLock.unlock();
			};
	}
	for (short i = 0; i != 100; ++i)
		tests[i]();

	/*
	std::thread Testing[100] =
	{
		std::thread(tests[0]),
		std::thread(tests[1]),
		std::thread(tests[2]),
		std::thread(tests[3]),
		std::thread(tests[4]),
		std::thread(tests[5]),
		std::thread(tests[6]),
		std::thread(tests[7]),
		std::thread(tests[8]),
		std::thread(tests[9]),
		std::thread(tests[10]),
		std::thread(tests[11]),
		std::thread(tests[12]),
		std::thread(tests[13]),
		std::thread(tests[14]),
		std::thread(tests[15]),
		std::thread(tests[16]),
		std::thread(tests[17]),
		std::thread(tests[18]),
		std::thread(tests[19]),
		std::thread(tests[20]),
		std::thread(tests[21]),
		std::thread(tests[22]),
		std::thread(tests[23]),
		std::thread(tests[24]),
		std::thread(tests[25]),
		std::thread(tests[26]),
		std::thread(tests[27]),
		std::thread(tests[28]),
		std::thread(tests[29]),
		std::thread(tests[30]),
		std::thread(tests[31]),
		std::thread(tests[32]),
		std::thread(tests[33]),
		std::thread(tests[34]),
		std::thread(tests[35]),
		std::thread(tests[36]),
		std::thread(tests[37]),
		std::thread(tests[38]),
		std::thread(tests[39]),
		std::thread(tests[40]),
		std::thread(tests[41]),
		std::thread(tests[42]),
		std::thread(tests[43]),
		std::thread(tests[44]),
		std::thread(tests[45]),
		std::thread(tests[46]),
		std::thread(tests[47]),
		std::thread(tests[48]),
		std::thread(tests[49]),
		std::thread(tests[50]),
		std::thread(tests[51]),
		std::thread(tests[52]),
		std::thread(tests[53]),
		std::thread(tests[54]),
		std::thread(tests[55]),
		std::thread(tests[56]),
		std::thread(tests[57]),
		std::thread(tests[58]),
		std::thread(tests[59]),
		std::thread(tests[60]),
		std::thread(tests[61]),
		std::thread(tests[62]),
		std::thread(tests[63]),
		std::thread(tests[64]),
		std::thread(tests[65]),
		std::thread(tests[66]),
		std::thread(tests[67]),
		std::thread(tests[68]),
		std::thread(tests[69]),
		std::thread(tests[70]),
		std::thread(tests[71]),
		std::thread(tests[72]),
		std::thread(tests[73]),
		std::thread(tests[74]),
		std::thread(tests[75]),
		std::thread(tests[76]),
		std::thread(tests[77]),
		std::thread(tests[78]),
		std::thread(tests[79]),
		std::thread(tests[80]),
		std::thread(tests[81]),
		std::thread(tests[82]),
		std::thread(tests[83]),
		std::thread(tests[84]),
		std::thread(tests[85]),
		std::thread(tests[86]),
		std::thread(tests[87]),
		std::thread(tests[88]),
		std::thread(tests[89]),
		std::thread(tests[90]),
		std::thread(tests[91]),
		std::thread(tests[92]),
		std::thread(tests[93]),
		std::thread(tests[94]),
		std::thread(tests[95]),
		std::thread(tests[96]),
		std::thread(tests[97]),
		std::thread(tests[98]),
		std::thread(tests[99]),
	};

	for (short i = 0; i < 100; ++i)
	{
		Testing[i].join();
	}*/
}


int main()
{
	Threads100();

	system("pause");
}
