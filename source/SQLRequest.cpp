#include <iostream>
#include <sstream>
#include "SQLRequest.h"
#include "CONSTANTS.h"
#include "InternalFunctions.h"



#ifdef _WIN32
#include <include/mysql/mysql.h>
#elif __linux__
#include "mysql/mysql.h"
#endif


// подлючение к БД
SQL::Base::Base()
{
	createMySQLConnect(this->mysql);
}

// есть ли коннект с БД
bool SQL::Base::isConnectedBD()
{
	// status = 0 значит коннект есть
	if (mysql_ping(&this->mysql) != 0)
	{
		createMySQLConnect(this->mysql);

		isConnectedBD();
	}
	else
	{
		return true;
	}
}

void SQL::showErrorBD(const std::string str, MYSQL *mysql) {
	
	std::cerr << str << "\n" << mysql_error(mysql) << "\n";
}

void SQL::showErrorBD(const std::string str)
{
	std::cerr << str << " -> Error: can't connect to database " << CONSTANTS::cHOST << ":" << CONSTANTS::cBD << "\n";
}

// подключаемся к БД MySQL
void SQL::Base::createMySQLConnect(MYSQL &mysql)
{
	const char *host	= CONSTANTS::cHOST.c_str();
	const char *login	= CONSTANTS::cLOGIN.c_str();
	const char *pwd		= CONSTANTS::cPASSWORD.c_str();
	const char *bd		= CONSTANTS::cBD.c_str();

	if (mysql_init(&mysql) == nullptr)
	{
		// Если дескриптор не получен — выводим сообщение об ошибке
		showErrorBD("Error: can't create MySQL-descriptor");
		return;
	}

	if (!mysql_real_connect(&mysql, host, login, pwd, bd, NULL, NULL, 0))
	{
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		showErrorBD("SQL::Base::createMySQLConnect -> Error: can't connect to database", &mysql);
		return;
	};

	mysql_set_character_set(&mysql, "cp1251");
}

void SQL::Base::createNewUser(const USER::UserStruct &newuser) {
	
	std::string query = "insert into users (login,pwd,first_name,last_name,state) values ('" 
											+ newuser.login + "','"
											+ std::to_string(newuser.pwd) + "','"
											+ newuser.first_name + "','"
											+ newuser.last_name + "','"
											+ "1')";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		showErrorBD("SQL::Base -> (createNewUser) error -> " + query, &this->mysql);
		return;
	}

	std::cout << "Новый пользователь зарегистрирован\n";
	std::cout << "\nХотите войти в чат? n/y?\n> ";
	char choise;
	std::cin >> choise;

	INTERNALFUNCTIONS::Menu menu;

	if (choise == 'y' || choise == 'н')
	{
		menu.login();
	}
	else
	{
		menu.main();
	}
}

bool SQL::Base::authorization(const USER::UserStruct &user) 
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL::Base::authorization");
		return false;
	}

	const std::string query = "select count(login) from users where login = '" + user.login + "' and pwd = '"+std::to_string(user.pwd)+"'";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ошибка считаем что есть запись		
		showErrorBD("SQL::Base::authorization -> " + query, &this->mysql);
		return false;
	}

	// результат
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);
	mysql_free_result(result);

	// mysql_close(&this->mysql); тут возможно ннадо будет вкл. понаблюдать за утечкой коннектов в mysql

	return (std::stoi(row[0]) == 0 ? false : true);

}

void SQL::Base::updateAuthTime(const USER::UserStruct &user)
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL::Base::updateAuthTime");
		return;
	}

	std::string query = "update users set last_login = '" + INTERNALFUNCTIONS::getCurrentDateTime() + "' where login = '" + user.login + "' and pwd = '"+std::to_string(user.pwd)+"'";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		showErrorBD("SQL::Base -> (updateAuthTime) error -> " + query, &this->mysql);
	};

	mysql_close(&this->mysql);
}

void SQL::Base::updateCurrentUserData(std::shared_ptr<USER::UserStruct> &user) 
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL::Base::updateCurrentUserData");
		return;
	}

	const std::string query = "select id,first_name,last_name from users where login ='"+user->login + "'";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ошибка считаем что есть запись		
		showErrorBD("SQL::Base -> (updateCurrentUserData) error -> " + query, &this->mysql);
		return;
	}

	// результат
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row;

	while ((row = mysql_fetch_row(result)) != NULL)
	{		
		for (int i = 0; i < mysql_num_fields(result); ++i)
		{
			if (i == 0)
			{
				user->id = std::atoi(row[i]);
			}
			else if (i == 1)
			{
				user->first_name = row[i];
			}
			else if (i == 2)
			{
				user->last_name = row[i];
			}
		}	
	}

	mysql_free_result(result);
	mysql_close(&this->mysql);
}


// получение всех активных пользователей(кроме самого себя);
USER::vuser SQL::Base::getAllUsers(const int id) {
	
	USER::vuser list;
	list.emplace_back(std::make_shared<USER::UserStruct>());
	
	if (!isConnectedBD())
	{
		showErrorBD("SQL::Base::getAllUsers");
		return list;
	}

	const std::string query = "select id,login,first_name,last_name from users where state ='1' and id <> '"+std::to_string(id)+"'";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{		
		showErrorBD("SQL::Base -> (getAllUsers) error -> " + query, &this->mysql);
		return list;
	}

	// результат
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row;
	int users_count{ 0 };	

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		// эта чась нужна т.к. без нее лишний shared_ptr делается с nullptr данными
		if (users_count != 0) {
			list.emplace_back(std::make_shared<USER::UserStruct>());
		}
		
		for (int i = 0; i < mysql_num_fields(result); ++i)
		{
			switch (i)
			{
				case 0:	{
					list[users_count]->id = std::atoi(row[i]);
					break;
				}
				case 1:
				{
					list[users_count]->login = row[i];
					break;
				}
				case 2:
				{
					list[users_count]->first_name = row[i];
					break;
				}
				case 3:
				{
					list[users_count]->last_name = row[i];
					break;
				}
			}		
			
		}			
		++users_count;		
	}

	mysql_free_result(result);
	mysql_close(&this->mysql);

	return list;
}

// занесение в бд нового сообщения
void SQL::Base::sendNewMessage(const int sender, const int recipient, const std::string &message)
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL::Base::sendNewMessage");
		return;
	}

	std::string query = "insert into message (sender,recipient,msg) values ('"
		+ std::to_string(sender) + "','"
		+ std::to_string(recipient) + "','"
		+ message + "')";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		showErrorBD("SQL::Base -> (sendNewMessage) error -> " + query, &this->mysql);
		return;
	}
}

// подгрузка новых сообщений
void SQL::Base::myMessage(const int id)
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL::Base::myMessage");
		return;
	}

	const std::string query = "select msg_time,msg from message where is_view = '0' and recipient = '" + std::to_string(id) + "'";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		showErrorBD("SQL::Base -> (myMessage) error -> " + query, &this->mysql);		
	}

	// результат
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row;
	//int msg_count{ 0 };

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		std::ostringstream buffer;
		
		for (int i = 0; i < mysql_num_fields(result); ++i)
		{
			switch (i)
			{
				case 0:
				{
					buffer << row[i] << ": ";			
					break;
				}
				case 1:
				{
					buffer << row[i]<<"\n";
					break;
				}			
			}
		}
		std::cout << buffer.str();
	}

	mysql_free_result(result);
	mysql_close(&this->mysql);

}

// кол-во новых сообщений
int SQL::Base::myNewMessageCount(const int id) 
{
	if (!isConnectedBD())
	{
		showErrorBD("SQL::Base::myNewMessageCount");
		return 0;
	}

	const std::string query = "select count(msg) from message where is_view = '0' and recipient = '" + std::to_string(id) + "'";

	if (mysql_query(&this->mysql, query.c_str()) != 0)
	{
		// ошибка считаем что есть запись		
		showErrorBD("SQL::Base::myNewMessageCount -> " + query, &this->mysql);
		return 0;
	}

	// результат
	MYSQL_RES *result = mysql_store_result(&this->mysql);
	MYSQL_ROW row = mysql_fetch_row(result);
	mysql_free_result(result);

	// mysql_close(&this->mysql); тут возможно ннадо будет вкл. понаблюдать за утечкой коннектов в mysql

	return std::atoi(row[0]);
}
 
