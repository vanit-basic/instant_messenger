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
       std::regex reg("[[:upper:]]");
        if(!std::regex_search(log,reg) || log.size()<8 || log.size()>16)
                return false;
        std::regex rgx("[[:alnum:]]+(\\.|_|-|@)");
        log=std::regex_replace(log,rgx,"");
        return (log=="" || std::regex_replace(log,std::regex("[[:alnum:]]"),"")=="")?true:false;

}
bool isValidName(std::string name){
bool n = true;
 for(int i = 0;i<name.size();i++){
                if(name[0]<65 || name[0]>90){
                        n = false;
                        break;
                }
                if(name[i]<65 || name[i]>122){
                        n = false;
                        break;
                }
                if(name[i]>90 && name[i]<97){
                        n = false;
                break;
                }
                else
                        n = true;
                                                                       }
return n;

}
bool isValidEmail(std::string email){
const std::regex pattern("(\\w+)(\\.|_)?(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return (std::regex_match(email,pattern));
	/*int dog=email.find("@");
	if(dog==-1)
		return false;
	std::string sub_before_dog=replace_before_dog(email.substr(0,dog));
	int point=email.rfind(".");
	if(point==-1 || point<=dog || email.size()-1-point<2)
		return false;
	std::string sub_after_dog_before_point=replace_after_dog_before_p(email.substr(dog+1,point-dog-1));
	std::string after_point=replace_after_p(email.substr(point+1));
	std::regex start("[[:alnum:]]+");
	std::regex middle("[[:alnum:]]+");
	std::regex end("[[:alpha:]](2,)");
	if(std::regex_match(sub_before_dog,start) && std::regex_match(sub_after_dog_before_point,middle) && after_point=="")
		return true;
	return false;*/
}
bool isValidBirthday(std::string date){
if(!std::regex_match(date,std::regex("[[:digit:]]+(\\-)[[:digit:]]+(\\-)[[:digit:]]+")))
                return false;
        int day=stoi(date.substr(0,date.find("-")));
        date.erase(0,date.find("-")+1);
        int month=stoi(date.substr(0,date.find("-")));
        date.erase(0,date.find("-")+1);
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
