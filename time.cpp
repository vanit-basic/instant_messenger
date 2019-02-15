#include <iostream>
#include <ctime>
#include <string>
bool dateValidation(std::string date,int count){
     time_t now = time(0);
     tm *ltm = localtime(&now);

     int one = date.find(':');
     std::string  year =date.substr(0,one);
     date = date.erase(0,one+1);
     int Year =stoi(year);
     
     int two = date.find(':');
     std::string month =date.substr(0,two);
     date = date.erase(0,two+1);
     int Month =stoi(month);

    int tree = date.find(':');
     std::string day =date.substr(0,tree);
     date = date.erase(0,tree+1);
     int Day =stoi(day);

     int four = date.find(':');
     std::string time =date.substr(0,four);
     date = date.erase(0,four+1);
     int Time =stoi(time);

     int five = date.find(':');
     std::string minut =date.substr(0,five);
     date = date.erase(0,five+1);
     int Minut =stoi(minut);
/*
     int six = date.find(':');
     std::string second =date.substr(0,six);
     date = date.erase(0,six+1);
     int Second =stoi(second);
     std::cout<<Second<<std::endl;
*/
if(5 >= count){
     if(Year == (1900+ltm->tm_year)){
    
	    if((1+ltm->tm_mon)== Month){

    		    if((ltm->tm_mday)==Day){
			int UTC = 4 + ltm->tm_hour;
			if((UTC-2) >= Time ){
				
				if((ltm->tm_hour) >= Minut){
					
						return true;
				}else{
						return false;
				}
			 }else{
			 	return false;
			 }
		  }else if((ltm->tm_mday) > Day){
		  	return true;
		  }else{
		  	return false;
		  }
	    }else if((1+ltm->tm_mon) > Month){
	    	return true;
	    }else{
	    	return false;
	    }
     }else if(Year < (1900+ltm->tm_year)){
     	return true;
     }
}else{
	return false;
}
// print various components of tm structure.
//   cout << "Month: "<< 1 + ltm->tm_mon<< endl;
//   cout << "Day: "<< ltm->tm_mday << endl;
//   cout << "Time: "<< 4 + ltm->tm_hour << ":";
//   cout <<  ltm->tm_min << ":";
//   cout << ltm->tm_sec << endl;
    
    }
int main() {
   std::string date = "";
   int count = 0 ;
   std::cin>>count;
   std::cin>>date;
   bool validation = dateValidation(date,count);
   	std::cout<<validation<<std::endl;
   return 0;
}
