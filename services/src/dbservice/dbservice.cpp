#include <cstdint>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <thread>

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

#include <dbservice/database.hpp>
#include <dbservice/dbservice.hpp>


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

void DbService::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&DbService::handleGet, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&DbService::handlePost, this, std::placeholders::_1));
}


std::string generateID(mongocxx::collection collection) {

	std::string id;
	bsoncxx::builder::stream::document document{};

	auto lastId = collection.find_one({});
	if(!lastId) {
		auto doc = bsoncxx::builder::stream::document{};
		bsoncxx::document::value doc_value = doc
			<< "lastId" << 1
			<< bsoncxx::builder::stream::finalize;
		auto result = collection.insert_one(std::move(doc_value));
		id = "u1";
	}
	else {
		bsoncxx::document::view view = lastId.value().view();
		bsoncxx::document::element element = view["lastId"];
		if(element.type() != bsoncxx::type::k_utf8) {
			int n = element.get_int32().value;
			id = "u" + std::to_string(n);
			collection.update_one(bsoncxx::builder::stream::document{} << "lastId" << n << finalize,
					bsoncxx::builder::stream::document{} << "$inc" << open_document
					<< "lastId" << 1
					<< close_document << bsoncxx::builder::stream::finalize);
		}
	}
	return id;
}

std::string date() {
	time_t now = time(0);
	char* dt = ctime(&now);
	std::string date = dt;
	return date;
}

bool DbService::createPool(std::string path) {
        
	std::ifstream configFile(path);
        json::value config;
        if (configFile.is_open()) {
                configFile >> config;
                configFile.close();
                this->poolMydb = new mongocxx::pool ({config.at("infoDB").as_string()});
                this->poolDB = new mongocxx::pool ({config.at("tokenDB").as_string()});
                this->dbserviceUri = config.at("dbservice").as_string();
                return true;
        } else {
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
                return false;
        }
}

DbService::DbService(std::string path, database* m) : BasicController() {
	static int count = 0;
	if (count < 1) {
		++count;
		mongocxx::instance instance{};
	}
	createPool(path);
	std::cout<<dbserviceUri<<std::endl;
	this->setEndpoint(dbserviceUri);
	this->m_db = m;
}

DbService::~DbService() {
}


void DbService::handleGet(http_request message) {
/*	auto threadfunc = [](mongocxx::client& client, std::string dbname) {
		auto coll = client[dbname]["account"].insert_one({});
	};
	std::thread t([&]() {
			auto c = poolMydb->acquire();
			threadfunc(*c, "infoDB");
			//	});

			auto c = poolMydb->acquire();
			std::cout<< message.to_string()<<std::endl;
			auto path = requestPath(message);

	});*/
	std::cout<< message.to_string()<<std::endl;
	auto path = requestPath(message);
	if (!(path.empty())) {
		if (path[0] == "ServiceTest"){
			message.reply(status_codes::OK, "DbService_Start");
		}
	}else{
		message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
	}
}

void DbService::handlePost(http_request message) {
	/*auto threadfunc = [](mongocxx::client& client, std::string dbname) {
                auto coll = client[dbname]["coll"].insert_one({});
        };*/
//        std::thread t([&]() {
                auto c1 = poolMydb->acquire();
                auto c2 = poolDB->acquire();
               // threadfunc(*c1, "infoDB");
               // threadfunc(*c2, "tokenDB");
//        });

	auto coll1 = (*c1)["infoDB"]["account"];
	auto coll2 = (*c2)["passDB"]["signin"];
	auto path = requestPath(message);
	message.extract_json()
		.then([message, path, &coll1, &coll2, &c1, &c2, this](json::value request) {
			if (!path.empty()) {
				if (path[0] == "check") {
					if (path[1] == "mail&login") {
						bsoncxx::stdx::optional<bsoncxx::document::value> mailResult =
							coll1.find_one(document{} << "mail" << request.at("email").as_string() << finalize);

						bsoncxx::stdx::optional<bsoncxx::document::value> loginResult =
							coll1.find_one(document{} << "login" << request.at("login").as_string() << finalize);

						auto response = json::value::object();

						if(loginResult) {
							response["loginStatus"] = json::value::string("alreadyTaken");
						} else {
							response["loginStatus"] = json::value::string("notUsing");
						}


						if (mailResult) {
							response["mailStatus"] = json::value::string("alreadyTaken");
						} else {
							response["mailStatus"] = json::value::string("notUsing");
						}

						message.reply(status_codes::OK, response);

					} else {
						message.reply(status_codes::NotFound);
					}
				} else {
			if (path[0] == "insert") {
				if (path[1] == "userRegistration") {
				std::string id = generateID(coll2);
				std::string password = request.at("password").as_string();

					std::string joinDate = date();
					auto builder = bsoncxx::builder::stream::document{};
					bsoncxx::document::value doc_value = builder
					<< "id" << id
					<< "firstname" << request.at("firstname").as_string()
  					<< "lastname" << request.at("lastname").as_string()
  					<< "email" << request.at("email").as_string()
  					<< "login" << request.at("login").as_string()
    					<< "birthdate" << request.at("birthdate").as_string()
  					<< "gender" << request.at("gender").as_string()
  					<< "joinDate" << joinDate
  					<< bsoncxx::builder::stream::finalize;
					auto result = coll1.insert_one(std::move(doc_value));
					
					auto response = json::value::object();
					response["status"] = json::value::string("successfullyRegistered");
					response["id"] = json::value::string(id);
					response["firstname"] = json::value::string(request.at("firstname").as_string());
					response["lastname"] = json::value::string(request.at("lastname").as_string());
					response["birthdate"] = json::value::string(request.at("birthdate").as_string());
					response["gender"] = json::value::string(request.at("gender").as_string());
					response["email"] = json::value::string(request.at("email").as_string());
					response["login"] = json::value::string(request.at("login").as_string());
					message.reply(status_codes::OK, response);

					
					builder = bsoncxx::builder::stream::document{};
					doc_value = builder
  					<< request.at("login").as_string() << bsoncxx::builder::stream::open_document
					<< "password" << request.at("password").as_string()
					<< "id" << id
					<< "visitCount" << 0
  					<< close_document
  					<< bsoncxx::builder::stream::finalize;
					result = coll2.insert_one(std::move(doc_value));
				} else if (path[1] == "userLogin") {
                                        bsoncxx::stdx::optional<bsoncxx::document::value> loginPassResult =
                                                coll1.find_one(document{} << "login" << request.at("login").as_string()
                                      	 		<< "password" << request.at("password").as_string() << finalize);
					auto response = json::value::object();
                                        if(loginPassResult) {
                                        	bsoncxx::stdx::optional<bsoncxx::document::value> infoResult =
                                                coll1.find_one(document{} << "login" << request.at("login").as_string()
						bsoncxx::document::view doc_view{logiPassResult.view()};
						auto id = doc_view["id"];
                                                coll2.find_one(document{} << id << open_document
							<< "login" << request.at("login").as_string()
							<< close_document << finalize);
						
						bsoncxx::document::view infoView{infoResult.view()};
						auto response = json::value::object();
						
						response["id"] = json::value::string(id);
						response["firstname"] = json::value::string(infoView["firstname"].as_string());
						response["lastname"] = json::value::string(infoView["lastname"].as_string());
						response["birthdate"] = json::value::string(infoView["birthdate"].as_string());
						response["gender"] = json::value::string(infoView["gender"].as_string());
						response["email"] = json::value::string(infoView["email"].as_string());
						response["login"] = json::value::string(infoView["login"].as_string());
						response["joinDate"] = json::value::string(infoView["joinDate"].as_string());
						
						message.reply(status_codes::OK, response);
                                        } else {
                                                bsoncxx::stdx::optional<bsoncxx::document::value> loginPassResult =
                                                coll1.find_one(document{} << "login" << request.at("login").as_string() << finalize);
                                                if (loginResult) {
                                                        response["passResult"] = json::value::string("wrongPass");
                                                        std::string loginDate = date();
                                                	
							coll1.find_one(document{} << "login" << request.at("login").as_string()
							bsoncxx::document::view doc_view{logiPassResult.view()};
							auto id = doc_view["id"];

                                                        collection.update_one(document{} << id << open_document
								<< "login" << login << close_document << finalize,
                                                                document{} << "$set" << open_document <<
                                                                document{} << "$inc" << open_document <<
								"visitCount" << 1 << close_document << finalize);

                                                        collection.update_one(document{} << id << open_document
								<< "login" << login << close_document << finalize,
                                                                document{} << "$set" << open_document <<
								"visitTime" << date() << close_document << finalize);
                                                } else {
                                                        response["loginStatus"] = json::value::string("unknownLogin");
                                                }

                                        }

				}
			}
		//	else{}
				}
			}
	                else
                        {
                                  message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
                        }

		});
//	});
}
