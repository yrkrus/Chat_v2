
#ifdef _WIN32
#include <include/mysql/mysql.h>
#elif __linux__
#include "mysql/mysql.h"
#endif

#include "User.h"


#ifndef SQLREQUEST_H
#define SQLREQUEST_H

namespace SQL
{
	class Base
	{
	public:
		Base();
		~Base() = default;
		bool isConnectedBD();													// есть ли коннект с БД
		void createNewUser(const USER::UserStruct &newuser);					// создание нового пользователя		
		bool authorization(const USER::UserStruct &user);						// автороизация		
		void updateAuthTime(const USER::UserStruct &user);						// обновление даты успешной атворизации
		void updateCurrentUserData(std::shared_ptr<USER::UserStruct> &user);	// обновление данных текущего пользователя

		USER::vuser getAllUsers(const int id);	// получение всех активных пользователей(кроме самого себя);			

		void sendNewMessage(const int sender, const int recipient, const std::string &message);				// занесение в бд нового сообщения
		void myMessage(const int id);			// подгрузка новых сообщений

		int myNewMessageCount(const int id);	// кол-во новых сообщений

	private:
		MYSQL mysql;
		void createMySQLConnect(MYSQL &mysql);				// подключаемся к БД MySQL			
	};


	void showErrorBD(const std::string str, MYSQL *mysql);	// отображение ошибки при SQL запросе 
	void showErrorBD(const std::string str);				// ошибка подключения к БД
};


#endif // SQLREQUEST_H

