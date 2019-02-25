#pragma once 

#include <string>

#include <cpprest/http_client.h>

#include <base/basic_controller.hpp>

using namespace cfx;
using namespace web::http::client;         

class Executor : public BasicController, Controller {
	private:
		std::string m_configFilePath;
		std::map<std::string, http_client*> m_clients;
		std::vector<std::string> m_services;
		
	public:
		bool isServiceRunning(std::string serviceName);
		bool startServices();
		bool startService(std::string serviceName);
		bool stopService(std::string serViceName);
		bool restartService(std::string serviceName);

		Executor(std::string);
		~Executor();

		void handleGet(http_request message) override;
		void handlePost(http_request message) override;
		void initRestOpHandlers() override;
};
