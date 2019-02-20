#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <string>

#include <controller.hpp>
#include <basic_controller.hpp>
#include <dbservice/database.hpp>
#include <cpprest/http_client.h>

#include <cpprest/filestream.h>

using namespace cfx;
using namespace utility;                   
using namespace web;                       
using namespace web::http;                 
using namespace web::http::client;         
using namespace concurrency::streams; 


class DbService: public BasicController, Controller, database {
	protected:
		http_listener _listener; 
	public:
	//	void initRestOpHandlers();
		std::string registerUser(std::string userInfo);
		std::string loginUser(std::string login, std::string password);
		bool updateUserInfo(std::string userInfo);
		std::string getUserInfo(std::string userID);
		std::string getUserShortInfo(std::string userID);
		bool singOut(std::string id);
		bool forgotPassword(std::string);
		bool deleteUser(std::string userId);
	
		std::string createGroup(std::string groupInfo);
                bool deleteGroup(std::string groupID);
                bool addUserToGroup(std::string groupID, std::string userID);
                bool removeFromGroup(std::string groupID, std::string userID);
		std::string getGroupInfo(std::string groupID);
		bool updateGroupInfo(std::string groupInfo);
                std::string getGroupUsers(std::string groupId);

		
		void handleGet(http_request message) override;
		void handlePost(http_request message) override;

	private:
		static json::value responseNotImpl(const http::method & method);
		void handlePut(http_request message) override;
                void handleDelete(http_request message) override;
                void handlePatch(http_request messge) override;
                void handleHead(http_request message) override;
                void handleOptions(http_request message) override;
                void handleTrace(http_request message) override;
                void handleConnect(http_request message) override;
            	void handleMerge(http_request message) override;

		std::string getUserConversations(std::string userID);
                std::string getUsersConversation(std::string fromID, std::string toID);
                std::string addUserMessage(std::string from, std::string to, std::string message);

		bool updateUserMessage(std::string from, std::string to, std::string messageInfo);
                bool removeUserConversation(std::string fromUserId, std::string toUserId);
                bool removeMessage(std::string messageInfo);
                bool removeGroupConversation(std::string groupInfo);
                bool removeMessageFromGroupConversation(std::string groupInfo);
                std::string getGroupConversation(std::string userID, std::string groupID);
                std::string addGroupMessage(std::string groupId, std::string userId, std::string message);
            	bool updateGroupMessage(std::string groupId, std::string messBody);

		void setEndpoint(const std::string & value);
                std::string endpoint() const;
                pplx::task<void> accept();
                pplx::task<void> shutdown();
                void initRestOpHandlers() {}
                std::vector<utility::string_t> requestPath(const http_request & message);

	
		DbService(std::string);
		~DbService() {}
};

#endif
