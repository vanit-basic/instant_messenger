#include <iostream>
#include <list>
#include <map>
#include <iterator>
#include <string>

std::string str = "";
std::map<std::string,std::string> myMap;
std::map<std::string,std::string>::iterator itr;
std::map<std::string,std::string> stringToMap(std::string keyValue1){
        int size1 = keyValue1.size();
	if(keyValue1[0]==':'){
		keyValue1 = keyValue1.substr(1,size1-1);
	int size1 = keyValue1.size(); 
	}
		std::string key = keyValue1.substr(0,keyValue1.find(":"));
		std::string mnacac = keyValue1.substr(keyValue1.find(":")+1);
		std::string value = mnacac.substr(0,mnacac.find(":"));
		std::string mnacac1 = mnacac.substr(mnacac.find(":")+1);
		myMap.insert(std::pair<std::string, std::string>(key, value));
		if(size1 !=0) 
		stringToMap(mnacac1);


        return myMap;
}
std::string mapToString(std::map<std::string,std::string> map){
	for(itr = map.begin();itr !=map.end();++itr){
		str = str + (*itr).first + ":" + (*itr).second + ":";
	}


	return str;
        
}
int main(){
	std::string a= "";
	std::cin>>a;
	stringToMap(a);
	for(itr = myMap.begin();itr !=myMap.end();++itr){
        std::cout<<"key->"<<(*itr).first<<"   :::   value->"<<(*itr).second<<std::endl;
        }
	mapToString(myMap);
	std::cout<<str<<std::endl;


	return 0;
}
