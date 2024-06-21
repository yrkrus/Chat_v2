#include <string>
#include <memory>
#include "User.h"

#ifndef INTERNALFUNCTIONS_H
#define INTERNALFUNCTIONS_H



namespace INTERNALFUNCTIONS
{
	
	enum class MenuCommands
	{
		NO_COMMANDS		= 0,	// �� ������� ������� �������
		LOGIN			= 1,	// ����
		REGISTRATION	= 2,	// �����������	
	};	

	enum class MenuAuthCommands
	{
		NO_COMMANDS		= 0,	// �� ������� ������� �������
		MY_MESSAGE		= 1,	// ��� ��������� c ������ �����
		NEW_MESSAGE		= 2,	// �������� ���������	
		EXIT			= 3,	// �����
	};

	std::istream &operator>>(std::istream &in, MenuCommands &commands);	
	std::istream &operator>>(std::istream &in, MenuAuthCommands &commands);	
	

	std::istream &getline(std::istream &in, MenuCommands &commands);
	std::istream &getline(std::istream &in, MenuAuthCommands &commands);

	struct Menu
	{
		Menu()	= default;
		~Menu() = default;

		void header();		// ������� ����
		void footer();		// ������ ����

		void main();												// ��������� ����
		void createNewUser();										// �������� ������ ������������
		void login();												// ���� �����	
		void main_auth(std::shared_ptr<USER::UserStruct>& user);	// ���� �������� �����������
		void newMessage(std::shared_ptr<USER::UserStruct>& user);	// ���� �������� ������ ���������, ��� ����������� ���������� ������������
		void myMessage(std::shared_ptr<USER::UserStruct>& user);	// ������� ������ ���������

	};


	std::string getCurrentDateTime(); // ������� ����� 

};


#endif // INTERNALFUNCTIONS_H
