#ifndef NOTIFICATIONDB_HPP
#define NOTIFICATIONDB_HPP

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

class NotificationDB {
	public:
		NotificationDB(){}
		~NotificationDB(){}
	public:
		virtual json::value userJoinGroup(std::string, std::string) = 0;
		virtual json::value userAcceptInvitation(std::string, std::string, std::string) = 0;
		virtual json::value groupInviteUser(std::string, std::string) = 0;
		virtual json::value pendToSend(std::string, std::string) = 0;
		virtual json::value groupAccepyUser(std::string, std::string, std::string) = 0;
		virtual json::value newMessage(json::value) = 0;
		virtual json::value messageFromService(json::value) = 0;
		virtual json::value groupRemoveUser(json::value) = 0;
		virtual json::value userLeaveGroup(json::value) = 0;
};

#endif
