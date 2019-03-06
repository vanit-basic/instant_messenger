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
	message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
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
				response["status"] = json::value::string("NOT_OK");
			}
			message.reply(status_codes::OK, response);
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
					response["status"] = json::value::string("NOT_OK");
				}
				message.reply(status_codes::OK, response);
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
						response["status"] = json::value::string("NOT_OK");
					}
					message.reply(status_codes::OK, response);
				}
				else
				{
					message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
				}
			}
		}
			});
}
