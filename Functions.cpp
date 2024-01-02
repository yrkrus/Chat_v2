#include "Functions.h"
#include "User.h"
#include "Chat.h"
#include <iostream>
#include <limits>
#include <vector>
#include <iterator>
#include <string>
#include <cstdlib>
#include <ctime>


using std::vector;
using std::cout;
using std::string;
using std::cin;



// ��������� �� ����� Constants.cpp 
extern bool const DEBUG;
extern unsigned short TESTUSERS;


vector<User> g_userslist;
User g_currentUser;
vector<Chat> g_globalchat;
vector<Chat> g_chat;



void createTestUsers() 
{
	const int SIZE_USERS = TESTUSERS;
	
	for (int i = 0; i < SIZE_USERS; ++i) 
	{
		UserStruct user;	
		
		user.name		= "User"+std::to_string(i);
		user.login		=  std::to_string(i);
		user.password	=  std::to_string(i);
		
		User newuser(user);

		g_userslist.push_back(newuser);
	}
}


void createTestMessage() 
{
	const int SIZE_USERS = TESTUSERS;

	for (int i = 0; i < SIZE_USERS; ++i)
	{
		ChatStruct chat;

		chat.message			= "Hello, world!";
		chat.userIDsender		= i;
		chat.userIDrecipient	= i + 1;
		chat.time				= time(nullptr);

		g_chat.push_back(chat);					
	}
}


void showUserList()
{
	menuHeader();	

	unsigned short countUser{ 0 }; // ������� ����� ������������ ��� ������������ ������ 

	for (vector<User> ::iterator it = g_userslist.begin(); it != g_userslist.end(); ++it) {
		if (g_currentUser.getLogin() == it->getLogin()) {
		
			cout << "\t" << countUser + 1 << ". �������� [" << g_userslist[countUser].getName() << "] (������� ������������, ����� ������ �����������)\n";

		}
		else {
			cout << "\t" << countUser + 1 << ". �������� [" << g_userslist[countUser].getName() << "] \n";
		}

		++countUser;
	}
	
	
	/*for (size_t i = 0; i < g_userslist.size(); ++i) 
	{
		if (g_currentUser.getLogin() == g_userslist[i].getLogin()) 
		{
			cout << "\t" << i + 1 << ". �������� [" << g_userslist[i].getName() << "] (������� ������������, ����� ������ �����������)\n";
		}
		else 
		{
			cout << "\t" << i + 1 << ". �������� [" << g_userslist[i].getName() << "] \n";
		}	
		
	}*/

	cout << "\t"<<g_userslist.size() + 1 << ". �����\n\n";
	cout << "> ";	

	unsigned short choise;
	cin >> choise;
		
	do 
	{	
		if (choise > g_userslist.size() + 1 || choise <= 0)
		{
			cout << "��� ����� �������!\n" << "> ";
			cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin >> choise;
		}
		else if (choise == g_userslist.size() + 1)
		{
			menuAuth();			
		}
		else {
			sendMessage(choise);
		}

	} while (choise == g_userslist.size() + 1);	

}

// �������� ��������� ������������ --> ����
void sendMessage() 
{
	string message;

	cout << g_currentUser.getName() << "[" << g_currentUser.getUserID() << "] --> " << "����" <<" : ";

	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, message, '\n');

	ChatStruct chat;
	
	chat.userIDrecipient		= -1;
	chat.userIDsender			= g_currentUser.getUserID();
	chat.message				= message;
	chat.time					= time(nullptr);
		
	g_chat.push_back(chat);

	// ����� ��� ���� ���������?
	cout << "��������� ��� ���� ���������? n/y?\n> ";

	char repeat;
	cin >> repeat;

	if (repeat != 'y' || repeat != '�')
	{
		showUserList();
	}
	else
	{
		sendMessage();
	}
}

// �������� ��������� ������������ --> ������������
void sendMessage(int userIDrecipient)
{
	int &choise = userIDrecipient;
	string message;	
	
	cout << g_currentUser.getName() << "[" << g_currentUser.getUserID() << "] --> " << g_userslist[choise - 1].getName() << "[" << g_userslist[choise - 1].getUserID() << "]" << " : ";

	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
	getline(cin, message, '\n');

	// �������� ���������
	ChatStruct chat;

	chat.userIDsender		= g_currentUser.getUserID();
	chat.userIDrecipient	= choise;
	chat.message			= message;
	chat.time				= time(nullptr);
	

	g_chat.push_back(chat);

	// ����� ��� ���� ���������?
	cout << "��������� ��� ���� ���������? n/y?\n> ";
	
	char repeat;
	cin >> repeat;

	if (repeat != 'y' || repeat != '�')
	{ 
		showUserList(); 
	}
	else 
	{
		sendMessage(choise);
	}
}

void exitCurrentUser()
{
	g_currentUser.clear();
}

void exitNow()
{
	exit(0);
}

void menuHeader()
{
	clearconsole();

	if (DEBUG) { viewTestUsersInfo(); }

	cout << "================ C H A T ================ \n\n";          

}


// �������� ��������� (��� �������� ������������)
void showCountMessageCurrentUser() 
{
	if (!g_chat.empty()) 
	{
		int countmessage = 0;
		
		for (size_t i = 0; i<g_chat.size(); ++i ) 
		{
			if (g_currentUser.getUserID() == g_chat[i].getUserIDrecipient() || g_chat[i].getUserIDrecipient() == -1)
			{
				countmessage++;
			}
		}
	
		if (countmessage > 0) 
		{
			cout << "������, " << g_currentUser.getName() << "[" << g_currentUser.getUserID() << "]. ����� ��������� (" << countmessage << ")\n\n";
			cout << "\t 0. ��������� ���������\n";
		}
		else 
		{
			cout << "������, " << g_currentUser.getName() << "[" << g_currentUser.getUserID() << "]\n\n";
		}		
	}
	else 
	{
		cout << "������, " << g_currentUser.getName() << "[" << g_currentUser.getUserID() << "]\n\n";
	}
	
}

// ����������� ���� ���������
void showMyMessage()
{
	menuHeader();
	
	for (const auto chat : g_chat) {
		if (g_currentUser.getUserID() == chat.getUserIDrecipient() || chat.getUserIDrecipient() == -1)
		{
			if (chat.getUserIDrecipient() == -1)
			{
				cout << "���� (" << g_userslist[chat.getUserIDsender()].getName() << "[" << chat.getUserIDsender() << "]) : " << chat.getMessage() << "\n";
			}
			else
			{
				cout << g_userslist[chat.getUserIDsender()].getName() << "[" << chat.getUserIDsender() << "]: " << chat.getMessage() << "\n";
			}
		}
	}
	
	cout << "\n\n";

	system("pause");

	menuAuth();
}

// ������� ����� �������� �����������
void menuAuth()
{
		
	menuHeader();
	
	// �������� ���� �� ���������
	showCountMessageCurrentUser();

	
	cout << "\t 1. �������� ������������\n"
		 << "\t 2. �������� ���� ������������� (" <<g_userslist.size() << ") \n"
		 << "\t 3. �����\n";
	cout << "> ";

	int choise;
	bool exitnow{ false };

	cin >> choise;

	while (!exitnow)
	{
		switch (choise)
		{ 
		case 0: // ���� ��������� (������� ������������) 
			{
			showMyMessage();
			break;
			}
		case 1: // �������� ������������
			{
			showUserList();
			break;
			}
		case 2: // �������� ���� ������������� 
			{
			sendMessage();
			break;
			}
		case 3:
		{
			exitnow = true;
			break;
		}
		default:
		{
			cout << "��� ����� �������!\n" << "> ";
			cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin >> choise;
		}
		}
	}

	exitCurrentUser();
	menu();
	return;
}

// ����������� ���������� � �������� �������������
void viewTestUsersInfo() 
{	
	cout << "����������������� ������������: \n";

	for (const auto usr : g_userslist) { cout << "login: " << usr.getLogin() << "\t" << "password: " << usr.getPassword() << "\n"; }	
	cout << "\n\n";
}

void menu()
{
	
	menuHeader();
	
	int choise;
	int counterr{ 0 };

	bool exitnow{ false };

	cout << "\t1. ���� \n"
		<<  "\t2. ����������� \n"
		<<  "\t3. ����� \n";
	cout << "> ";

	cin >> choise;
		
	while (!exitnow) 
	{
		switch (choise)
		{
		case 1: // ����
		{
			authorization();
			break;
		}
		case 2: // �����������
		{
			createNewUser();
			break;
		}
		case 3: // �����
		{
			exitNow();
		}
		default:
		{
			++counterr;

			if (counterr > 3) 
			{
				counterr = 0;
				menu();
			};
			
			cout << "��� ����� �������!\n" << "> ";
			cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin >> choise;
		}

		}
	}	
	
}


// ������� �������
void clearconsole() 
{
	system("cls");
}


// ����������� 
void authorization()
{
	menuHeader();
	
	if (!checkExistUsersList()) 
	{
		char choise;
		cout << "������! �� ��������������� �� ������ ������������! \n";
		
		cout << "������� ������ ������������? y/n? \n";
		cout << "> ";
		cin >> choise;
		if (choise != 'n')
		{
			createNewUser();
		}		

		menu();
		return;
	}

	std::string name,login,password;
	bool auth = false;					// �������� �����������

	
	cout << "�����: ";
	cin >> login;
	cout << "������: ";	
	cin >> password;

	
	// �������� �� �����������
	for (size_t i = 0; i < g_userslist.size(); ++i) 
	{
		if (g_userslist[i].getLogin() == login && g_userslist[i].getPassword() == password) 
		{
			auth = true;
			
			// ������� ����������� ������������
			g_currentUser.setName(g_userslist[i].getName());
			g_currentUser.setLogin(login);
			g_currentUser.setPassword(password);		
			g_currentUser.setUserIDManual(g_userslist[i].getUserID());
			break;
		}
	}
	
	if (auth) 
	{
		menuAuth(); // �������� �����������
	}
	else 
	{
		cout << "������! �����/������ ����������� \n";
		cout << "��������� ����? y/n? \n";
		cout << "> ";
		
		char choise;
		cin >> choise;

		if (choise == 'y')
		{
			authorization();
		}
		else 
		{
			menu();
		}

	}
}

// �������� �� ������ ( 3 ������� ����� � �����)
bool checkNewPassword(string password) 
{
	const int size_password = 3;	// ����������� ������ ������
	bool upper_letters = false;		// ��������� �������
	bool lower_letters = false;		// �������� �������
	bool number_letters = false;	// �����


	// �������� �� ����� ������
	if (password.length() < size_password) 
	{
		cout << "����� ������ ������ ���� �� ����� " << size_password << " �������� \n\n";
		return false;		
	}
	
	// �������� �� ��������� � �������� �����
	for (int i = 0; i < password.length(); ++i) 
	{
		if ('A' <= password[i] && password[i] <= 'Z') { upper_letters = true; }
		if ('a' <= password[i] && password[i] <= 'z') { lower_letters = true; }
		if ('1' <= password[i] && password[i] <= '9') { number_letters = true; }
	}
		if (!upper_letters) 
		{
			cout << "������ ������ ��������� ������� ������� ��������.\n\n";
			return false;

		} else if (!lower_letters)
		{
			cout << "������ ������ ��������� ������� �������� ��������.\n\n";
			return false;

		} else if (!number_letters)
		{
			cout << "������ ������ ��������� ���� �� 1 �����.\n\n";
			return false;
		}

	return true;
}


// �������� ������ ������������
void createNewUser()
{
	menuHeader();

	UserStruct user;

	char choise = 'y';	

	cout << "����������� ������ ������������ \n\n";

	cout << "���: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // ����� �� ������������ �� ����. ������
	getline(cin, user.name, '\n');

	cout << "�����: ";
	cin >> user.login;

	cout << "������: ";
	cin >> user.password;

	// �������� �� ������������ ������
	while (!checkNewPassword(user.password) || choise == 'n')
	{
		cout << "������ ����������� ��� ���? y/n? \n";
		cout << "> ";
		cin >> choise;

		if (choise != 'n' || choise != '�')
		{ 
			createNewUser(); 
		}
		else 
		{
			menu();
			return;
		}
	}	

	// �������� ������������ ������
	if (!g_userslist.empty()) 
	{
		for (size_t i = 0; i < g_userslist.size(); ++i) 
		{
			if (g_userslist[i].getLogin() == user.login) 
			{
				cout << "����� �� ��������, ����������� ��� ���? y/n? \n";
				cout << "> ";
				cin >> choise;

				if (choise != 'n')
				{
					createNewUser();
				}
				else
				{
					menu();
					return;
				}
			}
		}
	}

	// ������� ������ ������������
	User newuser(user);

	g_userslist.push_back(newuser);
	cout << "������������ " << newuser.getName() << " ������ \n\n";
	
	if (DEBUG) 
	{
		cout << "������� ������ ������������? y/n? \n";
		cout << "> ";

		cin >> choise;
		cout << "> ";
		if (choise == 'y' || choise == '�')
		{
			createNewUser();
		}
		else 
		{
			menu();
			return;
		}
	}

	menu();
	return;
}

// �������� ���� �� ������������ ������������������
bool checkExistUsersList()
{
	return (g_userslist.empty() ? false : true);
}


