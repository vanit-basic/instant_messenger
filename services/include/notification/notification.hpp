#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#include <string>

#include <mongocxx/pool.hpp>
#include <base/basic_controller.hpp>
#include <dbservice/database.hpp>
#include <cpprest/http_client.h>

#include <cpprest/filestream.h>

using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

class Notification : public BasicController, Controller {
        public:
                bool checkServices();
                database* m_db;
                Notification(std::string, database*);
                virtual ~Notification();

        private:
                std::string messagingUri;
                bool createClient(std::string path);
                void handleGet(http_request message) override;
                void handlePost(http_request message) override;
                void initRestOpHandlers() override;
};

#endif;
