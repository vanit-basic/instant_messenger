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


class Router : public BasicController, Controller {
        public:
		bool checkServices();
                Router(std::string);
                ~Router() {}

        private:
		std::string routerUri;
                http_client *TokenDbClient;
                http_client *AccountClient;
                http_client *GameClient;
                http_client *ConversationClient;
                http_client *NotificationClient;
                http_client *SearchClient;
                bool createClients(std::string path);
		void handleGet(http_request message) override;
                void handlePost(http_request message) override;
		void initRestOpHandlers() override;

};

