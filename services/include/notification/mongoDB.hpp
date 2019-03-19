#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#include <base/basic_controller.hpp>
#include <cpprest/http_client.h>

#include <string>
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


class NotDB: public Notification {
	private: 
		mongocxx::pool* poolDB;
		bool createPool(std::string);
        public:
                NotDB();
                ~NotDB();
        public:
                
		virtual json::value userJoinGroup(json::value);
                virtual json::value userAcceptInvitation(json::value);
                virtual json::value groupInviteUser(json::value);
                virtual json::value groupAccepyUser(json::value);
                virtual json::value newMessage(json::value);
		virtual json::value messageFromService(json::value);
                virtual json::value groupRemoveUser(json::value);
                virtual json::value userLeaveGroup(json::value);

};

#endif
