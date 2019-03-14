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
		virtual bool setToken(json::value);
                
		virtual bool checkToken(json::value);
                
		virtual bool deleteToken(json::value);

		//user related queries
		virtual json::value checkMailAndLogin(std::string mail, std::string login);

		virtual json::value signUp(json::value user);
		
		virtual json::value signIn(std::string, std::string);
	
		virtual json::value getUserInfo(std::string userId);
	
		virtual json::value getUserShortInfo(std::string userId);

		virtual json::value deleteUser(std::string userId);

		virtual json::value userUpdateInfo(json::value user);

		virtual bool removeUserConversation(std::string userId1, std::string userId2){};

		virtual json::value getUserConversations(std::string userId){};
		
		virtual json::value getUsersConversation(std::string userId1, std::string userId2){};

		virtual std::string addUserMessage(std::string from, std::string to, std::string message){};

		virtual bool updateUserMessage(std::string from, std::string to, std::string messageInfo){};
	
		virtual json::value changePassword(json::value);

		//group related queries
		
		virtual json::value getGroupInfo(std::string);
	
		virtual json::value getGroupShortInfo(std::string groupId);
	
		virtual json::value getGroupUsers(std::string groupId);
		
		virtual json::value createGroup(json::value groupInfo);

                virtual json::value deleteGroup(std::string groupId);
                
		virtual json::value searchUsers(json::value);
		virtual json::value searchGroups(json::value);

		virtual json::value addUserToGroup(std::string userId, std::string groupId, std::string cleintId);

                virtual json::value groupRemoveUser(std::string, std::string);
		
		virtual json::value groupUpdateInfo(json::value groupInfo);
               
	       	virtual bool removeMessage(json::value messageInfo){};

                virtual bool removeGroupConversation(std::string groupId){};

		virtual bool removeMessageFromGroupConversation(std::string groupId, std::string messageId){};
		
		virtual std::string getGroupConversation(std::string groupID){};

		virtual std::string addGroupMessage(std::string groupId, std::string userId, json::value message){};

		virtual bool updateGroupMessage(std::string groupId, json::value message) {};
		
		MongoDB(std::string);
		~MongoDB();

	private:
		json::value isUserInGroup(std::string, std::string);
		mongocxx::pool* poolMydb;
                mongocxx::pool* poolDB;
                bool createPool(std::string);
};

#endif
