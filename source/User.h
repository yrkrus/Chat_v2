#include <iostream>
#include <vector>
#include <string>

#ifndef USER_H
#define USER_H


namespace USER {

	struct UserStruct
	{
		std::string login;			// �����
		std::string first_name;		// ���
		std::string last_name;		// �������
		size_t pwd{ 0 };			// ������������ ������
		int id{ 0 };				// id ������������
	};
	
	using vuser = std::vector<std::shared_ptr<USER::UserStruct>>;	

	class AllUsers : public UserStruct
	{
	public:
		AllUsers() = delete;
		AllUsers(vuser &list) : list(list) {};
		~AllUsers() = default;		

		std::string getLogin(int list_id);
		std::string getFirstName(int list_id);
		std::string getLastName(int list_id);
		int getID(int list_id);

		int size();		
		bool empty(); 

	private:
		vuser list;
	};	

};


#endif // USER_H
