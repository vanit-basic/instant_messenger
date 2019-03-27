#pragma once 
#include <string>

//#include <mongocxx/uri.hpp>
#include <mongocxx/pool.hpp>
#include <base/basic_controller.hpp>
#include <dbservice/database.hpp>
#include <cpprest/http_client.h>
//#include "mongoDb.hpp"
#include <cpprest/filestream.h>

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include <messaging/echoserver.hpp>

using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

class Messaging : public BasicController, Controller {
        public:
                bool checkServices();
		http_client* AccountClient;
		database* m_db;
		EchoServer* wsQt;
                Messaging(int, const char**,database*,EchoServer*);
              	
	      	 ~Messaging();


        private:
                std::string messagingUri;
                bool createClients(int, const char**);
		
};


