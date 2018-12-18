#include "database.hpp"


class xmlDatabase : public database {

	public:
		//user related queries
		virtual std::string registerUser(std::string userInfo);
                virtual std::string loginUser(std::string login, std::string password);
                virtual bool updateUserInfo(std::string userInfo);
                virtual std::string getUserInfo(std::string userID);
		virtual std::string getUserShortInfo(std::string userID);
                virtual std::string getUserConversations(std::string userID);
                virtual std::string getUsersConversation(std::string fromID, std::string toID);
                virtual std::string addUserMessage(std::string from, std::string to, std::string message);

                //group related queries
                virtual std::string createGroup(std::string groupInfo);
                virtual bool deleteGroup(std::string groupID);
                virtual bool addUserToGroup(std::string groupID, std::string userID);
                virtual bool removeFromGroup(std::string groupID, std::string userID);
                virtual bool removeMessage(std::string messageInfo);
                virtual bool removeGroupConversation(std::string groupInfo);
                virtual std::string getGroupInfo(std::string groupID);
                virtual std::string getGroupConversation(std::string userID, std::string groupID);
                virtual bool updateGroupInfo(std::string groupInfo);
		virtual std::string addGroupMessage(std::string groupId, std::string userId, std::string message);

	public:
		xmlDatabase();
		~xmlDatabase();

	public:
		static xmlDatabase* getShared();
};
