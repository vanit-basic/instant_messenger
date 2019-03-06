#pragma once

#include <string>

#include <base/basic_controller.hpp>
#include <cpprest/http_client.h>
#include <dbservice/database.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/pool.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/types.hpp>

using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_document;


class MongoTokenDb : public database
{
	public:
		bool setToken(json::value) override;
		bool checkToken(json::value) override;
		bool deleteToken(json::value) override;
		MongoTokenDb(std::string);
		~MongoTokenDb();

		json::value checkMailAndLogin(std::string mail, std::string login){};
		json::value registerUser(json::value){};
		json::value loginUser(std::string login, std::string pass){};
		bool updateUserInfo(std::string userInfo){};
		json::value getUserInfo(std::string userId){};
		json::value getUserShortInfo(std::string userId){};
		json::value getUserConversations(std::string userId){};
		json::value getUsersConversation(std::string userId1, std::string userId2){};
		std::string addUserMessage(std::string from, std::string to, std::string message){};
		json::value updateUserInfo(json::value user){};

		bool updateUserMessage(std::string from, std::string to, std::string messageInfo){};
		json::value deleteUser(std::string userId){};
		bool removeUserConversation(std::string fromUserId, std::string toUserId){};
		json::value createGroup(json::value groupInfo){};
		json::value deleteGroup(std::string groupID) {};
		json::value addUserToGroup(json::value) {};
		json::value removeFromGroup(json::value){};
		bool removeMessage(json::value messageInfo){};
		bool removeGroupConversation(std::string groupInfo) {};
		bool removeMessageFromGroupConversation(std::string groupId, std::string messageId){};
		json::value getGroupShortInfo(std::string groupId){};
		json::value getGroupInfo(json::value){};
		std::string getGroupConversation(std::string groupID){};
		std::string addGroupMessage(std::string groupId, std::string userId, json::value message){};
		json::value getGroupUsers(json::value) {};
		bool updateGroupMessage(std::string groupId, json::value message){};
		json::value updateGroupInfo(json::value groupInfo){};
		json::value getPublicGroupInfo(std::string, std::string){};

	
	private:
		mongocxx::pool* clientPool;
		bool createPool(std::string);
};
