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



// константы из файла Constants.cpp 
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

	unsigned short countUser{ 0 }; // текущий номер пользователя для последующего выбора 

	for (vector<User> ::iterator it = g_userslist.begin(); it != g_userslist.end(); ++it) {
		if (g_currentUser.getLogin() == it->getLogin()) {
		
			cout << "\t" << countUser + 1 << ". Написать [" << g_userslist[countUser].getName() << "] (Текущий пользователь, потом убрать отображение)\n";

		}
		else {
			cout << "\t" << countUser + 1 << ". Написать [" << g_userslist[countUser].getName() << "] \n";
		}

		++countUser;
	}
	
	
	/*for (size_t i = 0; i < g_userslist.size(); ++i) 
	{
		if (g_currentUser.getLogin() == g_userslist[i].getLogin()) 
		{
			cout << "\t" << i + 1 << ". Написать [" << g_userslist[i].getName() << "] (Текущий пользователь, потом убрать отображение)\n";
		}
		else 
		{
			cout << "\t" << i + 1 << ". Написать [" << g_userslist[i].getName() << "] \n";
		}	
		
	}*/

	cout << "\t"<<g_userslist.size() + 1 << ". Выход\n\n";
	cout << "> ";	

	unsigned short choise;
	cin >> choise;
		
	do 
	{	
		if (choise > g_userslist.size() + 1 || choise <= 0)
		{
			cout << "Нет такой команды!\n" << "> ";
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

// отправка сообщения пользователь --> всем
void sendMessage() 
{
	string message;

	cout << g_currentUser.getName() << "[" << g_currentUser.getUserID() << "] --> " << "ВСЕМ" <<" : ";

	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, message, '\n');

	ChatStruct chat;
	
	chat.userIDrecipient		= -1;
	chat.userIDsender			= g_currentUser.getUserID();
	chat.message				= message;
	chat.time					= time(nullptr);
		
	g_chat.push_back(chat);

	// хотим еще одно отправить?
	cout << "Отправить еще одно сообщение? n/y?\n> ";

	char repeat;
	cin >> repeat;

	if (repeat != 'y' || repeat != 'н')
	{
		showUserList();
	}
	else
	{
		sendMessage();
	}
}

// отправка сообщения пользователь --> пользователь
void sendMessage(int userIDrecipient)
{
	int &choise = userIDrecipient;
	string message;	
	
	cout << g_currentUser.getName() << "[" << g_currentUser.getUserID() << "] --> " << g_userslist[choise - 1].getName() << "[" << g_userslist[choise - 1].getUserID() << "]" << " : ";

	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
	getline(cin, message, '\n');

	// отправим сообщение
	ChatStruct chat;

	chat.userIDsender		= g_currentUser.getUserID();
	chat.userIDrecipient	= choise;
	chat.message			= message;
	chat.time				= time(nullptr);
	

	g_chat.push_back(chat);

	// хотим еще одно отправить?
	cout << "Отправить еще одно сообщение? n/y?\n> ";
	
	char repeat;
	cin >> repeat;

	if (repeat != 'y' || repeat != 'н')
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


// проверка сообщений (для текущего пользователя)
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
			cout << "Привет, " << g_currentUser.getName() << "[" << g_currentUser.getUserID() << "]. Новых сообщений (" << countmessage << ")\n\n";
			cout << "\t 0. Прочитать сообщения\n";
		}
		else 
		{
			cout << "Привет, " << g_currentUser.getName() << "[" << g_currentUser.getUserID() << "]\n\n";
		}		
	}
	else 
	{
		cout << "Привет, " << g_currentUser.getName() << "[" << g_currentUser.getUserID() << "]\n\n";
	}
	
}

// отображение моих сообщений
void showMyMessage()
{
	menuHeader();
	
	for (const auto chat : g_chat) {
		if (g_currentUser.getUserID() == chat.getUserIDrecipient() || chat.getUserIDrecipient() == -1)
		{
			if (chat.getUserIDrecipient() == -1)
			{
				cout << "ВСЕМ (" << g_userslist[chat.getUserIDsender()].getName() << "[" << chat.getUserIDsender() << "]) : " << chat.getMessage() << "\n";
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

// менюшка после успешной авторизации
void menuAuth()
{
		
	menuHeader();
	
	// проверка есть ли сообщения
	showCountMessageCurrentUser();

	
	cout << "\t 1. Написать пользователю\n"
		 << "\t 2. Написать всем пользователям (" <<g_userslist.size() << ") \n"
		 << "\t 3. Выход\n";
	cout << "> ";

	int choise;
	bool exitnow{ false };

	cin >> choise;

	while (!exitnow)
	{
		switch (choise)
		{ 
		case 0: // есть сообщения (текущий пользователь) 
			{
			showMyMessage();
			break;
			}
		case 1: // Написать пользователю
			{
			showUserList();
			break;
			}
		case 2: // Написать всем пользователям 
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
			cout << "Нет такой команды!\n" << "> ";
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

// отображение информации о тестовых пользователях
void viewTestUsersInfo() 
{	
	cout << "Предустановленные пользователи: \n";

	for (const auto usr : g_userslist) { cout << "login: " << usr.getLogin() << "\t" << "password: " << usr.getPassword() << "\n"; }	
	cout << "\n\n";
}

void menu()
{
	
	menuHeader();
	
	int choise;
	int counterr{ 0 };

	bool exitnow{ false };

	cout << "\t1. Вход \n"
		<<  "\t2. Регистрация \n"
		<<  "\t3. Выход \n";
	cout << "> ";

	cin >> choise;
		
	while (!exitnow) 
	{
		switch (choise)
		{
		case 1: // вход
		{
			authorization();
			break;
		}
		case 2: // регистрация
		{
			createNewUser();
			break;
		}
		case 3: // выход
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
			
			cout << "Нет такой команды!\n" << "> ";
			cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin >> choise;
		}

		}
	}	
	
}


// очистка консоли
void clearconsole() 
{
	system("cls");
}


// авторизация 
void authorization()
{
	menuHeader();
	
	if (!checkExistUsersList()) 
	{
		char choise;
		cout << "ОШИБКА! Не зарегистировано ни одного пользователя! \n";
		
		cout << "Создать нового пользователя? y/n? \n";
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
	bool auth = false;					// успешная авторизация

	
	cout << "Логин: ";
	cin >> login;
	cout << "Пароль: ";	
	cin >> password;

	
	// проверка на авторизацию
	for (size_t i = 0; i < g_userslist.size(); ++i) 
	{
		if (g_userslist[i].getLogin() == login && g_userslist[i].getPassword() == password) 
		{
			auth = true;
			
			// текущий залогиненый пользователь
			g_currentUser.setName(g_userslist[i].getName());
			g_currentUser.setLogin(login);
			g_currentUser.setPassword(password);		
			g_currentUser.setUserIDManual(g_userslist[i].getUserID());
			break;
		}
	}
	
	if (auth) 
	{
		menuAuth(); // успешная авторизация
	}
	else 
	{
		cout << "ОШИБКА! логин/пароль некорректны \n";
		cout << "Повторить вход? y/n? \n";
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

// проверка на пароль ( 3 символа цифры и буквы)
bool checkNewPassword(string password) 
{
	const int size_password = 3;	// минимальная длинна пароля
	bool upper_letters = false;		// заглавные символы
	bool lower_letters = false;		// строчные символы
	bool number_letters = false;	// цифры


	// проверка на длину строки
	if (password.length() < size_password) 
	{
		cout << "Длина пароля должна быть не менее " << size_password << " символов \n\n";
		return false;		
	}
	
	// проверка на заглавные и строчные буквы
	for (int i = 0; i < password.length(); ++i) 
	{
		if ('A' <= password[i] && password[i] <= 'Z') { upper_letters = true; }
		if ('a' <= password[i] && password[i] <= 'z') { lower_letters = true; }
		if ('1' <= password[i] && password[i] <= '9') { number_letters = true; }
	}
		if (!upper_letters) 
		{
			cout << "Пароль должен содержать символы нижнего регистра.\n\n";
			return false;

		} else if (!lower_letters)
		{
			cout << "Пароль должен содержать символы верхнего регистра.\n\n";
			return false;

		} else if (!number_letters)
		{
			cout << "Пароль должен содержать хотя бы 1 цифру.\n\n";
			return false;
		}

	return true;
}


// создание нового пользователя
void createNewUser()
{
	menuHeader();

	UserStruct user;

	char choise = 'y';	

	cout << "Регистарция нового пользователя \n\n";

	cout << "Имя: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // чтобы не перескакивал на след. строку
	getline(cin, user.name, '\n');

	cout << "Логин: ";
	cin >> user.login;

	cout << "Пароль: ";
	cin >> user.password;

	// проверка на правильность пароля
	while (!checkNewPassword(user.password) || choise == 'n')
	{
		cout << "Хотите попробовать еще раз? y/n? \n";
		cout << "> ";
		cin >> choise;

		if (choise != 'n' || choise != 'т')
		{ 
			createNewUser(); 
		}
		else 
		{
			menu();
			return;
		}
	}	

	// проверка уникальности логина
	if (!g_userslist.empty()) 
	{
		for (size_t i = 0; i < g_userslist.size(); ++i) 
		{
			if (g_userslist[i].getLogin() == user.login) 
			{
				cout << "Логин не уникален, попробовать еще раз? y/n? \n";
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

	// создаем нового пользователя
	User newuser(user);

	g_userslist.push_back(newuser);
	cout << "Пользователь " << newuser.getName() << " создан \n\n";
	
	if (DEBUG) 
	{
		cout << "Создать нового пользователя? y/n? \n";
		cout << "> ";

		cin >> choise;
		cout << "> ";
		if (choise == 'y' || choise == 'н')
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

// проверка есть ли пользователи зарегистрированные
bool checkExistUsersList()
{
	return (g_userslist.empty() ? false : true);
}


