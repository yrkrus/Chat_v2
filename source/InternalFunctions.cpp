#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
//#include <windows.h>
#include <limits>
//#include <cstdlib>
#include <ctime>

#include "InternalFunctions.h"
#include "CONSTANTS.h"
#include "User.h"
#include "SQLRequest.h"

// fix т.к. идет переопределение max() в std::cin.ignore(std::numeric_limits<std::streamsize>::max()
#undef min
#undef max


namespace INTERNALFUNCTIONS
{
	std::istream &getline(std::istream &in, MenuCommands &commands)
	{
		int input;
		in >> input;

		switch (input)
		{
		case 1:
			commands = MenuCommands::LOGIN;
			break;
		case 2:
			commands = MenuCommands::REGISTRATION;
			break;
		default:
			commands = MenuCommands::NO_COMMANDS;
			break;
		}

		return in;
	}

	std::istream &getline(std::istream &in, MenuAuthCommands &commands)
	{
		int input;
		in >> input;

		switch (input)
		{
			case 1:
			{
				commands = MenuAuthCommands::MY_MESSAGE;
				break;
			}
			case 2:
			{
				commands = MenuAuthCommands::NEW_MESSAGE;
				break;
			}			
			case 3:
			{
				commands = MenuAuthCommands::EXIT;
				break;
			}

			default:
			{
				commands = MenuAuthCommands::NO_COMMANDS;
				break;
			}
		}

		return in;
	}
}

std::istream &INTERNALFUNCTIONS::operator>>(std::istream &in, MenuCommands &commands) {
	int input;
	in >> input;

	switch (input)
	{
		case 1:	{
			commands = MenuCommands::LOGIN;
			break;
		}
		case 2:	{
			commands = MenuCommands::REGISTRATION;
			break;
		}		
		default: {
			commands = MenuCommands::NO_COMMANDS;
			break;
		}		
	}

	return in;
}

std::istream &INTERNALFUNCTIONS::operator>>(std::istream &in, MenuAuthCommands &commands)
{
	int input;
	in >> input;

	switch (input)
	{
		case 1:	{
			commands = MenuAuthCommands::MY_MESSAGE;
			break;
		}
		case 2:	{
			commands = MenuAuthCommands::NEW_MESSAGE;
			break;
		}		
		case 3:	{
			commands = MenuAuthCommands::EXIT;
			break;
		}
	
		default: {
			commands = MenuAuthCommands::NO_COMMANDS;
			break;
		}
	}

	return in;
}


void INTERNALFUNCTIONS::Menu::header() {
	system("cls");

	std::cout << "==============================================\n";
	std::cout << "\t Chat v." << CONSTANTS::cVERSION << "\t\n";
	std::cout << "==============================================\n";
}

// меню при успешной аторизации 
void INTERNALFUNCTIONS::Menu::main_auth(std::shared_ptr<USER::UserStruct>& user)
{
	MenuAuthCommands commands{ MenuAuthCommands::NO_COMMANDS };

	SQL::Base base;
	int newMsgCount = base.myNewMessageCount(user->id);

	do
	{
		header();

		std::cout << "Здравствуйте, " << user->first_name << "\n\n";
		
		std::cout << "1. Новые сообщения (" << newMsgCount << ")\n";
		std::cout << "2. Написать сообщение\n";
		std::cout << "3. Выход\n";
		std::cout << ">> ";
		
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		getline(std::cin, commands);		

		switch (commands)
		{
			case MenuAuthCommands::MY_MESSAGE: {
						myMessage(user);
						break;
				}
			case MenuAuthCommands::NEW_MESSAGE: {
						newMessage(user);
						break;			
				}			
			case MenuAuthCommands::EXIT:	{
					main();
					break;
				}		
		
			default: {
				std::cout << "Error input type\n";
				Sleep(3);				
			}
		}

	} while (commands == MenuAuthCommands::NO_COMMANDS);
}

// стартовое меню
void INTERNALFUNCTIONS::Menu::main() {
	
	MenuCommands commands{ MenuCommands::NO_COMMANDS };

	do {		
		header();
		
		std::cout << "1. Войти\n";
		std::cout << "2. Регистрация\n";
		std::cout << ">> ";	
		
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		getline(std::cin, commands);	

		switch (commands)
		{
			case MenuCommands::LOGIN:	{
					login(); // вход 
					break;
				}
			case MenuCommands::REGISTRATION:	{
					createNewUser(); // создаем нового пользователя
					break;
				}
			default: {
					std::cout << "Error input type\n";
					Sleep(3);					
			}			
		}

	} while (commands == MenuCommands::NO_COMMANDS);

}

// текущее время 
std::string INTERNALFUNCTIONS::getCurrentDateTime() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	struct std::tm *now_tm = std::localtime(&now_c);

	//формат год-месяц-день 00:00:00
	std::string year = std::to_string((now_tm->tm_year + 1900));

	std::string mon = std::to_string((now_tm->tm_mon + 1));
	if (mon.length() == 1) { mon = "0" + mon; }

	std::string day = std::to_string(now_tm->tm_mday);
	if (day.length() == 1) { day = "0" + day; }

	std::string hour = std::to_string(now_tm->tm_hour);
	if (hour.length() == 1) { hour = "0" + hour; }

	std::string min = std::to_string(now_tm->tm_min);
	if (min.length() == 1) { min = "0" + min; }

	std::string sec = std::to_string(now_tm->tm_sec);
	if (sec.length() == 1) { sec = "0" + sec; }

	return year + "-" + mon + "-" + day + " " + hour + ":" + min + ":" + sec;
	
}

void INTERNALFUNCTIONS::Menu::createNewUser() {
	header();
	std::cout << "Menu->Создание нового пользователя\n\n";
		
	USER::UserStruct s_user;

	std::cout << "Логин >> ";
	std::cin >> s_user.login;

	std::cout << "Имя >> ";
	std::cin >> s_user.first_name;

	std::cout << "Фамилия >> ";
	std::cin >> s_user.last_name;

	std::cout << "Пароль >> ";
	std::string temp_pwd;
	std::cin >> temp_pwd;

	std::cout << "Пароль еще раз >> ";
	std::string temp_pwd2;
	std::cin >> temp_pwd2;	
	
	if (temp_pwd != temp_pwd2) {
		std::cout << "Пароли не совпадают!\n";
		
		std::cout << "\nПопробовать еще раз? n/y?\n> ";

		std::string repeat;
		std::cin >> repeat;

		if (repeat == "y" || repeat == "н")	{
			createNewUser(); 
		}
		else {
			return main();	
		}
	}
	else {
		s_user.pwd = std::hash<std::string>()(s_user.login + "_" + temp_pwd);
	}		

	// проверка соединения с БД
	SQL::Base base;
	
	if (base.isConnectedBD()) {
		base.createNewUser(s_user);
	}
}

void INTERNALFUNCTIONS::Menu::login()
{
	header();
	std::cout << "Menu->Вход\n\n";	

	auto s_user = std::make_shared<USER::UserStruct>();

	std::cout << "Логин >> ";
	std::cin >> s_user->login;

	std::cout << "Пароль >> ";
	std::string temp_pwd;	
	std::cin >> temp_pwd;
	s_user->pwd = std::hash<std::string>()(s_user->login + "_" + temp_pwd);

	// Проверка входа
	SQL::Base base;
	if (!base.authorization(*s_user)) {
		std::cerr << "Пользователь не найден";

		std::cout << "\nПопробовать еще раз? n/y?\n> ";

		std::string repeat;
		std::cin >> repeat;

		if (repeat == "y" || repeat == "н") {
			login();
		}
		else {
			return main();
		}

		return;
	}

	// обновляем дату авторизации
	base.updateAuthTime(*s_user);	
	
	// заполним его данные + откроем доступ до сообщений	
	base.updateCurrentUserData(s_user);
	main_auth(s_user);
}


// меню отправки нового сообщения, для конкретного выбранного пользователя
void INTERNALFUNCTIONS::Menu::newMessage(std::shared_ptr<USER::UserStruct> &user) 
{
	// подгружаем базу пользователей
	SQL::Base base;	
	USER::vuser list = base.getAllUsers(user->id);	

	USER::AllUsers allusers(list);

	header();
	std::cout << "Menu->Написать сообщение\n\n";

	std::cout << "Выберите кому хотите написать:\n";
	for (int i = 0; i < allusers.size(); ++i) {
		std::cout << i + 1 << ". " << allusers.getFirstName(i) <<" "<< allusers.getLastName(i) << "[" << allusers.getID(i) << "]\n";
	}

	std::cout << allusers.size() + 1 << ". Назад\n>> ";

	int choise;	
	std::cin >> choise;
	if ((choise == allusers.size() + 1) || (choise == 0)) {
		main_auth(user);
		return;
	}

	std::cout << user->first_name << "[" << user->id << "] -> " << allusers.getFirstName(choise - 1) << "[" << allusers.getID(choise - 1) << "]: ";
	
	std::string msg;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, msg);

	base.sendNewMessage(user->id, allusers.getID(choise - 1),msg);


	do {		
		std::cout << "\nОтправить еще одно сообщение? n/y?\n> ";
		std::string repeat;
		std::cin >> repeat;
		if (repeat == "y" || repeat == "н")
		{
			std::cout << user->first_name << "[" << user->id << "] -> " << allusers.getFirstName(choise - 1) << "[" << allusers.getID(choise - 1) << "]: ";

			std::string msg;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, msg);

			base.sendNewMessage(user->id, allusers.getID(choise - 1), msg);
		}
		else
		{
			main_auth(user);
		}

	} while (true);	
}

// менюшка своих сообщений
void INTERNALFUNCTIONS::Menu::myMessage(std::shared_ptr<USER::UserStruct> &user)
{
	// подгружаем нове сообщения пользователей
	header();
	std::cout << "Menu->Мои сообщения\n\n";
		

	while (true) {
		SQL::Base base;
		base.myMessage(user->id);

		std::cout << "\nВернуться назад? n/y?\n> ";
		std::string repeat;
		std::cin >> repeat;
		if (repeat == "y" || repeat == "н")
		{
			main_auth(user);
		}		
	}
}