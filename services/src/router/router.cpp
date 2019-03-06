#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <network_utils.hpp>

#include <router/router.hpp>


bool Router::createClients(std::string path)
{
	std::ifstream ConfigFile(path);
        json::value config;
	if (ConfigFile.is_open()) {
		ConfigFile>> config;
		ConfigFile.close();
		AccountClient = new http_client(NetworkUtils::hostURI(config.at("account").as_string()));
		ConversationClient = new http_client(NetworkUtils::hostURI(config.at("messaging").as_string()));
		GameClient = new http_client(NetworkUtils::hostURI(config.at("game").as_string()));
		NotificationClient = new http_client(NetworkUtils::hostURI(config.at("notification").as_string()));
		SearchClient = new http_client(NetworkUtils::hostURI(config.at("search").as_string()));
		TokenDbClient = new http_client(NetworkUtils::hostURI(config.at("tokendbservice").as_string()));
		this->routerUri = config.at("router").as_string();
		return true;
	}
        else {
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
		return false;
        }
}

bool ServiceStart (http_client* client, std::string serviceName) {
	uri_builder builder(U("/account/userDelete?clientId=12"));
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
                        pplx::task<http_response> requestTask = client->request(methods::GET, builder.to_string());
			requestTask.then([=](http_response resp){
					std::cout<<resp.to_string()<<std::endl;
					});
                        requestTask.wait();
                } catch (http_exception e) {
                        error = e.error_code();
			std::cerr<<e.what()<<std::endl;
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
/*	qani der patrast chen bolor MikroServicener@ toxnel vorpes comment
 
	if(accServStatus){
		convServStatus = ServiceStart(ConversationClient, "Messaging");}
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
*/
	if (accServStatus){
//		convServStatus = ServiceStart(ConversationClient, "Messaging");}
//	if (convServStatus){
	this->setEndpoint(routerUri);}
	return accServStatus;
}

Router::Router(std::string path)
{
	this->createClients(path);
}


void Router::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&Router::handleGet, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&Router::handlePost, this, std::placeholders::_1));
}

bool tokenValidator(http_request message){
	if(message.headers().has("token")){
		return true;
	}
	return true;
}

bool getIdValidator (http_request message){
	std::map<utility::string_t, utility::string_t>  i = uri::split_query(message.request_uri().query());
	if(i.find( "userId" ) != i.end()){
		return true;
	}
	return false;
}

void Router::handleGet(http_request message) {

	std::cout<<message.to_string()<<std::endl;
	auto path = requestPath(message);
	if (!(path.empty())){

		json::value tokenInfo;
		std::map<utility::string_t, utility::string_t>  i = uri::split_query(message.request_uri().query());

		bool Id = getIdValidator(message);
		bool Token = tokenValidator(message);

		if(Id && Token)
		{
			tokenInfo["id"] = json::value::string(i.find("userId")->second);
			tokenInfo["token"] = json::value::string(message.headers().operator[]("token"));

			uri_builder checkToken_path(U("/checkToken/"));

			TokenDbClient->request(methods::POST, checkToken_path.to_string(), tokenInfo).
				then([=](http_response tokenStatus){
						tokenStatus.extract_json().
						then([=](json::value token)
						{
								if(token.at("token").as_string() == "OK")
								{ 
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
			if(Id){
				http_response resp;
				resp.set_status_code(status_codes::OK);
				json::value info;
				info["status"] = json::value::string("TOKEN_IS_MISSING");
				resp.set_body(info);
				message.reply(resp);
			}
			else{
				http_response resp;
				resp.set_status_code(status_codes::OK);
				json::value info;
				info["status"] = json::value::string("USER_ID_IS_MISSING");
				resp.set_body(info);
				message.reply(resp);
			}
		}

	}
	else
	{
		message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET) );
	}

}

bool postIdValidator (http_request message){
	message.extract_json().
		then([=](json::value info)
	        {
		if(!(info.at("userId" ).is_null())){
			return true;
		}
		return false;
	});
}

void Router::handlePost(http_request message) {
	std::cout<<message.to_string()<<std::endl;	
	auto checkAction = requestPath(message);
	auto path = requestPath(message);
	if(path.empty()){ 
		if(!(checkAction[1] == "registration" || checkAction[1] == "signin" || checkAction[1] == "forgotPassword"))
		{
			json::value tokenInfo;
			std::map<utility::string_t, utility::string_t>  i = uri::split_query(message.request_uri().query());

			bool Id = postIdValidator(message);
			bool Token = tokenValidator(message);

			if(Id && Token)
			{
				tokenInfo["id"] = json::value::string(i.find("userId")->second);
				tokenInfo["token"] = json::value::string(message.headers().operator[]("token"));

				uri_builder checkToken_path(U("/checkToken/"));
				TokenDbClient->request(message).
				then([message, this](http_response tokenStatus)
				{
					tokenStatus.extract_json().then([message, this](json::value token)
					{
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
				if(Id){
					http_response resp;
					resp.set_status_code(status_codes::OK);
					json::value info;
					info["status"] = json::value::string("TOKEN_IS_MISSING");
					resp.set_body(info);
					message.reply(resp);
				}
				else{
					http_response resp;
					resp.set_status_code(status_codes::OK);
					json::value info;
					info["status"] = json::value::string("USER_ID_IS_MISSING");
					resp.set_body(info);
					message.reply(resp);
				}
			}
		}
		else
		{
			if(checkAction[1] == "registration" || checkAction[1] == "signin" || checkAction[1] == "forgotPassword")
			{
				AccountClient->request(message).
					then([message](http_response response){
							message.reply(response);
							});
			}
			else
			{
				message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET) );
			}
		}
	}
}
