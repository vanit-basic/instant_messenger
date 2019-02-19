#include "account.hpp"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include </home/narek/Documents/Tnayin/micro-service/source/foundation/include/std_micro_service.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


Account::Account(std::string path)
{
        this->createClients(path);
}

bool Account::createClients(std::string path)
{
        std::ifstream ConfigFile(path);
        json::value config;
        if (ConfigFile.is_open()) {
                ConfigFile>> config;
                ConfigFile.close();
                DatabaseClient = new http_client(config.at("dataBase").as_string());
                TokenDbClient = new http_client(config.at("tokenDb").as_string());
                this->accountUri = config.at("account").as_string();
                return true;
        }
        else {
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
                return false;
        }
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

bool Account::checkServices()
{
        bool status = false;
        bool DbServStatus = false;
        bool tokDbServStatus = false;
        DbServStatus = ServiceStart(DatabaseClient, "Account Database");
        if(DbServStatus){
                tokDbServStatus = ServiceStart(TokenDBClient, "TokenDatabase");}
        if (tokDbServStatus)
        {
                this->setEndpoint(accountUri);
                status = true;
        }
        return status;
}


void Account::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&Account::handleGet, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&Account::handlePut, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&Account::handlePost, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&Account::handleDelete, this, std::placeholders::_1));
    _listener.support(methods::PATCH, std::bind(&Account::handlePatch, this, std::placeholders::_1));
}

std::string setToken(){
	
	srand(time(NULL));
        int tempOne = rand()% 100000000000;
        int tempTwo = rand()% 10000;
        std::string tokenOne = std::to_string(tempOne);
        std::string tokenTwo = std::to_string(tempTwo);
        std::string Token =tokenOne + tokenTwo;
	
	return Token;
}

http_response getUserInfo(std::string userId, http_client* DataBaseClient){
	uri_builder uInfo("/getUserInfo/" + userId + "/");
	DataBaseClient->request(method::GET, uInfo.to_string()).
		then([](http_response userInfo ) // [] - pakagceri mej@ ?
			{
				return userInfo;
			});
}

http_response getUserShortInfo(td::string userId http_client* DataBaseClient){
	uri_builder uInfo("/getUserShortInfo/" + userId + "/");
	DataBaseClient->request(method::GET, uInfo.to_string()).
	then([](http_response userShortInfo) // [] - pakagceri mej@ ?
			{
				return userShortInfo;
			});
}

http_response getGroupInfo(std::string groupId, http_client* DataBaseClient){
	uri_builder gInfo("/getGroupInfo/" + groupId + "/");
	DataBaseClient->request(method::GET, gInfo.to_string()).
		then([](http_response groupInfo) // [] - pakagceri mej@ ?
			{
				return groupInfo;
			});
}

http_response getGroupUsers(std::string groupId, http_client* DataBaseClient){
	uri_builder gInfo("/getGroupUsers/" + groupId + "/");
	DataBaseClient->request(method::GET, gInfo.to_string()).
		then([](http_response groupUsers) // [] - pakagceri mej@ ?
			{
				return groupUsers;
			});
}

http_response groupRemoveUser (http_request message, http_client* DateBaseClient)
{ 
	auto path = requestPath(message);
	std::string adminId = path[2]; 
	std::string groupId = path[3]; 
	std::string userId  = path[4]; 
	auto gInfo = getGroupInfo(groupId);
	gInfo.extract_json().
	then([message](http_response groupInfo) 
	{        
		if(adminId == groupInfo.at("adminId").as_string()) 
		{        
			uri_builder groupRemoveUser_path(U("/groupRemoveUser/"+ adminId + "/"+groupId+"/"+userId+"/")); 
			DataBaseClient.request(method::GET,  groupRemoveUser_path.to_string()). 
			then([message](http_response userRemove_response) 
			{ 
				return userRemove_response; 
			} 
		}
	       	else
		{
			// ???????????????????????
		}	
	}); 
} 

				 


void Account::handleGet(http_request message) {
	std::cout<< message.to_string()<<std::endl;
	auto path = requestPath(message);
	if (!path.empty()) {
		if(path_first_request[1] == "getUserInfo")
		{
			auto path = requestPath(message);
			std::string userId = path[2].to_string();
			auto userInfo = getUserInfo(userId, this -> DatabaseClient);
			message.reply(userInfo);
		}
		else
		{
			if(path_first_request[1] == "getUserShortInfo")
			{
				auto path = requestPath(message);
				std::string userId = path[2].to_string();
				auto userShortInfo = getUserShortInfo(userId, this -> DatabaseClient);
				message.reply(userShortInfo);
			}
			else
			{
				if(path_first_request[1] == "groupInfo")
				{
					auto path = requestPath(meesage);
					std::string groupId = path[2].to_string();
					auto groupInfo = getGroupInfo(groupId, this -> DatabaseClient);
					message.reply(groupInfo);
				}
				else
				{
					if(path_first_request[1] == "groupInfo")
					{
						auto path = requestPath(meesage);
						std::string groupId = path[2].to_string();
						auto groupUsers = getGroupUsers(groupId, this -> DatabaseClient);
						message.reply(groupUsers);
					}
					else
					{
						if(path_first_request[1] == "groupRemoveUser")
						{
							auto resp = getGroupUsers(groupId, this -> DatabaseClient);
							message.reply(resp);
						}
					}
				}
			}
		}
	}
	else
	{
		message.reply(status_codes::NotFound);
	}
}

void registration(http_request message , http_client* DateBaseClient){
        message.extract_json().then([message](json::value info)
	{
        std::string ml = "/get/mail_login"; 
        json::value login_mail;
        login_mail["email"] = info.at("email").as_string();
        login_mail["login"] = info.at("login").as_string();
        uri_builder get_mail_login(U(ml));
        DataBaseClient->request(methods::POST, get_mail_login.to_string(), login_mail).

		then([message, info](http_response mail_login)
		{
			mail_login.extract_json().
			then([message, info](json::value mail_login_json)
			{
				if(!(mail_login_json["email"] ==  info.at("email").as_string() && mail_login_json["login"] == info.at("login").as_string()))
				{
					DataBaseClient->request(message).
					then([message](http_response registration_response)
					{
						message.reply(registration_response);
					});
				}
				else
				{
					json::value error;
					if(mail_login_json["email"] ==  info.at("email").as_string())
					{
						error["email"] = json::value::string(U("Invalid"));
					}
					if(mail_login_json["login"] ==  info.at("login").as_string())
					{
						error["login"] = json::value::string(U("Invalid"));
					}
						message.reply(status_codes::OK, error);
				}		
			});
		});
	});
}

void signIn(http_request message, http_client* DateBaseClient, http_client* TokenDB){ 
	message.extract_json().then([message](json::value request))
	json::value signinInfo;
	uri_builder signin_path(U("/signin/"));
	singinInfo["login"] = request.at("login");
	singinInfo["password"] = request.at("password");
	DataBaseClient->request(method::POST,  signin_path.to_string(), signinInfo).
	then([message](http_response signinStatus)
	{
		signinStatus.extract_json().
		then([message, request](json::value signinStatus_json)
		{
			if (signinStatus_json["status"] == "notFound")
			{
				message.reply(status_codes::OK, json::value::string("Login or Password is Wrong!!!"));
			}
			else
			{
				if(signinStatus_json["status"] == "wrong")
				{
					int attempt = std::stoi(signinStatus_json["attempt"].as_string());
					if((this->max_attempt) > attempt)
					{
						if(((this->max_attempt) - attempt) == 1)
						{
							message.reply(status_codes::OK, json::value::string("Attention!!! You have one attempt left!!!"));
						}
						else
						{
							message.reply(status_codes::OK, json::value::string("Login or Password is Wrong!!!"));
						}
					}
					else
					{
						message.reply(status_codes::OK, json::value::string("Attempt failed!!!"));
					}
				}
				else
				{
					if(signinStatus_json["status"] == "OK")
					{
						std::string id = signinStatus_json["id"].as_string();
						json::value userInfo = getUserInfo(id, this -> DatabaseClient);	//petq e kanchenq getUserInfo() funkcian u user infon stanaluc heto  token generacnenq  //
						std::string token = setToken();//funkcia vor@ petqe token generacni
						uri_builder token_uri("/SetToken/");
						json::value token_json;
						token_json["token"] = json::value::string(token);
						token_json["id"] = json::value::string(id);
						TokenDB -> request(methods::POST, token_uri.to_string(), token_json).
						then([message, token_json, userInfo](http_response token_response)
						{
							userInfo["id"] = token_json["id"];
							userInfo["token"] = token_json["token"];
							message.reply(status_codes::OK, userInfo);
						});
					}
				}
			}
		});
	});
}

http_response deleteAccount(std::string userId, http_cliemt* DateBaseClient){
	json::value deleteAccountInfo;
	uri_builder deleteAccount_path(U("/deleteAccount/"));
	deleteAccountInfo["id"] = userId;
	DataBaseClient.request(method::POST,  deleteAccount_path.to_string(), deleteAccountInfo).
	then([](http_response status)
		return status;
	);
}


http_response signOut(std::string userId, http_client* TokenDb){
	uri_builder deleteToken("/deleteToken/");
	json::value userIdInfo;
	userIdInfo["id"] = userId;
	TokenDB.request(method::POST, deleteToken, userIdInfo);
	then([](http_response status){
		return status;		
	}
}


void Account::handlePost(http_request message) {
	auto path_first_request = requestPath(message);
	message.extract_json().
		then([message](json::value request) 
				{
				if ( path_first_request[1] == "registration") 
				{
					registration(message, this -> DatabaseClient)
				}
				else
				{
					if( path_first_request[1] == "signin")
					{
						signIn(message, DatabaseClient, TokenDBClient);
					}
						else
						{
							if (path_first_request[1] == "deleteAccount")
							{	
								std::string userId = request.at("id");
								auto resp = deleteAccount(userId, DatabaseClient);
								message.reply(status_codes::OK, resp);
							}
							else
							{
								if(path_first_request[1] == "signout")
								{
									std::string userId = request.at("id");
									auto resp = signOut(userId, this -> TokenDBClient);
									message.reply(status_codes::OK, resp);
								}
								`else
								{
									if(path_first_request[1] == "userUpdateInfo")
									{
										DataBaseClient.request(method::POST, message).
										then([message](http_response response)
										{
											message.reply(status_codes::OK, response);
										});
									}
									else
									{
										if(path_first_request[1] == "groupUpdateInfo")
										{
											DataBaseClient.request(method::POST, message).
												then([message](http_response response)
														{
														message.reply(status_codes::OK, response);
														});
										}
									}
								}
							}
						}
				}
				});
}
/*		
			try {
				UserInformation userInfo {
					request.at("email").as_string(),
						request.at("password").as_string(),
						request.at("name").as_string(),
						request.at("lastName").as_string()
				};
				UserManager users;
				users.signUp(userInfo);
				json::value response;
				response["message"] = json::value::string(
						"succesful registration!");
				message.reply(status_codes::OK, response);
			}
		catch(UserManagerException & e) {
			message.reply(status_codes::BadRequest, e.what());
		}
		catch(json::json_exception & e) {
			message.reply(status_codes::BadRequest);
		}
		});
}


void Account::handlePost(http_request message) {
//    message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
        auto path = requestPath(message);
        message.extract_json().
        then([=](json::value request) {
    if (request.at("action").as_string() == "registration") {
    pplx::task<void> registr([](json::value request)
		    {
		    	std::string mail = request.at("email").as_string();
			std::string login = request.at("login").as_string();
			std::string ml = "action/validation/email/" + mail + "/login/" + login + "/"; 
			uri_builder builder(U(ml));
		    }.then([=](json::value obj)
			    {
			    DataBaseClient.request(methods::GET, builder.to_string());
			    }).then([=](http_response response)
				    {
					auto path1 = requestPath(response);
					if (path1[1] == "Ok" && path1[3] == "Ok")
					{
						DataBaseClient.request(method::POST, request.as_string()).then([=](http_response resp)
								{})
					}
				    })
		    )

            try {
                UserInformation userInfo {
                    request.at("email").as_string(),
                    request.at("password").as_string(),
                    request.at("name").as_string(),
                    request.at("lastName").as_string()
                };
                UserManager users;
                users.signUp(userInfo);
                json::value response;
                response["message"] = json::value::string(
                                        "succesful registration!");
                message.reply(status_codes::OK, response);
            }
            catch(UserManagerException & e) {
                message.reply(status_codes::BadRequest, e.what());
            }
            catch(json::json_exception & e) {
                message.reply(status_codes::BadRequest);
            }
        });
    }

}

*/
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

