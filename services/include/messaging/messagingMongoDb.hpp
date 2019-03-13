#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/pool.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/instance.hpp>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <bsoncxx/types.hpp>

#include <dbservice/database.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_document;
using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

class messagingMongoDb : public messagingDbBase {

	public:
		virtual json::value getUserConversations(std::string);
		virtual json::value getUsersConversation(std::string, std::string );
		virtual std::string userSendMessage(std::string, std::string, std::string );
		virtual bool userUpdateMessage(std::string, std::string, std::string );
		virtual bool userRemoveConversation(std::string, std::string );
		virtual bool userRemoveMessage(std::string, std::string, std::string);
		virtual bool groupRemoveConversation(std::string );
		virtual bool groupRemoveMessage(std::string, std::string );
		virtual std::string getGroupConversation(std::string);
		virtual std::string groupSendMessage(std::string , std::string , json::value );
		virtual bool groupUpdateMessage(std::string, std::string, json::value );
		messagingMongoDb(std::string path);
		~messagingMongoDb();

	private:
		mongocxx::pool* poolDB;
		bool createPool(std::string);

}
