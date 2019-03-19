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

bool NotMongo::createPool(std::string) {
	
}

NotMongo::NotMongo() {

}

NotMongo::~NotMongo() {
	
}

json::value NotMongo::userJoinGroup(json::value) {
	
}

json::value NotMongo::userAcceptInvitation(json::value) {
	
}

json::value NotMongo::groupInviteUser(json::value) {
	
}

json::value NotMongo::groupAccepyUser(json::value) {
	 
}

json::value NotMongo::newMessage(json::value) {
	
}

json::value NotMongo::messageFromService(json::value) {
	 
}

json::value NotMongo::groupRemoveUser(json::value) {
	
}

json::value NotMongo::userLeaveGroup(json::value) {
	
}
