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

bool MongoDB::setToken(json::value)
{
	std::cout<<"setToken"<<std::endl;
}
bool MongoDB::checkToken(std::string id, std::string token)
{
	std::cout<<"checkToken"<<std::endl;
}
bool MongoDB::deleteToken(json::value)
{
	std::cout<<"deleteToken"<<std::endl;
}


std::string generateID(mongocxx::collection collection) {
	std::cout<<"generateId function"<<std::endl;
        std::string id;
	std::cout<<__LINE__<<std::endl;
        bsoncxx::builder::stream::document document{};
	std::cout<<__LINE__<<std::endl;
        auto lastId = collection.find_one({});
	std::cout<<__LINE__<<std::endl;
        if(!lastId) {
	std::cout<<__LINE__<<std::endl;
                auto doc = bsoncxx::builder::stream::document{};
                bsoncxx::document::value doc_value = doc
                        << "lastId" << 1
                        << bsoncxx::builder::stream::finalize;
                auto result = collection.insert_one(std::move(doc_value));
                id = "u1";
        }
        else {
	std::cout<<__LINE__<<std::endl;
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
	std::cout<<__LINE__<<std::endl;
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
                this->poolMydb = new mongocxx::pool (mongocxx::uri{config.at("infoDB").as_string()});
                this->poolDB = new mongocxx::pool (mongocxx::uri{config.at("infoDB").as_string()});
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
	delete [] this->poolDB;
}

json::value MongoDB::mail_login(json::value request) {
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
	std::cout<<"registerUser function"<<std::endl;
	auto c1 = poolMydb->acquire();
        auto c2 = poolDB->acquire();
        auto coll1 = (*c1)["infoDB"]["account"];
        auto coll2 = (*c2)["passDB"]["signin"];
	
	std::cout<<__LINE__<<std::endl;
	std::cout<<request.at(utility::string_t("firstname")).as_string()<<std::endl;
	std::cout<<__LINE__<<std::endl;
	std::string firstname =  request.at(utility::string_t("firstname")).as_string();
	std::cout<<__LINE__<<std::endl;
        std::string lastname = request.at("lastname").as_string();
        std::string email =  request.at("email").as_string();
        std::string login = request.at("login").as_string();
        std::string birthdate =  request.at("birthdate").as_string();
        std::string gender =  request.at("gender").as_string();
        std::string password = request.at("password").as_string();
	
	std::cout<<__LINE__<<std::endl;
	
	std::string id = generateID(coll2);
	
	std::cout<<__LINE__<<std::endl;
	
	std::string joinDate = date();
	
	std::cout<<__LINE__<<std::endl;
	
	auto builder = bsoncxx::builder::stream::document{};
	bsoncxx::document::value doc_value = builder
		<< "id" << id
		<< "firstname" << firstname
		<< "lastname" << lastname
		<< "email" << email
		<< "login" << login
		<< "birthdate" << birthdate
		<< "gender" << gender
		<< "joinDate" << joinDate
		<< bsoncxx::builder::stream::finalize;
	
	std::cout<<__LINE__<<std::endl;
	
	auto result = coll1.insert_one(std::move(doc_value));

	std::cout<<__LINE__<<std::endl;
	
	json::value response;
	response["status"] = json::value::string("successfullyRegistered");
	response["id"] = json::value::string(id);
	response["firstname"] = json::value::string(firstname);
	response["lastname"] = json::value::string(lastname);
	response["birthdate"] = json::value::string(birthdate);
	response["gender"] = json::value::string(gender);
	response["email"] = json::value::string(email);
	response["login"] = json::value::string(login);

	std::cout<<__LINE__<<std::endl;
	
	auto builder1 = bsoncxx::builder::stream::document{};
	bsoncxx::document::value doc_value2 = builder1
		<< "login" << login
		<< "password" << password
		<< "id" << id
		<< "visitCount" << 0
		<< bsoncxx::builder::stream::finalize;
	std::cout<<__LINE__<<std::endl;
	
	result = coll2.insert_one(std::move(doc_value2));
	
	std::cout<<__LINE__<<std::endl;

	return response;
}

json::value MongoDB::loginUser(json::value request) {
	auto c1 = poolMydb->acquire();
        auto c2 = poolDB->acquire();
        auto coll1 = (*c1)["infoDB"]["account"];
        auto coll2 = (*c2)["passDB"]["signin"];
	std::string login = request.at("login").as_string();
	std::string password = request.at("password").as_string();
	json::value response;

	bsoncxx::stdx::optional<bsoncxx::document::value> result =
		coll2.find_one(document{} << "login" << login
				<< "password" << password << finalize);


	if (result) {
		bsoncxx::stdx::optional<bsoncxx::document::value> infoResult =
			coll2.find_one(document{} << "login" << request.at("login").as_string()<< finalize);
		bsoncxx::document::view doc = result->view();
		bsoncxx::document::view docInfo = infoResult->view();
		//auto id = doc_view["id"];
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

		bsoncxx::document::element element = doc["id"];
		std::string id = element.get_utf8().value.to_string();

		element = doc["firstname"];
		std::string firstname = element.get_utf8().value.to_string();

		element = doc["lastname"];
		std::string lastname = element.get_utf8().value.to_string();

		element = doc["birthdate"];
		std::string birthdate = element.get_utf8().value.to_string();

		element = doc["gender"];
		std::string gender = element.get_utf8().value.to_string();

		element = doc["email"];
		std::string mail = element.get_utf8().value.to_string();

		element = doc["login"];
		std::string login = element.get_utf8().value.to_string();


		response["id"] = json::value::string(id);
		response["firstname"] = json::value::string(firstname);
		response["lastname"] = json::value::string(lastname);
		response["birthdate"] = json::value::string(birthdate);
		response["gender"] = json::value::string(gender);
		response["email"] = json::value::string(mail);
		response["login"] = json::value::string(login);


		//  message.reply(status_codes::OK, response);

	} else {
		bsoncxx::stdx::optional<bsoncxx::document::value> loginPassResult =
			coll2.find_one(document{} << "login" << request.at("login").as_string() << finalize);
		if (loginPassResult) {
			response["passResult"] = json::value::string("wrongPass");
			std::string loginDate = date();

			bsoncxx::stdx::optional<bsoncxx::document::value> info =
				coll1.find_one(document{} << "login" << login << finalize);
			bsoncxx::document::view doc_view = info->view();
			coll1.update_one(document{} << "login" << login << finalize,
					document{} << "$set" <<
					document{} << "$inc" << open_document <<
					"visitCount" << 1 << close_document << finalize);

			coll1.update_one(document{} << "login" << login
					<< finalize,
					document{} << "$set" << open_document <<
					"visitTime" << date() << close_document << finalize);
		} else {
			response["loginStatus"] = json::value::string("unknownLogin");
		}

	}

	return response;
}

json::value MongoDB::getUserInfo(json::value request){
	auto response = json::value::object();
	auto c1 = poolMydb->acquire();
	auto coll1 = (*c1)["infoDB"]["account"];
	std::string id = request.at("cientId").as_string();

	bsoncxx::stdx::optional<bsoncxx::document::value> result =
		coll1.find_one(document{} << "id" << id << finalize);

	if (result) {
		bsoncxx::document::view doc = result->view();

		bsoncxx::document::element element = doc["firstname"];
		std::string firstname = element.get_utf8().value.to_string();

		element = doc["lastname"];
		std::string lastname = element.get_utf8().value.to_string();

		element = doc["nickname"];
		std::string nickname = element.get_utf8().value.to_string();

		element = doc["birthdate"];
		std::string birthdate = element.get_utf8().value.to_string();

		element = doc["gender"];
		std::string gender = element.get_utf8().value.to_string();

		element = doc["email"];
		std::string mail = element.get_utf8().value.to_string();

		element = doc["login"];
		std::string login = element.get_utf8().value.to_string();

		response["firstname"] = json::value::string(firstname);
		response["lastname"] = json::value::string(lastname);
		response["nickname"] = json::value::string(nickname);
		response["birthdate"] = json::value::string(birthdate);
		response["gender"] = json::value::string(gender);
		response["email"] = json::value::string(mail);
		response["login"] = json::value::string(login);

	} else {
		response["infoStatus"] = json::value::string("unknownID");
	}

	return response;
}

json::value MongoDB::getUserShortInfo(json::value request){
	auto response = json::value::object();
        auto c1 = poolMydb->acquire();
        auto coll1 = (*c1)["infoDB"]["userInfo"];
        std::string id = request.at("cientId").as_string();

        bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll1.find_one(document{} << "id" << id << finalize);

        if (result) {
		bsoncxx::document::view doc = result->view();

                bsoncxx::document::element element = doc["firstname"];
                std::string firstname = element.get_utf8().value.to_string();

                element = doc["lastname"];
                std::string lastname = element.get_utf8().value.to_string();

                element = doc["nickname"];
                std::string nickname = element.get_utf8().value.to_string();

                response["firstname"] = json::value::string(firstname);
                response["lastname"] = json::value::string(lastname);
                response["nickname"] = json::value::string(nickname);

        } else {
                response["infoStatus"] = json::value::string("unknownID");
        }
	
	return response;
}

json::value MongoDB::deleteUser(json::value request){
	auto c1 = poolMydb->acquire();
        auto c2 = poolDB->acquire();
	auto c3 = poolMydb->acquire();
        auto coll1 = (*c1)["infoDB"]["userInfo"];
        auto coll2 = (*c2)["passDB"]["signin"];
	auto coll3 = (*c3)["infoDB"]["groupInfo"];
        std::string id = request.at("clientId").as_string();
	auto response = json::value::object();

	bsoncxx::stdx::optional<mongocxx::result::delete_result> result1 =
		coll1.delete_one(document{} << "id" << id << finalize);
	
	bsoncxx::stdx::optional<mongocxx::result::delete_result> result2 =
		coll2.delete_one(document{} << "id" << id << finalize);

/*	bsoncxx::stdx::optional<mongocxx::result::update> result =
		coll3.update_many( document{} << "usersQuantity" << 
			document{} << "$inc" << open_document <<
			"i" << 100 << close_document << finalize);

	bsoncxx::stdx::optional<mongocxx::result::delete_result> result3 =
		coll3.delete_many(document{} << "id" << id << finalize);
*/	
	if (result1 && result2) {
                response["deteteStatus"] = json::value::string("userSuccesfullyDeleted");
	} else  {
		response["deteteStatus"] = json::value::string("unknownUser");
	}

	return response;
}
/*
json::value MongoDB::getGroupUsers(json::value request){
	auto c1 = poolMydb->acquire();
	auto c3 = poolMydb->acquire();
        auto coll1 = (*c1)["infoDB"]["userInfo"];
	auto coll3 = (*c3)["infoDB"]["groupInfo"];
        std::string userID = request.at("userId").as_string();
        std::string groupID = request.at("ugroupId").as_string();
	auto response = json::value::object();

        bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll3.find_one(document{} << "groupId" << groupID << finalize);

        if (result) {
                bsoncxx::document::view doc{*result.view()};

                bsoncxx::document::element element = doc["usersCount"];
                std::string usersCount = element.get_utf8().value.to_string();
		int n = std::stoi(usersCount);
		std::string* a = new std::string[n];

		for (int i = 9; i < n; ++i) {
			element = doc["userid" + std::to_string(i)];
			a[i] = element.get_utf8().value.to_string();
		}

		for (int i = 0; i < n; ++i) {
			bsoncxx::stdx::optional<bsoncxx::document::value> result =
				coll1.find_one(document{} << "id" << a[i] << finalize);

			if (result) {
				bsoncxx::document::view doc{*result.view()};

				bsoncxx::document::element element = doc["firstname"];
				std::string firstname = element.get_utf8().value.to_string();

				element = doc["lastname"];
				std::string lastname = element.get_utf8().value.to_string();

				element = doc["nickname"];
				std::string nickname = element.get_utf8().value.to_string();
				
				response["firstname"] = json::value::string(firstname);
				response["lastname"] = json::value::string(lastname);
				response["nickname"] = json::value::string(nickname);


			} else {
				response["infoStatus"] = json::value::string("unknownID");
			}
		}
		delete []a;

	}

	return response;


}
*/
