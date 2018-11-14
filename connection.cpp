#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

#include "connection.hpp"

bool isFileExist(std::string fileName) {
  struct stat buffer;
  return (stat (fileName.c_str(), &buffer) == 0);
}

void connection::read() {
	if(input.is_open()) {
		std::string msg = "";
		while(this->active) {
			getline(input, msg);
			if("" != msg) {
				recvMessageCallback(this, msg);
				if("q" == msg) {
					this->disconnect();
				}
			}
			usleep(100000);
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

void connection::setID(std::string id) {
	this->id = id;
}

std::string connection::getID() {
	return this->id;
}


void connection::setRecvMessageCallback(recvCallback clbk) {
	recvMessageCallback = clbk;
}

void connection::disconnect() {
	this->active = false;
}

void connection::unbind() {
	this->send("q");
}

connection::connection(std::string in , std::string out) {
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

	this->active = true;

	readerThread = std::thread(&connection::read, this);
}

connection::~connection() {

	readerThread.join();

	input.close();
	output.close();

	std::remove(input_name.c_str());
	std::remove(output_name.c_str());	
}
