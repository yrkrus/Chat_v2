
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
		bool isConnectedBD();													// ���� �� ������� � ��
		void createNewUser(const USER::UserStruct &newuser);					// �������� ������ ������������		
		bool authorization(const USER::UserStruct &user);						// ������������		
		void updateAuthTime(const USER::UserStruct &user);						// ���������� ���� �������� �����������
		void updateCurrentUserData(std::shared_ptr<USER::UserStruct> &user);	// ���������� ������ �������� ������������

		USER::vuser getAllUsers(const int id);	// ��������� ���� �������� �������������(����� ������ ����);			

		void sendNewMessage(const int sender, const int recipient, const std::string &message);				// ��������� � �� ������ ���������
		void myMessage(const int id);			// ��������� ����� ���������

		int myNewMessageCount(const int id);	// ���-�� ����� ���������

	private:
		MYSQL mysql;
		void createMySQLConnect(MYSQL &mysql);				// ������������ � �� MySQL			
	};


	void showErrorBD(const std::string str, MYSQL *mysql);	// ����������� ������ ��� SQL ������� 
	void showErrorBD(const std::string str);				// ������ ����������� � ��
};


#endif // SQLREQUEST_H

