#include <iostream>
#include "InternalFunctions.h"

#include "User.h"
#include <memory>

int main()
{
    setlocale(LC_ALL, "");
    system("chcp 1251");

    INTERNALFUNCTIONS::Menu menu;       
    menu.main();

    return 0;
}

