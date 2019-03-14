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

class cashDatabase
{
	public:
		virtual bool setInfo(json::value info) = 0;
		virtual json::value getInfo(std::string key, std::string from, std::string to) = 0;
		cashDatabase(){}
		~cashDatabase(){}
};
