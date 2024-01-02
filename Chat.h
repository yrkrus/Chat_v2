#include <vector>
#include <string>

#define CHAT_H
#ifdef CHAT_H

using std::string;


struct ChatStruct
{
	string message;
	unsigned int userIDsender;		// отправитель
	unsigned int userIDrecipient;	// получатель
	time_t time;
};

class Chat
{
public:
	Chat();
	Chat(ChatStruct chat);

	~Chat();

	//void sendMessage();

	int getUserIDrecipient() const;
	int getUserIDsender() const;
	string getMessage() const;

private:
	ChatStruct _chat;
};


#endif // CHAT_H


