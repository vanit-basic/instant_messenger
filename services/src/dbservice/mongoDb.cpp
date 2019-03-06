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
        std::string id;
        auto lastIdf = collection.find_one(document{} << "lastId" << open_document << "$gte" << 0 << close_document << finalize);
        if(!lastIdf) {
                auto doc = bsoncxx::builder::stream::document{};
                bsoncxx::document::value doc_value = doc
                        << "lastId" << 1
                        << bsoncxx::builder::stream::finalize;
                auto result = collection.insert_one(std::move(doc_value));
	}
        auto lastId = collection.find_one(document{} << "lastId" << open_document << "$gte" << 0 << close_document << finalize);
                bsoncxx::document::view view = lastId.value().view();
                bsoncxx::document::element element = view["lastId"];
                if(element.type() != bsoncxx::type::k_utf8) {
                bsoncxx::document::view view = lastId.value().view();
                        int n = element.get_int32().value;
                        id = "u" + std::to_string(n);
                        collection.update_one(bsoncxx::builder::stream::document{} << "lastId" << n << finalize,
                                        bsoncxx::builder::stream::document{} << "$inc" << open_document
                                        << "lastId" << 1 << close_document << bsoncxx::builder::stream::finalize);
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
                this->poolMydb = new mongocxx::pool (mongocxx::uri{config.at("mongodbserver").as_string()});
                this->poolDB = new mongocxx::pool (mongocxx::uri{config.at("mongodbserver").as_string()});
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
		coll1.find_one(document{} << "email" << mail << finalize);

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
	auto c1 = poolMydb->acquire();
        auto c2 = poolDB->acquire();
        auto coll1 = (*c1)["infoDB"]["account"];
        auto coll2 = (*c2)["passDB"]["signin"];
	
	std::string firstName =  request.at(utility::string_t("firstName")).as_string();
        std::string lastName = request.at("lastName").as_string();
        std::string email =  request.at("email").as_string();
        std::string login = request.at("login").as_string();
        std::string birthDate =  request.at("birthDate").as_string();
        std::string gender =  request.at("gender").as_string();
        std::string password = request.at("password").as_string();
	std::string id = generateID(coll2);
	std::string joinDate = date();
	
	auto builder = bsoncxx::builder::stream::document{};
	bsoncxx::document::value doc_value = builder
		<< "id" << id
		<< "firstName" << firstName
		<< "lastName" << lastName
		<< "email" << email
		<< "login" << login
		<< "nickname" << firstName
		<< "birthDate" << birthDate
		<< "gender" << gender 
		<< "level" << "0"
		<< "joinDate" << joinDate
		<< "statistics" << bsoncxx::builder::stream::open_document
		<< "playedGames" << "0"
		<< "redCard" << "0"
		<< "blackCard" << "0"
		<< "sheriff" << "0"
		<< "don" << "0"
		<< "wins" << "0"
		<< "fails" << "0"
		<< "killed" << "0"
		<< bsoncxx::builder::stream::close_document
		<< bsoncxx::builder::stream::finalize;
	
	auto result = coll1.insert_one(std::move(doc_value));

	json::value response;
	response["status"] = json::value::string("successfullyRegistered");
	response["id"] = json::value::string(id);
	response["firstName"] = json::value::string(firstName);
	response["lastName"] = json::value::string(lastName);
	response["nickname"] = json::value::string(firstName);
	response["birthDate"] = json::value::string(birthDate);
	response["gender"] = json::value::string(gender);
	response["email"] = json::value::string(email);
	response["level"] = json::value::string("0");
	response["playedGames"] = json::value::string("0");
       	response["redCard"] = json::value::string("0");
	response["blackCard"] = json::value::string("0");	
	response["sheriff"] = json::value::string("0");
	response["don"] = json::value::string("0"); 
	response["wins"] = json::value::string("0");
	response["fails"] = json::value::string("0");
	response["killed"] = json::value::string("0");
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

	std::cout << "SignIn\n";
	if (result) {
		bsoncxx::stdx::optional<bsoncxx::document::value> infoResult =
			coll1.find_one(document{} << "login" << login << finalize);
		bsoncxx::document::view doc = result->view();
		bsoncxx::document::view docInfo = infoResult->view();
		
		bsoncxx::document::element element = docInfo["id"];
		std::string id = element.get_utf8().value.to_string();

		element = docInfo["firstName"];
		std::string firstName = element.get_utf8().value.to_string();

		element = docInfo["lastName"];
		std::string lastName = element.get_utf8().value.to_string();
		
		element = docInfo["nickname"];
		std::string nickname = element.get_utf8().value.to_string();
		
		element = docInfo["birthDate"];
		std::string birthDate = element.get_utf8().value.to_string();
		
		element = docInfo["gender"];
		std::string gender = element.get_utf8().value.to_string();

		element = docInfo["level"];
		std::string level = element.get_utf8().value.to_string();
		
		element = docInfo["statistics"]["playedGames"];
		std::string playedGames = element.get_utf8().value.to_string();

		element = docInfo["statistics"]["redCard"];
		std::string redCard = element.get_utf8().value.to_string();
		
		element = docInfo["statistics"]["blackCard"];
		std::string blackCard = element.get_utf8().value.to_string();
		
		element = docInfo["statistics"]["sheriff"];
		std::string sheriff = element.get_utf8().value.to_string();

		element = docInfo["statistics"]["don"];
		std::string don = element.get_utf8().value.to_string();
		
		element = docInfo["statistics"]["wins"];
		std::string wins = element.get_utf8().value.to_string();
		
		element = docInfo["statistics"]["fails"];
		std::string fails = element.get_utf8().value.to_string();
		
		element = docInfo["statistics"]["killed"];
		std::string killed = element.get_utf8().value.to_string();

		element = docInfo["email"];
		std::string mail = element.get_utf8().value.to_string();

		element = docInfo["login"];
		std::string login = element.get_utf8().value.to_string();


		response["id"] = json::value::string(id);
		response["firstName"] = json::value::string(firstName);
		response["lastName"] = json::value::string(lastName);
		response["birthDate"] = json::value::string(birthDate);
		response["gender"] = json::value::string(gender);
		response["level"] = json::value::string(level);
		response["playedGames"] = json::value::string(playedGames);
		response["redCard"] = json::value::string(redCard);
		response["blackCard"] = json::value::string(blackCard);
		response["sheriff"] = json::value::string(sheriff);
		response["don"] = json::value::string(don);
		response["wins"] = json::value::string(wins);
		response["fails"] = json::value::string(fails);
		response["killed"] = json::value::string(killed);
		response["email"] = json::value::string(mail);
		response["login"] = json::value::string(login);

	} else {
		bsoncxx::stdx::optional<bsoncxx::document::value> loginPassResult =
			coll2.find_one(document{} << "login" << login << finalize);
		if (loginPassResult) {
			response["passResult"] = json::value::string("wrongPass");
			std::string loginDate = date();
			
			bsoncxx::stdx::optional<bsoncxx::document::value> info =
				coll2.find_one(document{} << "login" << login << finalize);
			bsoncxx::document::view doc_view = info->view();
			coll2.update_one(document{} << "login" << login << finalize,
					document{} << "$inc" << open_document <<
					"visitCount" << 1 << close_document << finalize);

			coll2.update_one(document{} << "login" << login
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

	std::cout << __LINE__ << std::endl;
	bsoncxx::stdx::optional<bsoncxx::document::value> result =
		coll1.find_one(document{} << "id" << id << finalize);

	std::cout << __LINE__ << std::endl;
	if (result) {
		bsoncxx::document::view doc = result->view();
	std::cout << __LINE__ << std::endl;

		bsoncxx::document::element element = doc["firstName"];
		std::string firstName = element.get_utf8().value.to_string();

		element = doc["lastName"];
		std::string lastName = element.get_utf8().value.to_string();

		element = doc["nickname"];
		std::string nickname = element.get_utf8().value.to_string();

		element = doc["birthDate"];
		std::string birthDate = element.get_utf8().value.to_string();

		element = doc["gender"];
		std::string gender = element.get_utf8().value.to_string();

		

		element = doc["level"];
		std::string level = element.get_utf8().value.to_string();
		
		element = doc["statistics"]["playedGames"];
		std::string playedGames = element.get_utf8().value.to_string();

		element = doc["statistics"]["redCard"];
		std::string redCard = element.get_utf8().value.to_string();
		
		element = doc["statistics"]["blackCard"];
		std::string blackCard = element.get_utf8().value.to_string();
		
		element = doc["statistics"]["sheriff"];
		std::string sheriff = element.get_utf8().value.to_string();

		element = doc["statistics"]["don"];
		std::string don = element.get_utf8().value.to_string();
		
		element = doc["statistics"]["wins"];
		std::string wins = element.get_utf8().value.to_string();
		
		element = doc["statistics"]["fails"];
		std::string fails = element.get_utf8().value.to_string();
		
		element = doc["statistics"]["killed"];
		std::string killed = element.get_utf8().value.to_string();

		element = doc["email"];
		std::string mail = element.get_utf8().value.to_string();

		element = doc["login"];
		std::string login = element.get_utf8().value.to_string();
		std::cout << __LINE__ << std::endl;

		response["firstName"] = json::value::string(firstName);
		response["lastName"] = json::value::string(lastName);
		response["nickname"] = json::value::string(nickname);
		response["birthDate"] = json::value::string(birthDate);
		response["gender"] = json::value::string(gender);
		response["level"] = json::value::string(level);
		response["playedGames"] = json::value::string(playedGames);
		response["redCard"] = json::value::string(redCard);
		response["blackCard"] = json::value::string(blackCard);
		response["sheriff"] = json::value::string(sheriff);
		response["don"] = json::value::string(don);
		response["wins"] = json::value::string(wins);
		response["fails"] = json::value::string(fails);
		response["killed"] = json::value::string(killed);
		response["email"] = json::value::string(mail);
		response["login"] = json::value::string(login);

	} else {
	std::cout << __LINE__ << std::endl;
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

                bsoncxx::document::element element = doc["firstName"];
                std::string firstName = element.get_utf8().value.to_string();

                element = doc["lastName"];
                std::string lastName = element.get_utf8().value.to_string();

                element = doc["nickname"];
                std::string nickname = element.get_utf8().value.to_string();

		element = doc["level"];
		std::string level = element.get_utf8().value.to_string();
		
		element = doc["statistics"]["playedGames"];
		std::string playedGames = element.get_utf8().value.to_string();

		element = doc["statistics"]["redCard"];
		std::string redCard = element.get_utf8().value.to_string();
		
		element = doc["statistics"]["blackCard"];
		std::string blackCard = element.get_utf8().value.to_string();
		
		element = doc["statistics"]["sheriff"];
		std::string sheriff = element.get_utf8().value.to_string();

		element = doc["statistics"]["don"];
		std::string don = element.get_utf8().value.to_string();
		
		element = doc["statistics"]["wins"];
		std::string wins = element.get_utf8().value.to_string();
		
		element = doc["statistics"]["fails"];
		std::string fails = element.get_utf8().value.to_string();
		
		element = doc["statistics"]["killed"];
		std::string killed = element.get_utf8().value.to_string();

                response["firstName"] = json::value::string(firstName);
                response["lastName"] = json::value::string(lastName);
                response["nickname"] = json::value::string(nickname);
		response["level"] = json::value::string(level);
		response["playedGames"] = json::value::string(playedGames);
		response["redCard"] = json::value::string(redCard);
		response["blackCard"] = json::value::string(blackCard);
		response["sheriff"] = json::value::string(sheriff);
		response["don"] = json::value::string(don);
		response["wins"] = json::value::string(wins);
		response["fails"] = json::value::string(fails);
		response["killed"] = json::value::string(killed);

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
	std::string newFirstname = user.at("firstName").as_string();
	std::string newLastname = user.at("lastName").as_string();
        
	bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll1.find_one(document{} << "id" << id << finalize);

        if (result) {
		bsoncxx::document::view doc = result->view();

                bsoncxx::document::element element = doc["firstName"];
                std::string firstName = element.get_utf8().value.to_string();

		if (firstName.compare(newFirstname) == 0 && newFirstname.compare("") != 0) {
			coll1.update_one(document{} << "id" << id << finalize,
                      		document{} << "$set" << open_document <<
                      		"firstName" << newFirstname << close_document << finalize);	
		}

                element = doc["lastName"];
                std::string lastName = element.get_utf8().value.to_string();

		if (lastName.compare(newLastname) == 0 && newLastname.compare("") != 0) {
			coll1.update_one(document{} << "id" << id << finalize,
                      		document{} << "$set" << open_document <<
                      		"lastName" << newLastname << close_document << finalize);
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

        bsoncxx::stdx::optional<bsoncxx::document::value> group = groups.find_one(document{} << "groupId" << groupId <<  finalize);
        bsoncxx::document::view view = group.value().view();
        for(auto doc : view) {
                bsoncxx::stdx::optional<mongocxx::result::update> deleteResult =
                        users.update_one(document{} << "_id" << groupId << finalize,
                        document{} << "$pull" << open_document
                        << "groups" << groupId << close_document << finalize);
        }
}

json::value MongoDB::deleteUser(std::string id){
        auto c1 = poolMydb->acquire();
        auto c2 = poolDB->acquire();
        auto c3 = poolMydb->acquire();
        auto coll1 = (*c1)["infoDB"]["userInfo"];
        auto coll2 = (*c2)["passDB"]["signin"];
        auto coll3 = (*c3)["infoDB"]["groupInfo"];
        auto response = json::value::object();

        bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll3.find_one(document{} << "userId" << id << finalize);

        if (result) {
                bsoncxx::document::view doc = result->view();

                auto count = doc["groupsQuantity"];
                int n = std::stoi(count.get_utf8().value.to_string());

                for (int i = 0; i < n; ++i) {
                        bsoncxx::array::element element = doc["groups"][i];
                        std::string group = element.get_utf8().value.to_string();
                                bsoncxx::stdx::optional<mongocxx::result::update> deleteResult =
                                        coll3.update_many(document{} << "groupId" << group << finalize,
                                        document{} << "$pull" << open_document
                                        << "members" << id << close_document << finalize);
                                bsoncxx::stdx::optional<mongocxx::result::update> res =
                                        coll3.update_many(
                                        document{} << "usersQuantity" << open_document <<
                                        "groupId" << group << close_document << finalize,
                                        document{} << "$inc" << open_document <<
                                        "usersQunatity" << -1 << close_document << finalize);
                }

                bsoncxx::stdx::optional<mongocxx::result::delete_result> result1 =
                        coll1.delete_one(document{} << "id" << id << finalize);

                bsoncxx::stdx::optional<mongocxx::result::delete_result> result2 =
                        coll2.delete_one(document{} << "id" << id << finalize);

                bsoncxx::stdx::optional<mongocxx::result::delete_result> result3 =
                        coll3.delete_many(document{} << "id" << id << finalize);

                if (result1 && result2) {
                        response["deteteStatus"] = json::value::string("userSuccesfullyDeleted");
                }
        } else  {
                response["deteteStatus"] = json::value::string("unknownUser");
        }

        return response;
}

std::string generateGroupID(mongocxx::collection collection) {
        std::string id;
        auto lastId = collection.find_one(document{} << "lastId"
		<< open_document << "$gte" << 0
	       	<< close_document << finalize);
        if(!lastId) {
                auto doc = bsoncxx::builder::stream::document{};
                bsoncxx::document::value doc_value = doc
                        << "lastId" << 1
                        << bsoncxx::builder::stream::finalize;
                auto result = collection.insert_one(std::move(doc_value));
                id = "g1";
        } else {
                bsoncxx::document::view view = lastId.value().view();
                bsoncxx::document::element element = view["lastId"];
                if (element.type() != bsoncxx::type::k_utf8) {
                	bsoncxx::document::view view = lastId.value().view();
                        int n = element.get_int32().value;
                        id = "g" + std::to_string(n);
                        collection.update_one(bsoncxx::builder::stream::document{} << "lastId" << n << finalize,
                                        bsoncxx::builder::stream::document{} << "$inc" << open_document
                                        << "lastId" << 1 << close_document << bsoncxx::builder::stream::finalize);
                }
        }
        return id;
}


json::value MongoDB::createGroup(json::value groupInfo) {
	auto c1 = poolMydb->acquire();
	auto c3 = poolMydb->acquire();
	auto coll1 = (*c1)["infoDB"]["userInfo"];
	auto coll3 = (*c3)["infoDB"]["groupInfo"];
	auto response = json::value::object();

	std::string groupName = groupInfo.at("groupName").as_string();
        std::string userId = groupInfo.at("userId").as_string();
        std::string access = groupInfo.at("access").as_string();
	std::string id = generateGroupID(coll3);

	auto builder = bsoncxx::builder::stream::document{};
	bsoncxx::document::value doc_value = builder
		<< "groupId" << id
		<< "groupName" << groupName
		<< "access" << access
		<< "adminId" << userId
		<< "createDate" << date()
		<< "usersQuantity" << 1
		<< "members" << bsoncxx::builder::stream::open_array
		<< userId << close_array
		<< bsoncxx::builder::stream::finalize;

	bsoncxx::document::view view = doc_value.view();

	bsoncxx::stdx::optional<mongocxx::result::insert_one> result1 =
		coll3.insert_one(view);

	bsoncxx::stdx::optional<mongocxx::result::update> result2 =
                        coll1.update_one(document{} << "userId" << userId << finalize,
                        document{} << "$push" << open_document
                        << "groups" << id << close_document << finalize);

	if (result1 && result2) {
		response["groupId"] = json::value::string(id);
		response["groupName"] = json::value::string(groupName);
		response["adminId"] = json::value::string(userId);
		response["createDate"] = json::value::string(date());
		response["access"] = json::value::string("access");
		response["status"] = json::value::string("OK");
	} else {
		response["status"] = json::value::string("INTERNAL_ERROR");
	}

	return response;
}

json::value MongoDB::addUserToGroup(json::value request) {
	auto c1 = poolMydb->acquire();
	auto c3 = poolMydb->acquire();
	auto coll1 = (*c1)["infoDB"]["userInfo"];
	auto coll3 = (*c3)["infoDB"]["groupInfo"];
	auto response = json::value::object();

	std::string userId = request.at("userId").as_string();
	std::string groupId = request.at("groupId").as_string();

	bsoncxx::stdx::optional<bsoncxx::document::value> groupResult =
		coll3.find_one(document{} << "groupId" << groupId << finalize);

	if (groupResult) {
                	bsoncxx::document::view doc = groupResult->view();

                	auto count = doc["usersQuantity"];
                	int n = std::stoi(count.get_utf8().value.to_string());

                	for (int i = 0; i < n; ++i) {
                        	bsoncxx::array::element element = doc["memebers"][i];
                        	std::string user = element.get_utf8().value.to_string();
				if (user.compare(userId) == 0) {
					response["status"] = json::value::string("ALREADY_IN_GROUP");
					return response;
				}
                	}

			bsoncxx::stdx::optional<mongocxx::result::update> result1 =
                        	coll3.update_one(document{} << "groupId" << groupId << finalize,
                        	document{} << "$push" << open_document
                        	<< "members" << userId << close_document << finalize);

			bsoncxx::stdx::optional<mongocxx::result::update> result2 =
				coll3.update_one( document{} << "usersQuantity" << open_document <<
				"groupId" << groupId << close_document << finalize,
				document{} << "$inc" << open_document <<
				"usersQunatity" << 1 << close_document << finalize);

			bsoncxx::stdx::optional<mongocxx::result::update> result3 =
                                coll1.update_one(document{} << "userId" << userId << finalize,
                                document{} << "$push" << open_document
                                << "groups" << groupId << close_document << finalize);

			bsoncxx::stdx::optional<mongocxx::result::update> result4 =
				coll1.update_one( document{} << "groupsQuantity" << open_document <<
				"userId" << userId << close_document << finalize,
				document{} << "$inc" << open_document <<
				"groupsQunatity" << 1 << close_document << finalize);
			if (result1 && result2 && result3 && result4) {
				response["status"] = json::value::string("OK");
			} else {
				response["status"] = json::value::string("INTERNAL_ERROR");
			}

	} else {
		response["status"] = json::value::string("INVALID_GROUP");
	}

	return response;
}

json::value MongoDB::removeFromGroup(json::value request){
	auto c1 = poolMydb->acquire();
        auto c3 = poolMydb->acquire();
        auto coll1 = (*c1)["infoDB"]["userInfo"];
        auto coll3 = (*c3)["infoDB"]["groupInfo"];
        auto response = json::value::object();

        std::string userId = request.at("userId").as_string();
        std::string groupId = request.at("groupId").as_string();
        
	bsoncxx::stdx::optional<bsoncxx::document::value> groupResult =
                coll3.find_one(document{} << "groupId" << groupId << finalize);

	if (groupResult) {
		bsoncxx::stdx::optional<mongocxx::result::update> result1 =
			coll3.update_one(document{} << "groupId" << groupId << finalize,
			document{} << "$pull" << open_document
                        << "members" << userId << close_document << finalize);

		bsoncxx::stdx::optional<mongocxx::result::update> result2 =
			coll3.update_one( document{} << "usersQuantity" << open_document <<
			"groupId" << groupId << close_document << finalize,
			document{} << "$inc" << open_document <<
			"usersQunatity" << -1 << close_document << finalize);

		bsoncxx::stdx::optional<mongocxx::result::update> result3 =
                	coll1.update_one(document{} << "userId" << userId << finalize,
                        document{} << "$pull" << open_document
                        << "groups" << groupId << close_document << finalize);

		bsoncxx::stdx::optional<mongocxx::result::update> result4 =
			coll1.update_one( document{} << "groupsQuantity" << open_document <<
			"userId" << userId << close_document << finalize,
			document{} << "$inc" << open_document <<
			"groupsQunatity" << -1 << close_document << finalize);
		
		if (result1 && result2 && result3 && result4) {
			response["status"] = json::value::string("OK");
		} else {
			response["status"] = json::value::string("INTERNAL_ERROR");
		}

	} else {
		response["status"] = json::value::string("INVALID_GROUP");
	}

	return response;
}

json::value MongoDB::updateGroupInfo(json::value request) {
        auto c3 = poolMydb->acquire();
        auto coll3 = (*c3)["infoDB"]["groupInfo"];
	auto response = json::value::object();

        std::string groupId = request.at("groupId").as_string();
        std::string userId = request.at("userId").as_string();
        std::string newName = request.at("name").as_string();

        bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll3.find_one(document{} << "groupId" << groupId << finalize);

        if (result) {
                bsoncxx::document::view doc = result->view();

                bsoncxx::document::element element = doc["name"];
                std::string name = element.get_utf8().value.to_string();

                if (name.compare(newName) == 0 && newName.compare("") != 0) {
                        coll3.update_one(document{} << "groupId" << groupId << finalize,
                                document{} << "$set" << open_document <<
                                "name" << newName << close_document << finalize);
                	response["status"] = json::value::string("OK");
                } else {
			response["status"] = json::value::string("Names is same");
		}

        } else {
                response["status"] = json::value::string("unknownID");
        }

        return response;

}

json::value MongoDB::getPublicGroupInfo(std::string groupId, std::string userId) {
	auto c3 = poolMydb->acquire();
        auto coll3 = (*c3)["infoDB"]["groupInfo"];
	auto response = json::value::object();

        bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll3.find_one(document{} << "groupId" << groupId << finalize);

	bsoncxx::document::view doc = result->view();
	bsoncxx::document::element element = doc["name"];
	std::string name = element.get_utf8().value.to_string();

	element = doc["adminId"];
	std::string adminId = element.get_utf8().value.to_string();
		
	element = doc["usersQuantity"];
	std::string count = element.get_utf8().value.to_string();
			
	element = doc["createDate"];
	std::string createDate = element.get_utf8().value.to_string();

	int n = std::stoi(count);
	std::string allUsers = "";
	for (int i = 0; i < n; ++i) {
		bsoncxx::array::element element = doc["memebers"][i];
		std::string user = element.get_utf8().value.to_string();
		if (i == n) {
			allUsers += user;
		} else {
			allUsers += user + ",";
		}
	}
			
	response["name"] = json::value::string(name);
	response["adminId"] = json::value::string(adminId);
	response["users"] = json::value::string(allUsers);
	response["createDate"] = json::value::string(createDate);
	response["usersQuantity"] = json::value::string(count);
	response["status"] = json::value::string("OK");

	return response;

}

json::value MongoDB::getGroupInfo(json::value request) {
        auto c3 = poolMydb->acquire();
        auto coll3 = (*c3)["infoDB"]["groupInfo"];
	auto response = json::value::object();

	std::string groupId = request.at("groupId").as_string();
        std::string userId = request.at("userId").as_string();

        bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll3.find_one(document{} << "groupId" << groupId << finalize);
	
	if (result) {
		bsoncxx::document::view doc = result->view();
               	auto count = doc["usersQuantity"];
                int n = std::stoi(count.get_utf8().value.to_string());

		int k = 0;
                for (int i = 0; i < n; ++i) {
                        bsoncxx::array::element element = doc["members"][i];
                        std::string user = element.get_utf8().value.to_string();
			if (user.compare(userId) == 0) {
				++k;
			}
                }

		if (k > 0) {
			response = getPublicGroupInfo(groupId, userId);
		} else {
			bsoncxx::document::element element = doc["access"];
			std::string access = element.get_utf8().value.to_string();
			if (access.compare("public") == 0) {
				response = getPublicGroupInfo(groupId, userId);
			} else {
				response = getGroupShortInfo(groupId);
			}
		}

		response["status"] = json::value::string("OK");
	} else {
		response["status"] = json::value::string("INVALID_GROUP_ID");
	}

	return response;
}
