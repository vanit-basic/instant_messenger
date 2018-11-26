#include <iostream>
#include <string>
#include <regex>
#include "connection.hpp"
bool valid_name(std::string name) {
	bool f = false;
	if(name.length() > 1) {
		if('A' <= name[0] && name[0] <= 'Z') {
			int i = 1;
			while(i < name.length()) {
				if('a' <= name[i] && name[i] <= 'z'){
					f = true;
					i++;
				}
				else
				{	f=false;
					break;
				}
			}
		}
	}
	return f;
}
bool valid_login(std::string log) {
	std::regex reg("[[:upper:]]");
        if(!std::regex_search(log,reg) || log.size()<8 || log.size()>16)
                return false;
        std::regex rgx("[[:alnum:]]+(\\.|_|-|@)");
        log=std::regex_replace(log,rgx,"");
        return (log=="" || std::regex_replace(log,std::regex("[[:alnum:]]"),"")=="")?true:false;
} 
bool valid_gender(std::string gender) {
	bool f = false;
	if(gender == "male" || gender == "female")
		f = true;
	return f;
}
bool valid_birthdate(std::string date) {
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
std::string replace_before_dog(std::string mail) {
       std::regex e("[[:alnum:]]+(\\.|_|-)");
       return std::regex_replace(mail,e,"");
}
std::string replace_after_dog_before_p(std::string mail) {
       std::regex e("[[:alnum:]]+(\\.|-)");
       return std::regex_replace(mail,e,"");
}
std::string replace_after_p(std::string mail) {
       std::regex e("[[:alpha:]]");
       return std::regex_replace(mail,e,"");
}
bool valid_mail(std::string mail) {
       int dog = mail.find("@");
       if(dog == -1)
               return false;
       std::string sub_before_dog = replace_before_dog(mail.substr(0,dog));
       int point = mail.rfind(".");
       if(point == -1 || point <= dog || mail.size() - 1 - point < 2)
               return false;
       std::string sub_after_dog_before_point = replace_after_dog_before_p(mail.substr(dog + 1, point - dog - 1));
       std::string after_point = replace_after_p(mail.substr(point + 1));
       std::regex start("[[:alnum:]]+");
       std::regex middle("[[:alnum:]]+");
       std::regex end("[[:alpha:]](2,)");
       if(std::regex_match(sub_before_dog,start) && std::regex_match(sub_after_dog_before_point,middle) && after_point == "")
               return true;
       return false;
}
bool valid_password(std::string password) {
	bool isValid=true;
	std::string copypass=password;
	if((8 > copypass.size()) || (16 < copypass.size()))
	{
		isValid = false;
	}
	else
	{
		std::regex p("[A-Za-z0-9]+");
		copypass=std::regex_replace(copypass, p, "");
		if(copypass!="")
		{
			isValid=false;
		}
		else
		{
			copypass=password;
			std::regex l("[A-Z]");
			std::regex s("[a-z]");
			std::regex n("[0-9]");
			if(!(regex_search(password, l) && regex_search(password, s) && regex_search(password, n)))
			{
				isValid=false;
			}
		}
	}
	return isValid;
}
std::string infos(std::map<std::string, user> m_map, std::string id) {
        std::string data = "";
        data = ":firstname:" + (m_map[id]).getFirstName() + ":lastname:" + (m_map[id]).getLastName() + ":birth_date:" + (m_map[id]).getBirthDate() + ":gender:" + (m_map[id]).getGender() + ":email:" + (m_map[id]).getEmail() + ":login:" + (m_map[id]).getLogin() + ":id:" + (m_map[id]).getId() + ":";
        return data;
}
