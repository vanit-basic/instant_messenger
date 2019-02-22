#include <messaging/messaging.hpp>
#include <std_micro_service.hpp>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


bool Messaging::createClients(std::string path)
{
        std::ifstream ConfigFile(path);
        json::value config;
        if (ConfigFile.is_open()) {
                ConfigFile>> config;
                ConfigFile.close();
                DataBaseClient = new http_client(config.at("dataBase").as_string());
                this->messagingtUri = config.at("messaging").as_string();
                return true;
        }
        else {
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
                return false;
        }
}

Messaging::Messaging(std::string path)
{
        this->createClients(path);
}
bool ServiceStart (http_client* client, std::string serviceName) {
        uri_builder builder(U("/ServiceTest/"));
        std::error_code error;

        int count = 0;
        int exequtionCount = 0;
        const int maxExequtionCount = 10;
        const int maxCount = 60;
        do{
                if(count == maxCount)
                {
                        //avelacnel exequtor funkciayi kanch(vor@ petq e start ani DBservicner@)
                        if(exequtionCount >= maxExequtionCount)
                        {
                                std::cout<<serviceName<<" DBservices is dead!!!"<<std::endl;
                                return false;
                        }
                        ++exequtionCount;
                        count = 0;
                }
                usleep(100000);
                error.clear();
                try {
                        count++;
                        pplx::task<web::http::http_response> requestTask = client->request(methods::GET, builder.to_string());
                        requestTask.wait();
                } catch (http_exception e) {
                        error = e.error_code();
                }}
        while (error.value());
        return true;
}

bool Messaging::checkServices()
{
        bool status = false;
        bool DbServStatus = false;
        bool tokDbServStatus = false;
        DbServStatus = ServiceStart(DataBaseClient, "Messaging Database");
        if(DbServStatus){
                tokDbServStatus = ServiceStart(TokenDBClient, "TokenDatabase");}
        if (tokDbServStatus)
        {
                this->setEndpoint(messagingtUri);
                status = true;
        }
        return status;
}


void Account::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&Messaging::handleGet, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&Messaging::handlePut, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&Messaging::handlePost, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&Messaging::handleDelete, this, std::placeholders::_1));
    _listener.support(methods::PATCH, std::bind(&Messaging::handlePatch, this, std::placeholders::_1));
}
http_response userRemoveMessage(std::sting firstUserId,std::string secondUserId,http_client* DataBaseClient){
  
	uri_bilder uRremoveMessage("/userRemoveMessage/"+firstUserId+"/"+secondUserId+"/"+messageId+"/");
 	DataBaseClient->request(method::GET,uRemoveMessage.to_string());
  	then([=](http_response removeMessage)
	{
		return removeMessage;
	});
}
void Messaging::handleGet(http_request message) {
	auto path = requestPath(message);
	if(!(path.empty()))
	{
		if(path[1] == "userRemoveMessage")
		{
			std::string firstUserId  = path[2];
			std::string secondUserId = path[3];
			std::string messageId    = path[4];
			auto  removeMessage =userRemoveMessage(firstUserId,secondUserId,this->DataBaseClient);
			message.reply(removeMessage);
		}else
		{
		
		}
		
	}else
	{
    		message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
	}
}


void Messaging::handlePost(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
}

void Messaging::handlePatch(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PATCH));
}


void Messaging::handlePut(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PUT));
}


void Messaging::handleDelete(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::DEL));
}

void Messaging::handleHead(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::HEAD));
}

void Messaging::handleOptions(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::OPTIONS));
}

void Messaging::handleTrace(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::TRCE));
}

void Messaging::handleConnect(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::CONNECT));
}

void Messaging::handleMerge(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::MERGE));
}

json::value Account::responseNotImpl(const http::method & method) {
    auto response = json::value::object();
    response["serviceName"] = json::value::string("C++ Mircroservice Sample");
    response["http_method"] = json::value::string(method);
    return response ;
}


