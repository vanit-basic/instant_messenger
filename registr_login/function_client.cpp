#include <iostream>
#include <unistd.h>
#include <string>
#include <thread>
#include "connection.hpp"
#include "isvalid.hpp"
#include "function_client.hpp"

std::string after_sign,sign_in1,name,surname,login,email,birthday,gender,phone,password,password1,allInfo,your_id;
static std::string id = "";
void recv_message(connection* c1,std::string message){
	std::cout << "SERVER: "<< message <<std::endl;
	if (message == "REGISTRATION->R::LOGIN->L::QUIT->Q"){
		r_l_q(c1);
	}
	if(message =="YOUR EMAIL IS BUSY,PLEASE ENTER ANOTHER EMAIL"){
		email = email_busy(c1);
	}
	if(message =="YOUR LOGIN IS BUSY,PLEASE ENTER ANOTHER LOGIN"){
		login = login_busy(c1);
	}
	if(message.find("Your information") != std::string::npos){
		your_id = message.substr(message.rfind(":")+1);
	}


	if (message == "ALL USERS->all users:::SEND MESSAGE->send message:::LOGOUT->logout"){
		std::thread* thr = new std::thread(sign_in,c1);
	}
}
void binder_recv_message(connection* c, std::string firstMessage) {
	if(firstMessage!="q")
	{std::cout<<firstMessage<<std::endl;
		std::string pipe1 = firstMessage.substr(0,firstMessage.find(":"));

		std::string pipe2 = firstMessage.substr(firstMessage.find(":")+1,firstMessage.find(".")-(firstMessage.find(":")+1));
		id = firstMessage.substr(firstMessage.find(".")+1);
		connection client(pipe1,pipe2);
		client.setRecvMessageCallback(recv_message);
		client.send("barev");
	}

}
void r_l_q(connection* c1){
	std::string str="";
	do{
		getline(std::cin,str);
		if(str !="R" && str !="Q" && str !="L")
			std::cout<<"ENTER RIGHT REQUEST"<<std::endl;
	}
	while(str !="R" && str !="Q" && str !="L");
		if(str == "R"){
			email = reg_email(c1);
			login = reg_login(c1);
			name = reg_name();
			surname = reg_surname();
			birthday = reg_birthday();
			gender = reg_gender();
			phone = reg_phone();
			reg_password();
			password = reg_password1(c1);
			all_information(c1);
		}
		if(str == "L")
			login_password(c1);
		if(str == "Q")
			c1->send(str);
}
std::string reg_email(connection* c1){
	std::cout<<"Enter your EMAIL*"<<std::endl;
	getline(std::cin,email);
	while(isValidEmail(email) !=true){
		std::cout<<"INVALID EMAIL::Enter your EMAIL again"<<std::endl;
		email = "";
		getline(std::cin,email);
	}
	email= "1email:"+email+":";
	c1->send(email);
	email = email.substr(1);
	return email;
}
std::string reg_login(connection* c1){
	std::cout<<"Enter your LOGIN*"<<std::endl;
	getline(std::cin,login);
	while(isValidLogin(login) !=true){
		std::cout<<"INVALID LOGIN::Enter your LOGIN again"<<std::endl;
		login = "";
		getline(std::cin,login);
	}     
	login = "1login:"+login+":";
	c1->send(login);
	login = login.substr(1);
	return login;
}
std::string reg_name(){
	std::cout<<"Enter your NAME*"<<std::endl;
	getline(std::cin,name);
	while(isValidName(name) !=true){
		std::cout<<"INVALID NAME::Enter your NAME again"<<std::endl;
		getline(std::cin,name);
	}
	name = "name:"+name+":";
	return name;
}
std::string reg_surname(){
	std::cout<<"Enter your SURNAME*"<<std::endl;
	getline(std::cin,surname);
	while(isValidName(surname) !=true){
		std::cout<<"INVALID SURNAME::Enter your SURNAME again"<<std::endl;
		getline(std::cin,surname);
	}
	surname="surname:"+surname+":";
	return surname;
}
std::string reg_birthday(){
	std::cout<<"Enter your DATE OF BIRTH*"<<std::endl;
	getline(std::cin,birthday);
	while(isValidBirthday(birthday) !=true){
		std::cout<<"INVALID BIRTHDAY::Enter your BIRTHDAY again"<<std::endl;
		getline(std::cin,birthday);
	}
	birthday="birthday:"+birthday+":";
	return birthday;
}
std::string reg_gender(){
	std::cout<<"Enter your GENDER*"<<std::endl;
	getline(std::cin,gender);
	while(isValidGender(gender) !=true){
		std::cout<<"INVALID GENDER::Enter your GENDER again"<<std::endl;
		getline(std::cin,gender);
	}
	gender="gender:"+gender+":";
	return gender;
}
std::string reg_phone(){
	std::cout<<"Enter your PHONE NUMBER*"<<std::endl;
	getline(std::cin,phone);
	while(isValidPhone(phone) !=true){
		std::cout<<"INVALID PHONE::Enter your PHONE again"<<std::endl;
		getline(std::cin,phone);
	}
	phone="phone:"+phone+":";
	return phone;
}
void reg_password(){
	std::cout<<"Enter your PASSWORD*"<<std::endl;
	getline(std::cin,password);
	while(isValidPassword(password) !=true){
		std::cout<<"INVALID PASSWORD::Enter your PASSWORD again"<<std::endl;
		getline(std::cin,password);
	}
	//		return password;
}
std::string reg_password1(connection* c1){
	std::cout<<"Enter your PASSWORD again*"<<std::endl;
	getline(std::cin,password1);
	while (password1 !=password){
		std::cout<<"Passwords are not equal::enter PASSWORD again"<<std::endl;
		getline(std::cin,password1);
	}
	password1 = "password2:"+password1+":";
	c1->send(password1);
	password="password:"+password+":";
	return password;
}
void all_information(connection* c1){

	if(login == "login::")
		login = "login:"+email.substr(email.find(":")+1);
	allInfo = "allinformation:"+email+login+name+surname+birthday+gender+phone+password;
	c1->send(allInfo);
}
std::string email_busy(connection* c1){
	getline(std::cin,email);
	while(isValidEmail(email) !=true){
		std::cout<<"INVALID EMAIL::Enter your EMAIL again"<<std::endl;
		email = "";
		getline(std::cin,email);
	}
	email= "1email:"+email+":";
	c1->send(email);
	email = email.substr(1);
	return email;
}
std::string login_busy(connection* c1){
	getline(std::cin,login);
	while(isValidLogin(login) !=true){
		std::cout<<"INVALID LOGIN::Enter your LOGIN again"<<std::endl;
		login = "";
		getline(std::cin,login);
	}
	login= "1login:"+login+":";
	c1->send(login);
	login = login.substr(1);
	return login;
}
void login_password(connection* c1){
	std::cout<<"Enter your LOGIN*"<<std::endl;
	getline(std::cin,login);
	std::cout<<"Enter your PASSWORD*"<<std::endl;
	getline(std::cin,password);
	sign_in1 = "sign_in:"+login+":"+password;
	c1->send(sign_in1);
}
std::string sign_in(connection* c1){
	do{
		getline(std::cin,after_sign);
		if(after_sign !="all users" && after_sign !="send message" && after_sign != "logout")
			std::cout<<"ENTER RIGHT REQUEST"<<std::endl;
	}
	while(after_sign !="all users" && after_sign !="send message" && after_sign != "logout");
	if(after_sign == "send message")
		c1->send(send_message());
	else
		c1->send(after_sign);
}
std::string send_message(){
	std::string str="";
	std::string str_id="";
	std::cout<<"Write reciever's id,for quit write <esc>"<<std::endl;
	getline(std::cin,str_id);
	if(str_id == "esc"){
		return str_id;
	}
	else{
		std::cout<<"Write message"<<std::endl;
		getline(std::cin,str);
		std::string id_message="from user:"+your_id+":"+str+":"+str_id;
		return id_message;
	}
}
