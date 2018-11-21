#include<iostream>
#include<map>
#include<string>
#include<regex>
/*std::string replace_before_dog(std::string mail)
{
        std::regex e("[[:alnum:]]+(\\.|_|-)");
        return std::regex_replace(mail,e,"");
}
std::string replace_after_dog_before_p(std::string mail)
{
        std::regex e("[[:alnum:]]+(\\.|-)");
        return std::regex_replace(mail,e,"");
}
std::string replace_after_p(std::string mail)
{
        std::regex e("[[:alpha:]]");
        return std::regex_replace(mail,e,"");
}
*/
bool isvalid_firstname(std::string fname)
{
        std::regex reg("[[:upper:]][[:lower:]]{2,}");
        return (std::regex_match(fname,reg));
}
bool isvalid_lastname(std::string lname)
{
        std::regex reg("[[:upper:]][[:lower:]]{2,}");
        return (std::regex_match(lname,reg));
}
bool isvalid_mail(std::string email)
{
        const std::regex pattern("(\\w+)(\\.|_)?(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        return (std::regex_match(email,pattern));
        /*int dog=email.find("@");
        if(dog==-1)
                return false;
        std::string sub_before_dog=replace_before_dog(email.substr(0,dog));
        int point=email.rfind(".");
        if(point==-1 || point<=dog || email.size()-1-point<2)
                return false;
        std::string sub_after_dog_before_point=replace_after_dog_before_p(email.substr(dog+1,point-dog-1));
        std::string after_point=replace_after_p(email.substr(point+1));
        std::regex start("[[:alnum:]]+");
        std::regex middle("[[:alnum:]]+");
        std::regex end("[[:alpha:]](2,)");
        if(std::regex_match(sub_before_dog,start) && std::regex_match(sub_after_dog_before_point,middle) && after_point=="")
                return true;
        return false;*/

}
bool isvalid_gender(std::string gen)
{
        return (gen=="male" || gen=="female")?true:false;
}
bool isvalid_birth_date(std::string date)
{
        if(!std::regex_match(date,std::regex("[[:digit:]]+(\\.)[[:digit:]]+(\\.)[[:digit:]]+")))
                return false;
        int day=stoi(date.substr(0,date.find("-")));
        date.erase(0,date.find("-")+1);
        int month=stoi(date.substr(0,date.find("-")));
        date.erase(0,date.find("-")+1);
        int year=stoi(date);
        if(day<1 || day>31 || month<1 || month>12 || year>2002 || year<1958)
                return false;
        if ((month==2 && day>29) || (month==4 && day>30) || (month==6 && day>30) || (month==9 && day>30) || (month==11 && day>30) || (year%4!=0 && month==2 && day>28))
                return false;
        return true;
}
bool isvalid_login(std::string log)
{
        std::regex reg("[[:upper:]]");
        if(!std::regex_search(log,reg) || log.size()<8 || log.size()>16)
                return false;
        std::regex rgx("[[:alnum:]]+(\\.|_|-|@)");
        log=std::regex_replace(log,rgx,"");
        return (log=="" || std::regex_replace(log,std::regex("[[:alnum:]]"),"")=="")?true:false;

}
bool isvalid_password(std::string passw)
{
        std::regex upp("[[:upper:]]");
        std::regex dig("[[:digit:]]");
        std::regex low("[[:lower:]]");
        if(!std::regex_search(passw,upp) || !std::regex_search(passw,dig) || !std::regex_search(passw,low) || passw.size()<8 || passw.size()>16)
                return false;
        std::regex rgx("[[:alnum:]]+(\\.|_|-|@)");
        passw=std::regex_replace(passw,rgx,"");
        return (passw=="" || std::regex_replace(passw,std::regex("[[:alnum:]]"),"")=="")?true:false;
}
std::string global(std::map<std::string,std::string> mymap)
{
        std::string response="";

        if(!isvalid_firstname(mymap["firstname"]))
                response+=":firstname:valid";
        else
                response+=":firstname:invalid";

        if(!isvalid_lastname(mymap["lastname"]))
                response+=":lastname:valid";
        else
                response+=":lastname:invalid";

        if(!isvalid_mail(mymap["mail"]))
                response+=":mail:valid";
        else
                response+=":mail:invalid";

        if(!isvalid_gender(mymap["gender"]))
                response+=":gender:valid";
        else
                response+=":gender:invalid";

        if(!isvalid_birth_date(mymap["birth_date"]))
                response+=":birth_date:valid";
        else
                response+=":birth_date:invalid";

        if(!isvalid_login(mymap["login"]))
                response+=":login:valid";
        else
                response+=":login:invalid";

        if(response.find("invalid")==-1)
                return "OK";
        return response;

}

