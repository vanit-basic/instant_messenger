#include <map>
#include <iostream>
#include <string>

std::map<std::string, std::string> f_map (std::string registration) {
        std::string str, str2;
        std::map <std::string, std::string> s_map;

        int size = registration.length();
        registration.erase(0, 1);
        registration.erase(size - 1, 1);

        while (registration != "") {
                int pos = registration.find(":");
                str = registration.substr(0, pos);
                registration.erase(0, pos + 1);
                pos = registration.find(":");
                str2 = registration.substr(0, pos);
                registration.erase(0, pos + 1);
                s_map.insert(std::pair<std::string, std::string> (str, str2));
                str = "";
                str2 = "";
        }

        return s_map;
}

void print (std::map<std::string, std::string> s_map) {
        std::cout << "Map\n";
        for (std::map <std::string, std::string>::iterator itr = s_map.begin(); itr != s_map.end(); ++itr) {
                std::cout << itr->first << " - " << itr->second << '\n';
        }
}

std::string f_str (std::map<std::string, std::string> s_map) {
        std::string m_str = ":";
        std::map<std::string, std::string>::iterator it;
        for (it = s_map.begin(); it != s_map.end(); ++it) {
                m_str += (*it).first + ":" + (*it).second + ":";
        }
        return m_str;
}

int main () {
        std::string registration = ":action:registration:firstname:Valod:lastname:Valodyan:mail:v_valodyan@mail.ru:male:female:login:v_validyan:birth_date:12-12-1912:";
        std::map<std::string, std::string> strToMap = f_map(registration);
        print(strToMap);
        std::string mapToStr = f_str(strToMap);
        std::cout << "\n" << "String  " << "\n" << mapToStr << "\n";
        return 0;
}
