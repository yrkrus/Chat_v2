#include <string>
#include <memory>
#include "User.h"

#ifndef INTERNALFUNCTIONS_H
#define INTERNALFUNCTIONS_H



namespace INTERNALFUNCTIONS
{
	
	enum class MenuCommands
	{
		NO_COMMANDS		= 0,	// не выбрана никакая команда
		LOGIN			= 1,	// вход
		REGISTRATION	= 2,	// регистрация	
	};	

	enum class MenuAuthCommands
	{
		NO_COMMANDS		= 0,	// не выбрана никакая команда
		MY_MESSAGE		= 1,	// Мои сообщения c учетом новых
		NEW_MESSAGE		= 2,	// написать сообщение	
		EXIT			= 3,	// выход
	};

	std::istream &operator>>(std::istream &in, MenuCommands &commands);	
	std::istream &operator>>(std::istream &in, MenuAuthCommands &commands);	
	

	std::istream &getline(std::istream &in, MenuCommands &commands);
	std::istream &getline(std::istream &in, MenuAuthCommands &commands);

	struct Menu
	{
		Menu()	= default;
		~Menu() = default;

		void header();		// верхнее меню
		void footer();		// нижнее меню

		void main();												// стартовое меню
		void createNewUser();										// создание нового пользователя
		void login();												// меню входа	
		void main_auth(std::shared_ptr<USER::UserStruct>& user);	// меню успешной авторизации
		void newMessage(std::shared_ptr<USER::UserStruct>& user);	// меню отправки нового сообщения, для конкретного выбранного пользователя
		void myMessage(std::shared_ptr<USER::UserStruct>& user);	// менюшка свойих сообщений

	};


	std::string getCurrentDateTime(); // текущее время 

};


#endif // INTERNALFUNCTIONS_H
