#include<iostream>
#include<map>
#include<string>
std::map <std::string,std::string> toString(std::string str){
	std::string left="";
	std::string right="";
	int mejtex=0;
	int mejtex1=0;
	for(int i=1;i<str.length()-1;i++){
		if(str[i]==':')
			mejtex=i;
	}
	for(int i=mejtex;i<str.length()-2;i++)
	{
		mejtex1++;
	}
	left=str.substr(1,mejtex-1);
	right=str.substr(mejtex+1,mejtex1);
	std::cout<<left<<std::endl;
	std::cout<<right<<std::endl;
	std::map<std::string,std::string>myMap={{left,right}};
	for(auto it=myMap.begin();it !=myMap.end();it++){
		it->first;
		it->second;
	}
	return myMap;
}
std::string mapString(std::map<std::string,std::string>myMap){
	std::string map_str="";
	for(auto it=myMap.begin();it!=myMap.end();it++){
		map_str+=it->first+" : "+it->second;
	}
	return map_str;
}
int main(){
	std::cout<<"example :word:word: "<<std::endl;
	std::string str="";
	std::cout<<" > ";
	std::cin>>str;
	char first=str[0];
	char last=str[str.length()-1];
	int temp=0;
	for(int i=0;i<str.length();i++){
		if(first==':' && last==':' && str[i]==':'){
			temp++;
		}
	}
	while(temp !=3){
		std::cout<<" > ";
		std::cin>>str;
		for(int j=0;j<str.length();j++){
			 if(str[0]==':' && str[str.length()-1]==':' && str[j]==':'){
                        		temp++;	 
		 		}	
		}
	}
	std::cout<<mapString(toString(str))<<std::endl;
	return 0;
}
