#include <cstdint>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <thread>

#include <bsoncxx/builder/basic/array.hpp>
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

#include <bsoncxx/types/value.hpp>

#include <bsoncxx/document/value.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/array/view.hpp>

#include <messaging/messagingMongoDb.hpp>

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

bool messagingMongoDb::createPool(std::string path) {

	std::ifstream configFile(path);
	json::value config;
	if (configFile.is_open()) {
		configFile >> config;
		configFile.close();
		this->poolDB = new mongocxx::pool (mongocxx::uri{config.at("mongodbserver").as_string()});
		return true;
	} 
	else {
		std::cerr << "ConfigFile is not exist!!!" << std::endl;
		return false;
	}
}

json::value messagingMongoDb::getUserConversations(std::string) {
	
}

json::value messagingMongoDb::getUsersConversation(std::string, std::string ) {
	
}

std::string messagingMongoDb::userSendMessage(std::string, std::string, std::string ) {
	
}

bool messagingMongoDb::userUpdateMessage(std::string, std::string, std::string ) {
	
}

bool messagingMongoDb::userRemoveConversation(std::string, std::string ) {
	
}

bool messagingMongoDb::userRemoveMessage(std::string, std::string, std::string) {
	
}

bool messagingMongoDb::groupRemoveConversation(std::string ) {
	
}

bool messagingMongoDb::groupRemoveMessage(std::string, std::string ) {
	
}

std::string messagingMongoDb::getGroupConversation(std::string) {
	
}

std::string messagingMongoDb::groupSendMessage(std::string , std::string , json::value ) {
	
}

bool messagingMongoDb::groupUpdateMessage(std::string, std::string, json::value ) {
	
}

messagingMongoDb::messagingMongoDb(std::string path) {
	
	mongocxx::instance instance{};
	createPool(path);
}

messagingMongoDb::~messagingMongoDb() {
	
	delete []  this->poolDB;
}


