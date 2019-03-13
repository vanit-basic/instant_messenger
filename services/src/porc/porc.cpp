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

void getRequest(http_client client, uri_builder uri)
{
	client.request(methods::GET, uri.to_string()).then([](http_response response){
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
	uri_builder checkMailAndLogin(U("/check/mailAndLogin"));
        uri_builder signOut(U("/account/signOut?clientId=u1"));
        
	uri_builder getUserInfo1(U("/account/getUserInfo?userId=u1"));
        uri_builder getUserInfo2(U("/account/getUserInfo?userId=u2"));
        
	uri_builder getUserShortInfo1(U("/account/getUserShortInfo?clientId=u1"));
	uri_builder getUserShortInfo2(U("/account/getUserShortInfo?clientId=u2"));

	uri_builder isUserInGroup(U("/account/isUserInGroup?groupId=g1&userId=u1"));
	uri_builder addUserToGroup1(U("/account/addUserToGroup?userId=u1&groupId=g1&clientId=u2"));
	uri_builder addUserToGroup2(U("/account/addUserToGroup?userId=u2&groupId=g2&clientId=u1"));
        uri_builder deleteUser(U("/account/deleteUser?userId=u1"));
        uri_builder deleteGroup(U("/account/deleteGroup?groupId=g7&userId=u2"));
        uri_builder createGroup(U("/account/createGroup"));
        uri_builder getGroupInfo(U("/account/getGroupInfo?clientId=u1&groupId=g1"));
        uri_builder getGroupShortInfo(U("/account/getGroupShortInfo?clientId=u1&groupId=g1"));
        uri_builder groupRemoveUser(U("/account/groupRemoveUser"));
      	uri_builder updateUserInfo(U("/account/updateUserInfo"));
        uri_builder changePassword(U("/account/changePassword"));
      	uri_builder updateGroupInfo(U("/account/updateGroupInfo"));
        uri_builder checkToken(U("/checkToken"));
        uri_builder deleteToken(U("/deleteToken"));
        uri_builder setToken(U("/setToken"));
        uri_builder getGroupUsers(U("/account/getGroupUsers?groupId=g1"));

        uri_builder removeFromGroup(U("/account/removeFromGroup?groupId=g1&userId=u2"));

	json::value Token;
	Token["userId"] = json::value::string("u1");
	Token["token"] = json::value::string("asdasdasdasdasd54564asd");
	
	json::value registrationRequest1;
        registrationRequest1["firstName"] = json::value::string("Valod");
        registrationRequest1["lastName"] = json::value::string("Valodyan");
        registrationRequest1["gender"] = json::value::string("male");
        registrationRequest1["email"] = json::value::string("valodyan1212@mail.ru");
        registrationRequest1["birthDate"] = json::value::string("12.12.1990");
        registrationRequest1["login"] = json::value::string("valodyan1212");
        registrationRequest1["password"] = json::value::string("Valodik90");
        
	json::value registrationRequest2;
        registrationRequest2["firstName"] = json::value::string("Jon");
        registrationRequest2["lastName"] = json::value::string("Valodyan");
        registrationRequest2["gender"] = json::value::string("male");
        registrationRequest2["email"] = json::value::string("valodyan@mail.ru");
        registrationRequest2["birthDate"] = json::value::string("12.12.1990");
        registrationRequest2["login"] = json::value::string("valodyan");
        registrationRequest2["password"] = json::value::string("Valodik90");

	json::value checkMailAndLoginReq1;
	checkMailAndLoginReq1["email"] = json::value::string("valodyan1212@mail.ru");
	checkMailAndLoginReq1["login"] = json::value::string("valodyan1212");
	

	json::value checkMailAndLoginReq2;
	checkMailAndLoginReq2["email"] = json::value::string("valodyan12@mail.ru");
	checkMailAndLoginReq2["login"] = json::value::string("valodyan1215");
        
	json::value signInReq1;
        signInReq1["login"] = json::value::string("valodyan1212");
        signInReq1["password"] = json::value::string("Valodik90");

	json::value signInReq2;
        signInReq2["login"] = json::value::string("valodyan");
        signInReq2["password"] = json::value::string("Valodik90"); 
        
	json::value changePasswordReq;
	changePasswordReq["userId"] = json::value::string("u10");
	changePasswordReq["password"] = json::value::string("Valodik90");
	changePasswordReq["newPassword"] = json::value::string("Valod90");

	json::value createGroupReq1;
        createGroupReq1["groupName"] = json::value::string("Best");
        createGroupReq1["userId"] = json::value::string("u1");
        createGroupReq1["access"] = json::value::string("public");
        createGroupReq1["avatar"] = json::value::string("base64_string");

	json::value createGroupReq2;
        createGroupReq2["groupName"] = json::value::string("Mafia");
        createGroupReq2["userId"] = json::value::string("u2");
        createGroupReq2["access"] = json::value::string("private");
        createGroupReq1["avatar"] = json::value::string("base64_string");

        json::value updateGroupInfoReq;
        updateGroupInfoReq["groupId"] = json::value::string("g10");
        updateGroupInfoReq["newName"] = json::value::string("mafiaForever");
        updateGroupInfoReq["newAvatar"] = json::value::string("base64_string1");

        json::value groupRemoveUserReq;
        groupRemoveUserReq["groupId"] = json::value::string("g1");
        groupRemoveUserReq["clientId"] = json::value::string("u1");
        groupRemoveUserReq["userId"] = json::value::string("u2");

        json::value updateUserInfoReq1;
	updateUserInfoReq1["userId"] = json::value::string("u1");
        updateUserInfoReq1["firstName"] = json::value::string("Valodik");
        updateUserInfoReq1["lastName"] = json::value::string("Valodyan");
        updateUserInfoReq1["avatar"] = json::value::string("base64_string");
        updateUserInfoReq1["nickName"] = json::value::string("Valod90");
        
	json::value updateUserInfoReq2;
	updateUserInfoReq2["userId"] = json::value::string("u2");
        updateUserInfoReq2["firstName"] = json::value::string("Jonik");
        updateUserInfoReq2["lastName"] = json::value::string("Valodyan");
        updateUserInfoReq2["avatar"] = json::value::string("base64_string");
        updateUserInfoReq2["nickName"] = json::value::string("Jon90");

	http_request req(methods::GET);
	req.headers().add(U("token"), U("112431574564"));
	req.set_request_uri(U("Account/getUserInfo?clientId=u1"));
        int count = 0;
	do{
		try {
                        ++count;
/*
			std::cout<<"///////////////////      TOKEN  DB  SERVICE TEST      /////////////////"<<std::endl;
			postRequest(tokenClient, setToken, Token);
			postRequest(tokenClient, checkToken, Token);
			postRequest(tokenClient, deleteToken, Token);
			std::cout<<std::endl;

			std::cout<<"///////////////////     REGISTRATION(DB  SERVICE) TEST      /////////////////"<<std::endl;
			postRequest(dbServiceClient, registr, registrationRequest1);
			postRequest(dbServiceClient, registr, registrationRequest2);
			std::cout<<std::endl;
*/			
			std::cout<<"///////////////////     CHANGE PASSWORD(DB  SERVICE) TEST      /////////////////"<<std::endl;
			postRequest(dbServiceClient, changePassword, changePasswordReq);
			std::cout<<std::endl;
	
/* 			std::cout<<"///////////////////     UPDATE USER INFO(DB  SERVICE) TEST      /////////////////"<<std::endl;
			postRequest(dbServiceClient, updateUserInfo, updateUserInfoReq1);
			postRequest(dbServiceClient, updateUserInfo, updateUserInfoReq2);
			std::cout<<std::endl;

			
			std::cout<<"///////////////////     CHECK MAIL AND LOGIN(DB  SERVICE) TEST      /////////////////"<<std::endl;
			postRequest(dbServiceClient, checkMailAndLogin, checkMailAndLoginReq1);
			postRequest(dbServiceClient, checkMailAndLogin, checkMailAndLoginReq2);
			std::cout<<std::endl;

	
			std::cout<<"///////////////////     SIGN IN(DB  SERVICE) TEST      /////////////////"<<std::endl;
			postRequest(dbServiceClient, signIn, signInReq1);
			postRequest(dbServiceClient, signIn, signInReq2);
		

			std::cout<<"///////////////////     GET USER SHORTINFO(DB  SERVICE) TEST      /////////////////"<<std::endl;
			getRequest(dbServiceClient, isUserInGroup);
			std::cout<<std::endl;

			std::cout<<"///////////////////     CREATE GROUP(DB  SERVICE) TEST      /////////////////"<<std::endl;
			postRequest(dbServiceClient, createGroup, createGroupReq1);
			postRequest(dbServiceClient, createGroup, createGroupReq2);
                        std::cout<<std::endl;			

			std::cout<<"///////////////////     UPDATE GROUP INFO(DB  SERVICE) TEST      /////////////////"<<std::endl;
			postRequest(dbServiceClient, updateGroupInfo, updateGroupInfoReq);
                        std::cout<<std::endl;			

			
			std::cout<<"///////////////////     Add user to group(DB  SERVICE) TEST      /////////////////"<<std::endl;
                        getRequest(dbServiceClient, addUserToGroup1);
                       // getRequest(dbServiceClient, addUserToGroup2);

			std::cout<<"///////////////////     GET USER INFO(DB  SERVICE) TEST      /////////////////"<<std::endl;
			getRequest(dbServiceClient, getUserInfo1);
			getRequest(dbServiceClient, getUserInfo2);
			std::cout<<std::endl;
			
			std::cout<<"///////////////////     GET USER SHORTINFO(DB  SERVICE) TEST      /////////////////"<<std::endl;
			getRequest(dbServiceClient, getUserShortInfo1);
			getRequest(dbServiceClient, getUserShortInfo2);
			std::cout<<std::endl;

			std::cout<<"///////////////////     Delete user(DB  SERVICE) TEST      /////////////////"<<std::endl;
                        getRequest(dbServiceClient, deleteUser);
                        std::cout<<std::endl;

			std::cout<<"///////////////////     GET USER SHORTINFO(DB  SERVICE) TEST      /////////////////"<<std::endl;
			getRequest(dbServiceClient, getUserShortInfo1);
			getRequest(dbServiceClient, getUserShortInfo2);
			std::cout<<std::endl; 

			std::cout<<"///////////////////     DELETE GROUP (DB  SERVICE) TEST      /////////////////"<<std::endl;
                        getRequest(dbServiceClient, deleteGroup);
                        std::cout<<std::endl;
	
			std::cout<<"///////////////////     GET GROUP USERS (DB  SERVICE) TEST      /////////////////"<<std::endl;
			getRequest(dbServiceClient, getGroupUsers);
			std::cout<<std::endl;

			std::cout<<"///////////////////     GET GROUP SHORT INFO(DB  SERVICE) TEST      /////////////////"<<std::endl;
			getRequest(dbServiceClient, getGroupShortInfo);
			std::cout<<std::endl;
			
			std::cout<<"///////////////////     GET GROUP INFO(DB  SERVICE) TEST      /////////////////"<<std::endl;
			getRequest(dbServiceClient, getGroupInfo);
			std::cout<<std::endl;
			
			std::cout<<"///////////////////     REMOVE FROM GROUP (DB  SERVICE) TEST      /////////////////"<<std::endl;
			getRequest(dbServiceClient, removeFromGroup);
			//getRequest(dbServiceClient, removeFromGroup);
			std::cout<<std::endl;

			std::cout<<"///////////////////     GET GROUP USERS (DB  SERVICE) TEST      /////////////////"<<std::endl;
			getRequest(dbServiceClient, getGroupUsers);
			std::cout<<std::endl;
*/

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

