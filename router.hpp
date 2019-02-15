#pragma once 

#include <basic_controller.hpp>

using namespace cfx;

class Router : public BasicController, Controller {
        public:
		bool checkServices();
                Router(std::string) : BasicController();
                ~Router() {}

        private:
		std::string routerUri;
                http_client *TokenDbClient;
                http_client *AccountClient;
                http_client *GameClient;
                http_client *ConversationClient;
                http_client *NotificationClient;
                http_client *SearchClient;
                void handleGet(http_request message) override;
                void handlePut(http_request message) override;// = delete;
                void handlePost(http_request message) override;
                void handlePatch(http_request message) override;// = delete;
                void handleDelete(http_request message) override;// = delete;
                void handleHead(http_request message) override;// = delete;
                void handleOptions(http_request message) override;// = delete;
                void handleTrace(http_request message) override;// = delete;
                void handleConnect(http_request message) override; // = delete;
                void handleMerge(http_request message) override; // = delete;
                void initRestOpHandlers() override;

                static json::value responseNotImpl(const http::method & method);
};

