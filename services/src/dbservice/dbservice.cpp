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

#include <std_micro_service.hpp>
#include <basic_controller.hpp>

#include <dbservice/dbservice.hpp>

mongocxx::instance instance{};

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


std::string generateID() {
	mongocxx::uri uri{"mongodb://localhost:27017"};
	mongocxx::pool pool{uri};

	std::string id;
	mongocxx::client client{mongocxx::uri{"mongodb://localhost:27017"}};
	mongocxx::database db = client["db"];
	auto collection = client["db"]["signin"];
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

DbService::DbService(std::string dbname) : BasicController() {
/*	static int count = 0;
	if (count < 1) {
		++count;
		mongocxx::instance instance{};
	}
*/
	std::string path = decideDB(dbname);
	std::cout << path << "\n";
	mongocxx::uri uri{path};
	mongocxx::pool pool{uri};
}

DbService::~DbService() {

}

bool DbService::createClients(std::string path, std::string dbname) {
        std::ifstream configFile(path);
        json::value config;
        if (configFile.is_open()) {
                configFile >> config;
                configFile.close();
                poolMydb = new mongocxx::pool (config.at("db").as_string());
                poolDB = new mongocxx::pool (config.at("myfb").as_string());
                this->dbserviceUri = config.at("dbservice").as_string();
                return true;
        } else {
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
                return false;
        }
}


void DbService::handleGet(http_request message) {
	mongocxx::uri uri{"mongodb://localhost:27017"};
	mongocxx::pool pool{uri};
	auto threadfunc = [](mongocxx::client& client, std::string dbname) {
		auto coll = client[dbname]["account"].insert_one({});
	};
	std::thread t([&]() {
			auto c = pool.acquire();
			threadfunc(*c, "mydb");
			//	});

			std::cout<< message.to_string()<<std::endl;
			auto path = requestPath(message);
			if (!path.empty()) {
				if (path[0] == "get") {
					if (path[1] == "mail" && path[3] == "login") {
						auto coll = (*c)["mydb"]["account"];
						bsoncxx::stdx::optional<bsoncxx::document::value> mailResult =
							coll.find_one(document{} << "mail" << path[2] << finalize);

						bsoncxx::stdx::optional<bsoncxx::document::value> loginResult =
							coll.find_one(document{} << "login" << path[4] << finalize);

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

						response["status"] = json::value::string("OK");
						message.reply(status_codes::OK, response);

					} else {
						message.reply(status_codes::NotFound);
					}
				} else {
					message.reply(status_codes::NotFound);
				}
			}
	});
}

void DbService::handlePost(http_request message) {
	mongocxx::uri uri{"mongodb://localhost:27017"};
	mongocxx::pool pool{uri};
	auto threadfunc = [](mongocxx::client& client, std::string dbname) {
                auto coll = client[dbname]["coll"].insert_one({});
        };
        std::thread t([&]() {
                auto c = pool.acquire();
                threadfunc(*c, "mydb");
                threadfunc(*c, "db");
//        });

	auto coll = (*c)["mydb"]["account"];
	auto coll2 = (*c)["db"]["signin"];
	auto path_first_request = requestPath(message);
	message.extract_json()
		.then([message, path_first_request, &coll, &coll2](json::value request) {
			if (path_first_request[1] == "registration") {
				//auto coll = (*c)["mydb"]["account"];
				std::string id = generateID();
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
					auto result = coll.insert_one(std::move(doc_value));
					
					json::value response;
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
					<< "status" << "good"
  					<< close_document
  					<< bsoncxx::builder::stream::finalize;
					result = coll2.insert_one(std::move(doc_value));
				}

		});
	});
}

void DbService::handlePatch(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PATCH));
}

void DbService::handlePut(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PUT));
}

void DbService::handleDelete(http_request message) {    
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::DEL));
}

void DbService::handleHead(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::HEAD));
}

void DbService::handleOptions(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::OPTIONS));
}

void DbService::handleTrace(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::TRCE));
}

void DbService::handleConnect(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::CONNECT));
}

void DbService::handleMerge(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::MERGE));
}
