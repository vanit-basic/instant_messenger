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

using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

bool MongoDB::setToken(json::value token)
{
	std::cout<<"setToken"<<std::endl;
}

bool MongoDB::checkToken(json::value token)
{
	std::cout<<"checkToken"<<std::endl;
}

bool MongoDB::deleteToken(json::value token)
{
	std::cout<<"deleteToken"<<std::endl;
}

std::string generateID(mongocxx::collection collection) {
	std::cout<<"generateId function"<<std::endl;
        std::string id;
        auto lastId = collection.find_one(document{} << "lastId" << open_document << "$gte" << 0 << close_document << finalize);
	std::cout << bsoncxx::to_json(*lastId) << std::endl;
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
                                        << "lastId" << 1 << close_document << bsoncxx::builder::stream::finalize);
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
                this->poolMydb = new mongocxx::pool (mongocxx::uri{config.at("mongodbServer").as_string()});
                this->poolDB = new mongocxx::pool (mongocxx::uri{config.at("mongodbServer").as_string()});
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

json::value MongoDB::checkMailAndLogin(std::string mail, std::string login) {
	auto c1 = poolMydb->acquire();
	auto coll1 = (*c1)["infoDB"]["account"];
	bsoncxx::stdx::optional<bsoncxx::document::value> mailResult =
		coll1.find_one(document{} << "mail" << mail << finalize);

	bsoncxx::stdx::optional<bsoncxx::document::value> loginResult =
		coll1.find_one(document{} << "login" << login << finalize);

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
	
	std::cout<<request.at(utility::string_t("firstname")).as_string()<<std::endl;
	std::string firstname =  request.at(utility::string_t("firstname")).as_string();
        std::string lastname = request.at("lastname").as_string();
        std::string email =  request.at("email").as_string();
        std::string login = request.at("login").as_string();
        std::string birthdate =  request.at("birthdate").as_string();
        std::string gender =  request.at("gender").as_string();
        std::string password = request.at("password").as_string();
	
	std::string id = generateID(coll2);
	std::string joinDate = date();
	
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
	
	auto result = coll1.insert_one(std::move(doc_value));

	json::value response;
	response["status"] = json::value::string("successfullyRegistered");
	response["id"] = json::value::string(id);
	response["firstname"] = json::value::string(firstname);
	response["lastname"] = json::value::string(lastname);
	response["birthdate"] = json::value::string(birthdate);
	response["gender"] = json::value::string(gender);
	response["email"] = json::value::string(email);
	response["login"] = json::value::string(login);

	auto builder1 = bsoncxx::builder::stream::document{};
	bsoncxx::document::value doc_value2 = builder1
		<< "login" << login
		<< "password" << password
		<< "id" << id
		<< "visitCount" << 0
		<< bsoncxx::builder::stream::finalize;
	
	result = coll2.insert_one(std::move(doc_value2));
	return response;
}

json::value MongoDB::loginUser(std::string login, std::string password) {
	auto c1 = poolMydb->acquire();
        auto c2 = poolDB->acquire();
        auto coll1 = (*c1)["infoDB"]["account"];
        auto coll2 = (*c2)["passDB"]["signin"];
	json::value response;

	bsoncxx::stdx::optional<bsoncxx::document::value> result =
		coll2.find_one(document{} << "login" << login
				<< "password" << password << finalize);

	if (result) {
		bsoncxx::stdx::optional<bsoncxx::document::value> infoResult =
			coll2.find_one(document{} << "login" << login << finalize);
		bsoncxx::document::view doc = result->view();
		bsoncxx::document::view docInfo = infoResult->view();

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

	} else {
		bsoncxx::stdx::optional<bsoncxx::document::value> loginPassResult =
			coll2.find_one(document{} << "login" << login << finalize);
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

json::value MongoDB::getUserInfo(std::string id) {
	auto response = json::value::object();
	auto c1 = poolMydb->acquire();
	auto coll1 = (*c1)["infoDB"]["account"];

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

json::value MongoDB::getUserShortInfo(std::string id) {
	auto response = json::value::object();
        auto c1 = poolMydb->acquire();
        auto coll1 = (*c1)["infoDB"]["userInfo"];

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

json::value MongoDB::getGroupShortInfo(std::string groupId) {
	auto c3 = poolMydb->acquire();
	auto coll3 = (*c3)["infoDB"]["groupInfo"];
        auto response = json::value::object();
	bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll3.find_one(document{} << "groupId" << groupId << finalize);

        if (result) {
		bsoncxx::document::view doc = result->view();

                bsoncxx::document::element element = doc["groupName"];
                std::string groupName = element.get_utf8().value.to_string();

                element = doc["usersQuantity"];
                std::string count = element.get_utf8().value.to_string();

                response["groupName"] = json::value::string(groupName);
                response["usersQuantity"] = json::value::string(count);
                response["status"] = json::value::string("OK");

        } else {
                response["infoStatus"] = json::value::string("INVALID_GROUP_ID");
        }
	
	return response;
}

json::value MongoDB::updateUserInfo(json::value user) {
	auto response = json::value::object();
        auto c1 = poolMydb->acquire();
        auto coll1 = (*c1)["infoDB"]["userInfo"];
        std::string id = user.at("id").as_string();
	std::string newNickname = user.at("nickname").as_string();
	std::string newFirstname = user.at("firstname").as_string();
	std::string newLastname = user.at("lastname").as_string();
        
	bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll1.find_one(document{} << "id" << id << finalize);

        if (result) {
		bsoncxx::document::view doc = result->view();

                bsoncxx::document::element element = doc["firstname"];
                std::string firstname = element.get_utf8().value.to_string();

		if (firstname.compare(newFirstname) == 0 && newFirstname.compare("") != 0) {
			coll1.update_one(document{} << "id" << id << finalize,
                      		document{} << "$set" << open_document <<
                      		"firstname" << newFirstname << close_document << finalize);	
		}

                element = doc["lastname"];
                std::string lastname = element.get_utf8().value.to_string();

		if (lastname.compare(newLastname) == 0 && newLastname.compare("") != 0) {
			coll1.update_one(document{} << "id" << id << finalize,
                      		document{} << "$set" << open_document <<
                      		"lastname" << newLastname << close_document << finalize);
		}

                element = doc["nickname"];
                std::string nickname = element.get_utf8().value.to_string();
		
		if (nickname.compare(newNickname) == 0 && newNickname.compare("") != 0) {
			coll1.update_one(document{} << "id" << id << finalize,
                      		document{} << "$set" << open_document <<
                      		"nickname" << newNickname << close_document << finalize);
		}

                response = getUserInfo(id);
                response["status"] = json::value::string("OK");

        } else {
                response["status"] = json::value::string("unknownID");
        }

	return response;
}

json::value MongoDB::deleteGroup(std::string groupId) {
	auto client = poolMydb->acquire();
	auto db = (*client)["infoDB"];
	auto groups = db["groups"];
	auto users = db["users"];
	std::cout << groupId << std::endl;

	bsoncxx::stdx::optional<bsoncxx::document::value> group = groups.find_one(document{} << "groupID" << groupId <<  finalize);
	bsoncxx::document::view view = group.value().view();
	for(auto doc : view) {
		//std::cout << doc.get_utf8().value.to_string() << "\n";
		/*bsoncxx::stdx::optional<mongocxx::result::update> deleteResult = 
			coll3.update_one(document{} << "_id" << groupId << finalize,
			document{} << "$pull" << open_document 
			<< "users" << "u3" << close_document << finalize);*/
	}
}

