#pragma once
#include <string>
#include <base/basic_controller.hpp>
#include <cpprest/http_client.h>

#include <cpprest/filestream.h>

using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

class tokenDatabase {
	public:
                virtual bool setToken(json::value) = 0;
                virtual bool checkToken(json::value) = 0;
                virtual bool deleteToken(json::value) = 0;
                tokenDatabase(){};
                ~tokenDatabase(){};
};
