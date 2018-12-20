#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>

class database {

	//Public pure virtual functions
	public:
		//user related queries
		virtual std::string registerUser(std::string userInfo) = 0;
		
		virtual std::string loginUser(std::string login, std::string password) = 0;

		virtual bool updateUserInfo(std::string userInfo) = 0;
		
		virtual std::string getUserInfo(std::string userID) = 0;
	
		virtual std::string getUserShortInfo(std::string userID) = 0;

		virtual std::string getUserConversations(std::string userID) = 0;
		
		virtual std::string getUsersConversation(std::string fromID, std::string toID) = 0;
		
		virtual std::string addUserMessage(std::string from, std::string to, std::string message) = 0;

		virtual bool updateUserMessage(std::string updateInfo) = 0;

		virtual bool deleteUser(std::string userId) = 0;

		virtual bool updateGroupMessage(std::string groupId, std::string messId, std::string messBody) = 0;
                virtual bool removeUserConversation(std::string fromUserId, std::string toUserId) = 0;

		//group related queries
		
		virtual std::string createGroup(std::string groupInfo) = 0;

                virtual bool deleteGroup(std::string groupID) = 0;

		virtual bool addUserToGroup(std::string groupID, std::string userID) = 0;

                virtual bool removeFromGroup(std::string groupID, std::string userID) = 0;

                virtual bool removeMessage(std::string messageInfo) = 0;

                virtual bool removeGroupConversation(std::string groupInfo) = 0;

		virtual bool removeMessageFromGroupConversation(std::string groupInfo) = 0;
		
		virtual std::string getGroupInfo(std::string groupID) = 0;
		
		virtual std::string getGroupConversation(std::string userID, std::string groupID) = 0;
		
		virtual bool updateGroupInfo(std::string groupInfo) = 0;

		virtual std::string addGroupMessage(std::string groupId, std::string userId, std::string message) = 0;

		virtual std::string getGroupUsers(std::string groupId) = 0;
	public:
		database() {}
		~database() {}

};

#endif
