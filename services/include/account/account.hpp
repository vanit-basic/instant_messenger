#pragma once 

#include <base/basic_controller.hpp>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <string>

using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

class Account : public BasicController, Controller {
	public:
		bool checkServices();
		Account(std::string);
		~Account() {}

	private:
		std::string accountUri;
		http_client *DataBaseClient;
		http_client *TokenDBClient;
		bool createClients(std::string path);
		void handleGet(http_request message) override;
		void handlePost(http_request message) override;
    		void initRestOpHandlers() override;
};

