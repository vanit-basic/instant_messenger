#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <router/router.hpp>

/*
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
}*/

bool Router::createClients(std::string path)
{
	std::ifstream ConfigFile(path);
        json::value config;
	if (ConfigFile.is_open()) {
		ConfigFile>> config;
		ConfigFile.close();
		AccountClient = new http_client(config.at("account").as_string());
		ConversationClient = new http_client(config.at("conversation").as_string());
		GameClient = new http_client(config.at("game").as_string());
		NotificationClient = new http_client(config.at("notification").as_string());
		SearchClient = new http_client(config.at("search").as_string());
		TokenDbClient = new http_client(config.at("tokenDb").as_string());
		this->routerUri = config.at("router").as_string();
		return true;
	}
        else {
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
		return false;
        }
}

//http_client client(U("http://127.0.1.1:6502/v1/ivmero/api"));
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
			//avelacnel exequtor funkciayi kanch(vor@ petq e start ani servicner@)
                        if(exequtionCount >= maxExequtionCount)
                        {
				std::cout<<serviceName<<" service is dead!!!"<<std::endl;
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

bool Router::checkServices()
{
	bool status = false;
	bool accServStatus = false;
	bool convServStatus = false;
	bool gameServStatus = false;
	bool notifServStatus = false;
	bool searchServStatus = false;
	bool tokDbServStatus = false;
	accServStatus = ServiceStart(AccountClient, "Account");
	if(accServStatus){
		convServStatus = ServiceStart(ConversationClient, "Conversation");}
	if(convServStatus){
		gameServStatus = ServiceStart(GameClient, "Game");}
	if(gameServStatus){
		notifServStatus = ServiceStart(NotificationClient, "Notification");}
	if(notifServStatus){
		searchServStatus = ServiceStart(SearchClient, "Search");}
	if(searchServStatus){
		tokDbServStatus = ServiceStart(TokenDbClient, "TokenDB");}
	if (tokDbServStatus)
	{
		this->setEndpoint(routerUri);
		status = true;
	}
	return status;
/*
	this->setEndpoint(routerUri);
	return true;*/
}

Router::Router(std::string path)
{
	this->createClients(path);
}


void Router::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&Router::handleGet, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&Router::handlePost, this, std::placeholders::_1));
}

void Router::handleGet(http_request message) {
//	std::cout<<message.to_string()<<std::endl;
	TokenDbClient->request(message).
		then([message, this](http_response tokenStatus){
				tokenStatus.extract_json().then([message, this](json::value token){
				if(token.at("token").as_string() == "valid")
				{
					auto path = requestPath(message);
					if(path[0] == "Account")
					{
					AccountClient->request(message).
					then([message](http_response response){
						message.reply(response);
						});
					}
					else
					{
						if(path[0] == "Conversation")
						{
						ConversationClient->request(message).
						then([message](http_response response){
							message.reply(response);
						});
						}		
						else
						{
							if(path[0] == "Search")
							{
							SearchClient->request(message).
							then([message](http_response response){
								message.reply(response);
								});
							}
							else
							{
								if(path[0] == "Game")
								{
								GameClient->request(message).
								then([message](http_response response){
									message.reply(response);
									});
								}
								else
								{
									if(path[0] == "Notification")
									{
									NotificationClient->request(message).
									then([message](http_response response){
										message.reply(response);
										});
									}
								}
							}
						}
					}
				}
				else
				{
					message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET) );
				}
				});
		});
}

void Router::handlePost(http_request message) {
//	std::cout<<message.to_string()<<std::endl;	
	auto checkAction = requestPath(message);
	if(!(checkAction[1] == "registration" || checkAction[1] == "signin" || checkAction[1] == "forgotPassword"))
	{
	TokenDbClient->request(message).
		then([message, this](http_response tokenStatus){
				tokenStatus.extract_json().then([message, this](json::value token){
				if(token.at("token").as_string() == "valid")
				{
					auto path = requestPath(message);
					if(path[0] == "Account")
					{
					AccountClient->request(message).
					then([message](http_response response){
						message.reply(response);
						});
					}
					else
					{
						if(path[0] == "Conversation")
						{
						ConversationClient->request(message).
						then([message](http_response response){
							message.reply(response);
						});
						}		
						else
						{
							if(path[0] == "Search")
							{
							SearchClient->request(message).
							then([message](http_response response){
								message.reply(response);
								});
							}
							else
							{
								if(path[0] == "Game")
								{
								GameClient->request(message).
								then([message](http_response response){
									message.reply(response);
									});
								}
								else
								{
									if(path[0] == "Notification")
									{
									NotificationClient->request(message).
									then([message](http_response response){
										message.reply(response);
										});
									}
								}
							}
						}
					}
				}
				else
				{
					message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET) );
				}
				});
		});
	}
	else
	{
		AccountClient->request(message).
			then([message](http_response response){
					message.reply(response);
					});

	}

}
