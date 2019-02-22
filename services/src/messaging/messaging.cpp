#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <messaging/messaging.hpp>

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
    _listener.support(methods::POST, std::bind(&Messaging::handlePost, this, std::placeholders::_1));
}

http_response userRemoveMessage(std::sting firstUserId , std::string secondUserId , messageId , http_client* DataBaseClient){
	uri_bilder uRremoveMessage("/userRemoveMessage/"+firstUserId+"/"+secondUserId+"/"+messageId+"/");
 	DataBaseClient->request(method::GET,uRemoveMessage.to_string());
  	then([=](http_response removeMessage)
	{
		return removeMessage;
	});
}
http_response userRemoveConversation(std::sting firstUserId,std::string secondUserId,http_client* DataBaseClient){
        uri_bilder uRremoveConversation("/userRemoveConversation/"+firstUserId+"/"+secondUserId+"/");
        DataBaseClient->request(method::GET,uRemoveConversation.to_string());
        then([=](http_response removeConversation)
        {
                return removeConversation;
        });
}
//conversation
http_response getUserConversation(std::sting firstUserId,std::string secondUserId,http_client* DataBaseClient){
        uri_bilder gUserConversation("/userRemoveConversation/"+firstUserId+"/"+secondUserId+"/");
        DataBaseClient->request(method::GET,gUserConversation.to_string());
        then([=](http_response userConversation)
        {
                return userConversation;
        });
}
//conversations
http_response getUserConversations(std::sting userId,http_client* DataBaseClient){
        uri_bilder gUserConversations("/getUserConversations/"+userId+"/");
        DataBaseClient->request(method::GET,gUserConversations.to_string());
        then([=](http_response userConversations)
        {
                return userConversations;
        });
}

http_response getGroupConversation(std::sting userId,std::string groupId ,http_client* DataBaseClient){
        uri_bilder gGroupConversation("/getGroupConversation/"+userId+"/"+groupId+"/");
        DataBaseClient->request(method::GET,gGroupConversation.to_string());
        then([=](http_response groupConversation)
        {
                return groupConversation;
        });
}

http_response groupRemoveConversation(std::sting userId,std::string groupId ,http_client* DataBaseClient){
        uri_bilder gRemoveConversation("/groupRemoveConversation/"+userId+"/"+groupId+"/");
        DataBaseClient->request(method::GET,gRemoveConversation.to_string());
        then([=](http_response removeConversation)
        {
                return removeConversation;
        });
}

http_response groupRemoveMessage(std::sting userId,std::string groupId , std::string messageId , http_client* DataBaseClient){
        uri_bilder gRemoveMessage("/groupRemoveMessage/"+userId+"/"+groupId+"/"+messageId+"/");
        DataBaseClient->request(method::GET,gRemoveMessage.to_string());
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
			auto  removeMessage =userRemoveMessage(firstUserId , secondUserId , messageId , this->DataBaseClient);
			message.reply(removeMessage);
		}else
		{
			if(path[1] == "userRemoveConversation")
			{
				std::string firstUserId  = path[2];
				std::string secondUserId = path[3];
				auto removeConversation  = userRemoveConversation(firstUserId,secondUserId,this->DataBaseClient);
				message.reply(removeConversation);
			}else
			{
				if(path[1] == "getUserConversation")
				{
					std::string firstUserId  = path[2];
                                	std::string secondUserId = path[3];
                                	auto userConversation  = getUserConversation(firstUserId,secondUserId,this->DataBaseClient);
                                	message.reply(userConversation);
				}else
				{
					if(path[1] == "getUserConversations")
                                	{	
						std::string userId  = path[2];
                                		auto userConversations  = getUserConversations(userId,this->DataBaseClient);
                                		message.reply(userConversations);
                                	}else
                                	{
						if(path[1] == "getGroupConversation")
						{
							std::string userId  = path[2];
							std::string groupId = path[3];
							auto groupConversation = getGroupConversation(userId,groupId,this->DataBaseClient);
							message.reply(groupConversation);
						}else
						{
							if(path[1] == "groupRemoveConversation")
							{
								std::string userId  = path[2];
                	                                        std::string groupId = path[3];
        	                                                auto removeConversation = grouptRemoveConversation(userId,groupId,this->DataBaseClient);
	                                                        message.reply(removeConversation);

							}else
							{
								if(path[1] =="groupRemoveMessage")
								{
									std::string userId    = path[2];
                                                                	std::string groupId   = path[3];
                                                                	std::string messageId = path[4];
									auto removeMessage = grouptRemoveMessage(userId , groupId , messageId , this->DataBaseClient);
                                                                	message.reply(removeMessage;
								}
							}
						}
                               		}
				}
			}
		}
		
	}else
	{
    		message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
	}
}

http_response userUpdateMessage (json::value req, http_client* DataBaseClient){
		uri_builder userUpdateMessage_path(U("/userUpdateMessage/"));
		DataBaseClient->request(methods::POST, userUpdateMessage_path.to_string(), req).
		then([=](http_response status){
			return status;
		});
}

http_response userSendMessage (json::value req, http_client* DataBaseClient){
		uri_builder userSenaMessage_path(U("/userSendMessage/"));
		DataBaseClient->request(methods::POST, userSendMessage_path.to_string(), req).
		then([=](http_response status){
			return status;
		});
}

http_response groupUpdateMessage (json::value req, http_client* DataBaseClient){
		uri_builder groupUpdateMessage_path(U("/groupUpdateMessage/"));
		DataBaseClient->request(methods::POST, groupUpdateMessage_path.to_string(), req).
		then([=](http_response status){
			return status;
		});
}

http_response groupSendMessage (json::value req, http_client* DataBaseClient){
	uri_builder userSenaMessage_path(U("/groupSendMessage/"));
	DataBaseClient->request(methods::POST, groupSendMessage_path.to_string(), req).
	then([=](http_response status){
		return status;
	});
}

void Messaging::handlePost(http_request message) {
	auto path = requestPath(message);
	message.extract_json().
	then([=](json::value request)
	{
		if(path[1] == "userUpdateMessage"){
			auto resp = userUpdateMessage (request, this -> DataBaseClient);
			message.reply(resp);
		}
		else
		{
			if(path[1] == "userSendMessage"){
				auto resp = userSendMessage (request, this -> DataBaseClient);
				message.reply(resp);
			}
			else
			{
				if(path[1] == "groupUpdateMessage"){
					auto resp = groupUpdateMessage (request, this -> DataBaseClient);
					message.reply(resp);
				}
				else
				{
					if(path[1] == "groupSendMessage"){
						auto resp = groupSendMessage (request, this -> DataBaseClient);
						message.reply(resp);
					}
					else
					{
						message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
					}
				}
			}
		}
	});
}
