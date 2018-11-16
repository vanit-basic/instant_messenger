#include <unistd.h>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include "connection.hpp"

bool isFileExist(std::string fileName) {
	struct stat buffer;
	return (stat(fileName.c_str(),&buffer)==0);
}
void connection::read() {
        if(input.is_open()) {
                std::string msg = "";
                while(true) {
                        getline(input, msg);
			if("q"==msg)
				break;
                       // if("" != msg) {
                                recvMessageCallback(this, msg);
				
                       // }
                        usleep(1000);
                }
        }
}

void connection::send(std::string message) {
        if(output.is_open()) {
                output << message << std::endl;
        } else {
                std::cout << "cant open output" << std::endl;
        }
}

void connection::setRecvMessageCallback(recvCallback clbk) {
        recvMessageCallback = clbk;
}

connection::connection(std::string in,std::string out) {
        if(! isFileExist(in)) {
                mkfifo(in.c_str(), 0666);
        }

        if(! isFileExist(out)) {
                mkfifo(out.c_str(), 0666);
        }
        input = std::ifstream(in, std::ios::in | std::ios::out);
        output = std::ofstream(out, std::ios::in | std::ios::out);

        input_name = in;
        output_name = out;

        readerThread = std::thread(&connection::read, this);
}

connection::~connection() {

        readerThread.join();

        input.close();
        output.close();

 //       std::remove(input_name.c_str());
 //       std::remove(output_name.c_str());

}
class user
{
       private:
               std::strind id;
               std::string firstname;
               std::string lastname;
               std::string mail;
               std::string birth_date;
               std::string gender;
               std::string login;
       pubic: 
	       user(std::string,std::string,std::string,std::string,std::string,std::string,std::string);
               ~user();
               static bool isvalid_firstname(std::string);
               static bool isvalid_lastname(std::string);
               static bool isvalid_mail(std::string);
               static bool isvalid_gender(std::string);
               static bool isvalid_login(std::string);
}
