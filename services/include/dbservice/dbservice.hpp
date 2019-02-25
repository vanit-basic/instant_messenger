#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <string>

//#include <mongocxx/uri.hpp>
#include <mongocxx/pool.hpp>
#include <base/basic_controller.hpp>
#include <dbservice/database.hpp>
#include <cpprest/http_client.h>
//#include "mongoDb.hpp"

#include <cpprest/filestream.h>

using namespace cfx;
using namespace utility;                   
using namespace web;                       
using namespace web::http;                 
using namespace web::http::client;         
using namespace concurrency::streams; 


class DbService: public BasicController, Controller {
	public:
		DbService(std::string);
		virtual ~DbService();
	private:
		database * m_db;
		std::string dbserviceUri; 
		mongocxx::pool* poolMydb;
		mongocxx::pool* poolDB;
		bool createPool(std::string path);
		void handleGet(http_request message) override;
		void handlePost(http_request message) override;
    		void initRestOpHandlers() override;
};

#endif
