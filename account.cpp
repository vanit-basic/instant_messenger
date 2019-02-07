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

void Account::handleGet(http_request message) {
        std::cout<< message.to_string()<<std::endl;
        auto path = requestPath(message);
        if (!path.empty()) {
                if (path[0] == "service" && path[1] == "test1") {
                        auto response = json::value::object();
                        response["version"] = json::value::string("0.1.1");
                        response["status"] = json::value::string("ready!");
                        message.reply(status_codes::OK, response);
                }

                else {
                        if(path[0] == "service" && path[1] == "test2")
                        {
                                auto response = json::value::object();
                                response["patasxan"] = json::value::string("staca");
                                response["status"] = json::value::string("verjacreci");
                                message.reply(status_codes::OK, response);
                        }
                }
        }
        else{
                message.reply(status_codes::NotFound);
        }
}

void Account::handlePost(http_request message) {
	//    message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
	auto path_first_request = requestPath(message);
	message.extract_json().
		then([message](json::value request) 
		{
				if (path_first_request[1] == "registration") 
				{
				std::string mail = request.at("email").as_string();
				std::string login = request.at("login").as_string();
				std::string ml = "/get/email/" + mail,"/login/" + login + "/"; 
				uri_builder get_mail_login(U(ml));
				DataBaseClient.request(methods::GET, get_mail_login.to_string()).

				then([message, request](http_response mail_login)
					{
						auto path = requestPath(mail_login);
						if(!(path[2] ==  request.at("email").as_string() && path[4] == request.at("login").as_string()))
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
							if(path[2] ==  request.at("email").as_string())
							{
								error["email"] = json::value::string(U("Invalid"));
							}
							if(path[4] ==  request.at("login").as_string())
							{
								error["login"] = json::value::string(U("Invalid"));
							}
							message.reply(status_codes::OK, error);
								});
					});
				}
				else
				{
					if(path_first_request[1] == "signin")
					{
						json::value signinInfo;
						uri_builder signin_path(U("/signin/"));
						singinInfo["login"] = request.at("login");
						singinInfo["password"] = request.at("password");
						DataBaseClient.request(method::POST,  signin_path.to_string(), signinInfo).
							then([message](http_response)
								);

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

