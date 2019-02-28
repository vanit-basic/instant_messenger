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

#include <dbservice/mongoDb.hpp>
#include <dbservice/database.hpp>

using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

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

bool MongoDB::createPool(std::string path) {
        std::ifstream configFile(path);
        json::value config;
        if (configFile.is_open()) {
                configFile >> config;
                configFile.close();
                this->poolMydb = new mongocxx::pool ({config.at("infoDB").as_string()});
                this->poolDB = new mongocxx::pool ({config.at("tokenDB").as_string()});
                return true;
        } else {
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
                return false;
        }
}

MongoDB::MongoDB(std::string path) {
	static int count = 0;
        if (count < 1) {
                ++count;
                mongocxx::instance instance{};
        }
	createPool(path);
}

MongoDB::~MongoDB() {
	delete [] this->poolMydb;
	delete [] this->pooldb;
}

json::value MongoDB::mail&login(json::value request) {
	auto c1 = poolMydb->acquire();
	auto coll1 = (*c1)["infoDB"]["account"];
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
	return response;
}

json::value MongoDB::registerUser(json::value request) {
	auto c1 = poolMydb->acquire();
        auto c2 = poolDB->acquire();
        auto coll1 = (*c1)["infoDB"]["account"];
        auto coll2 = (*c2)["passDB"]["signin"];
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

	builder = bsoncxx::builder::stream::document{};
	doc_value = builder
		<< request.at("login").as_string() << bsoncxx::builder::stream::open_document
		<< "password" << request.at("password").as_string()
		<< "id" << id
		<< "visitCount" << 0
		<< close_document
		<< bsoncxx::builder::stream::finalize;
	result = coll2.insert_one(std::move(doc_value));
	return response;
}

json::value MongoDB::loginUser(json::value request) {
	auto c1 = poolMydb->acquire();
        auto c2 = poolDB->acquire();
        auto coll1 = (*c1)["infoDB"]["account"];
        auto coll2 = (*c2)["passDB"]["signin"];
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


                                                response["id"] = infoResult["id"];

                                                message.reply(status_codes::OK, response);

                                        } else {
                                                bsoncxx::stdx::optional<bsoncxx::document::value> loginPassResult =
                                                coll2.find_one(document{} << "login" << request.at("login").as_string() << finalize);
                                                if (loginResult) {
                                                        response["passResult"] = json::value::string("wrongPass");
                                                        std::string loginDate = date();

                                                bsoncxx::stdx::optional<bsoncxx::document::value> info =
                                                        coll1.find_one(document{} << "login" << login
                                                                bsoncxx::document::view doc_view{*info.view()};
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
