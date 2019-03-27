#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <network_utils.hpp>
#include <messaging/messaging.hpp>
#include <string>

#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <messaging/echoserver.hpp>

bool Messaging::createClients(int argc, const char** argv)
{
	EchoServer* server;
	database* m_db;
	json::value config;
	std::string path = std::string(argv[1]);
	char** arg= const_cast<char**>(argv);
	std::ifstream ConfigFile(path);
		if (ConfigFile.is_open()) {
                ConfigFile>> config;
                ConfigFile.close();
                
		this -> AccountClient = new http_client(NetworkUtils::hostURI(config.at("account").as_string()));
                this -> messagingUri = config.at("messaging").as_string();
		
		 ///
		 std::string messagingPort =config.at("messagingPort").as_string();
		 QCoreApplication a(argc,arg);
		 QCommandLineParser parser;
		 parser.setApplicationDescription("QtWebSockets example: echoserver");
		 parser.addHelpOption();
		 QCommandLineOption dbgOption(QStringList() << "d" << "debug",
		 QCoreApplication::translate("main", "Debug output [default: off]."));
		 parser.addOption(dbgOption);
		 QCommandLineOption portOption(QStringList() << "p" << "port",
		 QCoreApplication::translate("main","Port for echoserver [default:1205]."),
		 QCoreApplication::translate("main", "port"), QLatin1Literal("1205"));
		 parser.addOption(portOption);
		 parser.process(a);
		 bool debug = parser.isSet(dbgOption);
		 int port = parser.value(portOption).toInt();

		 server = new EchoServer(quint16(port), debug,nullptr);
		 
		///
		 return true;
        }
        else {
                std::cerr << "ConfigFile is not exist!!!" << std::endl;
                return false;
        }
}

Messaging::Messaging(int argc, const char** argv, database* mongoDb,EchoServer* QtWs)
{
	this->m_db = mongoDb;
        this->createClients(argc, argv);
	this->wsQt = QtWs;
	
}
Messaging::~Messaging(){
	this->wsQt->~EchoServer();
}
bool ServiceStart (http_client* client, std::string serviceName) {
        uri_builder builder(U("/ServiceTest/"));
        std::error_code error;

        int count = 0;
        int exequtionCount = 0;
        const int maxExequtionCount = 10;
        const int maxCount = 60;
        do{
                if(count == maxCount)
                {
                        //avelacnel exequtor funkciayi kanch(vor@ petq e start ani DBservicner@)
                        if(exequtionCount >= maxExequtionCount)
                        {
                                std::cout<<serviceName<<" DBservices is dead!!!"<<std::endl;
                                return false;
                        }
                        ++exequtionCount;
                        count = 0;
                }
                usleep(100000);
                error.clear();
                try {
                        count++;
                        pplx::task<web::http::http_response> requestTask = client->request(methods::GET, builder.to_string());
                        requestTask.wait();
                } catch (http_exception e) {
                        error = e.error_code();
                }}
        while (error.value());
        return true;
}
/*
void Messaging::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&Messaging::handleGet, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&Messaging::handlePost, this, std::placeholders::_1));
}

http_response userRemoveMessage(std::string userId, std::string clientId, std::string messageId, database* DataBaseClient){
 	auto resp = DataBaseClient->userRemoveMessage(userId, clientId, messageId);
	return resp;
}
http_response userRemoveConversation(std::string userId,std::string clientId, database* DataBaseClient){
 	auto resp = DataBaseClient->userRemoveConversation(userId, clientId);
	return resp;
}

http_response getUsersConversation(std::string userId, std::string clientId, database* DataBaseClient){
 	auto resp = DataBaseClient->getUsersConversation(userId, clientId);
	return resp;
}

http_response getUserConversations(std::string userId, database* DataBaseClient){
 	auto resp = DataBaseClient->getUserConversations(userId);
	return resp;
}

http_response getGroupConversation(std::string userId, std::string groupId, database* DataBaseClient){
 	auto resp = DataBaseClient->getGroupConversation(groupId);
	return resp;
}

http_response groupRemoveConversation(std::string userId, std::string groupId, database* DataBaseClient){
 	auto resp = DataBaseClient->groupRemoveConversation(groupId);
	return resp;
}

http_response groupRemoveMessage(std::string userId,std::string groupId , std::string messageId , database* DataBaseClient){
 	auto resp = DataBaseClient->groupRemoveMessage(groupId, messageId);
	return resp;
}





void Messaging::handleGet(http_request message) {
	std::cout<<message.to_string()<<std::endl;
	auto path = requestPath(message);
	if(!(path.empty()))
	{
		if(path[0] == "ServiceTest")
		{message.reply(status_codes::OK,"Messaging_Start");}
		else if(path[1] == "userRemoveMessage")
		{
			std::string firstUserId  = path[2];
			std::string secondUserId = path[3];
			std::string messageId    = path[4];
			auto  removeMessage =userRemoveMessage(firstUserId , secondUserId , messageId , this->m_db);
			message.reply(removeMessage);
		}else
		{
			if(path[1] == "userRemoveConversation")
			{
				std::string firstUserId  = path[2];
				std::string secondUserId = path[3];
				auto removeConversation  = userRemoveConversation(firstUserId,secondUserId,this->m_db);
				message.reply(removeConversation);
			}else
			{
				if(path[1] == "getUsersConversation")
				{
					std::string firstUserId  = path[2];
                                	std::string secondUserId = path[3];
                                	auto userConversation  = getUsersConversation(firstUserId,secondUserId,this->m_db);
                                	message.reply(userConversation);
				}else
				{
					if(path[1] == "getUserConversations")
                                	{	
						std::string userId  = path[2];
                                		auto userConversations  = getUserConversations(userId,this->m_db);
                                		message.reply(userConversations);
                                	}else
                                	{
						if(path[1] == "getGroupConversation")
						{
							std::string userId  = path[2];
							std::string groupId = path[3];
							auto groupConversation = getGroupConversation(userId,groupId,this->m_db);
							message.reply(groupConversation);
						}else
						{
							if(path[1] == "groupRemoveConversation")
							{
								std::string userId  = path[2];
                	                                        std::string groupId = path[3];
        	                                                auto removeConversation = groupRemoveConversation(userId,groupId,this->m_db);
	                                                        message.reply(removeConversation);

							}else
							{
								if(path[1] =="groupRemoveMessage")
								{
									std::string userId    = path[2];
                                                                	std::string groupId   = path[3];
                                                                	std::string messageId = path[4];
									auto removeMessage = groupRemoveMessage(userId , groupId , messageId , this->m_db);
                                                                	message.reply(removeMessage);
								}
							}
						}
                               		}
				}
			}
		}
		
	}else
	{
    		message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
	}
}

http_response userUpdateMessage (json::value req, database* DataBaseClient){
	auto resp = DataBaseClient->userUpdateMessage(from, to, message);
	return resp;
}

http_response userSendMessage (json::value req, database* DataBaseClient){
	auto resp = DataBaseClient->userSendMessage(from, to, message);
	return resp;
}

http_response groupUpdateMessage (json::value req, database* DataBaseClient){
	DataBaseClient->groupUpdateMessage_path.to_string();
}

http_response groupSendMessage (json::value req, database* DataBaseClient){
	uri_builder groupSendMessage_path(U("/groupSendMessage/"));
	DataBaseClient->request(methods::POST, groupSendMessage_path.to_string(), req).
	then([=](http_response status){
		return status;
	});
}

void Messaging::handlePost(http_request message) {
	auto path = requestPath(message);
	message.extract_json().
	then([=](json::value request)
	{
		if(path[1] == "userUpdateMessage"){
			auto resp = userUpdateMessage (request, this -> m_db);
			message.reply(resp);
		}
		else
		{
			if(path[1] == "userSendMessage"){
				auto resp = userSendMessage (request, this -> m_db);
				message.reply(resp);
			}
			else
			{
				if(path[1] == "groupUpdateMessage"){
					auto resp = groupUpdateMessage (request, this -> m_db);
					message.reply(resp);
				}
				else
				{
					if(path[1] == "groupSendMessage"){
						auto resp = groupSendMessage (request, this -> m_db);
						message.reply(resp);
					}
					else
					{
						message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
					}
				}
			}
		}
	});
}
*/
