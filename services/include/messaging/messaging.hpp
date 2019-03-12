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

class Messaging : public BasicController, Controller {
        public:
                bool checkServices();
                messagingDbBase* m_db;
                Messaging(std::stringi,database*);
                virtual ~Messaging();

        private:
                std::string messagingUri;

                void handleGet(http_request message) override;
                void handlePost(http_request message) override;
                void initRestOpHandlers() override;
};


