#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <general_exceptions.hpp>

#include <executor/executor.hpp>

struct serviceInfo {
	int status;
	std::string url;
	std::string name;
	std::vector <std::string> friendServices;
	serviceInfo();
	serviceInfo(json::value info);
};

Executor::Executor(std::string path) : m_configFilePath(path) {
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
				m_clients[srvName] = c;
				m_services.push_back(srvName);
			}
		} else {
			throw InvalidConfig();
		}
	}
        else {
		std::cerr << "ConfigFile is not exists!!!" << std::endl;
        }
}

void executeSrevice(const std::string & serviceName, const std::string & configFile) {
	std::string command = "";
	command += "../scripts/service_contoller.sh";
	command += " ";
	command += serviceName;
	command += " ";
	command += configFile;
	command += " ";
	command += ".";
	command += " ";
	command += ">> result";
	system(command.c_str());
}

bool Executor::startServices() {
	std::vector<std::string>::iterator it = m_services.begin();
	for (; it != m_services.end(); ++it) {
		executeSrevice(*it, m_configFilePath);
	}
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
