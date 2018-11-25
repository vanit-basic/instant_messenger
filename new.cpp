#include <iostream>
#include <string>
#include <list>
#include <iterator>

std::list<std::string> str_to_list(std::string message){
	std::list<std::string> actions;
	while(message != ""){
		int pos = message.find(" or ");
		actions.push_back(message.substr(0,pos));
	//	message.erase(0,pos+3);
	}
	return actions;
}

int main(){

	std::list<std::string> actions;
	std::string str;
	std::cin>>str;
	actions = str_to_list(str);
	for (std::list<std::string>::iterator it = actions.begin(); it != actions.end(); it++)
		std::cout << *it << ' ';


return 0;
}
