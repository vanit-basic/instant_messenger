#include <iostream>
#include <fstream>

#include <tokenDbService/tokenDbService.hpp>

void tokenDbService::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&tokenDbService::handleGet, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&tokenDbService::handlePost, this, std::placeholders::_1));
}

bool tokenDbService::getUri(std::string path) {
        std::ifstream configFile(path);
        json::value config;
        if (configFile.is_open()) {
                configFile >> config;
                configFile.close();
                this->tokenDbServiceUri = config.at("tokenDbService").as_string();
                return true;
        } else {
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
                return false;
        }
}

tokenDbService::tokenDbService(std::string path, database* m) : BasicController() {
        if(getUri(path)) {
                this->setEndpoint(tokenDbServiceUri);
        }
        this-> db = m;
}

void tokenDbService::handleGet(http_request message)
{
	std::cout<<"message  " <<message.to_string()<<std::endl;
/*	std::string token;
	json::value response;
	if(message.headers().match("token", token))
	{
		std::map<utility::string_t, utility::string_t>  inf = uri::split_query(message.request_uri().query());
		std::string id = std::string(inf["userId"]);
		auto path = requestPath(message);
		if(path[0] == "checkToken")
		{
			if(db->checkToken(id, token))
			{
				response["status"] = json::value::string("OK");
				message.reply(status_codes::OK, response);
			}
			else
			{
				response["status"] = json::value::string("notFound");
				message.reply(status_codes::OK, response);
			}
		}
	}
	else
	{
		response["status"] = json::value::string("invalidRequest");
		message.reply(status_codes::OK, response);
	}
*/
}
void tokenDbService::handlePost(http_request message)
{
	std::cout<<"message  " <<message.to_string()<<std::endl;
	message.extract_json().then([message, this](json::value info){
		auto path = requestPath(message);
		json::value response;
		if(path[0] == "setToken")
		{
			if((this->db)->setToken(info))
			{
				response["status"] = json::value::string("OK");
			}
			else
			{
				response["status"] = json::value::string("notFound");
			}
		}
		else
		{
			if(path[0] == "deleteToken")
			{
				if((this->db)->deleteToken(info))
				{
					response["status"] = json::value::string("OK");
				}
				else
				{
					response["status"] = json::value::string("notFound");
				}
			}
			else
			{
				if(path[0] == "checkToken")
				{
					if((this->db)->checkToken(info))
					{
						response["status"] = json::value::string("OK");
					}
					else
					{
						response["status"] = json::value::string("notFound");
					}
				}
				else
				{
					response["status"] = json::value::string("invalidRequest");
				}
			}
		}
		message.reply(status_codes::OK, response);
			});
}
