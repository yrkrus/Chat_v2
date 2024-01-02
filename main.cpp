#include "Functions.h"
#include "Chat.h"
#include "User.h"
#include <iostream>

// константы из файла Constants.cpp 
extern bool const DEBUG;

int main()
{
	setlocale(LC_ALL, ""); 
	system("chcp 1251");
    
	// тестовое создание пользователей	
	if (DEBUG) {
		createTestUsers();
		createTestMessage();
	}
	
	menu();

	return 0;	
}

