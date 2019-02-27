#ifndef MONGODB_HPP
#define MONGODB_HPP

#include <string>

#include <base/basic_controller.hpp>
#include <dbservice/database.hpp>
#include <cpprest/http_client.h>

#include <cpprest/filestream.h>

using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

class MongoDB : public database {
	public:
		json::value mail&login(json::value);
		json::value registerUser(json::value);

		bool loginUser(std::string login, std::string password);

		bool updateUserInfo(std::string userInfo);

		bool getUserInfo(std::string userID);

		bool getUserShortInfo(std::string userID);

		bool getUserConversations(std::string userID);

		bool getUsersConversation(std::string fromID, std::string toID);

		bool addUserMessage(std::string from, std::string to, std::string message);

		bool updateUserMessage(std::string from, std::string to, std::string messageInfo);

		bool deleteUser(std::string userId);

		bool removeUserConversation(std::string fromUserId, std::string toUserId);

		//group related queries

		bool createGroup(std::string groupInfo);

		bool deleteGroup(std::string groupID);

		bool addUserToGroup(std::string groupID, std::string userID);

		bool removeFromGroup(std::string groupID, std::string userID);

		bool removeMessage(std::string messageInfo);

		bool removeGroupConversation(std::string groupInfo);

		bool removeMessageFromGroupConversation(std::string groupInfo);

		bool getGroupInfo(std::string groupID);

		bool getGroupConversation(std::string userID, std::string groupID);

		bool updateGroupInfo(std::string groupInfo);

		bool addGroupMessage(std::string groupId, std::string userId, std::string message);

		bool getGroupUsers(std::string groupId);

		bool updateGroupMessage(std::string groupId, std::string messBody);

		MongoDB() {}
		~MongoDB() {}

	private:
		mongocxx::pool* poolMydb;
                mongocxx::pool* poolDB;
                bool createPool(std::string);

};

#endif
