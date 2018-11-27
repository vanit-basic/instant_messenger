#include "validations.hpp"
#include <iostream>
#include <regex>



bool isValidFirstName(std::string fn)
{
	const std::regex pattern ("[A-Z]{1}[a-z]+"); 
	return regex_match (fn,pattern);
}
bool isValidLastName(std::string ln)
{
	const std::regex pattern ("[A-Z]{1}[a-z]+");
	return regex_match (ln,pattern);
}

bool isValidEmail(std::string email)
{
	const std::regex pattern ("(\\w+)(\\.|_)?(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

	return regex_match (email,pattern);
}
bool isValidGender(std::string g)
{

	return (g == "female" || g == "male")?true:false; 
}
bool isValidBirthDate(std::string date)
{
	std::regex pattern ("[[:digit:]]{1,2}[\\.][[:digit:]]{1,2}[\\.][[:digit:]]{4}");
	if (!std::regex_match (date, pattern)) return false;

	std::string days = date.substr(0, date.find("."));
	date.erase(0, date.find(".") +1);
	std::string monthes = date.substr(0, date.find("."));
	date.erase(0, date.find(".") +1);
	std::string years = date;

	int D = stoi(days);
	int M = stoi(monthes);
	int Y = stoi(years);

	if (! (1<=M && M<=12) ) return false;
	if (! (1<=D && D<=31) ) return false;
	if ( (D==31) && (M==2 || M==4 || M==6 || M==9 || M==11) )
		return false;
	if ( (D==30) && (M==2) ) return false;
	if ( (M==2) && (D==29) ) {
		if ( Y%4 != 0 )  return false; }
	if ((2019 - Y) < 16 || (2019 - Y) > 80) return false;
	return true;
}

bool isValidLogin(std::string l)

{
        if (l.length() < 4 || l.length() > 32)
                return false;
        std::regex upper ("[[:upper:]]");
        std::regex digit ("[[:digit:]]");
        std::regex lower ("[[:lower:]]");

        std::regex pattern ("(\\w+)(\\.|_)?");
        if ( std::regex_search (l, upper) && std::regex_search (l, digit) && std::regex_search (l, lower))

                return std::regex_match(l,pattern);
        return false;
}


bool isValidPassword(std::string p)

{
	if (p.length() < 8 || p.length() > 16)
		return false;
	std::regex upper ("[[:upper:]]");
	std::regex digit ("[[:digit:]]");
	std::regex lower ("[[:lower:]]");

	std::regex pattern ("(\\w+)(\\.|_)?");
	if ( std::regex_search (p, upper) && std::regex_search (p, digit) && std::regex_search (p, lower))

		return std::regex_match(p,pattern);
	return false;
}

//string to map

Map myMap(std::string userInfo)
{
        Map infoMap;
        std::string key;
        std::string value;
        userInfo.erase(0,1);
        while (userInfo != "")
        {
                key  = userInfo.substr(0,userInfo.find(":"));
                userInfo.erase(0, userInfo.find(":") +1);
                value = userInfo.substr(0,userInfo.find(":"));
                userInfo.erase(0, userInfo.find(":") +1);
                infoMap.insert (std::pair <std::string, std::string>(key, value));
        }
        return infoMap;
}

//map to string
std::string userInformation (Map infoMap)
{
        std::string userInfo;
	Map::iterator it;
        for (it = infoMap.begin(); it != infoMap.end(); ++it)
        {
                userInfo = userInfo + it->first + ":" + it->second + ":";
        }

        return ":" + userInfo;
}


bool email(std::string mail)
{
	Map emailId;
        Map::iterator it;
        for (it = emailId.begin(); it != emailId.end(); ++it)
        {
                if(it->first==mail)
                        return false;
        }
        return true;
}

bool login(std::string login)
{
	Map logPassId; 
        Map::iterator it;
        for (it = logPassId.begin(); it != logPassId.end(); ++it)
        {
                if(it->first==login)
                        return false;
        }
        return true;
}


