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

#include <notification/mongoDB.hpp>

bool NotificationMongo::createPool(std::string) {
	
}

NotificationMongo::NotificationMongo() {

}

NotifiactionMongo::~NotificationMongo() {
	
}

json::value NotificationMongo::userJoinGroup(json::value) {
	
}

json::value NotificationMongo::userAcceptInvitation(json::value) {
	
}

json::value NotificationMongo::groupInviteUser(json::value) {
	
}

json::value NotificationMongo::groupAccepyUser(json::value) {
	 
}

json::value NotificationMongo::newMessage(json::value) {
	
}

json::value NotificationMongo::messageFromService(json::value) {
	 
}

json::value NotificationMongo::groupRemoveUser(json::value) {
	
}

json::value NotificationMongo::userLeaveGroup(json::value) {
	
}
