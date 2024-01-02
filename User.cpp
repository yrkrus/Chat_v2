#include "User.h"
#include <vector>;
#include "Chat.h"


// константы из файла Constants.cpp
extern unsigned short USERIDGLOBAL;			// ID user


User::User()
{
}

User::User(UserStruct user) : 
	_user(user)
{
	setUserID();
}


User::~User()
{
}

void User::setName(std::string name)
{
	_user.name = name;
}

std::string User::getName() const
{
	return _user.name;
}

void User::setLogin(std::string login)
{
	_user.login = login;
}

std::string User::getLogin() const
{
	return _user.login;
}

void User::setPassword(std::string password)
{
	_user.password = password;
}

std::string User::getPassword() const
{
	return _user.password;
}

void User::setUserID()
{
	++USERIDGLOBAL;
	_user.userID = USERIDGLOBAL;
}

void User::setUserIDManual(unsigned short ID)
{
	_user.userID = ID;
}

int User::getUserID() const
{
	return _user.userID;
}

void User::clear()
{
	_user.userID	= 0;
	_user.name		= "";
	_user.login		= "";
	_user.password	= "";
	
}





