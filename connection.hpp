#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <fstream>
#include <string>
#include <thread>

class connection;

typedef void (*recvCallback) (connection*, std::string);

class connection {
	private:
		std::string id;
		std::string input_name;
		std::string output_name;

		std::ifstream input;
		std::ofstream output;

		bool active;

		recvCallback recvMessageCallback;
		std::thread readerThread;

		void read();
				
	public:
		void setID(std::string id);
		std::string getID();

		void send(std::string message);

		void setRecvMessageCallback(recvCallback clbk);

		void unbind();

		void disconnect();

		connection(std::string, std::string);
		~connection();
};

#endif
