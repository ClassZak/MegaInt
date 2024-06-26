#include <iostream>
#include "MegaInt.h"



int main()
{
    // TODO:
    // Додеделать исправление шаблонных функций и методов
    

    while (true)
    {
        MegaInt a (std::string("2"));
        a.MakePrefix();

        while (a.GetSize()<=120)
        {
            a += a;
            std::cout << a<<std::endl;
        }
    }
}
