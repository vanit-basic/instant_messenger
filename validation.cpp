#include <string>
#include <regex>
bool valid_name(std::string name) {
	bool f = false;
	if(name.length() > 1) {
		if('A' <= name[0] && name[0] <= 'Z') {
			int i = 1;
			while(i < name.length()) {
				if('a' <= name[i] && name[0] <= 'z'){
					f = true;
					i++;
				}
			}
		}
	}
	return f;
}
bool valid_login(std::string login) {
	bool f = false;
	if(login.length() >= 8 && login.length() <= 32) {
		std::regex reg("[A-Za-z0-9]+");
		if(std::regex_match(login,reg))
			f = true;
	}
	return f;
} 
bool valid_gender(std::string gender) {
	bool f = false;
	if(gender == "male" || gender == "female")
		f = true;
	return f;
}
bool valid_birthdate(std::string date) {
	
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
