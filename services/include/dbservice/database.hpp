#ifndef DATABASE_HPP
#define DATABASE_HPP

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

class database {

	//Public pure virtual functions
	public:
		virtual bool setToken(json::value) = 0;
                
		virtual bool checkToken(std::string id, std::string token) = 0;
                
		virtual bool deleteToken(json::value) = 0;

		//user related queries
		virtual json::value mail_login(json::value) = 0;

		virtual json::value registerUser(json::value) = 0;
		
		virtual json::value loginUser(json::value) = 0;

		virtual bool updateUserInfo(std::string userInfo) = 0;
		
		virtual json::value getUserInfo(json::value) = 0;
	
		virtual json::value getUserShortInfo(json::value) = 0;

		virtual json::value getUserConversations(json::value) = 0;
		
		virtual json::value getUsersConversation(json::value) = 0;
		
		virtual std::string addUserMessage(std::string from, std::string to, std::string message) = 0;

		virtual bool updateUserMessage(std::string from, std::string to, std::string messageInfo) = 0;

		virtual json::value deleteUser(json::value) = 0;

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

		virtual json::value getGroupUsers(json::value) = 0;
		
		virtual bool updateGroupMessage(std::string groupId, std::string messBody) = 0;
	
	public:
		database() {}
		~database() {}

};

#endif
