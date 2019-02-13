#include "router.hpp"
#include <fstream>
#include <string>
#include <iostream>


using namespace web;
using namespace http;

json::value readConfigFile(std::string path)
{
        std::ifstream ConfigFile(path);
	json::value config;
	if (ConfigFile.is_open()) {
		ConfigFile>> config;
        	ConfigFile.close();
	}
	else {
		std::cerr << "ConfigFile is not exist!!!" << std::endl;
	}
	return config;
}

void createClients(json::value config, std::string& routerUri)
{
	routerUri = config.at("router").as_string();
	AccountClient = new http_client(config.at("account").as_string());
	ConcersationClient = new http_client(config.at("conversation").as_string);
	GameClient = new http_client(config.at("game").as_string());
	NotificationClient = new http_client(config.at("notification").as_string());
	SearchClient = new http_client(config.at("search").as_string());
	TokenDbClient = new http_client(config.at("tokenDb").as_string());
}

bool start () {
	bool accServStatus = false;
	bool convServStatus = false;
	bool gameServStatus = false;
	bool notifStatus = false;
	bool searchServStatus = false;
	bool tokDbServStatus = false;
	uri_builder builder(U("/ServiceTest"));
	int numberOfAttempts = 0;
	while (accServStatus == false || convServStatus == false || gameServStatus == false || notifServStatus == false || searchServStatus == false || tokDbServStatus == false)
       	{
/*		if(!accServStatus)
		{
		AccountClient->request(methods::GET, builder.to_string()).then([](http_response response)
				{
					accServStatus = true;
				});
		}
		if(!accServStatus)
		{
		AccountClient->request(methods::GET, builder.to_string()).then([](http_response response)
				{
					accServStatus = true;
				});
		}
*/	}
}

Router::Router(std::string path)
{
	std::string routerUri = "";
	createClients(readConfigFile(path), routerUri);
}


void Router::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&Account::handleGet, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&Account::handlePut, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&Account::handlePost, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&Account::handleDelete, this, std::placeholders::_1));
    _listener.support(methods::PATCH, std::bind(&Account::handlePatch, this, std::placeholders::_1));
}

void Account::handleGet(http_request message) {
        http_request msg = message;
	auto path = requestPath(msg);
}

void Account::handlePost(http_request message) {
        http_request msg = message;
        auto path_first_request = requestPath(msg);
	if(path_first_request[0] == "account")
	{

	}
}

void Account::handlePatch(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PATCH));
}


void Account::handlePut(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PUT));
}


void Account::handleDelete(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::DEL));
}

void Account::handleHead(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::HEAD));
}

void Account::handleOptions(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::OPTIONS));
}

void Account::handleTrace(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::TRCE));
}

void Account::handleConnect(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::CONNECT));
}

void Account::handleMerge(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::MERGE));
}

json::value Account::responseNotImpl(const http::method & method) {
    auto response = json::value::object();
    response["serviceName"] = json::value::string("C++ Mircroservice Sample");
    response["http_method"] = json::value::string(method);
    return response ;
}

