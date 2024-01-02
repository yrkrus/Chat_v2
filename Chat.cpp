#include "Chat.h"
#include <vector>

extern std::vector<Chat> g_chat;			// список с чатом текущего пользователя (написать конкретному пользователю)

Chat::Chat()
{
}

Chat::Chat(ChatStruct chat)
	: _chat(chat)
{
}


Chat::~Chat()
{
}

//void Chat::sendMessage()
//{
//
//}

int Chat::getUserIDrecipient() const
{
	return _chat.userIDrecipient;
}

int Chat::getUserIDsender() const
{
	return _chat.userIDsender;
		
}

std::string Chat::getMessage() const
{
	return _chat.message;
		
}
