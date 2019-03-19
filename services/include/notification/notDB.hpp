#ifndef NOTDB_HPP
#define NOTDB_HPP

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

class NotDB {
	public:
		NotDB(){}
		~NotDB(){}
	public:
		virtual json::value userJoinGroup(json::value) = 0;
		virtual json::value userAcceptInvitation(json::value) = 0;
		virtual json::value groupInviteUser(json::value) = 0;
		virtual json::value groupAccepyUser(json::value) = 0;
		virtual json::value newMessage(json::value) = 0;
		virtual json::value messageFromService(json::value) = 0;
		virtual json::value groupRemoveUser(json::value) = 0;
		virtual json::value userLeaveGroup(json::value) = 0;
};

#endif
