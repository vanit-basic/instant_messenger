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

bool NotificationMongo::createPool(std::string path) {
	std::ifstream configFile(path);
        json::value config;
        if (configFile.is_open()) {
                configFile >> config;
                configFile.close();
                this->poolDB = new mongocxx::pool (mongocxx::uri{config.at("mongoNotification").as_string()});
                return true;
        } else {
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
                return false;
        }
}

NotificationMongo::NotificationMongo(std::string path) {
	static int count = 0;
        if (count < 1) {
                ++count;
                mongocxx::instance instance{};
        }
	createPool(path);
}

NotifiactionMongo::~NotificationMongo() {
	delete[] this->poolDB;	
}

json::value NotificationMongo::userJoinGroup(std::string uid, std::string gid) {
	auto c1 = poolDB->acquire();			
	auto coll1 = (*c1)["notificationDB"]["joinGroup"];
	json::value response;

	bsoncxx::stdx::optional<bsoncxx::document::value> result =
		coll1.find_one(document{} << "_id" << uid << finalize);

	if (result) {
		bsoncxx::document::view doc = result->view();
                bsoncxx::document::element element = doc["groups"];

                if (element.type() == type::k_array) {
                        bsoncxx::array::view subarray{element.get_array().value};
                        for (const bsoncxx::array::element& groups : subarray) {
                                if (groups.type() == type::k_utf8) {
                                        std::string group = groups.get_utf8().value.to_string();
                                        if (group.compare(gid) == 0) {
                                               	json::value response["status"] = json::value::string("ALREADY_SENDED");
						return response;
					}
                                }
                        }
                }
		
		result = coll1.update_one(document{} << "_id" << uid << finalize,
		document{} << "$push" << open_document
		<< "groups" << gid << close_document << finalize);
		json::value response["status"] = json::value::string("OK");

	} else {
		auto builder = bsoncxx::builder::stream::document{};
	        bsoncxx::document::value doc_value = builder
		<< "_id" << uid
                << "groups" << open_array << gid << close_array
                << bsoncxx::builder::stream::finalize;
		auto result = coll1.insert_one(std::move(doc_value));

		json::value response["status"] = json::value::string("OK");
	}
	
	return response;
}

json::value NotificationMongo::userAcceptInvitation(std::string uid, std::string gid) {
	auto c1 = poolDB->acquire();
        auto coll1 = (*c1)["notification"]["groupInvite"];
        json::value response;

	bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll1.find_one(document{} << "_id" << gid << finalize);
	
	if (result) {
		bsoncxx::document::view doc = result->view();
                bsoncxx::document::element element = doc["users"];

                if (element.type() == type::k_array) {
                        bsoncxx::array::view subarray{element.get_array().value};
                        for (const bsoncxx::array::element& users : subarray) {
                                if (users.type() == type::k_utf8) {
                                        std::string user = users.get_utf8().value.to_string();
                                        if (user.compare(uid) == 0) {
						result = coll1.update_one(document{} << "_id" << gid << finalize,
							document{} << "$push" << open_document
							<< "users" << uid << close_document << finalize);
						json::value response["status"] = json::value::string("OK");
						return response;
					}
                                }
                        }
                }
		
		json::value response["status"] = json::value::string("INVALID_GROUP");
	} else {
		json::value response["status"] = json::value::string("INVALID_GROUP");
	}

	return response;
}

json::value NotificationMongo::groupInviteUser(json::value) {
	
}

json::value NotificationMongo::groupAcceptUser(json::value) {
	 
}

json::value NotificationMongo::newMessage(json::value) {
	
}

json::value NotificationMongo::messageFromService(json::value) {
	 
}

json::value NotificationMongo::groupRemoveUser(json::value) {
	
}

json::value NotificationMongo::userLeaveGroup(json::value) {
	
}
