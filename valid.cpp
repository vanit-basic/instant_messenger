#include "connectionUser.h"

#include <iostream>
#include <unistd.h>
#include <mutex>
#include <string>
#include <map>
#include <string>
#include <regex>
#include <thread>

bool isValidMail(std::string mail) {
	bool isValid = true;
	int k = 0;
	int n = 0;
	int s = 0;
	s = mail.size();
	std::string copyMail;
	std::regex mail1 ("[A-Za-z0-9]{2,}");
	std::regex mail3 ("[A-Za-z]{2,}");
	std::regex mail2 ("[A-Za-z0-9]+@");
	std::regex beforeAt("[A-Za-z0-9]+(\\.|_|-)");
	std::regex afterAt("[A-Za-z0-9]+(\\.|-)");
	if (s < 4 || s > 32) {
		isValid = false;
	} else {
		k = mail.find('@');
		n = mail.rfind('.');
		copyMail = mail.substr(0, k + 1);
		copyMail = std::regex_replace(copyMail, beforeAt, "");
		if(regex_match(copyMail, mail2)) {
			copyMail = mail.substr(k + 1, n - k);
			copyMail = std::regex_replace(copyMail, afterAt, "");
			if (copyMail == "") {
				copyMail = mail.substr(n + 1, mail.size() - n - 1);
				if (regex_match(copyMail, mail3)) {
					isValid = true;
				} else {
					isValid = false;
				}
			} else {
				isValid=false;
			}
		} else {
			isValid = false;
		}
	}
	return isValid;
}

bool isValidName(std::string name) {
	int n = name.length();
	bool t = true;
	if (n > 1) {
		if (name[0] >= 'A' && name[0] <= 'Z') {
			t = true;
		} else {
			return false;
		}

		for (int i = 1; i < n; ++i) {
			if (name[i] >= 'a' && name[i] <= 'z') {
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
		if (surname[0] >= 'A' && surname[0] <= 'a') {
			t = true;
		} else {
			return false;
		}

		for (int i = 1; i < n; ++i) {
			if (surname[i] >= 'a' && surname[i] <= 'z') {
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
	if (n == 10) {
		std::string day = birthdate.substr(0, 2);
		std::string month = birthdate.substr(3, 2);
		std::string year = birthdate.substr(6, 4);
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
		} else {
			return false;
		}
		return t;
	}
}

bool isValidGender(std::string gender) {
	int n = gender.length();
	if (n >= 4) {
		if (gender == "male" || gender == "female") {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool isValidLogin(std::string login) {
	int n = login.length();
	bool t = true;
	if (n >= 6) {
		for (int i = 0; i < n; ++i) {
			if ((login[i] >= 'a' && login[i] <= 'z') || (login[i] >= 48 && login[i] <= 57)) {
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

bool isValidPass(std::string password) {
	if (password.length() >= 8) {
		return true;
	} else {
		return false;
	}
}

