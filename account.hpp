#pragma once 

#include </home/narek/Documents/Tnayin/micro-service/source/foundation/include/basic_controller.hpp> 
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

class Account : public BasicController, Controller {
	public:
		bool checkServices();
		bool createClients(std::string path);
		Account() : BasicController() {}
		~Account() {}

	private:
		http_client *DatabaseClient;
		http_client *TokenDBClient;
		std::string accountUri;
		void handleGet(http_request message) override;
		void handlePut(http_request message) override;
		void handlePost(http_request message) override;
		void handlePatch(http_request message) override;
		void handleDelete(http_request message) override;
		void handleHead(http_request message) override;
		void handleOptions(http_request message) override;
		void handleTrace(http_request message) override;
		void handleConnect(http_request message) override;
		void handleMerge(http_request message) override;
		void initRestOpHandlers() override;

		static json::value responseNotImpl(const http::method & method);
};

