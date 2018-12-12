#include <string>

class database {

	//Public pure virtual functions
	public:
		//user related queries
		virtual std::string registerUser(std::string userInfo) = 0;
		
		virtual std::string loginUser(std::string login, std::string password) = 0;

		virtual bool updateUserInfo(std::string userInfo) = 0;
		
		virtual std::string getUserInfo(std::string userID) = 0;
		
		virtual std::string getUserConversations(std::string userID) = 0;
		
		virtual std::string getUsersConversation(std::string fromID, std::string toID) = 0;
		
		virtual bool addUserMessage(std::string messageInfo) = 0;

		//group related queries
		
		virtual std::string createGroup(std::string groupInfo) = 0;

                virtual bool deleteGroup(std::string groupID) = 0;

		virtual bool addUserToGroup(std::string groupID, std::string userID) = 0;

                virtual bool removeFromGroup(std::string groupID, std::string userID) = 0;

                virtual bool removeMessage(std::string messageInfo) = 0;

                virtual bool removeGroupConversation(std::string groupInfo) = 0;
		
		virtual std::string getGroupInfo(std::string groupID) = 0;
		
		virtual std::string getGroupConversation(std::string groupID) = 0;
		
		virtual std::string updateGroupInfo(std::string groupInfo) = 0;

		virtual bool addGroupMessage(std::string messageInfo) = 0;

	public:
		database() {}
		~database() {}

};
