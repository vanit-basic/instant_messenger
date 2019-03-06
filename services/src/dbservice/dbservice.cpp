#include <cstdint>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <thread>

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
auto path = requestPath(message);
if (!(path.empty())) {
	if (path[0] == "ServiceTest"){
		message.reply(status_codes::OK, "DbService_Start");
	}
}else{
	message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
}
}

void checkMailAndLogin(const http_request &message, const DbService *service) {
	message.extract_json().then([message, service](json::value request) {
				std::string mail = request.at("mail").as_string();
				std::string login = request.at("login").as_string();
				json::value response = service->m_db->checkMailAndLogin(mail, login);
				message.reply(status_codes::OK, response);
			});
}

void signIn (const http_request &message, const DbService *service) {
	message.extract_json().then([message, service](json::value request) {
			std::string login = request.at("login").as_string();
			std::string pass = request.at("password").as_string();
			json::value response = service->m_db->loginUser(login, pass);
			message.reply(status_codes::OK, response);
			});
}

void signUp (const http_request &message, const DbService *service) {
	message.extract_json().then([message, service](json::value request) {
	json::value response = service->m_db->registerUser(request);
	message.reply(status_codes::OK, response);
			});
}

void notImplemented(const http_request &message) {
	message.reply(status_codes::NotImplemented);
}

void DbService::handlePost(http_request message) {
	auto path = requestPath(message);
	if (!path.empty()) {
		if (path[0] == "check") {
			if (path[1] == "mail&login") {
				checkMailAndLogin(message, this);
			} else if (path[1] == "signIn") {
				signIn(message, this);
			} else {
				notImplemented(message);
			}
		} else if (path[0] == "insert") {
			if (path[1] == "registration") {
				signUp(message, this);
			} else {
				notImplemented(message);
			}
		} else {
			notImplemented(message);
		}
	} else {
		notImplemented(message);
	}
}
