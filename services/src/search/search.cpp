#include <cstdint>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <stdio.h>

#include <search/search.hpp>
#include <search/cashdatabase.hpp>

void Search::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&Search::handleGet, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&Search::handlePost, this, std::placeholders::_1));
}

bool Search::createClients(std::string path)
{
        std::ifstream ConfigFile(path);
        json::value config;
        if (ConfigFile.is_open()) 
	{
                ConfigFile>> config;
                ConfigFile.close();
                this->searchUri = config.at("search").as_string();
                DataBaseClient = new http_client(NetworkUtils::hostURI(config.at("dbservice").as_string()));
                return true;
        }
        else 
	{
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
                return false;
        }
}


Search::Search(std::string path, cashDatabase* mongo_cash_db)
{
	if(createClients(path))
	{
		this -> cashDb = mongo_cash_db;
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
                                std::cout<<serviceName<<" is dead!!!"<<std::endl;
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

bool Search::checkServices()
{
//      qani der patrast chen DbServicner@ toxnel vorpes comment

	bool status = false;
	bool DbServStatus = false;
/*	DbServStatus = ServiceStart(DataBaseClient, "Database");	
	if(DbServStatus)
	{
		this->setEndpoint(searchUri);
		status = true;
	}
	return status;
*/
        this->setEndpoint(searchUri);
        return true;
}

void Search::handleGet(http_request message) {

	auto path = requestPath(message);
	if (!(path.empty()))
	{
		std::map<utility::string_t, utility::string_t>  fields = uri::split_query(message.request_uri().query());
		json::value info;
		std::string userId = fields["userId"];
		if(path[1] == "user")
		{
			std::string firstName = "";
			std::string lastName = "";
			std::string nickName = "";
			if(fields.count("firstName") > 0)
			{
				firstName = fields["firstName"];
				if(fields.count("lastName") > 0)
				{
					lastName = fields["lastName"];
					if(fields.count("nickName") > 0)
					{
						nickName = fields["nickName"];
					}
				}

				info = cashDb -> getInfo(firstName + lastName + nickName, fields["from"], fields["to"]);
				uri_builder usersInfo("/getUsersShortInfos");
				
				if(info.at("status").as_string() == "OK")
				{
					info.erase("status");
					http_response response = DataBaseClient->request(methods::POST, usersInfo.to_string(), info).get();
					message.reply(response);
				}
				if(info.at("status").as_string() == "NOT_FOUND")
				{
					http_response response = DataBaseClient->request(message).get();
					json:: value Ids = response.extract_json().get();
					cashDb -> setInfo(Ids);
					info.erase("status");
					info = cashDb -> getInfo(firstName + lastName + nickName, fields["from"], fields["to"]);
					http_response usersInfos = DataBaseClient->request(methods::POST, usersInfo.to_string(), info).get();
					message.reply(usersInfos);
				}
			}
			else
			{
				message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
			}
		}
		else
		{
			if(path[1] == "group")
			{
				std::string groupName = "";
				if(fields.count("groupName") > 0)
				{
					groupName = fields["groupName"];
					info = cashDb -> getInfo(groupName, fields["from"], fields["to"]);
					uri_builder groupsInfo("/getGroupsShortInfos");
					if(info.at("status").as_string() == "OK")
					{
						info.erase("status");
						http_response response = DataBaseClient->request(methods::POST, groupsInfo.to_string(), info).get();
						message.reply(response);
					}
					if(info.at("status").as_string() == "NOT_FOUND")
					{
						http_response response = DataBaseClient->request(message).get();
						json:: value Ids = response.extract_json().get();
						cashDb -> setInfo(Ids);
						info.erase("status");
						info = cashDb -> getInfo(groupName, fields["from"], fields["to"]);
						http_response groupsInfos = DataBaseClient->request(methods::POST, groupsInfo.to_string(), info).get();
						message.reply(groupsInfos);
					}
				}
				else
				{
					message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
				}
			}
			else
			{
				message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
			}
		}
	}
	else
	{
		message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
	}
}

void Search::handlePost(http_request message)
{
	std::cout<<message.to_string()<<std::endl;
	message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
}
