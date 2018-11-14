#include <iostream>
#include <regex>

typedef std::map<std::string, std::string> map_s;
typedef map_s::iterator map_iter;

void printMap(map_s m) {
	map_iter cur = m.begin();
	map_iter end = m.end();
	for (; cur != end; cur++) {
		std::cout << cur->first << ":" << cur->second << std::endl;
	}
}

map_s messageToMap(std::string message) {
	map_s result;
	result[std::string("key")] = std::string("value");
	return result;
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


int main (int argc, char** argv) {
	if (argc < 3) {
		std::cerr << "key input" << std::endl;
		return -1;
	}
	std::cout << getValueByKey(std::string(argv[1]), std::string(argv[2])) << std::endl;
	map_s m = messageToMap(std::string(argv[2]));
	printMap(m);
	return 0;
}
