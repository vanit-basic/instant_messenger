#include <iostream>
#include <string>
#include <regex>
#include "isvalid.hpp"
std::string replace_before_at(std::string mail){
        std::regex e("[[:alnum:]]+(\\.|_|-)");
        return std::regex_replace(mail,e,"");
}
std::string replace_after_at(std::string mail){
        std::regex a("[[:alnum:]]+(\\.|-)");
        return std::regex_replace(mail,a,"");
}

bool isValidLogin(std::string log){
	if(log == "")
		return true;
       std::regex reg("[[:upper:]]");
        if(!std::regex_search(log,reg) || log.size()<=8 || log.size()>16)
                return false;
        std::regex rgx("[[:alnum:]]+(\\.|_|-|@)");
        log=std::regex_replace(log,rgx,"");
        return (log=="" || std::regex_replace(log,std::regex("[[:alnum:]]"),"")=="")?true:false;

}
bool isValidName(std::string name){
	std::regex pattern("[A-Z]{1}[a-z]+");
	return std::regex_match(name,pattern);

}
bool isValidEmail(std::string email){
const std::regex pattern("(\\w+)(\\.|_)?(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return (std::regex_match(email,pattern));
}
bool isValidBirthday(std::string date){
if(!std::regex_match(date,std::regex("[[:digit:]]+(\\.)[[:digit:]]+(\\.)[[:digit:]]+")))
                return false;
        int day=stoi(date.substr(0,date.find(".")));
        date.erase(0,date.find(".")+1);
        int month=stoi(date.substr(0,date.find(".")));
        date.erase(0,date.find(".")+1);
        int year=stoi(date);
        if(day<1 || day>31 || month<1 || month>12 || year>2002 || year<1958)
                return false;
        if ((month==2 && day>29) || (month==4 && day>30) || (month==6 && day>30) || (month==9 && day>30) || (month==11 && day>30) || (year%4!=0 && month==2 && day>28))
   return false;
        return true;
}
bool isValidGender(std::string gen){
if(gen=="male" || gen=="female")
                return true;
        else
                return false;

}
bool isValidPhone(std::string phone){
        std::regex digit("(\\+)[[:digit:]]+");
        if(std::regex_match(phone,digit))
                return true;
        else
                return false;
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
               std::cout<<"Your password must ba at least 8 characters\n";
                return false;
}
