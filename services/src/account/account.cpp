#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <map>
#include <iterator>

#include <network_utils.hpp>
#include <base/std_micro_service.hpp>

#include <account/account.hpp>

static int max_attempt = 5;

void Account::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&Account::handleGet, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&Account::handlePost, this, std::placeholders::_1));
}


bool Account::createClients(std::string path)
{
        std::ifstream ConfigFile(path);
        json::value config;
        if (ConfigFile.is_open()) {
                ConfigFile>> config;
                ConfigFile.close();
                DataBaseClient = new http_client(NetworkUtils::hostURI(config.at("dbservice").as_string()));
                TokenDBClient = new http_client(NetworkUtils::hostURI(config.at("tokendbservice").as_string()));
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
/*
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
}*/

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
			std::cout<<e.what()<<std::endl;
                }}
        while (error.value());
        return true;
}

bool Account::checkServices()
{
//	qani der patrast chen DbServicner@ toxnel vorpes comment

        bool status = false;
        bool DbServStatus = false;
        bool tokDbServStatus = false;
/*        DbServStatus = ServiceStart(DataBaseClient, "Database");
        if(DbServStatus){
                this->setEndpoint(accountUri);
		status = true;}
      {          tokDbServStatus = ServiceStart(TokenDBClient, "TokenDatabase");
        if (tokDbServStatus)
        {
                this->setEndpoint(accountUri);
                status = true;
        }*/
	this->setEndpoint(accountUri);
        return true;
}



std::string getToken(){
	
	srand(time(NULL));
        int temp = rand()% 100000000000;
        std::string token = std::to_string(temp);
	return token;
}

http_response getUserInfo(std::string userId, http_client* DataBaseClient){
	uri_builder uInfo("/getUserInfo?userId=" + userId);
	http_response userInfo = DataBaseClient->request(methods::GET, uInfo.to_string()).get();
	return userInfo;
}

http_response getUserShortInfo(std::string userId, http_client* DataBaseClient){
	uri_builder uInfo("/getUserShortInfo?userId=" + userId);
	http_response userShortInfo = DataBaseClient->request(methods::GET, uInfo.to_string()).get();
	return userShortInfo;
}

http_response getGroupUsers(std::string groupId, http_client* DataBaseClient){
	uri_builder gInfo("/getGroupUsers?groupId=" + groupId);
	http_response groupUsers = DataBaseClient->request(methods::GET, gInfo.to_string()).get();
	return groupUsers;
}

http_response getGroupShortInfo(std::string userId, std::string groupId, http_client* DataBaseClient){
	uri_builder gSInfo("/getGroupShortInfo?groupId=" + groupId);
	DataBaseClient->request(methods::GET, gSInfo.to_string()).
	then([=](http_response groupShortInfo)
	{
		groupShortInfo.extract_json().
		then([=](json::value groupShortInf)
		{
			if(groupShortInf.at("access").as_string() == "private")
			{
				auto groupUsers = getGroupUsers(groupId, DataBaseClient);
				groupUsers.extract_json().
				then([=](json::value groupUsersResp)
				{
					if(!(groupUsersResp.at(userId).is_null()))//poxel
					{
						return groupShortInfo;
					}
					else
					{
						http_response resp;
						json::value groupShortInfoResp;
						groupShortInfoResp["status"] = json::value::string("Not Found");//status@ poxel
						resp.set_body(groupShortInfoResp);
						return resp;
					}
				});
			}
			else
			{
				return groupShortInfo;
			}
		});
	});
}
bool validUsers(std::string userId ,std::string members ){

	while(members != ""){
		int pos = members.find(',');
		std::string clientId = members.substr(0,pos);
		if(userId == clientId){
			 return true;
		}
		members = members.erase(0,pos-1);
	}
	return false;
}
http_response getGroupInfo(std::string userId, std::string groupId, http_client* DataBaseClient){
	uri_builder gInfo("/getGroupInfo?groupId=" + groupId);
	DataBaseClient->request(methods::GET, gInfo.to_string()).
	then([=](http_response groupInfo)
	{
		groupInfo.extract_json().
		then([=](json::value groupInf)
		{
			if(groupInf.at("access").as_string() == "private")
			{
				auto groupUsers = getGroupUsers(groupId, DataBaseClient);
				groupUsers.extract_json().
				then([=](json::value groupUsersResp)
				{
					if(validUsers)
					{
						return groupInfo;
					}
					else
					{
						http_response resp;
						json::value groupInfoResp;
						groupInfoResp["status"] = json::value::string("Not Found");//status@ poxel
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
	uri_builder userDelete_path(U("/userDelete"));
	userDeleteInfo["userId"] = json::value::string(userId);
	DataBaseClient->request(methods::POST, userDelete_path.to_string(), userDeleteInfo).
	then([=](http_response status){
		return status;
	});
}


http_response signOut(std::string userId, http_client* TokenDb){
	uri_builder deleteToken("/deleteToken");
	json::value userIdInfo;
	userIdInfo["userId"] = json::value::string(userId);
	TokenDb->request(methods::POST, deleteToken.to_string(), userIdInfo).
	then([=](http_response status)
	{
		return status;		
	});
}

				 


void Account::handleGet(http_request message) {
		std::cout<<"message  " << message.headers().operator[]("token")<<std::endl;
	std::map<utility::string_t, utility::string_t>  i = uri::split_query(message.request_uri().query());
	std::map<std::string, std::string>::iterator it;

	auto path_first_request = requestPath(message);
	if (!(path_first_request.empty())) 
	{
		if (path_first_request[0] == "ServiceTest")
		{
			message.reply(status_codes::OK, "Account_Start");
		}
		else if(path_first_request[1] == "getUserInfo")
		{
			std::string userId = "";
			userId = i.find("userId")->second;
			if(!(userId == ""))
			{
				auto userInfo = getUserInfo(userId, this -> DataBaseClient);
				message.reply(userInfo);
			}
			else
			{
				message.reply(status_codes::NotFound);
			}
		}
		else
		{
			if(path_first_request[1] == "getUserShortInfo")
			{
				std::string userId = "";
				userId = i.find("userId")->second;
				if(!(userId == ""))
				{
					auto userShortInfo = getUserShortInfo(userId, this -> DataBaseClient);
					message.reply(userShortInfo);
				}
				else
				{
					message.reply(status_codes::NotFound);
				}
			}
			else
			{
				if(path_first_request[1] == "getGroupInfo")
				{
					std::string userId = "";
					std::string groupId = "";
					userId = i.find("userId")->second;
					groupId = i.find("groupId")->second;
					if(!(userId == ""))
					{
						if(!(groupId == ""))
						{
							auto groupInfo = getGroupInfo(userId,groupId, this->DataBaseClient);
							message.reply(groupInfo);
						}
						else
						{
							message.reply(status_codes::NotFound);
						}
					}
					else
					{
						message.reply(status_codes::NotFound);
					}
				}
				else
				{
					if (path_first_request[1] == "userDelete")
					{	
						std::string userId = "";
						userId = i.find("userId")->second;
						if(!(userId == ""))
						{
							auto resp = userDelete(userId, this->DataBaseClient);
							message.reply(resp);
							}
						else
						{
							message.reply(status_codes::NotFound);
						}
					}
					else
					{
						if(path_first_request[1] == "signOut")
						{
							std::string userId = "";
							userId = i.find("userId")->second;
							if(!(userId == ""))
							{
								auto resp = signOut(userId, this->TokenDBClient);
								message.reply(resp);
							}
							else
							{
								message.reply(status_codes::NotFound);
							}
						}
						else
						{
							if(path_first_request[1] == "getGroupShortInfo")
							{
								std::string userId = "";
								std::string groupId = "";
								userId = i.find("userId")->second;
								groupId = i.find("groupId")->second;
								if(!(userId == ""))
								{
									if(!(groupId == ""))
									{
										auto groupShortInfo = getGroupShortInfo(userId,groupId, this->DataBaseClient);
										message.reply(groupShortInfo);
									}
									else
									{
										message.reply(status_codes::NotFound);
									}
								}
								else
								{
									message.reply(status_codes::NotFound);
								}
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

void registration(http_request message , http_client* DataBaseClient, http_client* TokenDBClient){
        message.extract_json().then([=](json::value info)
	{
        std::string ml = "/check/mailAndLogin"; 
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
				if(mail_login_json.at("mailStatus").as_string() == "notUsing" && mail_login_json.at("loginStatus").as_string() == "notUsing")
				{
					uri_builder reg_path(U("/insert"));
					DataBaseClient->request(methods::POST,  reg_path.to_string(), info).
					then([=](http_response registration_response)
					{
						registration_response.extract_json().
						then([=](json::value regInfo)
						{
							if("SUCCESSFULLY_REGISTERED" == regInfo.at("status").as_string())
							{
								std::string token = setToken();
								uri_builder token_uri("/SetToken/");
								json::value token_json;
								token_json["token"] = json::value::string(token);
								token_json["userId"] = json::value::string(regInfo.at("userId").as_string());
								TokenDBClient -> request(methods::POST, token_uri.to_string(), token_json).
								then([=](http_response token_response)
								{
									token_response.extract_json().
									then([=](json::value tokenInfo)
									{
										if("OK" == tokenInfo.at("status").as_string())
										{
											json::value resp = regInfo;
											resp["token"] = json::value::string(token);		
											message.reply(status_codes::OK, resp);		
										}
									});
								});
							}
						});
					});
				}
				else
				{
					json::value error;
					if("alreadyTaken" ==  mail_login_json.at("mailStatus").as_string())
					{
						error["email"] = json::value::string(U("Invalid"));
					}
					if("alreadyTaken" ==  mail_login_json.at("loginStatus").as_string())
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
						int attempt = std::stoi(signinStatus_json["attempt"].as_string());
						if(max_attempt > attempt)
						{
							std::string id = signinStatus_json["userId"].as_string();
							http_response res = getUserInfo(id, DataBaseClient);//hanel
							res.extract_json().
							then([=](json::value userInf)
							{
								json::value userInfo = userInf;
								std::string token = setToken();
								uri_builder token_uri("/SetToken/");
								json::value token_json;
								token_json["token"] = json::value::string(token);
								token_json["id"] = json::value::string(id);
								TokenDBClient -> request(methods::POST, token_uri.to_string(), token_json).
								then([message, &userInfo, id, token](http_response token_response)
								{
									userInfo["token"] = json::value::string(token);
									message.reply(status_codes::OK, userInfo);
								});
							});
						}
						else
						{
							message.reply(status_codes::OK, json::value::string("Attempt failed!!!"));
						}
					}
				}
			}
		});
	});
	});
}

http_response leaveGroup(http_request message,http_client* DataBaseClient)
{
	message.extract_json().
	then([=](json::value leaveInfo)
	{
		std::string userId = leaveInfo.at("userId").as_string();
		std::string groupId = leaveInfo.at("groupId").as_string();
		auto groupUserInfo = getGroupUsers(groupId,DataBaseClient);
		groupUserInfo.extract_json().
		then([=](json::value UserInfo)
		{
			std::string adminId = UserInfo.at("adminId").as_string();
			if(userId == adminId)
			{
				http_response resp;
				resp.set_status_code(status_codes::OK);
				json::value info;
				info["error"] = json::value::string("change admin");
				resp.set_body(info);
				return resp;
			}
			else
			{
				std::string quantity = UserInfo.at("usersQuantity").as_string();
				int temp = std::stoi(quantity);
				std::string members[temp];
				int j =temp;
				for(int temp = 0 ; temp < j ; j++ )
				{
					members[temp] = UserInfo.at("members").as_string();
					if(userId == members[temp])
					{
						uri_builder leaveGroup_path(U("/leaveGroup?userId="+userId+"&groupId="+groupId));
						DataBaseClient->request(methods::GET,  leaveGroup_path.to_string()).
						then([message](http_response leaveGroup_response)
						{
							return leaveGroup_response;
						});
						}
				}
				http_response resp;
				resp.set_status_code(status_codes::OK);
				json::value info;
				info["status"] = json::value::string("GROUP_NOT_FOUND");
				resp.set_body(info);
				return resp;
			}
		});
	});
}

http_response groupRemoveUser (http_request message, http_client* DataBaseClient)
{
        message.extract_json().
        then([=](json::value reqInfo)
        {
                std::string userId = reqInfo.at("userId").as_string();
                std::string groupId = reqInfo.at("groupId").as_string();
                std::string clientId = reqInfo.at("clientId").as_string();
                auto gInfo = getGroupInfo(clientId ,groupId, DataBaseClient);
                gInfo.extract_json().
                then([=](json::value groupInfo)
                {
                        if(userId == groupInfo.at("").as_string())
                        {
                                if(clientId == userId){

                                        http_response resp;
                                        resp.set_status_code(status_codes::OK);
                                        json::value info;
                                        info["error"] = json::value::string("change admin");
                                        resp.set_body(info);
                                        return resp;
                                }
                                else
                                {
                                        uri_builder groupRemoveUser_path(U("/groupRemoveUser?userId="+ userId + "&groupId="+groupId+"&clientId" + clientId));
                                        DataBaseClient->request(methods::GET,  groupRemoveUser_path.to_string()).
                                        then([message](http_response userRemove_response)
                                        {
                                        return userRemove_response;
                                        });
                                }
                        }
                        else
                        {
                                        http_response resp;
                                        resp.set_status_code(status_codes::OK);
                                        json::value info;
                                        info["error"] = json::value::string("you are not admin");
                                        resp.set_body(info);
                                        return resp;
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
	if ( path_first_request[1] == "registration") 
	{
		registration(message, this -> DataBaseClient, this -> TokenDBClient);
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
					if(path_first_request[1] == "groupRemoveUser")
					{
						auto resp = groupRemoveUser(message, this -> TokenDBClient);
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
							if(path_first_request[1] == "leaveGroup")
							{
								auto resp = leaveGroup(message, this -> TokenDBClient);
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
	}
}
