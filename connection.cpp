#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include "connection.hpp"
//stugm a et anunov fayl ka te che
bool isFileExist(std::string fileName) {
	struct stat buff;
	return (stat(fileName.c_str(), &buff)==0);
}
//kardum a pipe-i mejic
void connection::read() {
	if(input.is_open()) {
		std::string msg = "";
		while(true) {
			getline(input, msg);
			if("" != msg) {
				recvMessageCallback(this, msg);
				if("q" == msg) {
					break;
				}
			}
			usleep(100000);
		}
	}
}
//uxarkum a message
void connection::send(std::string message) {
	if(output.is_open()) {
		output << message << std::endl;
	} else {
	//	std::cout << "cant open output" << "\n";
	}
}
//callback functian vor@ stanum a functiayi pointer u read-i stacac message@ qcum a stacac functiayi mej,vorpes erkrord argument
void connection::setRecvMessageCallback(recvCallback clbk) {
	recvMessageCallback = clbk;
}
void connection::setId(std::string id){
	this->id=id;
}
std::string connection::getId(){
	return this->id;
}
//constructor
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
//stop
void connection::stop()
{
	readerThread.detach();
}
//destructor
connection::~connection() {

	readerThread.join();

	input.close();
	output.close();

//	std::remove(input_name.c_str());
//	std::remove(output_name.c_str());	
}
