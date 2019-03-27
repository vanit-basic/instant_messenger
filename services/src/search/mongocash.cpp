#include <cstdint>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <stdio.h>

#include <mongocxx/exception/query_exception.hpp>
#include <search/mongocash.hpp>

bool MongoCashDb::createPool(std::string path) 
{
        std::ifstream configFile(path);
        json::value config;
        if (configFile.is_open()) 
	{
                configFile >> config;
                configFile.close();
                this->clientPool = new mongocxx::pool (mongocxx::uri{config.at("mongodbserver").as_string()});
                return true;
        } 
	else 
	{
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
                return false;
        }
}

MongoCashDb::MongoCashDb(std::string path) 
{
	mongocxx::instance instance{};
	createPool(path);
}
MongoCashDb::~MongoCashDb() 
{
        delete [] this->clientPool;
}

bool MongoCashDb::setInfo(json::value info)
{
	bool status = false;
	try
	{
		auto client = clientPool->acquire();
		auto coll = (*client)["CashDb"]["userIds"];
		std::string jsonString = info.as_string();
		bsoncxx::document::value inf = bsoncxx::from_json(jsonString);
		coll.insert_one(std::move(inf));
		status = true;
	}
	catch(...) 
	{
		std::cerr<<"cant insert info in cashDb"<<std::endl;
	}
	return status;
}

json::value MongoCashDb::getInfo(std::string key, std::string from, std::string get)
{
	json::value info;
	try
	{
		auto client = clientPool->acquire();
		auto coll = (*client)["CashDb"]["userIds"];
		int x = std::stoi(from);
		int y = std::stoi(get);
		auto distinct_results = coll.distinct(key, {});
		if (distinct_results.begin() != distinct_results.end())
		{
			std::vector<bsoncxx::document::value> results;
			for (auto&& result : distinct_results) 
			{
				results.emplace_back(result);
			}
			bsoncxx::document::view doc = results[0].view();
			bsoncxx::document::element element = doc[key];
			if (element.type() == type::k_array)
			{
				bsoncxx::array::view subarray{element.get_array().value};
				if (std::distance(subarray.begin(), subarray.end()) < (x + y))
				{
					y = std::distance(subarray.begin(), subarray.end()) - x;
				}
				
				std::vector<json::value> mass(y);
				for(int i = 0; i < y; ++i)
				{
					mass[i] = json::value::string(((subarray.find(x+i))->get_utf8().value.to_string()));
				}
				info["status"] = json::value::string("OK");
				info["users"] = json::value::array(mass);
			}
			else
			{
				std::cout<<"MongoCashDb::getInfo element type not array"<<std::endl;
			}
		}
		else
		{
			std::cout<<"MongoCashDb::getInfo distinct_results is empty"<<std::endl;
			info["status"] = json::value::string("NOT_FOUND");
		}
	}
	catch(mongocxx::query_exception e) 
	{
		std::cerr<<"distinct exception  "<<e.what()<<std::endl;
	}
	catch(...) 
	{
		std::cerr<<"MongoCashDb::getInfo something wrong"<<std::endl;
	}
	return info;
}
