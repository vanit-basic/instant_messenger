#include "connection.hpp"
#include "verification.hpp"
#include "user.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <list>
#include <map>
static int id=9;
//std::map<std::string,std::string> log_passw;
std::map<std::string,std::string> current_user;
std::map<std::string,std::pair<std::string,std::string>> user_info;
std::map<int,user> id_ob;
bool search_log(std::string log)
{
        std::map<std::string,std::pair<std::string,std::string>>::iterator it;
        for(it=user_info.begin();it!=user_info.end();it++)
                if(it->first==log)
                        return false;
        return true;
}
std::map<std::string,std::string> string_to_map(std::string str)
{
        std::map<std::string,std::string> mymap;
        str.erase(0,1);
        std::string first="";
        std::string second="";
        while(str!="")
        {
                first=str.substr(0,str.find(":"));
                str.erase(0,str.find(":")+1);
                second=str.substr(0,str.find(":"));
                str.erase(0,str.find(":")+1);
                mymap.insert ( std::pair<std::string,std::string>(first,second));
        }
        return mymap;

}
std::string map_to_string(std::map<std::string,std::string> mymap)
{
        std::map<std::string,std::string>::iterator it;
        std::string str=":";
        for (it=mymap.begin(); it!=mymap.end(); ++it)
                str+=it->first+":"+it->second+":";
        return str;
}

static int value=0;

std::list<connection*> connections;
std::string str="";
void recieve(connection* c, std::string msg) {
        std::cout << "from client : " << msg << std::endl;
        if(":action:help:"==msg)
        {
                c->send("<registration> or <sign in>");
                return;
        }
        if("registration"==msg)
        {
                c->send("Enter your information");
                return;
        }

        if(msg[0]==':')
        {
                current_user=string_to_map(msg);
                if(search_log(current_user["login"]))
                {

                        ++id;
                        current_user.insert(std::pair<std::string,std::string>("id",std::to_string(id)));
                        user ob(current_user);
                        id_ob.insert(std::pair<int,user>(id,ob));
                        user_info.emplace(current_user["login"],std::make_pair(std::to_string(id),current_user["password"]));
                        str="your id : "+ std::to_string(id);
                        c->send(str);
                        return;
                }
                else
                {
                        c->send("The login coincides\n<registration> or <log in>\n");
                        return;
                }
        }
        else
        {
                c->send("Error message!\n<registration> or <log in>\n");
                return;
        }

}

void binder_recieve(connection* c, std::string msg)
{
        if(msg=="first message")
        {
                value++;
                std::string fifo1="C"+std::to_string(value);
                std::string fifo2="S"+std::to_string(value);
                connection* s=new connection(fifo1,fifo2);
                s->setRecvMessageCallback(recieve);
                connections.push_back(s);
                fifo2=fifo2+":"+fifo1;
                c->send(fifo2);
                c->send("q");
        }
}

int main()
{
        connection binder(std::string("out"),std::string("in"));
        binder.setRecvMessageCallback(binder_recieve);
        remove("busy.lock");

        return 0;

}

