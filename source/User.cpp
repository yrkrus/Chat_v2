#include "User.h"
#include <iterator>

std::string USER::AllUsers::getLogin(int list_id)
{	
	return (!list.empty() ? list[list_id]->login : "null");		
}

std::string USER::AllUsers::getFirstName(int list_id)
{
	return (!list.empty() ? list[list_id]->first_name : "null");
}

std::string USER::AllUsers::getLastName(int list_id)
{
	return (!list.empty() ? list[list_id]->last_name : "null");
}

int USER::AllUsers::getID(int list_id)
{
	return (!list.empty() ? list[list_id]->id : 0);
}

int USER::AllUsers::size()
{
	return list.size();
}

bool USER::AllUsers::empty()
{
	return list.empty();
}

