#include <iostream>
#include <regex>


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
	return 0;
}
