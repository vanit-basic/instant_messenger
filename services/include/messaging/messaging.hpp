#pragma once 
#include <string>

//#include <mongocxx/uri.hpp>
#include <mongocxx/pool.hpp>
#include <base/basic_controller.hpp>
#include <messaging/messagingDbBase.hpp>
#include <cpprest/http_client.h>
//#include "mongoDb.hpp"

#include <cpprest/filestream.h>


using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

class Messaging : public BasicController, Controller {
        public:
                bool checkServices();
		messagingDbBase* m_db;
                Messaging(std::string,messagingDbBase*);
                virtual ~Messaging();


        private:
                std::string messagingUri;
                bool createClients(std::string path);
                void handleGet(http_request message) override;
                void handlePost(http_request message) override;
                void initRestOpHandlers() override;
};


