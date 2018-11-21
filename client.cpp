#include <iostream>
#include <unistd.h>
#include "connection.hpp"
#include "verification.hpp"
#include <mutex>
#include <string>
std::string fifo1="";
std::string fifo2="";
connection* mainConnection = NULL;

void recv_message_c(connection* c, std::string message) {

        std::cout << "From server : " << message << std::endl;
        std::string msg="";
        std::string info="";
        std::string confmsg="";

        if(message=="<registration> or <sign in>")
        {
                do
                {
                        std::cout<<"Enter action!\n";
                        getline(std::cin,msg);
                        if(msg!="registration" && msg!="sign in")
                                std::cout<<"Wrong action!";
                }
                while(msg!="registration" && msg!="sign in");
                c->send(msg);
                return;
        }

        if(message=="Enter your information")
        {
                std::string msg;
                do
                {
                        std::cout<<"Firstname: ";
                        getline(std::cin,msg);
                        if(!isvalid_firstname(msg))
                                std::cout<<"Invalid firstname!\n";
                }
                while(!isvalid_firstname(msg));
                info+=":firstname:"+msg;

                do
                {
                        std::cout<<"Lastname: ";
                        getline(std::cin,msg);
                        if(!isvalid_lastname(msg))
                                std::cout<<"Invalid lastname!\n";
                }
                while(!isvalid_lastname(msg));
                info+=":lastname:"+msg;

                do
                {
                        std::cout<<"Mail: ";
                        getline(std::cin,msg);
                        if(!isvalid_mail(msg))
                                std::cout<<"Invalid mail!\n";
                }
                while(!isvalid_mail(msg));
                info+=":mail:"+msg;

                do
                {
                        std::cout<<"Birth date: ";
                        getline(std::cin,msg);
                        if(!isvalid_birth_date(msg))
                                std::cout<<"Invalid birth date!\n";
                }
                while(!isvalid_birth_date(msg));
                info+=":birth_date:"+msg;

                do
                {
                        std::cout<<"Gender: ";
                        getline(std::cin,msg);
                        if(!isvalid_gender(msg))
                                std::cout<<"Invalid gender!\n";
                }
                while(!isvalid_gender(msg));
                info+=":gender:"+msg;

                do
                {
                        std::cout<<"Login: ";
                        getline(std::cin,msg);
                        if(!isvalid_login(msg))
                                std::cout<<"Invalid login!\n";
                }
                while(!isvalid_login(msg));
                info+=":login:"+msg;

                do
                {
                        do
                        {
                                std::cout<<"Password: ";
                                getline(std::cin,msg);
                                if(!isvalid_password(msg))
                                        std::cout<<"Invalid password!\n";
                        }
                        while(!isvalid_password(msg));

                        std::cout<<"Confirm password: ";
                        getline(std::cin,confmsg);
                }
                while(msg!=confmsg);
                info+=":password:"+msg;
                info+=":";

                c->send(info);
                return;
        }
}

void binder_recv_message(connection* c, std::string message) {
        if(message!="q" && message!="")
        {
        fifo1=message.substr(0,message.find(":"));
        fifo2=message.substr(message.find(":")+1);

        mainConnection = new connection(fifo1,fifo2);
        mainConnection->setRecvMessageCallback(recv_message_c);
        mainConnection->send(":action:help:");
        }
}
int main () {
        std::ifstream busy("busy.lock");
        if(busy.is_open())
        {
                while(busy.is_open())
                {
                        usleep(10);
                }
        }
        else
        {
                std::ofstream busy1("busy.lock");

                connection binder(std::string("in"),std::string("out"));
                binder.setRecvMessageCallback(binder_recv_message);
                binder.send("first message");
                busy1.close();
                remove("busy.lock");
        }
        while(true){}
        return 0;

}

