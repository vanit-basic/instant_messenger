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

#include <notification/notification.hpp>
#include <notification/mongoDB.hpp>

bool Notification::createClient(std::string path) {
	std::ifstream configFile(path);
	json::value config;
	if (configFile.is_open()) {
		configFile >> config;
		configFile.close();
		
		return true;
	} else {
		std::cerr << "ConfigFile is not exist!!!" << std::endl;
		return false;
	}
}

Notification::Notification(std::string path, database* mongo) {
	static int count = 0;
	if (count < 1) {
		++count;
		mongocxx::instance instance{};
	}
	this->m_db = mongo;
	this->createClient(path);
}

Notification::~Notification() {

}

NOtification::hendleGet(http_request message) {
	auto path = requestPath(message);
	if (!path.empty()) {
		if (path[0] == "serviceStart") {
			message.reply(status_codes::OK, "Notification_Start");
		} else if (path[1] == "userJoinGroup") {
			std::string userId  = path[3];
			std::string groupId = path[5];
			auto mess = userJoinGroup(userId, groupId);
			message.reply(mess);
		} else if (path[1] == "userAcceptInvitation") {
			std::string userId  = path[3];
			std::string groupId = path[5];
			auto  mess = userAcceptInvitation(userId, groupId);
			message.reply(mess);
		} else if (path[1] == "groupInviteUser") {
			std::string groupId  = path[3];
			std::string userId = path[5];
			auto mess = groupInviteUser(groupId, userId);
			message.reply(mess);
		} else if (path[1] == "getUserConversations") {
			std::string userId  = path[2];
			auto userConversations  = getUserConversations(userId,this->m_db);
			message.reply(userConversations);
		} else {
			if(path[1] == "getGroupConversation") {
				std::string userId  = path[2];
				std::string groupId = path[3];
				auto groupConversation = getGroupConversation(userId,groupId,this->m_db);
				message.reply(groupConversation);
			} else {
				if(path[1] == "groupRemoveConversation")
				{
					std::string userId  = path[2];
					std::string groupId = path[3];
					auto removeConversation = groupRemoveConversation(userId,groupId,this->m_db);
					message.reply(removeConversation);

				}else
				{
					if(path[1] =="groupRemoveMessage")
					{
						std::string userId    = path[2];
						std::string groupId   = path[3];
						std::string messageId = path[4];
						auto removeMessage = groupRemoveMessage(userId , groupId , messageId , this->m_db);
						message.reply(removeMessage);
					}
				}
			}
		}
	} else {
		message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
	}
}

