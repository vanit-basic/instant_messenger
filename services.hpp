#ifndef SERVICES_HPP
#define SERVICES_HPP
class Service {
	public:
		connection DBconnection;
		void send(std::string);
		std::string recive();
		std::string getAction(std::string);
		Service(std::string url);
		~Service();
}

class Authetification:public Service {
	public:
		std::string registerUser(std::string userInfo);
		std::string loginUser (std::string login, std::string password);
		std::string forgotPassword(std::string Email);
		std::string enterCode(std::string conde);

		Authetification(std::string url);
		~Authetification();
}

class Conversation:public Service {
	public:	
		bool addUserMessage(std::string from,std::string to,std::string massageInfo);
		bool removeUserConversation(std::string fromUserId,std::string toUserId);
		bool removeMessageFromUserConversation(std::string fromId,std::toId,std::string messageId);
		bool removeGroupConversation(std::string groupInfo);
		bool removeMessageFromGroupConversation(std::string groupInfo);
		std::string getUserConversation(std::string fromId,std::string toId);
		std::string getUserConversations(std::string userId);
		std::string getGroupconversation (std::string userId,std::string groupId);
		std::string updateGroupMessage (std::string groupId,std::sstring messBody);

		Conversation(std::string url);
		~Conversation();
}

class Account:public Service{
	public:
		bool deleteUser (std::string userId);
		bool deleteGroup (std::string groupId);
		bool updateUserInfo (std::string userInfo);
		bool updateGroupInfo(std::string groupInfo);
		bool addUserToGroup(std::string groupId,std::string userId);
		bool removeFromGroup(std::string groupId,std::string userId);
		bool singnOut(std::string userId);
		std::string getUserInfo(std::string userId);
		std::string getUserShortInfo(std::string userId);
		std::string getGroupInfo(std::string groupId);
		std::string getGroupUsers(std::string groupId);
		std::string createGroup(std::string groupInfo);

		Account(std::string url);
		~Account();

}

class Game:public Service {
	public:

}

class Notification:public Service {
	public:

}

#endif
