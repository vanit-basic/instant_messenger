#include <iostream>
#include <unistd.h>
#include <string>
#include "connection.hpp"
#include "isvalid.hpp"

static std::string id = "";
void recv_message(connection* c1,std::string message){
        std::cout << "SERVER: "<< message <<std::endl;
                std::string sign_in,name,surname,login,email,birthday,gender,phone,password,password1,allInfo;
        if (message == "FOR REGISTRATION ENTER R::FOR LOGIN ENTER L::FOR QUIT ENTER Q"){
                std::string str="";
			std::cout<<"ENTER REQUEST"<<std::endl;	
         	do{
                        getline(std::cin,str);
			if(str !="R" && str !="Q" && str !="L")	
			std::cout<<"ENTER WRONG REQUEST"<<std::endl;
		}	  
                while(str !="R" && str !="Q" && str !="L");
                
         
                        c1->send(str);
        }
        if(message == "Profile information"){
                std::cout<<"Enter your EMAIL*"<<std::endl;
                getline(std::cin,email);
                while(isValidEmail(email) !=true){
		std::cout<<"INVALID EMAIL::Enter your EMAIL again"<<std::endl;
                email = "";
                getline(std::cin,email);
                }
		std::string email1= "email1:"+email+":";
		c1->send(email1);
		email = "email:"+email+":";

		std::cout<<"Enter your LOGIN*"<<std::endl;
                getline(std::cin,login);
                while(isValidLogin(login) !=true){
                std::cout<<"INVALID LOGIN::Enter your LOGIN again"<<std::endl;
                login = "";
                getline(std::cin,login);
                }
                
		std::string login1 = "login1:"+login+":";
		
                c1->send(login1);
		login = "login:"+login+":";

		

                std::cout<<"Enter your NAME*"<<std::endl;
                getline(std::cin,name);
                while(isValidName(name) !=true){
                std::cout<<"INVALID NAME::Enter your NAME again"<<std::endl;
                getline(std::cin,name);

                }
                name = "name:"+name+":";

                std::cout<<"Enter your SURNAME*"<<std::endl;
                getline(std::cin,surname);
                while(isValidName(surname) !=true){
                std::cout<<"INVALID SURNAME::Enter your SURNAME again"<<std::endl;
                getline(std::cin,surname);
                }
                surname="surname:"+surname+":";


                std::cout<<"Enter your DATE OF BIRTH*"<<std::endl;
                getline(std::cin,birthday);
                while(isValidBirthday(birthday) !=true){
                std::cout<<"INVALID BIRTHDAY::Enter your BIRTHDAY again"<<std::endl;
                getline(std::cin,birthday);
                }
                birthday="birthday:"+birthday+":";

                std::cout<<"Enter your GENDER*"<<std::endl;
                getline(std::cin,gender);
                while(isValidGender(gender) !=true){
                std::cout<<"INVALID GENDER::Enter your GENDER again"<<std::endl;
                getline(std::cin,gender);
                }
                gender="gender:"+gender+":";

                std::cout<<"Enter your PHONE NUMBER*"<<std::endl;
                getline(std::cin,phone);
                while(isValidPhone(phone) !=true){
                std::cout<<"INVALID PHONE::Enter your PHONE again"<<std::endl;
                getline(std::cin,phone);
                }
                phone="phone:"+phone+":";

                std::cout<<"Enter your PASSWORD*"<<std::endl;
                getline(std::cin,password);
                while(isValidPassword(password) !=true){
                std::cout<<"INVALID PASSWORD::Enter your PASSWORD again"<<std::endl;
                getline(std::cin,password);
                }

                std::cout<<"Enter your PASSWORD again*"<<std::endl;
                getline(std::cin,password1);
                while (password1 !=password){
                        std::cout<<"Passwords are not equal::enter PASSWORD again"<<std::endl;
                        getline(std::cin,password1);
                }
		std::string password2 = "password2:"+password1+":";
		c1->send(password2);

                password="password:"+password+":";

                usleep(100000);
                allInfo = "allinformation:"+email+login+name+surname+birthday+gender+phone+password;
                c1->send(allInfo);
        }
	while(message =="YOUR EMAIL IS BUSY,PLEASE ENTER ANOTHER EMAIL"){
                getline(std::cin,email);
                while(isValidEmail(email) !=true){
		std::cout<<"INVALID EMAIL::Enter your EMAIL again"<<std::endl;
                email = "";
                getline(std::cin,email);
                }
                email= "email1:"+email+":";
		c1->send(email);
	
	}

	while(message =="YOUR LOGIN IS BUSY,PLEASE ENTER ANOTHER LOGIN"){
                getline(std::cin,login);
                while(isValidLogin(login) !=true){
		std::cout<<"INVALID LOGIN::Enter your LOGIN again"<<std::endl;
                login = "";
                getline(std::cin,login);
                }
		std::string login2= "login1:"+login+":";
		c1->send(login2);
		login = "login:"+login+":";
	
	}
	if(message == "ENTER YOUR LOGIN AND PASSWORD"){
		std::cout<<"Enter your LOGIN*"<<std::endl;
                getline(std::cin,login);

                std::cout<<"Enter your PASSWORD*"<<std::endl;
                getline(std::cin,password);

		sign_in = "sign_in:"+login+":"+password;
		c1->send(sign_in);
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


int main () {

        connection binder(std::string("in"), std::string("out"));
        binder.send("connect");
        binder.setRecvMessageCallback(binder_recv_message);
        usleep(1000);
        //      while(true){}






        return 0;
}
