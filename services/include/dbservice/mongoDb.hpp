#ifndef MONGODB_HPP
#define MONGODB_HPP

#include <string>

#include <base/basic_controller.hpp>
#include <cpprest/http_client.h>

#include <cpprest/filestream.h>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/pool.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/instance.hpp>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <bsoncxx/types.hpp>

#include <dbservice/database.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_document;
using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

class MongoDB : public database {
	public:
		json::value mail_login(json::value);
		json::value registerUser(json::value);

		std::string loginUser(std::string login, std::string password);

		bool updateUserInfo(std::string userInfo);

		std::string getUserInfo(std::string userID);

		std::string getUserShortInfo(std::string userID);

		std::string getUserConversations(std::string userID);

		std::string getUsersConversation(std::string fromID, std::string toID);

		std::string addUserMessage(std::string from, std::string to, std::string message);

		bool updateUserMessage(std::string from, std::string to, std::string messageInfo);

		bool deleteUser(std::string userId);

		bool removeUserConversation(std::string fromUserId, std::string toUserId);

		//group related queries

		std::string createGroup(std::string groupInfo);

		bool deleteGroup(std::string groupID);

		bool addUserToGroup(std::string groupID, std::string userID);

		bool removeFromGroup(std::string groupID, std::string userID);

		bool removeMessage(std::string messageInfo);

		bool removeGroupConversation(std::string groupInfo);

		bool removeMessageFromGroupConversation(std::string groupInfo);

		std::string getGroupInfo(std::string groupID);

		std::string getGroupConversation(std::string userID, std::string groupID);

		bool updateGroupInfo(std::string groupInfo);

		std::string addGroupMessage(std::string groupId, std::string userId, std::string message);

		std::string getGroupUsers(std::string groupId);

		bool updateGroupMessage(std::string groupId, std::string messBody);

		MongoDB() {}
		~MongoDB() {}

	private:
		mongocxx::pool* poolMydb;
                mongocxx::pool* poolDB;
                bool createPool(std::string);

};

#endif
