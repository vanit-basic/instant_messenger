#include <iostream>
#include <regex>
#include <string>
#include <iterator>
#include <map>

std::string map_to_string(std::map<std::string, std::string> mymap){
	std::string res = "";
	for (auto it = mymap.begin(); it != mymap.end(); it++){
		res += ":"+it->first+":"+it->second;
	}
	return res;
}

std::map<std::string, std::string> string_to_map(std::string mystr){
	std::map<std::string,std::string> mymap;
	std::regex forma ("[:w+:]+:");
	mystr.erase(0,1);
	std::regex_iterator<std::string::iterator> himn ( mystr.begin(), mystr.end(), forma );
	std::regex_iterator<std::string::iterator> erk;
	while(himn != erk){
		std::string key = std::to_string(*himn); 
		himn++;
		std::string value = std::to_string(*himn); 
		himn++;
		mymap.insert(std::pair<std::string, std::string>(key, value));
	}
	return mymap;
}

int main(){
	std::string text;
	std::map<std::string,std::string> mymap;
	std::cin>>text;
	mymap = string_to_map(text);
	std::map<std::string, std::string>::iterator it = mymap.begin();
	for (auto it=mymap.begin(); it!=mymap.end(); ++it){
		std::cout << it->first << " => " << it->second << '\n';	
	}
	text.clear();
	text = map_to_string(mymap);
	std::cout<<text<<std::endl;
return 0;
}
