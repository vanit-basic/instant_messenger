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
#include <dbservice/mongoDb.hpp>
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

bool DbService::getUri(std::string path) {
        std::ifstream configFile(path);
        json::value config;
        if (configFile.is_open()) {
                configFile >> config;
                configFile.close();
                this->dbserviceUri = config.at("dbservice").as_string();
                return true;
        } else {
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
                return false;
        }
}

DbService::DbService(std::string path, database* m) : BasicController() {
/*	static int count = 0;
	if (count < 1) {
		++count;
		mongocxx::instance instance{};
	}*/
	if(getUri(path)) {
		this->setEndpoint(dbserviceUri);
	}
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
	auto path = requestPath(message);

	message.extract_json()
		.then([message, path, this](json::value request) {
			if (!path.empty()) {
				if (path[0] == "check") {
					if (path[1] == "mail&login") {
						json::value response = m_db->mail_login(request);
						message.reply(status_codes::OK, response);
					} else {
						message.reply(status_codes::NotFound);
						}
				} else {
					if (path[0] == "insert") {
						if (path[1] == "userRegistration") {
							json::value response = m_db->registerUser(request);
							message.reply(status_codes::OK, response);
				 		} else if (path[1] == "userLogin") {
                                        std::string login = request.at("login").as_string();
                                        std::string password = request.at("password").as_string();
                                        auto response = json::value::object();

                                        bsoncxx::stdx::optional<bsoncxx::document::value> result =
                                                coll2.find_one(document{} << "login" << login
                                                                << "password" << password << finalize);

                                
                                        if (result) {   
                                                bsoncxx::stdx::optional<bsoncxx::document::value> infoResult =
                                                        coll2.find_one(document{} << "login" << request.at("login").as_string()
                                                                bsoncxx::document::view doc_view{*result.view()};
                                                        auto id = doc_view["id"];
                                                         //auto cursor = db["restaurants"].find({});
                                  /*              auto infoResult = coll1.find(document{} << "login" << login << finalize);
                                                auto builder = bsoncxx::builder::stream::document{};
                                                auto doc = document{};
                                                //bsoncxx::document::value doc_value;

                                                for (auto&& doc1 : infoResult) {
                                                doc = builder << bsoncxx::to_json(doc1);
                                                        //<< bsoncxx::builder::stream::finalize;
                                                        std::cout << bsoncxx::to_json(doc1) << std::endl;
                                                } */

                                              bsoncxx::document::element elementID = doc["id"];
                                                std::string id = elementID.get_utf8().value.to_string();

                                                bsoncxx::document::element elementfn = view["firstname"];
                                                std::string firstname = elementfn.get_utf8().value.to_string();

                                                bsoncxx::document::element elementln = view["lastname"];
                                                std::string lastname = elementln.get_utf8().value.to_string();

                                                bsoncxx::document::element elementbd = view["birthdate"];
                                                std::string birthdate = elementbd.get_utf8().value.to_string();

                                                bsoncxx::document::element elementgn = view["gender"];
                                                std::string gender = elementgn.get_utf8().value.to_string();
                                                
                                                bsoncxx::document::element elementml = view["email"];
                                                std::string mail = elementml.get_utf8().value.to_string();

                                                bsoncxx::document::element elementlg = view["login"];
                                                std::string login = elementlg.get_utf8().value.to_string();
                                                

                                                response["id"] = json::value::string(id);
                                                response["firstname"] = json::value::string(firstname);
                                                response["lastname"] = json::value::string(lastname);
                                                response["birthdate"] = json::value::string(birthdate);
                                                response["gender"] = json::value::string(gender);
                                                response["email"] = json::value::string(mail);
                                                response["login"] = json::value::string(login);
                                        
/*
                                                response["id"] = infoResult["id"];

                                                message.reply(status_codes::OK, response);

                                        } else {
                                                bsoncxx::stdx::optional<bsoncxx::document::value> loginPassResult =
                                                coll2.find_one(document{} << "login" << request.at("login").as_string() << finalize);
                                                if (loginResult) {
                                                        response["passResult"] = json::value::string("wrongPass");
                                                        std::string loginDate = date();

                                                bsoncxx::stdx::optional<bsoncxx::document::value> info =
                                                        coll1.find_one(document{} << "login" << login);
                                                                bsoncxx::document::view doc_view{info.view()};
                                                coll1.update_one(document{} << "login" << login << finalize,
                                                                document{} << "$set" << open_document <<
                                                                document{} << "$inc" << open_document <<
                                                                "visitCount" << 1 << close_document << finalize);

                                                coll1.update_one(document{} << "login" << login
                                                        << close_document << finalize,
                                                        document{} << "$set" << open_document <<
                                                        "visitTime" << date() << close_document << finalize);
                                                } else {
                                                        response["loginStatus"] = json::value::string("unknownLogin");
                                                }

                                        }

                                }
                        }
*/
		});
	//	});
}
