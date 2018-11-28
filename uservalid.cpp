#include <iostream>
#include <string>
#include <regex>
bool nameValid(std::string name){

 bool flag=true;
        if((int(name[0])>=65)&&(int(name[0])<=90))
        {
                for(int i=1;i<name.length();i++)
                {
                        if(int(name[i])<97 || int(name[i])>122)
                        {
                                flag=false;
                                break;
                        }
                }
        }
        else
                flag=false;

        return flag;
}
bool dateValid(std::string str){

        char first=str[2];
        char last=str[5];
        int day=0;
        int month=0;
        int year=0;
        for(int i=0;i<str.length();i++){
                if(first=='.' && last=='.'){
                        day=stoi(str);
                        str=str.substr(3,str.length()-3);
                        month=stoi(str);
                        str=str.substr(3,str.length()-3);
                        year=stoi(str);
                        break;
                }
        }

        if(year >= 1900 && year <= 2018){
                if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12 ){
                        if(day >= 1 && day <= 31){
                        	return true;
			}
                        else
                        	return false;
                }
                else if(month == 4 || month ==6 || month == 9 || month == 11){
                        if(day >= 1 && day <= 30){
                        	return true;
			}
                        else
                                return false;

                }
                else if(month == 2) {

                        if(year % 4 ==0 && day>=1 && day <= 29)
                                return true;
                        else if(year % 4 != 0 && day>=1 && day<= 28)
                                return true;
                        else
                                return false;
                }
        }
        else
                return false;

}
bool genderValid(std::string gen){

	 if(gen=="male" || gen =="female"){
		 return true;
        }
	else 	
		return false;	
}
bool loginValid(std::string log){
        for(int i = 0; i < log.length(); i++){
		int a=int(log[i]);
		if((a>47 && a<58) || (a>64 && a<91)||(a>96 && a<123)|| a==46 ||a==95 || a==45){
		return true;
		}
		else
			return false;
        }
}
std::string rba (std::string mail) {
        std::regex e("[[:alnum:]]+(\\.|_|-)");
        return std::regex_replace (mail, e, "");
}

std::string raa (std::string mail) {
        std::regex e("[[:alnum:]]+(\\.|-)");
        return std::regex_replace (mail, e, "");
}

bool mailValid(std::string mail)
{
        std::regex reg_s("[[:alnum:]]+@");
        std::regex reg("[[:alnum:]]+");
        std::regex reg_f("\\.[[:alpha:]]{2,}");
        bool isvalid = true;

        if (mail.length() >= 4 && mail.length() <= 32)
                {
                        std::size_t posAt = mail.find("@");
                        std::size_t posDot = mail.rfind(".");
                if ((posAt == std::string::npos) || (posDot == std::string::npos) || (mail.length() - posDot - 1 < 2))
                        isvalid = false;
                else
                        {
                                std::string str_m = mail.substr(0, posAt + 1);
                                str_m = rba(str_m);
                        if (regex_match(str_m, reg_s))
                                {
                                        str_m = mail.substr(posAt + 1, posDot - posAt - 1);
                                         str_m = raa(str_m);
                                if (regex_match(str_m, reg))
                                        {
                                                 str_m = mail.substr(posDot, mail.length() - posDot);
                                        if (regex_match(str_m,reg_f))
                                                isvalid = true;
                                        else
                                               isvalid = false;
                                        }
                                        else
                                                isvalid = false;
                                }
                                else
                                        isvalid = false;
                        }
                }

       return isvalid;

}

bool passValid(std::string pas){
	bool f=true;
	bool l=false;
	bool a=false;
	bool g=false;
	if(pas.length()>=8 && pas.length()<=16){
		
		for(int i=0;i<pas.length();i++){

			if(int(pas[i])>47 && int(pas[i])<58){
				l=true;
			}
			else if(int(pas[i])>64 && int(pas[i])<91){
				a=true;
			}	
			else if(int(pas[i])>96 && int(pas[i])<123){
				g=true;
			}
			else{
				f=false;
				break;
			}
		}
	}
	else{
		f=false;

	}
	return f &&  l && a && g;  
}
