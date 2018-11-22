
#include <map>
#include <string>
#include <iostream>
#include <regex>

bool isValidName(std::string name) {
    int n = name.length();
    bool t = true;
    if (n > 1) {
        if (name[0] > 'A' && name[0] < 'Z') {
            t = true;
        } else {
            return false;
        }

        for (int i = 1; i < n; ++i) {
            if (name[i] > 'a' && name[i] < 'z') {
                t = true;
            } else {
                return false;
            }
        }
    } else {
        t = false;
    }

    return t;
}

bool isValidSurname(std::string surname) {
    int n = surname.length();
    bool t = true;
    if (n > 1) {
        if (surname[0] > 'A' && surname[0] < 'a') {
            t = true;
        } else {
            return false;
        }

        for (int i = 1; i < n; ++i) {
            if (surname[i] > 'a' && surname[i] < 'z') {
                t = true;
            } else {
                return false;
            }
        }
    } else {
        t = false;
    }

    return t;
}

bool isValidBirthdate(std::string birthdate) {
    int n = birthdate.length();
    std::string day = birthdate;
    std::string month = birthdate;
    std::string year = birthdate;
    day.erase(2, n - 3);
    month.erase(0, 3);
    month.erase(3, n - 2);
    year.erase(0, n - 4);
    bool t = false;

    if (stoi(year) > 1900 && stoi(year) < 2008) { 
        if (month == "01" || month == "05" || month == "07" || month == "08" || month == "10" || month == "12") {
            if (stoi(day) <= 31 && stoi(day) > 0) {
                t = true;
            }
        } else if (month == "04" || month == "06" || month == "09" || month == "11") {
            if (stoi(day) <= 30 && stoi(day) > 0) {
                t = true;
            }
        } else if (month == "02") {
            if (stoi(year) % 4 == 0 && stoi(day) <= 29) {
                t = true;
            } else if (stoi(day) <= 28) {
                t = true;
            }
        }

        return t;
    }
}

bool isValidGender(std::string gender) {
    if (gender == "male" || gender == "female") {
        return true;
    } else {
        return false;
    }
}

bool isValidLogin(std::string login) {
    int n = login.length();
    bool t = true;
    if (n >= 4) {
        if (login[0] > 'A' && login[0] < 'a') {
            t = true;
        } else {
            return false;
        }

        for (int i = 1; i < n; ++i) {
            if (login[i] > 'a' && login[i] < 'z') {
                t = true;
            } else if (login[i] == 45 || login[i] == 46 || login[i] == 64 || login[i] == 95) {
                t = true;
            } else {
                return false;
            }
        }
    } else {
        t = false;
    }

    return t;
}

std::string replaceBeforeDog(std::string mail){
	std::regex e("[[:alnum:]]+(\\.|-|_)");
 	return std::regex_replace(mail, e, "");
	
}

std::string replaceAfterDog(std::string mail){
	std::regex e("[[:alnum:]]+(\\.|-)");
 	return std::regex_replace(mail, e, "");
}

std::string replaceBeforePoint(std::string mail){
	std::regex e("[[:alpha:]]");
 	return std::regex_replace(mail, e, "");
}



bool isValidMail(std::string mail){
	int posDog = mail.find("@");	
	int posPoint = mail.rfind(".");
	if(posDog == -1 || posPoint == -1 || posPoint < posDog || (mail.length() - posPoint - 1) < 2 ) {
		return false;
        }
	
	std::string strBeg = replaceBeforeDog(mail.substr(0, posDog));
	std::string strMid = replaceAfterDog(mail.substr(posDog + 1, posPoint - posDog - 1));
	std::string last = replaceBeforePoint(mail.substr(posPoint + 1));
	std::regex beg("[[:alnum:]]+");
	std::regex mid("[[:alnum:]]+");
	if (std::regex_match(strBeg, beg) && std::regex_match(strMid, mid) && last == "" ) {
		return true;
        } else {
		return false;
        }
}
