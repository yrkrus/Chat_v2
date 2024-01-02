#include <string>
#include <iostream>
#include <vector>


#define USER_H
#ifdef USER_H

using std::string;

struct UserStruct
{
	string name;
	string login;
	string password;
	unsigned short userID;
};

// ����� ������������
class User
{
public:
	
	// ����������� | ����������
	User();
	User(UserStruct user);
	~User();


	// ������� ������
	void setName(string name);
	std::string getName() const;

	void setLogin(std::string login);
	std::string getLogin() const;

	void setPassword(std::string password);
	std::string getPassword() const;

	void setUserID();
	void setUserIDManual(unsigned short ID);
	int getUserID() const;

	void clear();

private:
	UserStruct _user;

};



#endif // USER_H





