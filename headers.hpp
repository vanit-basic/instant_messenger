enum RequestType {
	RequestTypeINVALID = -1;
	RequestTypePOST,
	RequestTypeGET,
	RequestTypePUT,
	RequestTypeDELETE,
	RequestTypeOPTIONS
};

/*<request>
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

class Service {
	public:
		connection DBconnection;	
		virtual void send(std::string) = 0;
		virtual std::string recive() = 0;
		virtual std::string getAction(std::string) = 0;
		Service();
		~Service();	
}

class Connection {
	private:
		std::string ip;
		std::string port;
	public:
		std::string getIp();
		std::string getPort();
		void send(const std::string&);
		const std::string& recive();
		Connection(const std::string&, const std::string&); //(ip, port)
		~Connection();
}
