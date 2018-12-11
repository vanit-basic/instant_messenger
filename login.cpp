#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

int main() {
    std::string login = "";
    std::cout << "Enter login: ";
    std::cin >> login;

    std::string pass = "";
    std::cout << "Enter password: ";
    std::cin >> pass;

    // Open directory with login name
    DIR* loginDir = opendir(login.c_str());
    if (!loginDir) {
        // If there is not directory with such name then login and / or password is not available
        std::cout << "Your login and / or password is not available! Please, try again!" << std::endl;
    } else {
        // Open pass.txt
        std::string path = "./" + login + "/pass.txt"; 
        std::ifstream passFile(path.c_str());
        if (passFile.is_open()) {
            std::string tempPass;
            // If password matches print user id 
            if (std::getline(passFile, tempPass)) {
                if (pass.compare(tempPass) == 0) {
                    std::string id = "";
                    if (std::getline(passFile, id)) {
                        std::cout << "Your id is " << id << std::endl;
                    }
            } else {
                // Login and / or pass is not available
                std::cout << "Your login and / or password is not aveilable! Please, try again!" << std::endl;
            }
        }

        passFile.close();
    } else {
        std::cout << "Error 404 not found" << std::endl;
    }
}
    // return 0 if the file is closed, else return 1
    return closedir(loginDir);
}
