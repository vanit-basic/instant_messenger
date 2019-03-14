#pragma once 

#include <string>

#include <base/basic_controller.hpp>
#include <network_utils.hpp>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <search/cashdatabase.hpp>

using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

class Search : public BasicController, Controller {
        public:
                bool checkServices();
                Search(std::string, cashDatabase*);
                ~Search() {}

        private:
                std::string searchUri;
                http_client *DataBaseClient;
		cashDatabase* cashDb;
                bool createClients(std::string path);
                void handleGet(http_request message) override;
                void handlePost(http_request message) override;
                void initRestOpHandlers() override;
};

