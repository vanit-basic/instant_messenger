#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <base/basic_controller.hpp>
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
                
		virtual bool checkToken(json::value) = 0;
                
		virtual bool deleteToken(json::value) = 0;

		//user related queries
		virtual json::value checkMailAndLogin(std::string mail, std::string login) = 0;

		virtual json::value signUp(json::value user) = 0;
		
		virtual json::value signIn(std::string login, std::string pass) = 0;
		
		virtual json::value getUserInfo(std::string userId) = 0;
	
		virtual json::value getUserShortInfo(std::string userId) = 0;

		virtual json::value getUserConversations(std::string userId) = 0;
		
		virtual json::value getUsersConversation(std::string userId1, std::string userId2) = 0;
		
		virtual std::string addUserMessage(std::string from, std::string to, std::string message) = 0;

		virtual bool updateUserMessage(std::string from, std::string to, std::string messageInfo) = 0;

		virtual json::value deleteUser(std::string userId) = 0;

		virtual bool removeUserConversation(std::string userId1, std::string userId2) = 0;

		virtual json::value userUpdateInfo(json::value user) = 0;
		
		virtual json::value changePassword(json::value ) = 0;
	
		//group related queries
		virtual json::value changeGroupAdmin(std::string, std::string) = 0;

                virtual json::value getGroupUsers(std::string groupId) = 0;
		
                virtual json::value searchUsers(json::value) = 0;

                virtual json::value searchGroups(json::value) = 0;

		virtual json::value getGroupShortInfo(std::string groupId) = 0;
		
		virtual json::value createGroup(json::value groupInfo) = 0;

                virtual json::value deleteGroup(std::string groupId) = 0;
                
		virtual json::value addUserToGroup(std::string userId, std::string groupId, std::string clientId) = 0;

                virtual json::value groupRemoveUser(std::string, std::string) = 0;

                virtual bool removeMessage(json::value messageInfo) = 0;

                virtual bool removeGroupConversation(std::string groupId) = 0;

		virtual bool removeMessageFromGroupConversation(std::string groupId, std::string messageId) = 0;
		
		virtual json::value getGroupInfo(std::string) = 0;
		
		virtual std::string getGroupConversation(std::string groupID) = 0;
		
		virtual json::value groupUpdateInfo(json::value groupInfo) = 0;

		virtual std::string addGroupMessage(std::string groupId, std::string userId, json::value message) = 0;

		virtual bool updateGroupMessage(std::string groupId, json::value message) = 0;

	public:
		virtual json::value isUserInGroup(std::string, std::string) = 0;
		database() {}
		~database() {}

};

#endif
