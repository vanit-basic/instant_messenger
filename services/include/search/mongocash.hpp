#include <string>

#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/pool.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/types/value.hpp>
#include <bsoncxx/document/value.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/array/view.hpp>

#include <search/cashdatabase.hpp>






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

class MongoCashDb : public cashDatabase
{
	public:
		virtual bool setInfo(json::value info);
		virtual json::value getInfo(std::string key);
		MongoCashDb(std::string path);
		~MongoCashDb();
	private:
		mongocxx::pool* clientPool;
		bool createPool(std::string);
}
