#pragma once 

#include <basic_controller.hpp>

using namespace cfx;

class Router : public BasicController, Controller {
        public:
                Router(std::string) : BasicController();
                ~Router() {}

        private:
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
                http_client *TokenDbClient;
                http_client *AccountClient;
                http_client *GameClient;
                http_client *ConversationClient;
                http_client *NotificationClient;
                http_client *SearchClient;
                void CheckToken();
                static json::value responseNotImpl(const http::method & method);
};

