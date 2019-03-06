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

                "mongodbserver" : "mongodb://localhost:27017",

*/
void postRequest(http_client client, uri_builder uri, json::value value)
{
	client.request(methods::POST, uri.to_string(), value).then([](http_response response){
			response.extract_json().then([](json::value message){
					std::cout<<message.to_string()<<std::endl;
					}).wait();
			}).wait();
}

int main()
{
        http_client dbServiceClient(NetworkUtils::hostURI("http://host_auto_ip4:6508/v1/mafclub/api"));
        http_client tokenClient(NetworkUtils::hostURI("http://host_auto_ip4:6507/v1/mafclub/api"));
        http_client routerClient(NetworkUtils::hostURI("http://host_auto_ip4:6504/v1/mafclub/api"));
        http_client accountClient(NetworkUtils::hostURI("http://host_auto_ip4:6502/v1/mafclub/api"));
        http_client messagingClient(NetworkUtils::hostURI("http://host_auto_ip4:6503/v1/mafclub/api"));
        uri_builder test(U("/ServiceTest"));
        uri_builder registr(U("/insert/registration"));
        uri_builder signIn(U("/check/signIn"));
        uri_builder signOut(U("/account/signOut?clientId=u1"));
        uri_builder getUserInfo(U("/account/getUserInfo?clientId=u1"));
        uri_builder getUserShortInfo(U("/account/getUserShortInfo?clientId=u1&userId=u2"));
        uri_builder deleteUser(U("/account/deleteUser?clientId=u1"));
        uri_builder creatGroup(U("/account/creatGroup"));
        uri_builder deleteGroup(U("/account/deleteGroup?clientId=u1&groupId=g1"));
        uri_builder getGroupInfo(U("/account/getGroupInfo?clientId=u1&groupId=g1"));
        uri_builder getGroupShortInfo(U("/account/getGroupShortInfo?clientId=u1&groupId=g1"));
        uri_builder updateGroupInfo(U("/account/updateGroupInfo?clientId=u1"));
        uri_builder groupRemoveUser(U("/account/groupRemoveUser"));
        uri_builder updateUserInfo(U("/account/updateUserInfo?clientId=u1"));
        uri_builder checkToken(U("/checkToken"));
        uri_builder deleteToken(U("/deleteToken"));
        uri_builder setToken(U("/setToken"));

	json::value Token;
	Token["userId"] = json::value::string("u1");
	Token["token"] = json::value::string("asdasdasdasdasd54564asd");
	
	json::value regReq2;
        regReq2["firstName"] = json::value::string("Valod");
        regReq2["lastName"] = json::value::string("Valodyan");
        regReq2["gender"] = json::value::string("male");
        regReq2["email"] = json::value::string("valodyan1212@mail.ru");
        regReq2["birthDate"] = json::value::string("12.12.1990");
        regReq2["login"] = json::value::string("valodyan1212");
        regReq2["password"] = json::value::string("Valodik90");
        
	json::value regReq1;
        regReq1["firstName"] = json::value::string("Jon");
        regReq1["lastName"] = json::value::string("Valodyan");
        regReq1["gender"] = json::value::string("male");
        regReq1["email"] = json::value::string("valodyan@mail.ru");
        regReq1["birthDate"] = json::value::string("12.12.1990");
        regReq1["login"] = json::value::string("valodyan");
        regReq1["password"] = json::value::string("Valodik90");

        json::value signInReq;
        signInReq["login"] = json::value::string("v.valodyan");
        signInReq["password"] = json::value::string("Valodik90");

        json::value creatGroupReq;
        creatGroupReq["groupName"] = json::value::string("Best");
        creatGroupReq["clientId"] = json::value::string("u1");
        creatGroupReq["access"] = json::value::string("public");

        json::value updateGroupInfoReq;
        updateGroupInfoReq["groupId"] = json::value::string("g1");
        updateGroupInfoReq["name"] = json::value::string("mafiaForever");
        updateGroupInfoReq["avatar"] = json::value::string("base64_string");

        json::value groupRemoveUserReq;
        groupRemoveUserReq["groupId"] = json::value::string("g1");
        groupRemoveUserReq["clientId"] = json::value::string("u1");
        groupRemoveUserReq["userId"] = json::value::string("u2");

        json::value updateUserInfoReq;
        updateUserInfoReq["firstName"] = json::value::string("Valod");
        updateUserInfoReq["lastName"] = json::value::string("Valodyan");
        updateUserInfoReq["avatar"] = json::value::string("base64_string");
        updateUserInfoReq["nickName"] = json::value::string("asenqValod");

	http_request req(methods::GET);
	req.headers().add(U("token"), U("112431574564"));
	req.set_request_uri(U("Account/getUserInfo?clientId=u1"));
        int count = 0;
	do{
		try {
                        ++count;
			//////////      TOKEN  DB  SERVICE TEST   /////////////
			postRequest(tokenClient, setToken, Token);
			postRequest(tokenClient, checkToken, Token);
			postRequest(tokenClient, deleteToken, Token);


			///////     REGISTRATION TEST    //////
			//postRequest(dbServiceClient, registr, regReq1);
			//postRequest(dbServiceClient, registr, regReq2);
	
			
		} 
		catch (http_exception e) {
			std::cerr<<"error  "<<e.what()<<std::endl;
                }
			usleep(1000000);
	}
	while(count < 1);
/*	while(1)
	{
		usleep(1000);
	}*/
        return 0;
}

