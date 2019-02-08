#pragma once 

#include <basic_controller.hpp>

using namespace cfx;

class Account : public BasicController, Controller {
	public:
		Account() : BasicController() {}
		~Account() {}
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

	private:
		const int max_attempt = 5;
		http_client DatabaseClient;
		http_client TokenDB;
		void setToken();
		void registration(http_request);
		void signIn(http_request);
		
		void deleteUser(http_request);
		static json::value responseNotImpl(const http::method & method);
};

