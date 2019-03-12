#ifndef MESSAGINGDBBASE_HPP
#define MESSAGINGDBBASE_HPP

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

class messagingDbBase {
	
	virtual json::value getUserConversations(std::string userId) = 0;
	virtual json::value getUsersConversation(std::string userId1, std::string userId2) = 0;
	virtual std::string addUserMessage(std::string from, std::string to, std::string message) = 0;
	virtual bool updateUserMessage(std::string from, std::string to, std::string messageInfo) = 0;
	virtual bool removeUserConversation(std::string userId1, std::string userId2) = 0;
	virtual bool removeMessage(json::value messageInfo) = 0;
	virtual bool removeGroupConversation(std::string groupId) = 0;
	virtual bool removeMessageFromGroupConversation(std::string groupId, std::string messageId) = 0;
	virtual std::string getGroupConversation(std::string groupID) = 0;
	virtual std::string addGroupMessage(std::string groupId, std::string userId, json::value message) = 0;
	virtual bool updateGroupMessage(std::string groupId, json::value message) = 0;
};
#endif


