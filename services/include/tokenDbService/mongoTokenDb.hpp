#pragma once

#include <string>

#include <base/basic_controller.hpp>
#include <cpprest/http_client.h>
#include <tokenDbService/tokenDatabase.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/pool.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/types.hpp>

using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_document;


class MongoTokenDb : public tokenDatabase
{
	public:
		bool setToken(json::value) override;
		bool checkToken(json::value) override;
		bool deleteToken(json::value) override;
		MongoTokenDb(std::string);
		~MongoTokenDb();
	private:
		mongocxx::pool* clientPool;
		bool createPool(std::string);
};
