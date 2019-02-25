#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <executor/executor.hpp>

struct serviceInfo {
	int status;
	std::string url;
	std::string name;
	std::vector <std::string> friendServices;
	serviceInfo();
	serviceInfo(json::value info);
};

Executor::Executor(std::string path) {
	std::ifstream ConfigFile(path);
        json::value config;
	if (ConfigFile.is_open()) {
		ConfigFile>> config;
		ConfigFile.close();
		json::value content = config.at("executor");
		std::string endpoint = content.at("uri").as_string();
		setEndpoint(endpoint);
		json::value servicesValue = content.at("services");
		if(servicesValue.is_array()) {
			json::array services = servicesValue.as_array();
			for (json::array::const_iterator i = services.begin(); i != services.end(); ++i) {
				std::string srvName = (*i).as_string();
				std::string url = config.at(srvName).as_string();
				http_client *c = new http_client(url);
				m_services[srvName] = c;
			}
		} else {
			std::cout << servicesValue  << "is not array" << std::endl;
		}
	}
        else {
		std::cerr << "ConfigFile is not exists!!!" << std::endl;
        }
}

bool Executor::startServices() {
	return true;
}

bool Executor::startService(std::string serviceName) {
	return true;
}

bool Executor::stopService(std::string serViceName) {
	return true;
}

bool Executor::restartService(std::string serviceName) {
	return true;
}

bool Executor::isServiceRunning(std::string serviceName) {

}

void Executor::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&Executor::handleGet, this, std::placeholders::_1));
}

void Executor::handleGet(http_request message) {
	std::cout<< message.to_string()<<std::endl;
	auto path = requestPath(message);
	if (!(path.empty())) {
		
	} else {
		message.reply(status_codes::NotFound);
	}
}

void Executor::handlePost(http_request message) {
		message.reply(status_codes::OK);
}

Executor::~Executor() {
	//TODO 
	//clean the m_services
}
