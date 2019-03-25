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
        DbServStatus = ServiceStart(DataBaseClient, "Database");
        if(DbServStatus){
      		tokDbServStatus = ServiceStart(TokenDBClient, "TokenDatabase");
	}
        if (tokDbServStatus)
        {
                this->setEndpoint(accountUri);
                status = true;
        }
	//this->setEndpoint(accountUri);
        //return true;
	return status;
}


	
static int temp = 0;
std::string getToken(){
	std::cout<<"getToken"<<std::endl;
	srand(time(NULL));
//	int temp = rand()% 100000000000;
	++temp;
	std::string token = std::to_string(temp);
	return token;
}

http_response getUserInfo(std::string userId, http_client* DataBaseClient){
	uri_builder uInfo("/account/getUserInfo?userId=" + userId);
	http_response userInfo = DataBaseClient->request(methods::GET, uInfo.to_string()).get();
	return userInfo;
}

http_response getUserShortInfo(http_request message, http_client* DataBaseClient){
	http_response userShortInfo = DataBaseClient->request(message).get();
	return userShortInfo;
}

std::string randUserFromGroup(std::string userId, std::string groupId, http_client* DataBaseClient){
	uri_builder usersInfo("/account/getGroupUsers?groupId=" + groupId);
	http_response users = DataBaseClient->request(methods::GET, usersInfo.to_string()).get();
	users.extract_json().
	then([=](json::value members)
	{
		if(members.at("status").as_string() == "INVALID_GROUP_ID")
		{
			std::string status = "INVALID_GROUP_ID";
			return status;
		}
		web::json::array groupMembers = members.at("members").as_array();
		std::string user;
		for (auto i = groupMembers.begin(); i != groupMembers.end(); i++)
		{
			std::string iterId = (*i).as_string();
			if(!(userId == iterId))
			{
				user = iterId;
				return user;	
			}
		}
	});
	std::string status = "NOT_FOUND_MEMBERS";
	return status; 
}

bool isUserInGroup(std::string userId, std::string groupId, http_client* DataBaseClient){
	uri_builder isUserGroup("/account/isUserInGroup?userId=" + userId + "&groupId" + groupId);
	http_response resp = DataBaseClient->request(methods::GET, isUserGroup.to_string()).get();
	resp.extract_json().
	then([=](json::value status)
	{
		if(status.at("status").as_string() == "IN_GROUP")
		{
			return true;
		}
		else
		{
			return false;
		}
	});
}

http_response getGroupShortInfo(std::string userId, std::string groupId, http_client* DataBaseClient){
	uri_builder gSInfo("/account/getGroupShortInfo?groupId=" + groupId);
	DataBaseClient->request(methods::GET, gSInfo.to_string()).
	then([=](http_response groupShortInfo)
	{
		groupShortInfo.extract_json().
		then([=](json::value groupShortInf)
		{
			if(groupShortInf.at("access").as_string() == "private")
			{
				if(isUserInGroup(userId, groupId, DataBaseClient))
				{
					return groupShortInfo;
				}
				else
				{
					http_response resp;
					json::value groupShortInfoResp;
					groupShortInfoResp["status"] = json::value::string("INVALID_GROUP_ID");//status@ poxel
					resp.set_body(groupShortInfoResp);
					return resp;
				}
			}
			else
			{
				return groupShortInfo;
			}
		});
	});
}

json::value getGroupInfo(std::string userId, std::string groupId, http_client* DataBaseClient){
	std::cout<<__LINE__<<std::endl;
	uri_builder gInfo("/account/getGroupInfo?groupId=" + groupId);
	http_response groupInfo = DataBaseClient->request(methods::GET, gInfo.to_string()).get();
	std::cout<<__LINE__<<std::endl;
	json::value grIn = groupInfo.extract_json().get();
	std::cout<<"group info   "<<grIn.to_string()<<std::endl;
	if(grIn.at("access").as_string() == "private")
	{
	std::cout<<__LINE__<<std::endl;
		if(isUserInGroup(userId, groupId, DataBaseClient))
		{
			std::cout<<__LINE__<<std::endl;
			groupInfo.set_body(grIn);
			std::cout<<__LINE__<<std::endl;
			return grIn;
		}
		else
		{
	std::cout<<__LINE__<<std::endl;
			json::value groupInfoResp;
			groupInfoResp["status"] = json::value::string("INVALID_GROUP_ID");
			return groupInfoResp;
		}
	}
	else
	{
		std::cout<<__LINE__<<std::endl;
		return grIn;
	}
}


http_response userDelete(std::string userId, http_client* DataBaseClient){
	uri_builder userDelete_path(U("/account/deleteUser?userId" + userId));
	return DataBaseClient->request(methods::GET, userDelete_path.to_string()).get();
}


http_response signOut(std::string userId, std::string token, http_client* TokenDb){
	uri_builder deleteToken("/deleteToken");
	json::value userIdInfo;
	userIdInfo["userId"] = json::value::string(userId);
	userIdInfo["token"] = json::value::string(token);
	return TokenDb->request(methods::POST, deleteToken.to_string(), userIdInfo).get();
}

http_response groupDelete(std::string userId, std::string groupId, http_client* DataBaseClient){
	json::value groupInf = getGroupInfo(userId, groupId, DataBaseClient);
		if(groupInf.at("adminId").as_string() == userId)
		{
			uri_builder groupDelete_path(U("/account/deleteGroup?groupId"+ groupId));
			return DataBaseClient->request(methods::GET , groupDelete_path.to_string()).get();
		}
		else
		{
			http_response resp;
			json::value res;
			res["status"] = json::value::string("INVALID_ADMIN_ID");
			resp.set_body(res);
			return resp;
		}
}
				 

http_response leaveGroup(http_request message,http_client* DataBaseClient)
{
	std::map<utility::string_t, utility::string_t>  infoMap = uri::split_query(message.request_uri().query());
		std::string userId = infoMap["userId"];
		std::string groupId = infoMap["groupId"];
		if(isUserInGroup(userId, groupId, DataBaseClient))
		{
			json::value UserInfo = getGroupInfo(userId, groupId, DataBaseClient);
				std::string adminId = UserInfo.at("adminId").as_string();
				if(userId == adminId)
				{	
					std::string newAdminId = randUserFromGroup(userId, groupId, DataBaseClient);
					if(newAdminId != "NOT_FOUND_MEMBERS")
					{ 
						uri_builder userDelete_path(U("/account/changeGroupAdmin?groupId"+groupId+"&clientId"+newAdminId));
						DataBaseClient->request(methods::GET, userDelete_path.to_string()).
						then([=](http_response status)
						{
							status.extract_json().
							then([=](json::value statusJson)
							{
								if(statusJson.at("status").as_string() == "OK")
								{
									uri_builder leaveGroup_path(U("/groupRemoveUser?clientId="+ userId + "&groupId="+groupId));
									DataBaseClient->request(methods::GET,  leaveGroup_path.to_string()).
									then([message](http_response leaveGroup_response)
									{
										return leaveGroup_response;
									});
								}
							});
						});
					}
					else
					{
						http_response groupDeleteResp = groupDelete(userId, groupId, DataBaseClient);
						return groupDeleteResp;
					}
				}
				else
				{
						uri_builder leaveGroup_path(U("/account/groupRemoveUser?clientId="+userId+"&groupId="+groupId));
						DataBaseClient->request(methods::GET,  leaveGroup_path.to_string()).
						then([message](http_response leaveGroup_response)
						{
							return leaveGroup_response;
						});
				}
		}
		else
		{
			http_response resp;
			resp.set_status_code(status_codes::OK);
			json::value info;
			info["status"] = json::value::string("INVALID_GROUP_ID");
			resp.set_body(info);
			return resp;
		}
}

http_response groupRemoveUser (http_request message, http_client* DataBaseClient)
{
	std::map<utility::string_t, utility::string_t>  infoMap = uri::split_query(message.request_uri().query());
                std::string userId = infoMap["userId"];
                std::string groupId = infoMap["groupId"];
                std::string clientId = infoMap["clientId"];
		json::value groupInfo = getGroupInfo(clientId ,groupId, DataBaseClient);
                        if(userId == groupInfo.at("adminId").as_string())
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
                                        uri_builder groupRemoveUser_path(U("/account/groupRemoveUser?clientId="+ clientId + "&groupId="+groupId));
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
                                        info["error"] = json::value::string("INVAILD_ADMIN_ID");
                                        resp.set_body(info);
                                        return resp;
                        }
}

void Account::handleGet(http_request message) {
	//std::cout<<message.to_string()<<std::endl;
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
		else if(path_first_request[1] == "getUserShortInfo")
			{
				auto userShortInfo = getUserShortInfo(message, this -> DataBaseClient);
				message.reply(userShortInfo);
			}
		else if(path_first_request[1] == "getGroupInfo")
		{
			std::string userId = i.find("userId")->second;
			std::string groupId = i.find("groupId")->second;
			if(!(groupId == ""))
			{
			std::cout<<__LINE__<<std::endl;
			json::value response = getGroupInfo(userId,groupId, DataBaseClient);
			std::cout<<__LINE__<<std::endl;
			std::cout<<"uxarkeluc araj  "<<response<<std::endl;
				message.reply(status_codes::OK, response);
			}
			else
			{
				message.reply(status_codes::NotFound);
			}
		}
		else if (path_first_request[1] == "deleteUser")
		{	
			std::string userId = i.find("userId")->second;
			message.reply(userDelete(userId, this->DataBaseClient));
		}
		else if(path_first_request[1] == "signOut")
		{
			std::string userId = i.find("userId")->second;
			std::string token = message.headers()["token"];
			http_response resp = signOut(userId, token, this->TokenDBClient);
			message.reply(resp);
		}
		else if(path_first_request[1] == "getGroupShortInfo")
		{
			std::string userId = "";
			std::string groupId = "";
			userId = i.find("userId")->second;
			groupId = i.find("groupId")->second;
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
		else if(path_first_request[1] == "deleteGroup")
		{
			std::string userId = "";
			std::string groupId = "";
			userId = i["userId"];
			groupId = i["groupId"];
			if(!(groupId == ""))
			{
				auto deleteGroupInfo = groupDelete(userId,groupId, this->DataBaseClient);
				message.reply(deleteGroupInfo);
			}
		}
		else if(path_first_request[1] == "groupRemoveUser")
		{
			auto resp = groupRemoveUser(message, this -> DataBaseClient);
			message.reply(resp);
		}
		else if(path_first_request[1] == "leaveGroup")
		{
			auto resp = leaveGroup(message, this -> DataBaseClient);
			message.reply(resp);
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

void registration(http_request message , http_client* DataBaseClient, http_client* TokenDBClient) {
	message.extract_json().then([=](json::value info)
	{
        std::string ml = "/account/mailAndLogin"; 
        json::value login_mail;
        login_mail["email"] = json::value::string(info.at("email").as_string());
        login_mail["login"] = json::value::string(info.at("login").as_string());
        uri_builder get_mail_login(U(ml));
        uri_builder r(U("/account/signUp"));
        DataBaseClient->request(methods::POST, get_mail_login.to_string(), login_mail).
		then([=](http_response mail_login)
		{
			mail_login.extract_json().
			then([=](json::value mail_login_json)
			{
				if(mail_login_json.at("emailStatus").as_string() == "NOT_USING" && mail_login_json.at("loginStatus").as_string() == "NOT_USING")
				{
					DataBaseClient->request(methods::POST, r.to_string(), info).
					then([=](http_response registration_response)
					{
						registration_response.extract_json().
						then([=](json::value regInfo)
						{
							if("OK" == regInfo.at("status").as_string())
							{
								std::string token = getToken();
								uri_builder token_uri("/setToken/");
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
					if("ALREADY_TAKEN" ==  mail_login_json.at("emailStatus").as_string())
					{
						error["emailStatus"] = json::value::string(U("INVALID_EMAIL"));
					}
					if("ALREADY_TAKEN" ==  mail_login_json.at("loginStatus").as_string())
					{
						error["loginStatus"] = json::value::string(U("INVALID_LOGIN"));
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
	uri_builder signin_path(U("/account/signIn/"));
	signinInfo["login"] = request.at("login");
	signinInfo["password"] = request.at("password");
	DataBaseClient->request(methods::POST,  signin_path.to_string(), signinInfo).
	then([=](http_response signinStatus)
	{
		signinStatus.extract_json().
		then([=](json::value signinStatus_json)
		{
			if (signinStatus_json["status"] == json::value::string("INVALID_LOGIN"))
			{
				message.reply(status_codes::OK, json::value::string("INVALID_LOGIN"));
			}
			else
			{
				if(signinStatus_json["status"] == json::value::string("INVALID_PASSWORD"))
				{
					int attempt = std::stoi(signinStatus_json["attempt"].as_string());
					if(max_attempt > attempt)
					{
						if((max_attempt - attempt) == 1)
						{
							message.reply(status_codes::OK, json::value::string("LOGIN_LAST_ATTEMPT"));
						}
						else
						{
							message.reply(status_codes::OK, json::value::string("INVALID_LOGIN"));
						}
					}
					else
					{
						message.reply(status_codes::OK, json::value::string("USER_BLOCKED"));
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
							http_response res = getUserInfo(id, DataBaseClient);
							res.extract_json().
							then([=](json::value userInf)
							{
								json::value userInfo = userInf;
								std::string token = getToken();
								uri_builder token_uri("/setToken");
								json::value token_json;
								token_json["token"] = json::value::string(token);
								token_json["userId"] = json::value::string(id);
								http_response token_resp = TokenDBClient -> request(methods::POST, token_uri.to_string(), token_json).get();
								json::value tok_res = token_resp.extract_json().get();
								if(tok_res["status"] == json::value::string("OK"))
								{
									userInfo["token"] = json::value::string(token);
									message.reply(status_codes::OK, userInfo);
								}
								else
								{message.reply(status_codes::OK, json::value::string("TokenDb dead"));}
							});
						}
						else
						{
							message.reply(status_codes::OK, json::value::string("USER_BLOCKED"));
						}
					}
				}
			}
		});
	});
	});
}

http_response createGroup(http_request message, http_client* DataBaseClient)
{
	return DataBaseClient->request(message).get();
}

void Account::handlePost(http_request message) {
	std::cout<<message.to_string()<<std::endl;
	auto path_first_request = requestPath(message);
	if ( path_first_request[1] == "signUp") 
	{
		registration(message, this -> DataBaseClient, this -> TokenDBClient);
	}
	else if( path_first_request[1] == "signIn")
		{
			signIn(message, DataBaseClient, TokenDBClient);
		}
		else if(path_first_request[1] == "userUpdateInfo")
			{
			DataBaseClient->request(message).then([message](http_response response){
						message.reply(response);
				});
			}
			else if(path_first_request[1] == "groupUpdateInfo")
				{
					http_response response = this->DataBaseClient->request(message).get();
						message.reply(response);
				}
				else if(path_first_request[1] == "createGroup")
						{
							message.reply(createGroup(message, DataBaseClient));
						}
						else
						{
								message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
						}
}
