#include <cstdint>
#include <iostream>
#include <ctime>
#include <fstream>
#include <stdio.h>

#include <tokenDbService/mongoTokenDb.hpp>
#include <dbservice/database.hpp>

bool MongoTokenDb::createPool(std::string path) 
{
        std::ifstream configFile(path);
        json::value config;
        if (configFile.is_open()) 
	{
                configFile >> config;
                configFile.close();
                this->clientPool = new mongocxx::pool ({config.at("mongodbServer").as_string()});
                return true;
        } 
	else 
	{
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
                return false;
        }
}

MongoTokenDb::MongoTokenDb(std::string path) 
{
        mongocxx::instance instance{};
        createPool(path);
}

MongoTokenDb:: ~MongoTokenDb()
{
	delete[] this->clientPool;
}

bool MongoTokenDb::setToken(json::value info)
{
	bool status = false;
	std::string id;
	std::string token;
	try
	{
		id = info.at("userId").as_string();
		token = info.at("token").as_string();
		auto client = clientPool->acquire();
		mongocxx::database db = (*client)["tokenDb"];
		mongocxx::collection coll = db["token"];
		auto builder = bsoncxx::builder::stream::document{};
		bsoncxx::document::value doc_value = builder << id << token << finalize;
		auto res = coll.insert_one(std::move(doc_value));
		status = true;
	}
	catch(...)
	{
		std::cerr<<"tokenDbService cant insert document"<<std::endl;
	}
	return status;
}

bool MongoTokenDb::checkToken(json::value info)
{
	bool status = false;
	std::string id;
	std::string token;
	try
	{
		id = info.at("id").as_string();
		token = info.at("token").as_string();
		auto client = clientPool->acquire();
		mongocxx::database db = (*client)["tokenDb"];
		mongocxx::collection coll = db["token"];
		bsoncxx::stdx::optional<bsoncxx::document::value> result = coll.find_one(document{} << id << token << finalize);
		if (result)
		{
			status = true;
		}
	}
	catch(...)
	{
		std::cerr<<"tokenDbService cant open collection for check token"<<std::endl;
	}
	return status;
}

bool MongoTokenDb::deleteToken(json::value info)
{
	bool status = false;
	std::string id;
	std::string token;
	try
	{
		id = info.at("id").as_string();
		token = info.at("token").as_string();
		auto client = clientPool->acquire();
		mongocxx::database db = (*client)["tokenDb"];
		mongocxx::collection coll = db["token"];
		coll.delete_one(document{} << id << token << finalize);
		status = true;
	}
	catch(...)
	{
		std::cerr<<"tokenDbService cant delete token from collection"<<std::endl;
	}
	return status;
}
