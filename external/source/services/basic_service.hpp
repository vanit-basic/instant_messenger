#pragma once

#include <string>
#include <cpprest/http_listener.h>
#include <cpprest/http_client.h>
#include <pplx/pplxtasks.h>

using namespace web;
using namespace http::experimental::listener;
using namespace http::client;

namespace cfx {
    class BasicService : protected BasicController {

    protected:
	    std::vector<http_client> m_clients;

    public:
        BasicService();
        ~BasicService();
    };
}
