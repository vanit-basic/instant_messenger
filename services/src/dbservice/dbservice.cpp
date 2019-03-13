#include <cstdint>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <thread>
#include <map>

#include <dbservice/database.hpp>
#include <dbservice/dbservice.hpp>



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
	if(getUri(path)) {
		this->setEndpoint(dbserviceUri);
	}
	this->m_db = m;
}

DbService::~DbService() {
}

void DbService::handleGet(http_request message) {
	std::cout<< message.to_string()<<std::endl;
	auto path = requestPath(message);
	if (!(path.empty())) {
	std::map<utility::string_t, utility::string_t>  i = uri::split_query(message.request_uri().query());
		if (path[0] == "ServiceTest"){
			message.reply(status_codes::OK, "DbService_Start");
		} else if (path[0] == "account") {
			if (path[1] == "getUserInfo") {
				std::string id = "";
				id = i.find("userId")->second;
				json::value response = m_db->getUserInfo(id);
				message.reply(status_codes::OK, response);
			} else {
				if (path[1] == "deleteUser") {
					 std::string id = "";
                        	         id = i.find("userId")->second;
                                	 json::value response = m_db->deleteUser(id);
                                	 message.reply(status_codes::OK, response);
				} else {
					if (path[1] == "addUserToGroup") {
						std::string userId = i.find("userId")->second;
						std::string groupId = i.find("groupId")->second;
						std::string clientId = i.find("clientId")->second;
                                         	json::value response = m_db->addUserToGroup(userId, groupId, clientId);
                                         	message.reply(status_codes::OK, response);
					} else {
						if (path[1] == "getUserShortInfo") {
							std::string clientId = i.find("clientId")->second;
                                			json::value response = m_db->getUserShortInfo(clientId);
                                			message.reply(status_codes::OK, response);
						} else {
							if (path[1] == "isUserInGroup") {
								std::string userId = i.find("userId")->second;
								std::string groupId = i.find("groupId")->second;
                                         			json::value response = m_db->isUserInGroup(groupId, userId);
                                         			message.reply(status_codes::OK, response);
							} else if (path[1] == "deleteGroup") {
								std::string groupId = i.find("groupId")->second;
                                                                json::value response = m_db->deleteGroup(groupId);
                                                                message.reply(status_codes::OK, response);
							}
						}
					}
				}
			}
		}
		else{
			message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
		}
	}
}

void DbService::handlePost(http_request message) {
	message.extract_json().then([message, this](json::value request) {
		std::cout<<request.to_string()<<std::endl;
		auto path = requestPath(message);
		if (!path.empty()) {
			if (path[0] == "check") {
				if (path[1] == "mailAndLogin") {
					std::string mail = request.at("email").as_string();
					std::string login = request.at("login").as_string();
					json::value response = m_db->checkMailAndLogin(mail, login);
					message.reply(status_codes::OK, response);
				} else if (path[1] == "signIn") {
					std::string login = request.at("login").as_string();
					std::string pass = request.at("password").as_string();
					json::value response = m_db->loginUser(login, pass);
					message.reply(status_codes::OK, response);
				} else {
					message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
				}
			} else if (path[0] == "insert") {
				if (path[1] == "registration") {
					json::value response = m_db->registerUser(request);
					message.reply(status_codes::OK, response);
				
				} else { 
						message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
				}
			}else if (path[0] == "account") {
                                        if (path[1] == "createGroup") {
                                                std::cout<<__LINE__<<std::endl;
                                                        json::value response = m_db->createGroup(request);
                                                        message.reply(status_codes::OK, response);
                                        }
					else {
						if (path[1] == "updateUserInfo") {
                                                        json::value response = m_db->updateUserInfo(request);
                                                        message.reply(status_codes::OK, response);
						}
					}
                                }
		} else {
			message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
		}
		});
}
