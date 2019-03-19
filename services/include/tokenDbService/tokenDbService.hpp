#pragma once

#include <string>

#include <base/basic_controller.hpp>
#include <cpprest/http_client.h>
#include <tokenDbService/tokenDatabase.hpp>

using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

class tokenDbService : public BasicController, Controller 
{
	public:
		tokenDbService(std::string, tokenDatabase*);
		virtual ~tokenDbService() {}
	private:
		tokenDatabase* db;
		std::string tokenDbServiceUri;
		bool getUri(std::string path);
		void handleGet(http_request message) override;
		void handlePost(http_request message) override;
		void initRestOpHandlers() override;
};
