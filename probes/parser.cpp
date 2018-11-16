#include <iostream>
#include <regex>

std::string signup(":action:signup:firstname:Valod:lastname:Valodyan:gender:male:login:v_valodyan:birth_date:18798797978:");

typedef std::map<std::string, std::string> map_s;
typedef map_s::iterator map_iter;

void printMap(map_s m) {
	map_iter cur = m.begin();
	map_iter end = m.end();
	for (; cur != end; cur++) {
		std::cout << cur->first << ":" << cur->second << std::endl;
	}
}

std::string getValueByKey (std::string key, std::string input) {
	std::string pattern = key + ":(\\w+)";
	std::regex rgx(pattern.c_str());
	std::smatch match;
	std::string result = "";
	if (std::regex_search(input, match, rgx)) {
		result = std::string(match[1]);
	}
	return result;
}

map_s messageToMap(std::string message) {
	map_s result;
	std::string pattern = ":(\\w+):";
	std::regex rgx(pattern.c_str());
	auto it = std::sregex_iterator(message.begin(), message.end(), rgx);
	auto it_end = std::sregex_iterator();
	while(it != it_end) {
		std::smatch match = *it;
		std::string key = match[1].str();
		std::string value = getValueByKey(key, signup);
		result[key] = value;
		it++;
	}
	return result;
}

int main (int argc, char** argv) {
	map_s m = messageToMap(signup);
	printMap(m);
	std::cout << m["action"] << std::endl;
	return 0;
}
