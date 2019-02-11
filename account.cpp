#include "microsvc_controller.hpp"

using namespace web;
using namespace http;

void MicroserviceController::initRestOpHandlers() {
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

void Account::handleGet(http_request message) {
	std::cout<< message.to_string()<<std::endl;
	auto path = requestPath(message);
	if (!path.empty()) {
		if(path_first_request[1] == "UserInfo")
		{
			std::string userId = path[2].to_string();
			uri_builder uInfo("/getUserInfo/" + userId + "/");
			DataBaseClient.request(method::GET, uInfo.to_string()).
				then([message](http_response userInfo)
						{
						message.reply(status_codes::OK, userInfo);
						});
		}
		else
		{
			if(path_first_request[1] == "UserShortInfo")
			{
				std::string userId = path[2].to_string();
				uri_builder uInfo("/getUserShortInfo/" + userId + "/");
				DataBaseClient.request(method::GET, uInfo.to_string()).
					then([message](http_response userInfo)
							{
							message.reply(status_codes::OK, userInfo);
							});
			}
		}
	}
	else
	{
		message.reply(status_codes::NotFound);
	}
}
void Account::handlePost(http_request message) {
	//    message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
	auto path_first_request = requestPath(message);
	message.extract_json().
		then([message](json::value request) 
				{
				if ( path_first_request[1] == "registration") 
				{
				std::string mail = request.at("email").as_string();
				std::string login = request.at("login").as_string();
				std::string ml = "/get/email/" + mail,"/login/" + login + "/"; 
				uri_builder get_mail_login(U(ml));
				DataBaseClient.request(methods::GET, get_mail_login.to_string()).

				then([message, request](http_response mail_login)
						{
						//auto path = requestPath(mail_login);
						mail_login.extract_json().
						then([message, request](json::value mail_login_json)
								{
								if(!(mail_login_json["email"] ==  request.at("email").as_string() && mail_login_json["login"] == request.at("login").as_string()))
								{
								uri_builder registration_path(U("/registration/"));
								DataBaseClient.request(method::POST,  registration_path.to_string(), request).

								then([message](http_response registration_response)
										{
										message.reply(status_codes::OK, registration_response);
										}
										}
										else
										{
										json::value error;
										if(mail_login_json["email"] ==  request.at("email").as_string())
										{
										error["email"] = json::value::string(U("Invalid"));
										}
										if(mail_login_json["login"] ==  request.at("login").as_string())
										{
										error["login"] = json::value::string(U("Invalid"));
										}
										message.reply(status_codes::OK, error);
										});
								});
						});
				}
				else
				{
					if( path_first_request[1] == "signin")
					{
						json::value signinInfo;
						uri_builder signin_path(U("/signin/"));
						singinInfo["login"] = request.at("login");
						singinInfo["password"] = request.at("password");
						DataBaseClient.request(method::POST,  signin_path.to_string(), signinInfo).
						then([message](http_response signinStatus)
						{
							signinStatus.extract_json().
							then([message, request](json::value signinStatus_json)
							{
								
								switch (signinStatus[ "status" ]) {
									case "notFound" : 
										message.reply(status_codes::OK, json::value::string("Login or Password is Wrong!!!"));
										break;
									case "wrong" : 
										int attempt = std::stoi(signinStatus_json["attempt"].as_string());
										switch (this->max_attemp - attemp) {
											case 1:
												message.reply(status_codes::OK, json::value::string("Attention!!! You have one attempt left!!!"));
												break;
											case 0:
												message.reply(status_codes::OK, json::value::string("Attempt failed!!!"));
												break;
											default:
												message.reply(status_codes::OK, json::value::string("Login or Password is Wrong!!!"));
												break;
										}
									case "OK" :  
											std::string id = signinStatus_json["id"].as_string();
											json::value userInfo = getUserInfo(id);
											std::string token = setToken();
											uri_builder token_uri("/SetToken/");
											json::value token_json;
											token_json["token"] = json::value::string(token);
											token_json["id"] = json::value::string(id);
											TokenDB.request(methods::POST, token_uri.to_string(), token_json).
											then([message, token_json, userInfo](http_response token_response)
											{
												userInfo["id"] = token_json["id"];
												userInfo["token"] = token_json["token"];
												message.reply(status_codes::OK, userInfo);
											});
											break;
								}
								
								/*if (signinStatus_json["status"] == "notFound")
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
											if(((this->max_attempt) - attempt) ==1)
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
											json::value userInfo = getUserInfo(id);	//petq e kanchenq getUserInfo() funkcian u user infon stanaluc heto  token generacnenq
											std::string token = setToken();//funkcia vor@ petqe token generacni
											uri_builder token_uri("/SetToken/");
											json::value token_json;
											token_json["token"] = json::value::string(token);
											token_json["id"] = json::value::string(id);
											TokenDB.request(methods::POST, token_uri.to_string(), token_json).
											then([message, token_json, userInfo](http_response token_response)
											{
												userInfo["id"] = token_json["id"];
												userInfo["token"] = token_json["token"];
												message.reply(status_codes::OK, userInfo);
											});
										}
									}
								}*/
							});
						});
						}
						else
						{
							if (path_first_request[1] == "deleteAccount")
							{
								json::value deleteAccountInfo;
								uri_builder deleteAccount_path(U("/deleteAccount/"));
								deleteAccountInfo["id"] = request.at("id");
								DataBaseClient.request(method::POST,  deleteAccount_path.to_string(), deleteAccountInfo).
								then([message](http_response)
								    );
							}
							else
							{
								if(path_first_request[1] == "signout")
								{
									uri_builder deleteToken("/deleteToken/");
									json::value userId
									userId["id"] = request.at("id");
									TokenDB.request(method::POST, deleteToken, userId);
									message.reply(status_codes::OK, json::value::string("EXIT"));
								}
								else
								{
									if()
									{}
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


void MicroserviceController::handlePost(http_request message) {
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


void MicroserviceController::handlePatch(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PATCH));
}


void MicroserviceController::handlePut(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PUT));
}


void MicroserviceController::handleDelete(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::DEL));
}

void MicroserviceController::handleHead(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::HEAD));
}

void MicroserviceController::handleOptions(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::OPTIONS));
}

void MicroserviceController::handleTrace(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::TRCE));
}

void MicroserviceController::handleConnect(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::CONNECT));
}

void MicroserviceController::handleMerge(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::MERGE));
}

json::value MicroserviceController::responseNotImpl(const http::method & method) {
    auto response = json::value::object();
    response["serviceName"] = json::value::string("C++ Mircroservice Sample");
    response["http_method"] = json::value::string(method);
    return response ;
}

