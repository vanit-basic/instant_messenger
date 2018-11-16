#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include "connection.hpp"

bool isFileExist(std::string fileName) {
	struct stat buff;
	return (stat(fileName.c_str(), &buff)==0);
}

void connection::setId(std::string str)
{
	this->id=str;
}
std::string connection::getId()
{
	return this->id;
}
void connection::read() {
	if(input.is_open()) {
		std::string msg = "";
		while(true) {
			getline(input, msg);
			if("" != msg) {
				recvMessageCallback(this, msg);
				if("quit" == msg) {
					break;
				}
			}
			usleep(1000);
		}
	}
}

void connection::send(std::string message) {
	if(output.is_open()) {
		output << message << std::endl;
	} else {
	//	std::cout << "cant open output" << "\n";
	}
}

void connection::setRecvMessageCallback(recvCallback clbk) {
	recvMessageCallback = clbk;
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

	readerThread = std::thread(&connection::read, this);
}
void connection::stop()
{
	readerThread.detach();
}

connection::~connection() {

	readerThread.join();

	input.close();
	output.close();
	if((this->id) != "Client")
	{
	std::remove(input_name.c_str());
	std::remove(output_name.c_str());
	}
}
