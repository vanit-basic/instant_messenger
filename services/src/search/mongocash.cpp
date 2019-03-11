#include <cstdint>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <stdio.h>

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
		std::string jsonString = info.to_string();
		bsoncxx::document::value inf = bsoncxx::from_json(jsonString);
		coll.insert_one(inf);
		status = true;
	}
	catch(...) 
	{
		std::cerr<<"cant insert info in cashDb"<<std::endl;
	}
	return status;
}

json::value MongoCashDb::getInfo(std::string key, std::string from, std::string to)
{
	json::value info;
	try
	{
		auto client = clientPool->acquire();
		auto coll = (*client)["CashDb"]["userIds"];
		int x = std::stoi(from);
		int y = std::stoi(to);
/*		bsoncxx::document::element  element = docInfo[key];
		std::vector <json::value> Ids;
		if (element.type() == type::k_array)
		{
			bsoncxx::array::view subarray{element.get_array().value};
			int q = std::distance(subarray.begin(), subarray.end());
			if(y > q)
			{
				y = q;
			}

		}
		for (int i = x, )///sharunakel
*/	}
}
