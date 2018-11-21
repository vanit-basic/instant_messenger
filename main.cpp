#include <iostream>
#include <string>
#include "user.h"

int main(){
	std::string FirstName;
	std::cout<<"First Name : ";
	std::cin>>FirstName;
	user Fname;
	
	while(Fname.nameValid(FirstName)==false){
		 std::cout<<"First Name : ";
        	 std::cin>>FirstName;

	}
	std::string LastName;
	std::cout<<"Last Name : ";
        std::cin>>LastName;
        user Lname;

        while(Lname.nameValid(LastName)==false){
         	std::cout<<"Last Name : ";
        	std::cin>>LastName;
	}
	std::string BirthDate;
	std::cout<<"Birth Date : ";
	std::cin>>BirthDate;
	user Bdate;
	 while(Bdate.dateValid(BirthDate)==false){
                std::cout<<"Birth Date : ";
                std::cin>>BirthDate;
        }

	std::string Gender;
	std::cout<<"Gender : ";
	std::cin>>Gender;
	user gender;
	 while(gender.genderValid(Gender)==false){
                std::cout<<"Gender : ";
                std::cin>>Gender;
        }
	
	std::string Login;
	std::cout<<"Login : ";
        std::cin>>Login;
        user login;
         while(login.loginValid(Login)==false){
                std::cout<<"Login : ";
                std::cin>>Login;
        }

	std::string Id;

	std::string Mail;
	 std::cout<<"Mail : ";
        std::cin>>Mail;
        user mail;
         while(mail.mailValid(Mail)==false){
                std::cout<<"Mail : ";
                std::cin>>Mail;
        }
	 user person;
	std::string history="";
	history=person.getDetails();
	std::cout<<history<<std::endl;
	return 0;
}
