#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <fstream>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cpprest/http_msg.h>

#include <network_utils.hpp>
#include <base/basic_controller.hpp>
#include <base/std_micro_service.hpp>

using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

/*
                "account":"http://host_auto_ip4:6502/v1/mafclub/api",

                "messaging":"http://host_auto_ip4:6503/v1/mafclub/api",

                "router":"http://host_auto_ip4:6504/v1/mafclub/api",

                "game":"http://host_auto_ip4:6505/v1/mafclub/api",

                "search":"http://host_auto_ip4:6506/v1/mafclub/api",

                "tokendbservice":"http://host_auto_ip4:6507/v1/mafclub/api",

                "dbservice":"http://host_auto_ip4:6508/v1/mafclub/api",

                "notification":"http://host_auto_ip4:6509/v1/mafclub/api",

                "infoDB":"mongodb://localhost:27017",

                "tokenDB":"mongodb://localhost:27016",
*/


int main()
{
	http_client client(NetworkUtils::hostURI("http://host_auto_ip4:6508/v1/mafclub/api"));
	uri_builder test(U("/ServiceTest"));
	uri_builder registr(U("/insert/registration"));
	uri_builder signIn(U("/account/signIn"));
	uri_builder signOut(U("/account/signOut"));
	uri_builder getUserInfo(U("/account/getUserInfo"));
	uri_builder getUserShortInfo(U("/account/getUserShortInfo"));
	uri_builder deleteUser(U("/account/deleteUser"));

	json::value regReq;
	regReq["firstName"] = json::value::string("Valod");
	regReq["lastName"] = json::value::string("Valodyan");
	regReq["gender"] = json::value::string("male");
	regReq["email"] = json::value::string("v.valodyan@mail.ru");
	regReq["birthDate"] = json::value::string("12.12.1990");
	regReq["login"] = json::value::string("v.valodyan");
	regReq["password"] = json::value::string("Valodik90");

	json::value signInReq;
	signInReq["login"] = json::value::string("v.valodyan");
	signInReq["password"] = json::value::string("Valodik90");
	
	
	int count = 0;
	do{
		try {
			++count;
			pplx::task<web::http::http_response> requestTask = client.request(methods::POST, registr.to_string(), regReq);
			requestTask.then([](http_response resp){std::cout<<resp.to_string()<<std::endl;});
			requestTask.wait();

		} catch (http_exception e) {
			std::cerr<<e.what()<<std::endl;
		}
	}
	while ( count < 1);
	return 0;
}
