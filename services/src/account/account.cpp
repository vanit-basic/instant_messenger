#include <account/account.hpp>
#include <base/std_micro_service.hpp>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


static int max_attempt = 5;
bool Account::createClients(std::string path)
{
        std::ifstream ConfigFile(path);
        json::value config;
        if (ConfigFile.is_open()) {
                ConfigFile>> config;
                ConfigFile.close();
                DataBaseClient = new http_client(config.at("DbService").as_string());
                TokenDBClient = new http_client(config.at("tokenDb").as_string());
                this->accountUri = config.at("account").as_string();
                return true;
        }
        else {
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
                return false;
        }
}

Account::Account(std::string path)
{
        this->createClients(path);
}

bool checkToken(http_request message, http_client* TokenDB){
	TokenDB->request(message).
        then([=](http_response tokenStatus)
	{
		tokenStatus.extract_json().
		then([=](json::value token)
		{
                      	if(token.at("token").as_string() == "valid")
                        {
				return true;
			}
			else
			{
				return false;
			}
		});
	});	
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
			requestTask.then([](http_response resp){std::cout<<resp.to_string()<<std::endl;});
                        requestTask.wait();
                } catch (http_exception e) {
                        error = e.error_code();
                }}
        while (error.value());
        return true;
}

bool Account::checkServices()
{
/*	qani der patrast chen DbServicner@ toxnel vorpes comment

        bool status = false;
        bool DbServStatus = false;
        bool tokDbServStatus = false;
        DbServStatus = ServiceStart(DataBaseClient, "Account Database");
        if(DbServStatus){
                tokDbServStatus = ServiceStart(TokenDBClient, "TokenDatabase");}
        if (tokDbServStatus)
        {
                this->setEndpoint(accountUri);
                status = true;
        }
        return status;*/

                this->setEndpoint(accountUri);
		return true;
}


void Account::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&Account::handleGet, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&Account::handlePost, this, std::placeholders::_1));
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
	DataBaseClient->request(methods::GET, uInfo.to_string()).
		then([=](http_response userInfo ) 
			{
				return userInfo;
			});
}

http_response getUserShortInfo(std::string userId, http_client* DataBaseClient){
	uri_builder uInfo("/getUserShortInfo/" + userId + "/");
	DataBaseClient->request(methods::GET, uInfo.to_string()).
	then([=](http_response userShortInfo) 
			{
				return userShortInfo;
			});
}

http_response getGroupUsers(std::string userId, std::string groupId, http_client* DataBaseClient){
	uri_builder gInfo("/getGroupUsers/" + groupId + "/");
	DataBaseClient->request(methods::GET, gInfo.to_string()).
		then([=](http_response groupUsers) 
			{
				return groupUsers;
			});
}

http_response getGroupInfo(std::string userId, std::string groupId, http_client* DataBaseClient){
	uri_builder gInfo("/getGroupInfo/" + groupId + "/");
	DataBaseClient->request(methods::GET, gInfo.to_string()).
	then([=](http_response groupInfo)
	{
		groupInfo.extract_json().
		then([=](json::value groupInf)
		{
			if(groupInf.at("acces").as_string() == "private")
			{
				auto groupUsers = getGroupUsers(userId, groupId, DataBaseClient);
				groupUsers.extract_json().
				then([=](json::value groupUsersResp)
				{
					if(!(groupUsersResp.at(userId).is_null()))
					{
						return groupInfo;
					}
					else
					{
						http_response resp;
						json::value groupInfoResp;
						groupInfoResp["status"] = json::value::string("Not Found");
						resp.set_body(groupInfoResp);
						return resp;
					}
				});
			}
			else
			{
				return groupInfo;
			}
		});
	});
}


http_response userDelete(std::string userId, http_client* DataBaseClient){
	json::value userDeleteInfo;
	uri_builder userDelete_path(U("/userDelete/"));
	userDeleteInfo["id"] = json::value::string(userId);
	DataBaseClient->request(methods::POST, userDelete_path.to_string(), userDeleteInfo).
	then([=](http_response status){
		return status;
	});
}


http_response signOut(std::string userId, http_client* TokenDb){
	uri_builder deleteToken("/deleteToken/");
	json::value userIdInfo;
	userIdInfo["id"] = json::value::string(userId);
	TokenDb->request(methods::POST, deleteToken.to_string(), userIdInfo).
	then([=](http_response status)
	{
		return status;		
	});
}

				 


void Account::handleGet(http_request message) {
	std::cout<< message.to_string()<<std::endl;
	auto path_first_request = requestPath(message);
	if (!(path_first_request.empty())) {
		if (path_first_request[0] == "ServiceTest")
		{
			uri_builder builder("/AccountStart");
			message.reply(status_codes::OK, builder.to_string());
		}
		else if(path_first_request[1] == "getUserInfo")
		{
			std::string userId = path_first_request[3];
			auto userInfo = getUserInfo(userId, this -> DataBaseClient);
			message.reply(userInfo);
		}
		else
		{
			if(path_first_request[1] == "getUserShortInfo")
			{
				std::string userId = path_first_request[3];
				auto userShortInfo = getUserShortInfo(userId, this -> DataBaseClient);
				message.reply(userShortInfo);
			}
			else
			{
				if(path_first_request[1] == "groupInfo")
				{
					std::string userId = path_first_request[2];
					std::string groupId = path_first_request[3];
					auto groupInfo = getGroupInfo(userId,groupId, this->DataBaseClient);
					message.reply(groupInfo);
				}
				else
				{
					if(path_first_request[1] == "groupUsers")
					{
						std::string userId  = path_first_request[2];
						std::string groupId = path_first_request[3];
						auto groupUsers = getGroupUsers(userId, groupId, this -> DataBaseClient);
						message.reply(groupUsers);
					}
					else
					{
						if (path_first_request[1] == "userDelete")
						{	
							std::string userId = path_first_request[2];
							auto resp = userDelete(userId, this->DataBaseClient);
							message.reply(resp);
						}
						else
						{
							if(path_first_request[1] == "signOut")
							{
								std::string userId = path_first_request[2];
								auto resp = signOut(userId, this->TokenDBClient);
								message.reply(resp);
							}
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

void registration(http_request message , http_client* DataBaseClient){
        message.extract_json().then([=](json::value info)
	{
        std::string ml = "/get/mail_login"; 
        json::value login_mail;
        login_mail["email"] = json::value::string(info.at("email").as_string());
        login_mail["login"] = json::value::string(info.at("login").as_string());
        uri_builder get_mail_login(U(ml));
        DataBaseClient->request(methods::POST, get_mail_login.to_string(), login_mail).

		then([=](http_response mail_login)
		{
			mail_login.extract_json().
			then([=](json::value mail_login_json)
			{
				if(!(mail_login_json["email"] ==  info.at("email") && mail_login_json["login"] == info.at("login")))
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
					if(mail_login_json["email"] ==  info.at("email"))
					{
						error["email"] = json::value::string(U("Invalid"));
					}
					if(mail_login_json["login"] ==  info.at("login"))
					{
						error["login"] = json::value::string(U("Invalid"));
					}
						message.reply(status_codes::OK, error);
				}		
			});
		});
	});
}

void signIn(http_request message, http_client* DataBaseClient, http_client* TokenDBClient){ 
	message.extract_json().then([=](json::value request){
	json::value signinInfo;
	uri_builder signin_path(U("/signin/"));
	signinInfo["login"] = request.at("login");
	signinInfo["password"] = request.at("password");
	DataBaseClient->request(methods::POST,  signin_path.to_string(), signinInfo).
	then([=](http_response signinStatus)
	{
		signinStatus.extract_json().
		then([=](json::value signinStatus_json)
		{
			if (signinStatus_json["status"] == json::value::string("notFound"))
			{
				message.reply(status_codes::OK, json::value::string("Login or Password is Wrong!!!"));
			}
			else
			{
				if(signinStatus_json["status"] == json::value::string("wrong"))
				{
					int attempt = std::stoi(signinStatus_json["attempt"].as_string());
					if(max_attempt > attempt)
					{
						if((max_attempt - attempt) == 1)
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
					if(signinStatus_json["status"] == json::value::string("OK"))
					{
						std::string id = signinStatus_json["id"].as_string();
						http_response res = getUserInfo(id, DataBaseClient);
						res.extract_json().then([=](json::value userInf){
						json::value userInfo = userInf;
						std::string token = setToken();
						uri_builder token_uri("/SetToken/");
						json::value token_json;
						token_json["token"] = json::value::string(token);
						token_json["id"] = json::value::string(id);
						TokenDBClient -> request(methods::POST, token_uri.to_string(), token_json).
						then([message, &userInfo, id, token](http_response token_response)
						{
							userInfo["id"] = json::value::string(id);
							userInfo["token"] = json::value::string(token);
							message.reply(status_codes::OK, userInfo);
						});
						});
					}
				}
			}
		});
	});
	});
}
http_response groupRemoveUser (http_request message, http_client* DataBaseClient)
{ 
	message.extract_json().
	then([=](json::value reqInfo) 
	{
		std::string adminId = reqInfo.at("adminId").as_string(); 
		std::string groupId = reqInfo.at("groupId").as_string(); 
		std::string userId = reqInfo.at("userId").as_string(); 
		auto gInfo = getGroupInfo(adminId ,groupId, DataBaseClient);
		gInfo.extract_json().
		then([=](json::value groupInfo) 
		{        
			if(adminId == groupInfo.at("adminId").as_string()) 
			{        
				if(adminId == userId){
					
					http_response resp;
					resp.set_status_code(status_codes::OK);
					json::value info;
					info["error"] = json::value::string("change admin");
					resp.set_body(info);
					return resp;	
				}
				else
				{
					uri_builder groupRemoveUser_path(U("/groupRemoveUser/"+ adminId + "/"+groupId+"/"+userId+"/")); 
					DataBaseClient->request(methods::GET,  groupRemoveUser_path.to_string()). 
					then([message](http_response userRemove_response) 
					{ 
					return userRemove_response; 
					});
				}	
			}
	       		else
			{
				if(adminId == userId)
				{
					uri_builder groupRemoveUser_path(U("/groupRemoveUser/"+ adminId + "/"+groupId+"/"+userId+"/")); 
					DataBaseClient->request(methods::GET,  groupRemoveUser_path.to_string()). 
					then([message](http_response userRemove_response) 
					{ 
					return userRemove_response; 
					});
				}
				else{
					http_response resp;
					resp.set_status_code(status_codes::OK);
					json::value info;
					info["error"] = json::value::string("you are not admin");
					resp.set_body(info);
					return resp;	
				}
			}	
	});
	});	
} 

http_response createGroup(http_request message, http_client* DataBaseClient)
{
		DataBaseClient->request(message). 
		then([message](http_response createGroup_response) 
		{ 
			return createGroup_response; 
		}); 
}

void Account::handlePost(http_request message) {
auto path_first_request = requestPath(message);
message.extract_json().
then([=](json::value request) 
	{
		if ( path_first_request[1] == "registration") 
		{
			registration(message, this -> DataBaseClient);
		}
		else
		{
			if( path_first_request[1] == "signin")
			{
				signIn(message, DataBaseClient, TokenDBClient);
			}
			else
			{
				if(path_first_request[1] == "userUpdateInfo")
				{
					this->DataBaseClient->request(message).
					then([message](http_response response)
					{
					message.reply(response);
					});
				}
				else
				{
					if(path_first_request[1] == "groupUpdateInfo")
					{
						this->DataBaseClient->request(message).
						then([message](http_response response)
						{
						message.reply(response);
						});
					}
					else
					{
						if(path_first_request[1] == "removeFromGroup")
						{
							auto resp = signOut(request.at("id").as_string(), this -> TokenDBClient);
							message.reply(resp);
						}
						else 
						{
							if(path_first_request[1] == "createGroup")
							{
								auto resp = createGroup(message, this -> DataBaseClient);
								message.reply(resp);
							}
							else
							{
    								message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
							}
						}
					}
				}
			}
		}
	});
}
