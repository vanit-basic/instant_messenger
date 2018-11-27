#include <iostream>
#include <regex>
#include <string>
#include <map>
#include "valid1.hpp"

void print_map(std::map<std::string, std::string>  users)
{
        std::map<std::string, std::string>::iterator k=users.begin();
        for(; k != users.end(); ++k)
        {
                std::cout<<"ID :"<<k->first<<"  NAME:"<<k->second<<std::endl;
        }
}
std::string user_information(std::map<std::string, user> user_inf, std::string key)
{
        std::string inf=""; 
        inf=":Name:" + (user_inf[key]).getName() + ":SurName:" + (user_inf[key]).getSurName() + ":BirthDay:" + (user_inf[key]).getBirthDate() + ":Gender:" + (user_inf[key]).getGender() + ":Email:" + (user_inf[key]).getEmail() + ":Login:" + (user_inf[key]).getLogin() + ":Id:" + (user_inf[key]).getId() + ":";
        return inf;
}
std::map<std::string, std::string> string_to_map( std::string msg)
{
        std::map<std::string, std::string> user_inf;
        std::string key="";
        std::string value="";
        while(msg!="")
        {
                key = msg.substr(0, msg.find(':'));
                msg.erase(0, msg.find(':')+1);
                value = msg.substr(0, msg.find(':'));
                msg.erase(0, msg.find(':')+1);
                user_inf.emplace(key, value);
        }
        return user_inf;
}
std::string map_to_string(std::map<std::string, std::string> user_inf)
{
        std::string message="";
        std::map<std::string, std::string>::iterator k=user_inf.begin();
        for(; k != user_inf.end(); ++k)
        {
                message=message +":" + k->first + ":" + k->second;
        }
        message = message + ":";
        return message;
}
std::string us_inf(std::map<std::string, user> user_inf, std::string id)
{
        std::string inf = "";
        inf = "Name:" + (user_inf[id]).getName() + " " + (user_inf[id]).getSurName() + ":Id:" + (user_inf[id]).getId() + ":";
        return inf;
}

bool isValidSignIn(std::map<std::string, std::pair<std::string, std::string>> user_inf, std::string log, std::string pass)
{
        bool isValid=false;
        if(user_inf[log].second==pass)
        {
                isValid=true;
        }
        return isValid;
}
bool isValidJoined(std::map<std::string, bool> joined, std::string log)
{
        bool isValid=true;
        std::map<std::string, bool>::iterator k=joined.begin();
        for(; k != joined.end(); ++k)
        {
                if(((k->first)==log) && ((k->second)==true))
                {
                        isValid=false;
                        break;
                }
        }
 return isValid;
}
bool isValidKey(std::map<std::string, std::string> joined, std::string key)
{
        bool isValid=false;
        std::map<std::string, std::string>::iterator k=joined.begin();
        for(; k != joined.end(); ++k)
        {
                if((k->first) == key)
                {
                        isValid = true;
                        break;
                }
        }
        return isValid;
}
bool isValidKey1(std::map<std::string, bool> joined, std::string key)
{
        bool isValid=false;
        std::map<std::string, bool>::iterator k=joined.begin();
        for(; k != joined.end(); ++k)
        {
                if((k->first) == key)
                {
                        isValid = true;
                        break;
                }
        }
        return isValid;
}

bool isValidUser(std::map<std::string, std::string> users, std::string id)
{
        bool isValid=false;
        std::map<std::string, std::string>::iterator k=users.begin();
        for(; k != users.end(); ++k)
        {
                if(((k->first)==id))
                {
                        isValid=true;
       break;
                }
        }
        return isValid;
}

/*bool isValidEmail(std::string email){
const std::regex pattern("(\\w+)(\\.|_)?(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
}*/


bool isValidE_mail1(std::string mail)
{
        bool isValid = true;
        int k=0, n=0, s=0;
        s=mail.size();
        std::string copyMail;
        std::regex mail1 ("[A-Za-z0-9]{2,}");
        std::regex mail3 ("[A-Za-z]{2,}");
        std::regex mail2 ("[A-Za-z0-9]+@");
        std::regex beforeAt("[A-Za-z0-9]+(\\.|_|-)");
        std::regex afterAt("[A-Za-z0-9]+(\\.|-)");
        if(s<4 || s>32)
        {
                isValid = false;
        }
        else
        {
                k=mail.find('@');
                n=mail.rfind('.');
                copyMail=mail.substr(0,k+1);
                copyMail=std::regex_replace(copyMail, beforeAt, "");
                if(regex_match(copyMail,mail2))
                {
                        copyMail=mail.substr(k+1,n-k);
                        copyMail=std::regex_replace(copyMail, afterAt, "");
                        if(copyMail=="")
                        {
                                copyMail=mail.substr(n+1,mail.size()-n-1);
                                if(regex_match(copyMail,mail3))
                                {
                                        isValid = true;
                                }
                                else
                                {
                                        isValid = false;
                                }
                        }
                        else
{
                                isValid=false;
                        }
                }
                else
                {
                        isValid = false;
                }

        }
        return isValid;
}
bool isValidE_mail2(std::map<std::string, bool> user_inf, std::string str)
{
        bool isValid=true;
        std::map<std::string, bool>::iterator k=user_inf.begin();
                for(; k != user_inf.end(); ++k)
                {
                        if((k->first)==str)
                        {
                                isValid=false;
                                break;
                        }
                }
                return isValid;
}
bool isValidName(std::string name)
{
        bool isValid=true;
        for(int i = 0; i<name.size(); i++)
        {
                if(name[0]<65 || name[0]>90)
                {
                        isValid=false;
                        break;
                }
                if(name[i]<65 || name[i]>90)
                {
                        isValid=false;
                        break;
                }
                if(name[i]>90 && name[i]<97)
                {
                        isValid=false;
                        break;
                }
                else
                        isValid=true;
        }
        return isValid;
}
bool isValidBirthday(std::string date)
{
        if(!std::regex_match(date,std::regex("[[:digit:]]+(\\-)[[:digit:]]+(\\-)[[:digit:]]+")))
                return false;
        int day=stoi(date.substr(0,date.find(".")));
        date.erase(0,date.find(".")+1);
        int month=stoi(date.substr(0,date.find(".")));
        date.erase(0,date.find(".")+1);
        int year=stoi(date);
        if(day<1 || day>31 || month<1 || month>12 || year>2010 || year<1950)
                return false;
        if ((month==2 && day>29) || (month==4 && day>30) || (month==6 && day>30) || (month==9 && day>30) || (month==11 && day>30) || (year%4!=0 && month==2 && day>28))
                return false;
        return true;
}

bool isValidGender(std::string gender)
{
        /*if(gen=="male" || gen=="female")
                return true;
        else
                return false;*/
return (gender=="male" || gender=="female");
}

bool isValidPhone(std::string phone)
{
        std::regex digit("(\\+)[[:digit:]]+");
        if(std::regex_match(phone,digit))
                return true;
}
bool isValidLogin1(std::string login){
       std::regex reg("[[:upper:]]");
        if(!std::regex_search(log,reg) || log.size()<6 || log.size()>32)
                return false;
        std::regex rgx("[[:alnum:]]+(\\.|_|-|@)");
        log=std::regex_replace(log,rgx,"");
        if (log=="" || std::regex_replace(log,std::regex("[[:alnum:]]"),"")=="")
return true;
return false;
}
bool isValidLogin2(std::map<std::string, std::pair<std::string, std::string>> user_inf, std::string str)
{
        bool isValid=true;
        std::map<std::string, std::pair<std::string, std::string>>::iterator k=user_inf.begin();
                for(; k != user_inf.end(); ++k)
                {
                        if((k->first)==str)
                        {
                                isValid=false;
                                break;
                        }
                }
                return isValid;
}
bool isValidPassword(std::string password)
{


        std::regex pass("[A-Za-z0-9]+");
        if(std::regex_match(password,pass) && password.size() > 8  && password.size() < 16 )
        {
                std::regex lower("[a-z]");
                std::regex upper("[A-Z]");
                std::regex digit("[0-9]");
                if( regex_search(password,lower) && regex_search(password,upper) && regex_search(password,digit))
                        return true;
                else
                        return false;
        }
        else
               std::cout<<"Your password must be at least 8 characters\n";
                return false;
}


