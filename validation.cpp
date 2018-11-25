#include <iostream>
#include <regex>
#include <string>
#include <map>
#include "validation.hpp"

std::string replace_before_at (std::string mail) {
        std::regex e("[[:alnum:]]+(\\.|_|-)");
        return std::regex_replace (mail, e, "");
}

std::string replace_after_at (std::string mail) {
        std::regex e("[[:alnum:]]+(\\.|-)");
        return std::regex_replace (mail, e, "");
}

bool email_valid (std::string email) {
        std::regex reg_s("[[:alnum:]]+@");
        std::regex reg_f("\\.[[:alpha:]]{2,}");
        std::regex reg("[[:alnum:]]+");


        if (4 > email.length() || 32 < email.length())
                return false;

        std::size_t posAt = email.find("@");
        if (posAt == std::string::npos) {
                return  false;
        }
        std::size_t posDot = email.rfind(".");
        if (posDot == std::string::npos) {
                return false;
        }

        std::string str_m = email.substr(0, posAt + 1);
        str_m = replace_before_at(str_m);
        if (! regex_match(str_m, reg_s))
return false;
        str_m = email.substr(posAt + 1, posDot - posAt - 1);
        str_m = replace_after_at(str_m);
        if (! regex_match(str_m, reg))
                return false;
        str_m = email.substr(posDot, email.length() - posDot);
        if (! regex_match(str_m, reg_f))
                return false;
        return true;

}

bool email_valid2 (std::map<std::string, bool> m_map, std::string str) {
        std::map<std::string, bool>::iterator it;
        for(it = m_map.begin(); it != m_map.end(); ++it) {
                if((it->first) == str) {
                        return false;
                        break;
                }
        }
        return true;
}

bool firstname_valid (std::string firstname) {
        std::regex reg("[[:upper:]][[:lower:]]{2,}");
        return (std::regex_match(firstname, reg));
}

bool lastname_valid (std::string lastname) {
        std::regex reg("[[:upper:]][[:lower:]]{2,}");
        return (std::regex_match(lastname, reg));
}

bool gender_valid (std::string gender) {
        return ("female" == gender || "male" == gender);
}
bool birth_date_valid (std::string birth_date) {
        size_t length = birth_date.length();
        std::regex reg("[[:digit:]]+(\\.)[[:digit:]]+(\\.)[[:digit:]]+");
        if (! std::regex_match(birth_date, reg))
                return false;

        std::size_t pos = birth_date.find(".");
        std::size_t r_pos = birth_date.rfind(".");
        std::string str = birth_date.substr(0, pos);
        std::string str2 = birth_date.substr(pos + 1, r_pos - pos + 1);
        std::string str3 = birth_date.substr(r_pos + 1, length - r_pos);

        int day = std::stoi(str);
        int month = std::stoi(str2);
        int year = std::stoi(str3);
        if ((day < 1) || (day > 31) || (month < 1) || (month > 12) || (year < 1958) || (year > 2002))
                return false;
        if (((4 == month || 6 == month || 9 == month || 11 == month) && day > 30) || ((2 == month && 29 < day) || (0 != year%4 && 2 == month && 28 < day)))
                return false;
        return true;
}

bool password_valid (std::string password) {
        size_t length = password.length();
        if (length > 16 || length < 8)
                return false;
        std::regex reg("[A-Za-z0-9]+");
        std::string c_password = password;
        c_password = std::regex_replace(c_password, reg, "");
        if ("" != c_password)
                return false;
        std::regex upper("[A-Z]");
        std::regex lower("[a-z]");
        std::regex number("[0-9]");
if (! (regex_search(password, upper) && regex_search(password, lower) && regex_search(password, number)))
                return false;
        return true;
}

bool login_valid (std::string login) {
        size_t length = login.length();
        if (6 > length || 32 < length)
                return false;

        std::string c_login = login;
        std::regex reg("[A-Za-z0-9]+");
        c_login.erase(0, length - 2);
        c_login = std::regex_replace(c_login, reg, "");
        if ("" != c_login)
                return false;

        c_login = login;
        std::regex reg2("[A-Za-z0-9]+(\\.|-|_|@){0,1}");
        c_login = std::regex_replace(c_login, reg2, "");
        c_login = std::regex_replace(c_login, reg, "");
        if ("" != c_login)
                return false;

        return true;
}


bool login_valid2 (std::map<std::string, std::pair<std::string, std::string>> info_map, std::string login) {
        std::map<std::string, std::pair<std::string, std::string>>::iterator it;
	bool isValid = true;
        for( it = info_map.begin(); it != info_map.end(); ++it) {
                if (it->first == login) {
                        isValid=false;
			break;
                }
        }
	return isValid;
}

bool sign_in_valid (std::map<std::string, std::pair<std::string, std::string>> m_map, std::string login, std::string password) {
	if ( (m_map[login].second == password))	{
		return true;
	}
	else {
		return false;
	}
}

bool join_valid (std::map<std::string, bool> join, std::string login) {
        std::map<std::string, bool>::iterator it;
	bool isvalid = true;
        for(it = join.begin(); it != join.end(); ++it) {
                if(((it->first) == login) && ((it->second) == true)) {
                        isvalid = false;
			break;
                }
        }
        return isvalid;
}

bool id_valid (std::map<std::string, std::string> m_map, std::string id) {
	std::map<std::string, std::string>::iterator it;
	for (it = m_map.begin(); it != m_map.end(); ++it) {
		if (! (it->first == id)) {
			return false;
		}
	}
	return true;
}

void print (std::map<std::string, std::string> m_map) {
	std::map<std::string, std::string>::iterator it;
	for (it = m_map.begin(); it != m_map.end(); ++it) {
		std::cout << "id: " << it->first << ",  name: " << it->second << "\n";
	}
}

std::string info(std::map<std::string, user> m_map, std::string id) {
        std::string data = "";
        data = ":firstname:" + (m_map[id]).getFirstname() + ":lastname:" + (m_map[id]).getLastname() + ":birth_date:" + (m_map[id]).getBirth_date() + ":gender:" + (m_map[id]).getGender() + ":email:" + (m_map[id]).getMail() + ":login:" + (m_map[id]).getLogin() + ":id:" + (m_map[id]).getId() + ":";
        return data;
}

std::string global_validation (std::map<std::string,std::string> m_map) {
        std::string respons_valid = "";
        if (! firstname_valid (m_map["firstname"]))
                respons_valid += ":firstname:valid:";
        else
                respons_valid += "firstname:invalid:";
	if (! lastname_valid (m_map["lastname"]))
                respons_valid += "lastname:valid:";
        else
                respons_valid += "lastname:isvalid:";
        if (! email_valid (m_map["mail"]))
                respons_valid += "mail:valid:";
        else
                respons_valid += "mail:invalid:";
        if (! gender_valid (m_map["gender"]))
                respons_valid += "gender:valid:";
        else
                respons_valid += "gender:invalid:";
        if (! birth_date_valid (m_map["birth_date"]))
                respons_valid += "birth_date:valid:";
        else
                respons_valid += "birth_date:invalid:";
        if (! login_valid (m_map["login"]))
                respons_valid += "login:valid:";
        else
                respons_valid += "login:isvalid:";
        if (-1 == respons_valid.find("invalid"))
                return "OK";
        return respons_valid;
}

std::map<std::string, std::string> strToMap (std::string map_conv) {
        std::string key, value;
        std::map <std::string, std::string> m_map;

        int size = map_conv.length();
        map_conv.erase(0, 1);

        while (map_conv != "") {
		int pos = map_conv.find(":");
                key = map_conv.substr(0, pos);
                map_conv.erase(0, pos + 1);
                pos = map_conv.find(":");
                value = map_conv.substr(0, pos);
                map_conv.erase(0, pos + 1);
                m_map.insert(std::pair<std::string, std::string> (key, value));
        }

        return m_map;
}

std::string mapToStr (std::map<std::string, std::string> m_map) {
        std::string m_str = ":";
        std::map<std::string, std::string>::iterator it;
        for (it = m_map.begin(); it != m_map.end(); ++it) {
                m_str += (*it).first + ":" + (*it).second + ":";
        }
        return m_str;
}

