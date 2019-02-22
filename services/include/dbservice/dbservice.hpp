#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <string>

#include <controller.hpp>
#include <basic_controller.hpp>
#include <dbservice/database.hpp>
#include <cpprest/http_client.h>
//#include <mongoDb.hpp>

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
		mongocxx::pool * poolMydb;
		mongocxx::pool * poolDB;
		bool createPool(std::string path);
		void handleGet(http_request message) override;
		void handlePost(http_request message) override;
		void handlePut(http_request message) override;
		void handleDelete(http_request message) override;
		void handlePatch(http_request messge) override;
		void handleHead(http_request message) override;
		void handleOptions(http_request message) override;
		void handleTrace(http_request message) override;
		void handleConnect(http_request message) override;
		void handleMerge(http_request message) override;
    		void initRestOpHandlers() override;

		static json::value responseNotImpl(const http::method & method) {}
};

#endif
