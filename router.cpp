#include "router.hpp"


using namespace web;
using namespace http;

std::string readConfigFile(std::string path)
{
        std::ifstream ConfigFile(path);
        std::string config = "";
        do
        {
                if(ConfigFile.is_open())
                {
                        while(! ConfigFile.eof())
                        {
                                getline(ConfigFile, config);
                        }
                }
        }
        while(!ConfigFile.is_open())
        ConfigFile.close();
	return config;
}

Router::Router(std::string path)
{
	json::value config = json::value::parse(readConfigFile(path));
	std::string accountUri = config["account"];
	std::string conversationUri = config["conversation"];
	std::string gameUri = config["game"];
	std::string notificationUri = config["notification"];
	std::string searchUri = config["search"];
	std::string routerUri = config["router"];
	std::string tokenDbUri = config["tokenDb"];
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

