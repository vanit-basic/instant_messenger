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

void Request(http_client client, http_request req)
{
	client.request(req).then([](http_response response){
			response.extract_json().then([](json::value message){
					std::cout<<message.to_string()<<std::endl;
					}).wait();
			}).wait();
}

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
        http_client routerClient(NetworkUtils::hostURI("http://host_auto_ip4:6504/v1/mafclub/api"));
        
	http_client dbServiceClient(NetworkUtils::hostURI("http://host_auto_ip4:6508/v1/mafclub/api"));
        http_client tokenClient(NetworkUtils::hostURI("http://host_auto_ip4:6507/v1/mafclub/api"));
        http_client accountClient(NetworkUtils::hostURI("http://host_auto_ip4:6502/v1/mafclub/api"));
        http_client messagingClient(NetworkUtils::hostURI("http://host_auto_ip4:6503/v1/mafclub/api"));
        

	uri_builder isUserInGroup(U("/account/isUserInGroup?groupId=g1&userId=u1"));
        uri_builder changePassword(U("/account/changePassword"));
        uri_builder checkToken(U("/checkToken"));
        uri_builder deleteToken(U("/deleteToken"));
        uri_builder setToken(U("/setToken"));
        uri_builder getGroupUsers(U("/account/getGroupUsers?groupId=g1"));
	uri_builder searchUsers(U("/account/searchUsers"));
	uri_builder searchGroups(U("/account/searchGroups"));

	json::value Token;
	Token["userId"] = json::value::string("u1");
	Token["token"] = json::value::string("1");
	
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
        
	json::value searchUsersReq;
	searchUsersReq["users"][0] = json::value::string("u9");
	searchUsersReq["users"][1] = json::value::string("u10");
	
	json::value searchGroupsReq;
	searchGroupsReq["groups"][0] = json::value::string("g1");
	searchGroupsReq["groups"][1] = json::value::string("g2");
	
	json::value signInReq1;
        signInReq1["login"] = json::value::string("valodyan1212");
        signInReq1["password"] = json::value::string("Valodik90");

	json::value signInReq2;
        signInReq2["login"] = json::value::string("valodyan");
        signInReq2["password"] = json::value::string("Valodik9"); 
        
	json::value changePasswordReq1;
	changePasswordReq1["userId"] = json::value::string("u1");
	changePasswordReq1["password"] = json::value::string("Valodik90");
	changePasswordReq1["newPassword"] = json::value::string("Valod90");

	json::value changePasswordReq2;
	changePasswordReq2["userId"] = json::value::string("u2");
	changePasswordReq2["password"] = json::value::string("Vaasdasdasd");
	changePasswordReq2["newPassword"] = json::value::string("Valod90");
	
	json::value createGroupReq1;
        createGroupReq1["userId"] = json::value::string("u1");
        createGroupReq1["groupName"] = json::value::string("Best");
        createGroupReq1["access"] = json::value::string("public");

	json::value createGroupReq2;
        createGroupReq2["userId"] = json::value::string("u2");
        createGroupReq2["groupName"] = json::value::string("Mafia");
        createGroupReq2["access"] = json::value::string("private");

	json::value createGroupReq3;
        createGroupReq3["userId"] = json::value::string("u2");
        createGroupReq3["groupName"] = json::value::string("Mafia");
        createGroupReq3["access"] = json::value::string("private");
        
	json::value groupUpdateInfoReq1;
	groupUpdateInfoReq1["userId"] = json::value::string("u1");
        groupUpdateInfoReq1["groupId"] = json::value::string("g1");
        groupUpdateInfoReq1["newName"] = json::value::string("mafiaForever");
        groupUpdateInfoReq1["newAccess"] = json::value::string("private");
        groupUpdateInfoReq1["newAvatar"] = json::value::string("base64_string1");

	json::value groupUpdateInfoReq2;
	groupUpdateInfoReq2["userId"] = json::value::string("u2");
        groupUpdateInfoReq2["groupId"] = json::value::string("g1");
        groupUpdateInfoReq2["newName"] = json::value::string("mafiaForever");
        groupUpdateInfoReq2["newAccess"] = json::value::string("private");
        groupUpdateInfoReq2["newAvatar"] = json::value::string("base64_string1");
        
	json::value groupRemoveUserReq;
        groupRemoveUserReq["groupId"] = json::value::string("g1");
        groupRemoveUserReq["clientId"] = json::value::string("u1");
        groupRemoveUserReq["userId"] = json::value::string("u2");

        json::value updateUserInfoReq1;
	updateUserInfoReq1["userId"] = json::value::string("u1");
        updateUserInfoReq1["firstName"] = json::value::string("Valodik");
        updateUserInfoReq1["lastName"] = json::value::string("Valodyan");
        updateUserInfoReq1["avatar"] = json::value::string("asdasdasdasd");
        updateUserInfoReq1["nickName"] = json::value::string("Valod90");
        
	json::value updateUserInfoReq2;
	updateUserInfoReq2["userId"] = json::value::string("u2");
        updateUserInfoReq2["firstName"] = json::value::string("Jonik");
        updateUserInfoReq2["lastName"] = json::value::string("Valodyan");
        updateUserInfoReq2["avatar"] = json::value::string("base64_string");
        updateUserInfoReq2["nickName"] = json::value::string("Jon90");

// 	REGISTRATION REQUEST	
	uri registrationUri("/account/signUp");
	http_request userRegistration1(methods::POST);
	userRegistration1.set_body(registrationRequest1);
	userRegistration1.set_request_uri(registrationUri);
	http_request userRegistration2(methods::POST);
	userRegistration2.set_body(registrationRequest2);
	userRegistration2.set_request_uri(registrationUri);
//	GET USER INFO REQUEST
	http_request getUserInfoRequest1(methods::GET);
	uri getUserInfoUri1("/account/getUserInfo?userId=u1");
	getUserInfoRequest1.set_request_uri(getUserInfoUri1);
	getUserInfoRequest1.headers().add("token", "1");
	http_request getUserInfoRequest2(methods::GET);
	uri getUserInfoUri2("/account/getUserInfo?userId=u2");
	getUserInfoRequest2.set_request_uri(getUserInfoUri2);
	getUserInfoRequest2.headers().add("token", "2");
//	UPDATE USER INFO REQUEST	
	http_request updateUserInfoRequest(methods::POST);
	uri updateUserInfoUri("/account/userUpdateInfo");
	updateUserInfoRequest.set_request_uri(updateUserInfoUri);
	updateUserInfoRequest.set_body(updateUserInfoReq1);
	updateUserInfoRequest.headers().add("token", "1");
//	GET USER SHORT INFO REQUEST	
	http_request getUserShortInfoRequest1(methods::GET);
	uri getUserShortInfoUri1("/account/getUserShortInfo?userId=u1&clientId=u2");
	getUserShortInfoRequest1.set_request_uri(getUserShortInfoUri1);
	getUserShortInfoRequest1.headers().add("token", "1");
	http_request getUserShortInfoRequest2(methods::GET);
	uri getUserShortInfoUri2("/account/getUserShortInfo?userId=u2&clientId=u1");
	getUserShortInfoRequest2.set_request_uri(getUserShortInfoUri2);
	getUserShortInfoRequest2.headers().add("token", "2");
//	SIGN IN REQUEST
	uri signInUri("/account/signIn");
	http_request signInRequest1(methods::POST);
	signInRequest1.set_request_uri(signInUri);
	signInRequest1.set_body(signInReq1);
	http_request signInRequest2(methods::POST);
	signInRequest2.set_request_uri(signInUri);
	signInRequest2.set_body(signInReq2);
//	CREATE GROUP REQUEST
	http_request createGroupRequest1(methods::POST);
	uri createGroupUri("/account/createGroup");
	createGroupRequest1.set_request_uri(createGroupUri);
	createGroupRequest1.set_body(createGroupReq1);
	createGroupRequest1.headers().add("token", "1");
	http_request createGroupRequest2(methods::POST);
	createGroupRequest2.set_request_uri(createGroupUri);
	createGroupRequest2.set_body(createGroupReq2);
	createGroupRequest2.headers().add("token", "2");
	http_request createGroupRequest3(methods::POST);
	createGroupRequest3.set_request_uri(createGroupUri);
	createGroupRequest3.set_body(createGroupReq2);
	createGroupRequest3.headers().add("token", "2");
//	UPDATE GROUP INFO REQUEST
	http_request updateGroupInfoRequest1(methods::POST);
	uri updateGroupInfoUri1("/account/groupUpdateInfo");
	updateGroupInfoRequest1.set_request_uri(updateGroupInfoUri1);
	updateGroupInfoRequest1.set_body(groupUpdateInfoReq1);
	updateGroupInfoRequest1.headers().add("token", "1");
	http_request updateGroupInfoRequest2(methods::POST);
	uri updateGroupInfoUri2("/account/groupUpdateInfo");
	updateGroupInfoRequest2.set_request_uri(updateGroupInfoUri2);
	updateGroupInfoRequest2.set_body(groupUpdateInfoReq2);
	updateGroupInfoRequest2.headers().add("token", "2");
//	ADD USER TO GROUP REQUEST
	http_request addUserToGroupRequest1(methods::GET);
	uri addUserToGroupUri1("/account/addUserToGroup?userId=u1&groupId=g1&clientId=u2");
	addUserToGroupRequest1.set_request_uri(addUserToGroupUri1);
	addUserToGroupRequest1.headers().add("token", "1");
	http_request addUserToGroupRequest2(methods::GET);
	uri addUserToGroupUri2("/account/addUserToGroup?userId=u1&groupId=g2&clientId=u2");
	addUserToGroupRequest2.set_request_uri(addUserToGroupUri2);
	addUserToGroupRequest2.headers().add("token", "1");
//	GET GROUP INFO REQUEST
	http_request getGroupInfoRequest1(methods::GET);
	uri getGroupInfoUri1("/account/getGroupInfo?userId=u1&groupId=g1");
	getGroupInfoRequest1.set_request_uri(getGroupInfoUri1);
	getGroupInfoRequest1.headers().add("token", "1");
	http_request getGroupInfoRequest2(methods::GET);
	uri getGroupInfoUri2("/account/getGroupInfo?userId=u1&groupId=g2");
	getGroupInfoRequest2.set_request_uri(getGroupInfoUri2);
	getGroupInfoRequest2.headers().add("token", "1");
	http_request getGroupInfoRequest3(methods::GET);
	uri getGroupInfoUri3("/account/getGroupInfo?userId=u2&groupId=g2");
	getGroupInfoRequest3.set_request_uri(getGroupInfoUri3);
	getGroupInfoRequest3.headers().add("token", "2");
//	REMOVE FROM GROUP REQUEST
	http_request removeFromGroupRequest1(methods::GET);
	uri removeFromGroupUri1("/account/groupRemoveUser?groupId=g1&userId=u1&clientId=u2");
	removeFromGroupRequest1.set_request_uri(removeFromGroupUri1);
	removeFromGroupRequest1.headers().add("token", "1");
	http_request removeFromGroupRequest2(methods::GET);
	uri removeFromGroupUri2("/account/groupRemoveUser?groupId=g2&userId=u1&clientId=u2");
	removeFromGroupRequest2.set_request_uri(removeFromGroupUri2);
	removeFromGroupRequest2.headers().add("token", "1");
//	GET GROUP SHORT INFO REQUEST
	http_request getGroupShortInfoRequest1(methods::GET);
	uri getGroupShortInfoUri1("/account/getGroupShortInfo?userId=u1&groupId=g1");
	getGroupShortInfoRequest1.set_request_uri(getGroupShortInfoUri1);
	getGroupShortInfoRequest1.headers().add("token", "1");
	http_request getGroupShortInfoRequest2(methods::GET);
	uri getGroupShortInfoUri2("/account/getGroupShortInfo?userId=u1&groupId=g2");
	getGroupShortInfoRequest2.set_request_uri(getGroupShortInfoUri2);
	getGroupShortInfoRequest2.headers().add("token", "1");
//	LEAVE GROUP REQUEST
	http_request leaveGroupRequest(methods::GET);
	uri leaveGroupUri("/account/leaveGroup?userId=u2&groupId=g1");
	leaveGroupRequest.set_request_uri(leaveGroupUri);
	leaveGroupRequest.headers().add("token", "2");
//	CHANGE GROUP ADMIN REQUEST
	http_request changeGroupAdminRequest1(methods::GET);
	uri changeGroupAdminUri1("/account/changeGroupAdmin?groupId=g2&userId=u2&clientId=u1");
	changeGroupAdminRequest1.set_request_uri(changeGroupAdminUri1);
	changeGroupAdminRequest1.headers().add("token", "2");
	http_request changeGroupAdminRequest2(methods::GET);
	uri changeGroupAdminUri2("/account/changeGroupAdmin?groupId=g1&userId=u2&clientId=u2");
	changeGroupAdminRequest2.set_request_uri(changeGroupAdminUri2);
	changeGroupAdminRequest2.headers().add("token", "2");
//	DELETE GROUP REQUEST
	http_request deleteGroupRequest(methods::GET);
	uri deleteGroupUri("/account/deleteGroup?groupId=g3&userId=u2");
	deleteGroupRequest.set_request_uri(deleteGroupUri);
	deleteGroupRequest.headers().add("token", "2");

//	CHANGE PASSWORD REQUEST  
	http_request changePasswordRequest1(methods::POST);
	uri changePasswordUri("/account/changePassword");
	changePasswordRequest1.set_request_uri(changePasswordUri);
	changePasswordRequest1.set_body(changePasswordReq1);
	changePasswordRequest1.headers().add("token", "1");
	http_request changePasswordRequest2(methods::POST);
	changePasswordRequest2.set_request_uri(changePasswordUri);
	changePasswordRequest2.set_body(changePasswordReq2);
	changePasswordRequest2.headers().add("token", "2");

//	DELETE USER REQUEST
	http_request deleteUserRequest(methods::GET);
	uri deleteUserUri("account/deleteUser?userId=u2");
	deleteUserRequest.set_request_uri(deleteUserUri);
	deleteUserRequest.headers().add("token", "2");
//	SIGN OUT REQUEST
	http_request signOutRequest(methods::GET);
	uri signOutUri("account/signOut?userId=u1");
	signOutRequest.set_request_uri(signOutUri);
	signOutRequest.headers().add("token", "1");

        int count = 0;
	do{
		try {
                        ++count;

			std::cout<<"///////////////////     REGISTRATION TEST      /////////////////"<<std::endl;
			Request(routerClient, userRegistration1);
			Request(routerClient, userRegistration2);
			std::cout<<std::endl;
			
			std::cout<<"///////////////////     GET USER INFO TEST      /////////////////"<<std::endl;
			Request(routerClient, getUserInfoRequest1);
			Request(routerClient, getUserInfoRequest2);
			std::cout<<std::endl;
			
 			std::cout<<"///////////////////     UPDATE USER INFO TEST      /////////////////"<<std::endl;
			Request(routerClient, updateUserInfoRequest);
			std::cout<<std::endl;
			
			std::cout<<"///////////////////     GET USER SHORT INFO TEST      /////////////////"<<std::endl;
			Request(routerClient, getUserShortInfoRequest1);
			Request(routerClient, getUserShortInfoRequest2);
			std::cout<<std::endl;
			
/*			std::cout<<"///////////////////     Sign Out  TEST      /////////////////"<<std::endl;
                        Request(routerClient, signOutRequest);
                        std::cout<<std::endl;
			
			std::cout<<"///////////////////     SIGN IN TEST      /////////////////"<<std::endl;
			Request(routerClient, signInRequest1);
			Request(routerClient, signInRequest2);		
			std::cout<<std::endl;
*/			
			std::cout<<"///////////////////     CREATE GROUP TEST      /////////////////"<<std::endl;
			Request(routerClient, createGroupRequest1);
			Request(routerClient, createGroupRequest2);
			Request(routerClient, createGroupRequest3);
                        std::cout<<std::endl;

			std::cout<<"///////////////////     GET GROUP INFO TEST      /////////////////"<<std::endl;
			Request(routerClient, getGroupInfoRequest1);
			Request(routerClient, getGroupInfoRequest2);
			Request(routerClient, getGroupInfoRequest3);
			std::cout<<std::endl;
			
			std::cout<<"///////////////////     ADD USER TO GROUP TEST      /////////////////"<<std::endl;
                        Request(routerClient, addUserToGroupRequest1);
			Request(routerClient, addUserToGroupRequest2);
                        std::cout<<std::endl;
			
			std::cout<<"///////////////////     UPDATE GROUP INFO TEST      /////////////////"<<std::endl;
			Request(routerClient, updateGroupInfoRequest1);
			Request(routerClient, updateGroupInfoRequest2);
                        std::cout<<std::endl;

			std::cout<<"///////////////////     REMOVE FROM GROUP TEST      /////////////////"<<std::endl;
			Request(routerClient, removeFromGroupRequest1);
			Request(routerClient, removeFromGroupRequest2);
			std::cout<<std::endl;
			
			std::cout<<"///////////////////     GET GROUP INFO TEST      /////////////////"<<std::endl;
			Request(routerClient, getGroupInfoRequest1);
			Request(routerClient, getGroupInfoRequest2);
			Request(routerClient, getGroupInfoRequest3);
			std::cout<<std::endl;
			
			std::cout<<"///////////////////     GET GROUP SHORT INFO TEST      /////////////////"<<std::endl;
			Request(routerClient, getGroupShortInfoRequest1);
			Request(routerClient, getGroupShortInfoRequest2);
			std::cout<<std::endl;
			
			std::cout<<"///////////////////     DELETE GROUP TEST      /////////////////"<<std::endl;
                        Request(routerClient, deleteGroupRequest);
                        std::cout<<std::endl;			

			std::cout<<"///////////////////     Delete user TEST      /////////////////"<<std::endl;
                        Request(routerClient, deleteUserRequest);
                        std::cout<<std::endl;
			
			std::cout<<"///////////////////     GET GROUP INFO TEST      /////////////////"<<std::endl;
			Request(routerClient, getGroupInfoRequest1);
			Request(routerClient, getGroupInfoRequest2);
			Request(routerClient, getGroupInfoRequest3);
			std::cout<<std::endl;
			
			std::cout<<"///////////////////     GET USER INFO TEST      /////////////////"<<std::endl;
			Request(routerClient, getUserInfoRequest1);
			Request(routerClient, getUserInfoRequest2);
			std::cout<<std::endl;
						
			std::cout<<"///////////////////     CHANGE PASSWORD TEST      /////////////////"<<std::endl;
			Request(routerClient, changePasswordRequest1);
			Request(routerClient, changePasswordRequest2);
			std::cout<<std::endl;
			
			std::cout<<"///////////////////     CHANGE GROUP ADMIN TEST      /////////////////"<<std::endl;
			Request(routerClient, changeGroupAdminRequest1);
			Request(routerClient, changeGroupAdminRequest2);
			std::cout<<std::endl;
			
			std::cout<<"///////////////////     GET GROUP INFO TEST      /////////////////"<<std::endl;
			Request(routerClient, getGroupInfoRequest1);
			Request(routerClient, getGroupInfoRequest2);
			Request(routerClient, getGroupInfoRequest3);
			std::cout<<std::endl;
			
/*			std::cout<<"///////////////////     LEAVE GROUP TEST      /////////////////"<<std::endl;
			Request(routerClient, leaveGroupRequest);
			std::cout<<std::endl;
			
			std::cout<<"///////////////////     SEARCH USERS (DB  SERVICE) TEST      /////////////////"<<std::endl;
			postRequest(dbServiceClient, searchUsers, searchUsersReq);
			std::cout<<std::endl;
	
			std::cout<<"///////////////////     SEARCH GROUPS (DB  SERVICE) TEST      /////////////////"<<std::endl;
			postRequest(dbServiceClient, searchGroups, searchGroupsReq);
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

