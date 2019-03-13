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
                DataBaseClient = new http_client(NetworkUtils::hostURI(config.at("dbservice").as_string()));
                this->searchUri = config.at("search").as_string();
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
		this -> cash_db = mongo_cash_db;
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

bool Account::checkServices()
{
//      qani der patrast chen DbServicner@ toxnel vorpes comment

	bool status = false;
	bool DbServStatus = false;
	DbServStatus = ServiceStart(DataBaseClient, "Database");
/*	
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
		if(path[1] == "user")
		{
			std::string field_1 = "";
			std::string field_2 = "";
			std::string field_3 = "";
			if(fields.count("field_1") > 0)
			{
				field_1 = fields["field_1"];
				if(fields.count("field_2") > 0)
				{
					field_2 = fields["field_2"];
					if(fields.count("field_3") > 0)
					{
						field_3 = fields["field_3"];
					}
				}

				info = cashDatabase -> getInfo(field_1 + field_2 + field_3, fields["from"], fields["to"]);
				uri_builder usersInfo("/getUsersShortInfos");
				
				if(info.at("status").as_string() == "OK")
				{
					http_response response = DataBaseClient->request(methods::POST, usersInfo.to_string(), info).get();
					message.reply(response);
				}
				if(info.at("status").as_string() == "NOT_FOUND")
				{
					http_response response = DataBaseClient->request(message).get();//avelanalu e - response pahel cashi mej, request uxarkel dbService-in, patasxamel message-in
					message.reply(response);
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
