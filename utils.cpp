#include "utils.hpp"
#include <regex>
#include <cmath>
#include <iostream>
#include <map>

void string_to_map(std::map<std::string, std::string>, std::string msg)
{
	std::string key="";
	std::string value="";
	std::map<std::string, std::string> datebase;
	while(msg!="")
	{
		key = msg.substr(0, msg.find(':'));
		msg.erase(0, msg.find(':')+1);
		value = msg.substr(0, msg.find(':'));
		msg.erase(0, msg.find(':')+1);
		datebase.emplace(key, value);
	}

}
std::string map_to_string(std::map<std::string, std::string> datebase)
{
	std::string message="";
	std::map<std::string, std::string>::iterator k=datebase.begin();
        for(; k != datebase.end(); ++k)
	{
		message=message +":" + k->first + ":" + k->second;
	}
	message = message + ":";
	return message;
}
void string_to_map_and_log_pass(std::map<std::string, std::string>, std::string msg, std::string& log, std::string& pass)
{
	std::string key="";
	std::string value="";
	std::map<std::string, std::string> datebase;
	while(msg!="")
	{
		key = msg.substr(0, msg.find(':'));
		msg.erase(0, msg.find(':')+1);
		value = msg.substr(0, msg.find(':'));
		msg.erase(0, msg.find(':')+1);
		if(key=="Login")
		{
			log=value;
		}
		if(key=="Password")
		{
			pass=value;
		}
		datebase.emplace(key, value);
	}

}
bool isValidE_mail(std::string mail)
{
	bool isValid = true;
	int k=0, n=0, s=0;
	s=mail.size();
	std::string copyMail;
	std::regex mail1 ("[A-Za-z0-9]{2,}");
	std::regex mail3 ("[A-Za-z]{2,}");
	std::regex mail2 ("[A-Za-z0-9]+@");
	std::regex beforeAt("[A-Za-z0-9]+(\\.|_|-)");
	std::regex afterAt("[A-Za-z0-9]+(\\.|-)");
	if(s<4 || s>32)
	{
		isValid = false;
	}
	else
	{
		k=mail.find('@');
		n=mail.rfind('.');
		copyMail=mail.substr(0,k+1);
		copyMail=std::regex_replace(copyMail, beforeAt, "");
		if(regex_match(copyMail,mail2))
		{
			copyMail=mail.substr(k+1,n-k);
			copyMail=std::regex_replace(copyMail, afterAt, "");
			if(copyMail=="")
			{
				copyMail=mail.substr(n+1,mail.size()-n-1);
				if(regex_match(copyMail,mail3))
				{
					isValid = true;
				}
				else
				{
					isValid = false;
				}
			}
			else
			{
				isValid=false;
			}
		}
		else
		{
			isValid = false;
		}

	}
	return isValid;
}
bool isValidName(std::string name)
{
	bool isValid = true;
	if (name[0] >= 'A' && name[0] <= 'Z')
	{
		for (int i = 1; i < name.size(); i++)
		{
			if (name[i] < 'a' || name[i] > 'z')
			{
				isValid = false;
				break;
			}
		}
	}
	else
	{
		isValid = false;
	}
	return isValid;
}
bool isValidBirthDate(std::string date)
{
	bool isValid=true;
	int day=0;
	int mounth=0;
	int year=0;
	std::string copydate=date;
	std::regex birthdate("\\d{2}\\.\\d{2}\\.\\d{4}");
	copydate=std::regex_replace(copydate, birthdate, "");
	if(copydate!="")
	{
		isValid=false;
	}
	else
	{
		copydate=date.substr(0, 2);
		day=stoi(copydate);
		if(31 < day)
		{
			isValid=false;
		}
		else
		{
			copydate = date;
			copydate = copydate.erase(0, 3);
			copydate=copydate.substr(0, 2);
			mounth = stoi(copydate);
			if(mounth>12)
			{
				isValid=false;
			}
			else
			{
				copydate = date;
				copydate = copydate.erase(0, 6);
				year = stoi(copydate);
				if((1900 > year) || (2002 < year))
				{
					isValid=false;
				}
				else 
				{
					if(((mounth==2) && (day>29)) || ((year%4!=0) && (mounth==2) && (day>28)))
					{
						isValid=false;
					}
					else 
					{
						if((mounth==4 || mounth==6 || mounth==9 || mounth==11) && day>30)
						{
							isValid=false;
						}
					}
				}
			}
		}
	}
	return isValid;
}
bool isValidLogin(std::string login)
{
	bool isValid=true;
	std::string log=login;

	if((6 > log.size()) || (32 < log.size()))
	{
		isValid = false;
	}
	else
	{
		std::regex end("[A-Za-z0-9]+");
		log=log.erase(0,log.size()-2);
		log=std::regex_replace(log, end,"");
		if(log!="")
		{
			isValid=false;
		}
		else
		{
			log=login;
			std::regex l("[A-Za-z0-9]+(\\.|-|_|@){0,1}");
			log = std::regex_replace(log, l, "");
			log=std::regex_replace(log, end,"");

			if(log!="")
			{
				isValid = false;
			}

		}
	}
	return isValid;
}
bool isValidGender(std::string gender)
{
	bool isValid = true;
	if(!(gender=="male" || gender=="female"))
	{
		isValid = false;
	}
	return isValid;
}
bool isValidPassword(std::string password)
{
	bool isValid=true;
	bool l=false;
	bool s=false;
	bool n=false;
	std::string copypass=password;
	if((8 > copypass.size()) || (16 < copypass.size()))
	{
		isValid = false;
	}
	else
	{

		std::regex p("[A-Za-z0-9]+");
		copypass=std::regex_replace(copypass, p, "");
		if(copypass!="")
		{
			isValid=false;
		}
		else
		{
			copypass=password;
			std::regex l("[A-Z]");
			std::regex s("[a-z]");
			std::regex n("[0-9]");
			if(!(regex_search(password, l) && regex_search(password, s) && regex_search(password, n)))
			{
				isValid=false;
			}
		}
	}
	return isValid;
}
bool test(std::string& str, std::string msg)
{
	bool isValidFirstName=true;
	bool isValidLastName=true;
	bool isValidDate=true;
	bool isValidGen=true;
	bool isValidEmail=true;
	bool isValidLog=true;
	bool isValidPass=true;
	std::string key="";
	std::string value="";
	while(msg!="")
	{
		key = msg.substr(0, msg.find(':'));
		msg.erase(0, msg.find(':')+1);
		value = msg.substr(0, msg.find(':'));
		msg.erase(0, msg.find(':')+1);

		if("FirstName"==key)
		{
			if(!isValidName(value))
			{
				str = str.erase(str.find(key)-1, key.size()+value.size()+2);
				str=str + key + ":" + "INVALID" + ":";
				isValidFirstName=false;
			}
		}
		if("LastName"==key)
		{
			if(!isValidName(value))
			{
				str = str.erase(str.find(key)-1, key.size()+value.size()+2);
				str=str + key + ":" + "INVALID" + ":";
				isValidLastName=false;
			}
		}
		if("BirthDate"==key)
		{
			if(!isValidBirthDate(value))
			{
				str = str.erase(str.find(key)-1, key.size()+value.size()+2);
				str=str + key + ":" + "INVALID" + ":";
				isValidDate=false;
			}
		}
		if("Gender"==key)
		{
			if(!isValidGender(value))
			{
				str = str.erase(str.find(key)-1, key.size()+value.size()+2);
				str=str + key + ":" + "INVALID" + ":";
				isValidGen=false;
			}
		}
		if("Email"==key)
		{
			if(!isValidE_mail(value))
			{
				str = str.erase(str.find(key)-1, key.size()+value.size()+2);
				str=str + key + ":" + "INVALID" + ":";
				isValidEmail=false;
			}
		}
		if("Login"==key)
		{
			if(!isValidLogin(value))
			{
				str = str.erase(str.find(key)-1, key.size()+value.size()+2);
				str=str + key + ":" + "INVALID" + ":";
				isValidLog=false;
			}
		}
		if("Password"==key)
		{
			if(!isValidPassword(value))
			{
				str = str.erase(str.find(key)-1, key.size()+value.size()+2);
				str=str + key + ":" + "INVALID" + ":";
				isValidPass=false;
			}
		}
	}
	if (isValidFirstName && isValidLastName && isValidDate && isValidGen && isValidEmail && isValidLog && isValidPass)
	{
		return true;
	}
	else
	{
		return false;
	}
}
