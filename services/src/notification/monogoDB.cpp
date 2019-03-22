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
	auto c2 = poolDB->acquire();			
	auto coll1 = (*c1)["notification"]["joinGroup"];
	auto coll2 = (*c2)["infoDB"]["groupInfo"];
	json::value response;

	bsoncxx::stdx::optional<bsoncxx::document::value> groupResult =
		coll2.find_one(document{} << "_id" << gid << finalize);

	bool t = false;
	if (groupResult) {
		bsoncxx::document::view doc = groupResult->view();
		bsoncxx::document::element element = doc["members"];
		if (element.type() == type::k_array) {
			bsoncxx::array::view subarray{element.get_array().value};
			for (const bsoncxx::array::element& userIds : subarray) {
				if (userIds.type() == type::k_utf8) {
					std::string user = userIds.get_utf8().value.to_string();
					if (user.compare(uid) == 0) {
						t = true;
					}
				}
			}
		}

		if (t) {
			response["status"] = json::value::string("IN_GROUP");
		} else {
			response["status"] = json::value::string("OK");	
			auto builder = bsoncxx::builder::stream::document{};
        		bsoncxx::document::value doc_value = builder		
			<< "userId" << uid
			<< "groupId" << gid
			<< bsoncxx::builder::stream::finalize;
			coll1.insert_one(std::move(doc_value));	
		}
	} else {
		response["status"] = json::value::string("INVALID_GROUP_ID");
	}

//		
}

json::value NotificationMongo::userAcceptInvitation(std::string user, std::string group) {
	auto c1 = poolDB->acquire();
        auto c2 = poolDB->acquire();
        auto coll1 = (*c1)["notification"]["groupInvite"];
        auto coll2 = (*c2)["infoDB"]["groupInfo"];
        json::value response;

	bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll1.find_one(document{} << "groupId" << group << finalize);
	
	if (result) {
		bsoncxx::stdx::optional<mongocxx::result::delete_result> result2 =
                        coll1.delete_one(document{} << "groupId" << group << finalize);
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
