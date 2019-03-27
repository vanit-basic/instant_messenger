#include <base/basic_controller.hpp>
#include <cpprest/http_client.h>

#include <string>
#include <cpprest/filestream.h>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/pool.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/instance.hpp>
#include <cpprest/http_client.h>
#include <bsoncxx/types.hpp>

#include <bsoncxx/types/value.hpp>
#include <bsoncxx/document/value.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/array/view.hpp>

#include <cstdint>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <thread>

#include <notification/mongoDB.hpp>

using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::type;
using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

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

NotificationMongo::~NotificationMongo() {
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
                bsoncxx::document::element element = doc["pending"];

                if (element.type() == type::k_array) {
                        bsoncxx::array::view subarray{element.get_array().value};
                        for (const bsoncxx::array::element& groups : subarray) {
                                if (groups.type() == type::k_utf8) {
                                        std::string group = groups.get_utf8().value.to_string();
                                        if (group.compare(gid) == 0) {
                                               	response["status"] = json::value::string("ALREADY_SENDED");
						return response;
					}
                                }
                        }
                }
		
		coll1.update_one(document{} << "_id" << uid << finalize,
			document{} << "$push" << open_document
			<< "pending" << gid << close_document << finalize);

	} else {
		auto builder = bsoncxx::builder::stream::document{};
	        bsoncxx::document::value doc_value = builder
		<< "_id" << uid
                << "pending" << open_array << gid << close_array
		<< "send" << open_array << close_array
		<< "accept" << open_array << close_array
		<< "reject" << open_array << close_array
                << bsoncxx::builder::stream::finalize;
		auto result = coll1.insert_one(std::move(doc_value));

	}
	
	response["status"] = json::value::string("OK");
	return response;
}

json::value NotificationMongo::userAcceptInvitation(std::string uid, std::string gid, std::string status) {
	auto c1 = poolDB->acquire();
        auto coll1 = (*c1)["notification"]["groupInvite"];
        json::value response;

	bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll1.find_one(document{} << "_id" << gid << finalize);
	
	if (result) {
		bsoncxx::document::view doc = result->view();
                bsoncxx::document::element element = doc["sent"];

                if (element.type() == type::k_array) {
                        bsoncxx::array::view subarray{element.get_array().value};
                        for (const bsoncxx::array::element& users : subarray) {
                                if (users.type() == type::k_utf8) {
                                        std::string user = users.get_utf8().value.to_string();
					if (user.compare(uid) == 0) {
						coll1.update_one(document{} << "_id" << gid << finalize,
							document{} << "$pull" << open_document
							<< "sent" << uid << close_document << finalize);
						if (status.compare("accept") == 0) {
							coll1.update_one(document{} << "_id" << gid << finalize,
								document{} << "$push" << open_document
								<< "accept" << uid << close_document << finalize);
						} else {
							coll1.update_one(document{} << "_id" << gid << finalize,
								document{} << "$push" << open_document
								<< "reject" << uid << close_document << finalize);
						
						}
						
						response["status"] = json::value::string("OK");
						return response;
					}
                                }
                        }
                }
		
		response["status"] = json::value::string("INVALID_GROUP");
	} else {
		response["status"] = json::value::string("INVALID_GROUP");
	}

	return response;
}

json::value NotificationMongo::groupInviteUser(std::string user, std::string group) {
	auto c = poolDB->acquire();
	auto coll = (*c)["notificationDB"]["groupInvite"];
	json::value response;

	bsoncxx::stdx::optional<bsoncxx::document::value> result =
		coll.find_one(document{} << "_id" << group << finalize);

	if (result) {
		bsoncxx::document::view doc = result->view();
		bsoncxx::document::element element = doc["pending"];
		if (element.type() == type::k_array) {
			bsoncxx::array::view subarray{element.get_array().value};
			for (const bsoncxx::array::element& uId : subarray) {
				if (uId.type() == type::k_utf8) {
					std::string userId = uId.get_utf8().value.to_string();
					if (user.compare(userId) == 0) {
						response["status"] = json::value::string("ALREADY_SENDED");
						return response; 
					} 
				}
			}
		}
		coll.update_one(document{} << "_id" << group << finalize,
			document{} << "$push" << open_document
			<< "pending" << user << close_document << finalize);
	} else {
		auto builder = bsoncxx::builder::stream::document{};
	        bsoncxx::document::value doc_value = builder
                << "_id" << group
		<< "pending" << open_array 
		<< user << close_array
		<< "sent" << open_array << close_array
		<< "accept" << open_array << close_array
		<< "reject" << open_array << close_array
		<< bsoncxx::builder::stream::finalize;
		auto result = coll.insert_one(std::move(doc_value));
	}
	response["status"] = json::value::string("OK");
	return response;
}

json::value NotificationMongo::groupAcceptUser(std::string user, std::string group, std::string status) {
	auto c = poolDB->acquire();
        auto coll = (*c)["notificationDB"]["joinGroup"];
        json::value response;

        bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll.find_one(document{} << "_id" << user << finalize);

        if (result) {
                bsoncxx::document::view doc = result->view();
                bsoncxx::document::element element = doc["sent"];
                if (element.type() == type::k_array) {
                        bsoncxx::array::view subarray{element.get_array().value};
                        for (const bsoncxx::array::element& gId : subarray) {
                                if (gId.type() == type::k_utf8) {
                                        std::string groupId = gId.get_utf8().value.to_string();
                                        if (group.compare(groupId) == 0) {
						coll.update_one(document{} << "_id" << user << finalize,
                                                        document{} << "$pull" << open_document
                                                        << "sent" << group << close_document << finalize);
						if (status.compare("accept") == 0) {
							coll.update_one(document{} << "_id" << user << finalize,
								document{} << "$push" << open_document
                                                        	<< "accept" << group << close_document << finalize);
						} else if (status.compare("reject") == 0) {
							coll.update_one(document{} << "_id" << user << finalize,
								document{} << "$push" << open_document
                                                        	<< "reject" << group << close_document << finalize);
						}
                                                response["status"] = json::value::string("OK");
						return response;
                                        } 
                                }
                        }
                }
		response["status"] = json::value::string("INVALID_USER_ID");
        } else {
		response["status"] = json::value::string("INVALID_USER_ID");
	}
        return response;
}

json::value NotificationMongo::newMessage(json::value) {
	
}

json::value NotificationMongo::messageFromService(json::value) {
	 
}

json::value NotificationMongo::groupRemoveUser(json::value) {
	
}

json::value NotificationMongo::userLeaveGroup(json::value) {
	
}
