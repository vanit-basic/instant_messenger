#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string>
#include <iostream>
/*
enum RequestType {
	RequestTypeINVALID = -1,
	RequestTypePOST,
	RequestTypeGET,
	RequestTypePUT,
	RequestTypeDELETE,
	RequestTypeOPTIONS
};

<request>
<action>updateUser</action>
<body>body</body>
</request>


class Request {
	private:
		RequestType type;
		std::string url;
		std::map header;
		std::string body;
	public:
		void setType(RequestType);
		void setUrl(const std::string&);
		void setHeader(const std::map&);
		void setBody(const std::string&);
		RequestType getType();
		std::string getUrl();
		std::map getHeader();
		std::string getBody();
		Request(std::string);
		~Request();
}

class Response {
	private:
		int status;
		std::string body;
	public:
		void setStatus(std::string);
		void setBody(std::string);
		std::string getStatus();
		std::string getBody();
		Response(std::string);
		~Response();
}*/
/*
class Maker {
	private:
		std::string body;
	public:
		std::string getBody();
		void setBody(std::string);
		Maker(std::string);
		~Maker();
} */


class Connection {
	private:
		std::string ip;
		std::string port;
		int socket_server_fd;
		int socket_client_fd;
	public:
		std::string getIp();
		std::string getPort();
		bool Send(const std::string&);
		std::string Recive();
		Connection(const std::string path,int quantity);//LocalServer,if(quantity == 0) => client,esle => server
		Connection(const std::string& ip, int port, int quantity); //InetServer,if(quantity == 0) => client,esle => server
		Connection(){}
		~Connection(){}
};

class Service {
	public:
		Connection DBconnection;	
		virtual void send(std::string) = 0;
		virtual std::string recive() = 0;
		virtual std::string getAction(std::string) = 0;
		Service();
		~Service();	
};
