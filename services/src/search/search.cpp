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
	bool status = false;
	bool DbServStatus = false;
	DbServStatus = ServiceStart(DataBaseClient, "Database");	
	if(DbServStatus)
	{
		this->setEndpoint(searchUri);
		status = true;
	}
	return status;
}

void Search::handleGet(http_request message) {
	std::cout<<message.to_string()<<std::endl;
	message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
}

void Search::handlePost(http_request message)
{
	auto path = requestPath(message);
	json::value fields = message.extract_json().get();
	if (!(path.empty()))
	{
		json::value info;
		std::string userId = fields.at("userId").as_string();
		if(path[1] == "user")
		{
			std::string from = fields.at("from").as_string();
			std::string get = fields.at("get").as_string();
			std::string field1 = "";
			std::string field2 = "";
			std::string field3 = "";
			if(!fields.at("field1").is_null())
			{
				field1 = fields.at("field1").as_string();
				if(!fields["field2"].is_null())
				{
					field2 = fields.at("field2").as_string();
					if(!fields["field3"].is_null())
					{
						field3 = fields.at("field3").as_string();
					}
				}
				message.set_body(fields);
				info = cashDb -> getInfo(field1 + field2 + field3, from, get);
				uri_builder usersInfo("/getUsersShortInfos");
				
				if(info.at("status").as_string() == "OK")
				{
					info.erase("status");
					message.reply(DataBaseClient->request(methods::POST, usersInfo.to_string(), info).get());
				}
				if(info.at("status").as_string() == "NOT_FOUND")
				{
					json:: value Ids = DataBaseClient->request(message).get().extract_json().get();
					cashDb -> setInfo(Ids);
					info.erase("status");
					info = cashDb -> getInfo(field1 + field2 + field3, from, get);
					message.reply(DataBaseClient->request(methods::POST, usersInfo.to_string(), info).get());
				}
			}
			else
			{
				message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
			}
		}
		else
		{
			if(path[1] == "group")
			{
				std::string from = fields.at("from").as_string();
				std::string get = fields.at("get").as_string();
				std::string groupName = "";
				if(!fields["field1"].is_null())
				{
					groupName = fields.at("field1").as_string();
					info = cashDb -> getInfo(groupName, from, get);
					uri_builder groupsInfo("/getGroupsShortInfos");
					if(info.at("status").as_string() == "OK")
					{
						info.erase("status");
						http_response response = DataBaseClient->request(methods::POST, groupsInfo.to_string(), info).get();
						message.reply(response);
					}
					if(info.at("status").as_string() == "NOT_FOUND")
					{
						message.set_body(fields);
						http_response response = DataBaseClient->request(message).get();
						json:: value Ids = response.extract_json().get();
						cashDb -> setInfo(Ids);
						info.erase("status");
						info = cashDb -> getInfo(groupName, from, get);
						message.reply(DataBaseClient->request(methods::POST, groupsInfo.to_string(), info).get());
					}
				}
				else
				{
					message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
				}
			}
			else
			{
				message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
			}
		}
	}
	else
	{
		message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
	}
}
