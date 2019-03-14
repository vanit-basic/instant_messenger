#include <cstdint>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <thread>

#include <bsoncxx/builder/basic/array.hpp>
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

#include <bsoncxx/types/value.hpp>

#include <bsoncxx/document/value.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/array/view.hpp>

#include <dbservice/mongoDb.hpp>
#include <dbservice/database.hpp>

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
	auto coll1 = (*c1)["infoDB"]["userInfo"];
	bsoncxx::stdx::optional<bsoncxx::document::value> mailResult =
		coll1.find_one(document{} << "email" << mail << finalize);

	bsoncxx::stdx::optional<bsoncxx::document::value> loginResult =
		coll1.find_one(document{} << "login" << login << finalize);

	auto response = json::value::object();

	if(loginResult) {
		response["status"] = json::value::string("ALREADY_TAKEN");
	} else {
		response["status"] = json::value::string("NOT_USING");
	}


	if (mailResult) {
		response["status"] = json::value::string("ALREADY_TAKEN");
	} else {
		response["status"] = json::value::string("NOT_USING");
	}
	return response;
}

json::value MongoDB::signUp(json::value request) {
	auto c1 = poolMydb->acquire();
        auto c2 = poolDB->acquire();
        auto coll1 = (*c1)["infoDB"]["userInfo"];
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
		<< "_id" << id
		<< "firstName" << firstName
		<< "lastName" << lastName
		<< "email" << email
		<< "login" << login
		<< "nickName" << firstName
		<< "birthDate" << birthDate
		<< "gender" << gender 
		<< "level" << 0
		<< "joinDate" << joinDate
		<< "statistics" << bsoncxx::builder::stream::open_document
		<< "playedGames" << 0
		<< "redCard" << 0
		<< "blackCard" << 0
		<< "sheriff" << 0
		<< "don" << 0
		<< "wins" << 0
		<< "fails" << 0
		<< "killed" << 0
		<< bsoncxx::builder::stream::close_document
		<< "publicGroups" << open_array  << close_array
		<< "privateGroups" << open_array  << close_array
		<< bsoncxx::builder::stream::finalize;
	
	auto result = coll1.insert_one(std::move(doc_value));

	json::value response;
	response["userId"] = json::value::string(id);
	response["firstName"] = json::value::string(firstName);
	response["lastName"] = json::value::string(lastName);
	response["nickName"] = json::value::string(firstName);
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
	response["status"] = json::value::string("OK");

	auto builder1 = bsoncxx::builder::stream::document{};
	bsoncxx::document::value doc_value2 = builder1
		<< "login" << login
		<< "password" << password
		<< "userId" << id
		<< "visitCount" << 0
		<< bsoncxx::builder::stream::finalize;
	
	result = coll2.insert_one(std::move(doc_value2));
	return response;
}

json::value MongoDB::signIn(std::string login, std::string password) {
	auto c1 = poolMydb->acquire();
        auto c2 = poolDB->acquire();
        auto coll1 = (*c1)["infoDB"]["userInfo"];
        auto coll2 = (*c2)["passDB"]["signin"];
	json::value response;

	bsoncxx::stdx::optional<bsoncxx::document::value> result =
		coll2.find_one(document{} << "login" << login
				<< "password" << password << finalize);

	if (result) {
		bsoncxx::stdx::optional<bsoncxx::document::value> infoResult =
			coll1.find_one(document{} << "login" << login << finalize);
		bsoncxx::document::view doc = result->view();
		bsoncxx::document::view docInfo = infoResult->view();


		bsoncxx::document::element element = docInfo["_id"];
		std::string id = element.get_utf8().value.to_string();
		response = getUserInfo(id);

	} else {
		bsoncxx::stdx::optional<bsoncxx::document::value> loginPassResult =
			coll2.find_one(document{} << "login" << login << finalize);
		if (loginPassResult) {
			response["status"] = json::value::string("INVALID_PASSWORD");
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
			response["status"] = json::value::string("INVALID_LOGIN");
		}
	}

	return response;
}

json::value MongoDB::getUserInfo(std::string id) {
	auto response = json::value::object();
	auto c1 = poolMydb->acquire();
	auto coll1 = (*c1)["infoDB"]["userInfo"];

	bsoncxx::stdx::optional<bsoncxx::document::value> result =
		coll1.find_one(document{} << "_id" << id << finalize);

	if (result) {
		bsoncxx::document::view doc = result->view();

		bsoncxx::document::element element = doc["firstName"];
		std::string firstName = element.get_utf8().value.to_string();
		std::cout << firstName << std::endl;

		element = doc["lastName"];
		std::string lastName = element.get_utf8().value.to_string();

		element = doc["nickName"];
		std::string nickName = element.get_utf8().value.to_string();

		element = doc["birthDate"];
		std::string birthDate = element.get_utf8().value.to_string();

		element = doc["gender"];
		std::string gender = element.get_utf8().value.to_string();

		element = doc["level"];
		std::string level = std::to_string(element.get_int32().value);
		std::cout << "LEVEL  " << level <<std::endl;
		
		element = doc["statistics"]["playedGames"];
		std::string playedGames = std::to_string(element.get_int32().value);

		element = doc["statistics"]["redCard"];
		std::string redCard = std::to_string(element.get_int32().value);
		
		element = doc["statistics"]["blackCard"];
		std::string blackCard = std::to_string(element.get_int32().value);
		
		element = doc["statistics"]["sheriff"];
		std::string sheriff = std::to_string(element.get_int32().value);

		element = doc["statistics"]["don"];
		std::string don = std::to_string(element.get_int32().value);
		std::cout << "DON  " << don <<std::endl;
		
		element = doc["statistics"]["wins"];
		std::string wins = std::to_string(element.get_int32().value);
		
		element = doc["statistics"]["fails"];
		std::string fails = std::to_string(element.get_int32().value);
		
		element = doc["statistics"]["killed"];
		std::string killed = std::to_string(element.get_int32().value);

		element = doc["email"];
		std::string mail = element.get_utf8().value.to_string();

		element = doc["login"];
		std::string login = element.get_utf8().value.to_string();

		element = doc["publicGroups"];
                std::vector <json::value> gIDs;
                if (element.type() == type::k_array) {
                        bsoncxx::array::view subarray{element.get_array().value};
                        for (const bsoncxx::array::element& gId : subarray) {
                                if (gId.type() == type::k_utf8) {
                                        std::string groupId = gId.get_utf8().value.to_string();
                                        gIDs.push_back(json::value::string(groupId));
                                }
                        }
                }
		
		element = doc["privateGroups"];
                std::vector <json::value> gID;
                if (element.type() == type::k_array) {
                        bsoncxx::array::view subarray{element.get_array().value};
                        for (const bsoncxx::array::element& gId : subarray) {
                                if (gId.type() == type::k_utf8) {
                                        std::string groupId = gId.get_utf8().value.to_string();
                                        gID.push_back(json::value::string(groupId));
                                }
                        }
                }

                response["userId"] = json::value::string(id);
		response["firstName"] = json::value::string(firstName);
		response["lastName"] = json::value::string(lastName);
		response["nickName"] = json::value::string(nickName);
		response["birthDate"] = json::value::string(birthDate);
		response["gender"] = json::value::string(gender);
		response["level"] = json::value::string(level);
		response["publicGroups"] = json::value::array(gIDs);
                response["privateGroups"] = json::value::array(gID);
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
		response["status"] = json::value::string("OK");

	} else {
		response["status"] = json::value::string("INVALID_USER_ID");
	}

	return response;
}

json::value MongoDB::getUserShortInfo(std::string id) {
	json::value response;
        auto c1 = poolMydb->acquire();
        auto coll1 = (*c1)["infoDB"]["userInfo"];

        bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll1.find_one(document{} << "_id" << id << finalize);

        if (result) {
		bsoncxx::document::view doc = result->view();

                bsoncxx::document::element element = doc["firstName"];
                std::string firstName = element.get_utf8().value.to_string();

                element = doc["lastName"];
                std::string lastName = element.get_utf8().value.to_string();

		element = doc["nickName"];
                std::string nickName = element.get_utf8().value.to_string();

		element = doc["level"];
		std::string level = std::to_string(element.get_int32().value);
		std::cout << "LEVEL  " << level <<std::endl;
		
		element = doc["statistics"]["playedGames"];
		std::string playedGames = std::to_string(element.get_int32().value);

		element = doc["statistics"]["redCard"];
		std::string redCard = std::to_string(element.get_int32().value);
		
		element = doc["statistics"]["blackCard"];
		std::string blackCard = std::to_string(element.get_int32().value);
		
		element = doc["statistics"]["sheriff"];
		std::string sheriff = std::to_string(element.get_int32().value);

		element = doc["statistics"]["don"];
		std::string don = std::to_string(element.get_int32().value);
		std::cout << "DON  " << don <<std::endl;
		
		element = doc["statistics"]["wins"];
		std::string wins = std::to_string(element.get_int32().value);
		
		element = doc["statistics"]["fails"];
		std::string fails = std::to_string(element.get_int32().value);
		
		element = doc["statistics"]["killed"];
		std::string killed = std::to_string(element.get_int32().value);

		element = doc["publicGroups"];
		std::vector <json::value> gIDs;
		if (element.type() == type::k_array) {
			bsoncxx::array::view subarray{element.get_array().value};
			for (const bsoncxx::array::element& gId : subarray) {
				if (gId.type() == type::k_utf8) {
					std::string grId = gId.get_utf8().value.to_string();
					gIDs.push_back(json::value::string(grId));
				}
			}
		}

		response["userId"] = json::value::string(id);
		response["firstName"] = json::value::string(firstName);
		response["lastName"] = json::value::string(lastName);
		response["nickName"] = json::value::string(nickName);
		response["publicGroups"] = json::value::array(gIDs);
		response["level"] = json::value::string(level);
		response["playedGames"] = json::value::string(playedGames);
		response["redCard"] = json::value::string(redCard);
		response["blackCard"] = json::value::string(blackCard);
		response["sheriff"] = json::value::string(sheriff);
		response["don"] = json::value::string(don);
		response["wins"] = json::value::string(wins);
		response["fails"] = json::value::string(fails);
		response["killed"] = json::value::string(killed);
		response["status"] = json::value::string("OK");

	} else {
       		response["status"] = json::value::string("INVALID_USER_ID");
        }
	
	return response;
}

json::value MongoDB::getGroupUsers(std::string groupId) {
	auto c3 = poolMydb->acquire();
        auto coll3 = (*c3)["infoDB"]["groupInfo"];
	auto response = json::value::object();

        bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll3.find_one(document{} << "_id" << groupId << finalize);
	
	if (result) {
		bsoncxx::document::view doc = result->view();
		bsoncxx::document::element element = doc["members"];
                std::vector <json::value> mIDs;
                if (element.type() == type::k_array) {
                        bsoncxx::array::view subarray{element.get_array().value};
                        for (const bsoncxx::array::element& mId : subarray) {
                                if (mId.type() == type::k_utf8) {
                                        json::value memberId(mId.get_utf8().value.to_string());
                                        mIDs.push_back(memberId);
                                }
                        }
                }

		response["member"] = json::value::array(mIDs);
		response["status"] = json::value::string("OK");
	} else {
		response["status"] = json::value::string("INVALID_GROUP_ID");
	}

	return response;
}

json::value MongoDB::getGroupShortInfo(std::string groupId) {
	auto c3 = poolMydb->acquire();
	auto coll3 = (*c3)["infoDB"]["groupInfo"];
        auto response = json::value::object();
	bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll3.find_one(document{} << "_id" << groupId << finalize);

        if (result) {
		bsoncxx::document::view doc = result->view();
                
		bsoncxx::document::element element = doc["access"];
                std::string access = element.get_utf8().value.to_string();
		
                element = doc["groupName"];
                std::string groupName = element.get_utf8().value.to_string();
                
		element = doc["avatar"];
                std::string avatar = element.get_utf8().value.to_string();

                response["groupId"] = json::value::string(groupId);
                response["groupName"] = json::value::string(groupName);
                response["avatar"] = json::value::string(avatar);
		
		if (access.compare("public") == 0) {
			element = doc["members"];
                	std::vector <json::value> uIDs;
                	if (element.type() == type::k_array) {
                        	bsoncxx::array::view subarray{element.get_array().value};
                        	for (const bsoncxx::array::element& uId : subarray) {
                        	        if (uId.type() == type::k_utf8) {
                        	                std::string usId = uId.get_utf8().value.to_string();
                                	        uIDs.push_back(json::value::string(usId));
                                	}
                        	}
                	}
		
			response["members"] = json::value::array(uIDs);	
		}

                response["status"] = json::value::string("OK");

        } else {
                response["status"] = json::value::string("INVALID_GROUP_ID");
        }
	
	return response;
}

json::value MongoDB::userUpdateInfo(json::value user) {
	json::value response;
        auto c1 = poolMydb->acquire();
        auto coll1 = (*c1)["infoDB"]["userInfo"];
        std::string id = user.at("userId").as_string();
	std::string newNickname = user.at("nickName").as_string();
	std::string newFirstname = user.at("firstName").as_string();
	std::string newLastname = user.at("lastName").as_string();
        
	bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll1.find_one(document{} << "_id" << id << finalize);

        if (result) {
		bsoncxx::document::view doc = result->view();

                bsoncxx::document::element element = doc["firstName"];
                std::string firstName = element.get_utf8().value.to_string();

		if (firstName.compare(newFirstname) != 0 && newFirstname.compare("") != 0) {
			coll1.update_one(document{} << "_id" << id << finalize,
                      		document{} << "$set" << open_document <<
                      		"firstName" << newFirstname << close_document << finalize);	
		}
                
		element = doc["lastName"];
                std::string lastName = element.get_utf8().value.to_string();

		if (lastName.compare(newLastname) != 0 && newLastname.compare("") != 0) {
			coll1.update_one(document{} << "_id" << id << finalize,
                      		document{} << "$set" << open_document <<
                      		"lastName" << newLastname << close_document << finalize);
		}

                element = doc["nickName"];
                std::string nickName = element.get_utf8().value.to_string();
		
		if (nickName.compare(newNickname) != 0 && newNickname.compare("") != 0) {
			coll1.update_one(document{} << "_id" << id << finalize,
                      		document{} << "$set" << open_document <<
                      		"nickName" << newNickname << close_document << finalize);
		}

                response = getUserInfo(id);
                response["status"] = json::value::string("OK");

        } else {
                response["status"] = json::value::string("INVALID_USER_ID");
        }

	return response;
}

json::value MongoDB::groupDelete(std::string groupId) {
        auto c1 = poolMydb->acquire();
        auto c3 = poolDB->acquire();
        auto coll1 = (*c1)["infoDB"]["userInfo"];
        auto coll3 = (*c3)["infoDB"]["groupInfo"];
	json::value response;

        bsoncxx::stdx::optional<bsoncxx::document::value> result1 = 
		coll3.find_one(document{} << "_id" << groupId <<  finalize);

	 if (result1) {
                bsoncxx::document::view doc = result1->view();
                bsoncxx::document::element element = doc["access"];
		std::string access = element.get_utf8().value.to_string() + "Groups";
		
		element = doc["members"];
		if (element.type() == type::k_array) {
                        bsoncxx::array::view subarray{element.get_array().value};
                        for (const bsoncxx::array::element& uIds : subarray) {
                                if (uIds.type() == type::k_utf8) {
                                        std::string uId = uIds.get_utf8().value.to_string();
                                        coll1.update_one(document{} << "userId" << uId << finalize,
                                                        document{} << "$pull" << open_document
                                                        << access << groupId << close_document << finalize);
                                 }
                        }
                }

		bsoncxx::stdx::optional<mongocxx::result::delete_result> result2 =
                        coll3.delete_one(document{} << "_id" << groupId << finalize);
	if (result2) {
		response["status"] = json::value::string("OK"); 
		}
	 }
	 else 
		response["status"] = json::value::string("INVALID_GROUP_ID"); 

	return response;
}

json::value MongoDB::isUserInGroup(std::string gid, std::string uid) {
        auto c3 = poolMydb->acquire();
        auto coll3 = (*c3)["infoDB"]["groupInfo"];
	json::value response;

	bsoncxx::stdx::optional<bsoncxx::document::value> groupResult =
                coll3.find_one(document{} << "_id" << gid << finalize);

	bool t = false;
        if (groupResult) {
                bsoncxx::document::view doc = groupResult->view();
                bsoncxx::document::element element = doc["members"];

		std::cout << uid << std::endl;
                if (element.type() == type::k_array) {
                        bsoncxx::array::view subarray{element.get_array().value};
                        for (const bsoncxx::array::element& userIds : subarray) {
                                if (userIds.type() == type::k_utf8) {
					std::string user = userIds.get_utf8().value.to_string();
					std::cout << user << std::endl;
					if (user.compare(uid) == 0) {
						t = true;
                                    	}
                                }
                        }
                }
		
	if (t) {
		response["status"] = json::value::string("IN_GROUP");
	} else {
		response["status"] = json::value::string("NOT_FOUND_IN_GROUP");
	}
	} else {
		response["status"] = json::value::string("INVALID_GROUP_ID");
	}
	return response;
}

json::value MongoDB::deleteUser(std::string id){
        auto c1 = poolMydb->acquire();
        auto c2 = poolDB->acquire();
        auto c3 = poolMydb->acquire();
        auto coll1 = (*c1)["infoDB"]["userInfo"];
        auto coll2 = (*c2)["passDB"]["signin"];
        auto coll3 = (*c3)["infoDB"]["groupInfo"];
        json::value response;

        bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll1.find_one(document{} << "_id" << id << finalize);

        if (result) {
                bsoncxx::document::view doc = result->view();
		bsoncxx::document::element element = doc["publicGroups"];
                if (element.type() == type::k_array) {
                        bsoncxx::array::view subarray{element.get_array().value};
                        for (const bsoncxx::array::element& gIds : subarray) {
                                if (gIds.type() == type::k_utf8) {
                                        std::string group = gIds.get_utf8().value.to_string();
					coll3.update_one(document{} << "_id" << group << finalize,
							document{} << "$pull" << open_document
							<< "members" << id << close_document <<finalize);
                                 }
                        }
                }
	
		element = doc["privateGroups"];
                if (element.type() == type::k_array) {
                        bsoncxx::array::view subarray{element.get_array().value};
                        for (const bsoncxx::array::element& gIds : subarray) {
                                if (gIds.type() == type::k_utf8) {
                                        std::string group = gIds.get_utf8().value.to_string();
                                        std::cout << group << std::endl;
                                        coll3.update_one(document{} << "_id" << group << finalize,
                                                        document{} << "$pull" << open_document
                                                        << "members" << id << close_document <<finalize);
                                }
                        }
                }

                bsoncxx::stdx::optional<mongocxx::result::delete_result> result1 =
                        coll1.delete_one(document{} << "_id" << id << finalize);

                bsoncxx::stdx::optional<mongocxx::result::delete_result> result2 =
                        coll2.delete_one(document{} << "_id" << id << finalize);

                if (result1 && result2) {
                        response["status"] = json::value::string("OK");
                }
        } else  {
                response["status"] = json::value::string("INVALID_USER_ID");
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
                        << "lastId" << 2
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
	json::value pesponse;

	std::string groupName = groupInfo.at("groupName").as_string();
        std::string userId = groupInfo.at("userId").as_string();
        std::string access = groupInfo.at("access").as_string();
        std::string avatar = groupInfo.at("avatar").as_string();
	std::string id = generateGroupID(coll3);

	auto builder = bsoncxx::builder::stream::document{};
	bsoncxx::document::value doc_value = builder
		<< "_id" << id
		<< "groupName" << groupName
		<< "avatar" << avatar
		<< "access" << access
		<< "adminId" << userId
		<< "createDate" << date()
		<< "members" << bsoncxx::builder::stream::open_array
		<< userId << close_array
		<< bsoncxx::builder::stream::finalize;

	bsoncxx::document::view view = doc_value.view();

	bsoncxx::stdx::optional<mongocxx::result::insert_one> result1 =
		coll3.insert_one(view);



	bsoncxx::stdx::optional<mongocxx::result::update> result;
	if (access.compare("public") == 0) {
			coll1.update_one(document{} << "_id" << userId << finalize,
			document{} << "$push" << open_document
			<< "publicGroups" << id << close_document << finalize);
	} else if (access.compare("private") == 0) {
			coll1.update_one(document{} << "_id" << userId << finalize,
			document{} << "$push" << open_document
			<< "privateGroups" << id << close_document << finalize);
	}

	if (result) {
		response["groupId"] = json::value::string(id);
		response["groupName"] = json::value::string(groupName);
		response["avatar"] = json::value::string(avatar);
		response["adminId"] = json::value::string(userId);
		response["createDate"] = json::value::string(date());
		response["access"] = json::value::string(access);
		response["status"] = json::value::string("OK");
	} else {
		response["status"] = json::value::string("INTERNAL_ERROR");
	}

	return response;
}

json::value MongoDB::addUserToGroup(std::string userId, std::string groupId, std::string clientId) {
	auto c1 = poolMydb->acquire();
	auto c3 = poolMydb->acquire();
	auto coll1 = (*c1)["infoDB"]["userInfo"];
	auto coll3 = (*c3)["infoDB"]["groupInfo"];
	json::value response;

	bsoncxx::stdx::optional<bsoncxx::document::value> groupResult =
		coll3.find_one(document{} << "_id" << groupId << finalize);

	if (groupResult) {
		bsoncxx::document::view doc = groupResult->view();

		bsoncxx::document::element element = doc["access"];
		std::string access = element.get_utf8().value.to_string();

		bsoncxx::stdx::optional<mongocxx::result::update> result;
		if (access.compare("public") == 0) {
			coll1.update_one(document{} << "_id" << clientId << finalize,
					document{} << "$push" << open_document
					<< "publicGroups" << groupId << close_document << finalize);
		} else if (access.compare("private") == 0) {
			coll1.update_one(document{} << "_id" << clientId << finalize,
					document{} << "$push" << open_document
					<< "privateGroups" << groupId << close_document << finalize);
		}

		bsoncxx::stdx::optional<mongocxx::result::update> result1 =
			coll3.update_one(document{} << "_id" << groupId << finalize,
					document{} << "$push" << open_document
					<< "members" << clientId << close_document << finalize);

		if (result && result1) {
			response["status"] = json::value::string("OK");
		} else {
			response["status"] = json::value::string("INTERNAL_ERROR");
		}
	} else {
		response["status"] = json::value::string("INVALID_GROUP_ID");
	}

	return response;
}

json::value MongoDB::groupRemoveUser(std::string groupId, std::string userId) {
	auto c1 = poolMydb->acquire();
        auto c3 = poolMydb->acquire();
        auto coll1 = (*c1)["infoDB"]["userInfo"];
        auto coll3 = (*c3)["infoDB"]["groupInfo"];
        json::value response;

	bsoncxx::stdx::optional<bsoncxx::document::value> groupResult =
                coll3.find_one(document{} << "_id" << groupId << finalize);

	if (groupResult) {
		auto isInGroup = isUserInGroup(groupId, userId);
		std::string status = isInGroup.at("status").as_string();
		if (status.compare("IN_GROUP") == 0) {
			bsoncxx::document::view doc = groupResult->view();
			
			bsoncxx::document::element el = doc["access"];
                	std::string access = el.get_utf8().value.to_string();

                	bsoncxx::stdx::optional<mongocxx::result::update> result;
                	if (access.compare("public") == 0) {
                	        coll1.update_one(document{} << "_id" << userId << finalize,
                	        	document{} << "$pull" << open_document
                	                << "publicGroups" << groupId << close_document << finalize);

			} else if (access.compare("private") == 0) {
        	                coll1.update_one(document{} << "_id" << userId << finalize,
                	        	document{} << "$pull" << open_document
                        	        << "privateGroups" << groupId << close_document << finalize);
                	}
			
			bsoncxx::stdx::optional<mongocxx::result::update> result1 =
				coll3.update_one(document{} << "_id" << groupId << finalize,
					document{} << "$pull" << open_document
                        		<< "members" << userId << close_document << finalize);
			
			response["status"] = json::value::string("OK");
		} else {
			response["status"] = json::value::string("INVALID_USER_ID");
		}
	} else {
                response["status"] = json::value::string("INVALID_GROUP_ID");
	}

	return response;
}

json::value MongoDB::groupUpdateInfo(json::value request) {
	auto c = poolMydb->acquire();
        auto coll3 = (*c)["infoDB"]["groupInfo"];
	json::value response;

        std::string groupId = request.at("groupId").as_string();
        std::string newName = request.at("newName").as_string();
        std::string newAvatar = request.at("newAvatar").as_string();
        std::string newAccess = request.at("newAccess").as_string();

        bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll3.find_one(document{} << "_id" << groupId << finalize);

        if (result) {
                bsoncxx::document::view doc = result->view();

                bsoncxx::document::element element = doc["groupName"];
                std::string name = element.get_utf8().value.to_string();

                if (name.compare(newName) != 0 && newName.compare("") != 0) {
                        coll3.update_one(document{} << "_id" << groupId << finalize,
                                document{} << "$set" << open_document <<
        			"groupName" << newName << close_document << finalize);
		}

		element = doc["access"];
		std::string access = element.get_utf8().value.to_string();
                if (access.compare(newName) != 0 && newName.compare("") != 0) {
                        coll3.update_one(document{} << "_id" << groupId << finalize,
                                document{} << "$set" << open_document <<
        			"groupName" << newName << close_document << finalize);
		}

		element = doc["avatar"];
		std::string avatar = element.get_utf8().value.to_string();
		if (avatar.compare(newAvatar) != 0) {
			coll3.update_one(document{} << "_id" << groupId << finalize, 
					document{} << "$set" << open_document <<
					"avatar" << newAvatar << close_document << finalize);
		}
		response = getGroupInfo(groupId);
		response["status"] = json::value::string("OK");

        } else {
                response["status"] = json::value::string("INVALID_USER_ID");
        }

        return response;

}

json::value MongoDB::getGroupInfo(std::string groupId) {
        auto c3 = poolMydb->acquire();
        auto coll3 = (*c3)["infoDB"]["groupInfo"];
	auto response = json::value::object();

        bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll3.find_one(document{} << "_id" << groupId << finalize);
	
	if (result) {
		bsoncxx::document::view doc = result->view();
        	
		bsoncxx::document::element element = doc["groupName"];
		std::string groupName = element.get_utf8().value.to_string();

		element = doc["adminId"];
		std::string adminId = element.get_utf8().value.to_string();
		
		element = doc["createDate"];
		std::string createDate = element.get_utf8().value.to_string();
		
		element = doc["avatar"];
		std::string avatar = element.get_utf8().value.to_string();
		
		element = doc["members"];
                std::vector <json::value> uIDs;
                if (element.type() == type::k_array) {
			bsoncxx::array::view subarray{element.get_array().value};
                        for (const bsoncxx::array::element& uId : subarray) {
                        	if (uId.type() == type::k_utf8) {
                        		std::string usId = uId.get_utf8().value.to_string();
					uIDs.push_back(json::value::string(usId));
                                }
                        }
                }
		
		response["groupId"] = json::value::string(groupId);
		response["groupName"] = json::value::string(groupName);
		response["avatar"] = json::value::string(avatar);
		response["adminId"] = json::value::string(adminId);
		response["createDate"] = json::value::string(createDate);
		response["members"] = json::value::array(uIDs);	
		response["status"] = json::value::string("OK");
	} else {
		response["status"] = json::value::string("INVALID_GROUP_ID");
	}

	return response;
}

json::value MongoDB::changePassword(json::value request) {
	auto c = poolDB->acquire();
        auto coll2 = (*c)["passDB"]["signin"];
        json::value response;

        std::string user = request.at("userId").as_string();
        std::string password = request.at("password").as_string();
        std::string newPassword = request.at("newPassword").as_string();

        bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll2.find_one(document{} << "_id" << user << finalize);
	if (result) {
                bsoncxx::document::view doc = result->view();
         	
		bsoncxx::document::element element = doc["password"];
		std::string pass = element.get_utf8().value.to_string();
		
                if (pass.compare(password) == 0 && pass.compare(newPassword) != 0) {
                        coll2.update_one(document{} << "_id" << user << finalize,
                                document{} << "$set" << open_document <<
        			"password" << newPassword << close_document << finalize);
		}
		response["status"] = json::value::string("OK");
	}
	else
		response["status"] = json::value::string("INVALID_USER_ID");
	return response;
}

json::value MongoDB::searchGroups(json::value request) {
	json::value response;
	
	web::json::array groupsId = request.at("groups").as_array();
	//std::string group;
	for (auto i = groupsId.begin(); i != groupsId.end(); ++i) {
		std::string id = (*i).as_string();
		auto doc = getGroupShortInfo(id);
		response[id] = json::value::string(doc.to_string());
	}

	return response;
}

json::value MongoDB::searchUsers(json::value request) {
	json::value response;
	
	web::json::array usersId = request.at("users").as_array();
	//std::string group;
	for (auto i = usersId.begin(); i != usersId.end(); ++i) {
		std::string id = (*i).as_string();
		auto doc = getUserShortInfo(id);
		response[id] = json::value::string(doc.to_string());
	}

	return response;
}


json::value MongoDB::changeGroupAdmin(std::string groupId, std::string userId) {
	auto c3 = poolMydb->acquire();
        auto coll3 = (*c3)["infoDB"]["groupInfo"];

        bsoncxx::stdx::optional<bsoncxx::document::value> result =
                coll3.find_one(document{} << "_id" << groupId << finalize);

	auto response = json::value::object();
	if (result) {
		bsoncxx::document::view doc = result->view();
        	
		bsoncxx::document::element element = doc["userId"];
		std::string userId = element.get_utf8().value.to_string();
		coll3.update_one(document{} << "_id" << groupId << finalize,
			document{} << "$set" << open_document <<
			"adminId" << userId << close_document << finalize);
		
		response["status"] = json::value::string("OK");
		return response;
	} else {
		response["status"] = json::value::string("NOT_OK");
		return response;
	}

}
