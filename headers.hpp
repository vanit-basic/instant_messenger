/*class request {  // harcum
	private:
		type;
		std::string url;
		std::string header;
		std::string body;
	public:
		void setType(std::string);
		void setUrl(std::string);
		void setHeader(std::string);
		void setBody(std::string);
		std::string getType();
		std::string getUrl();
		std::string getHeader();
		std::string getBody();
		request(std::string);
		~request();
}


class response {  // patasxan
	private:
		std::string url;
		std::string header;
		std::string body;
	public:
		void setUrl(std::string);
		void setHeader(std::string);
		void setBody(std::string);
		std::string getUrl();
		std::string getHeader();
		std::string getBody();
		response(std::string);
		~response();
}*/

class connection {
	private:
		std::string ip;
		std::string port;
	public:
		std::string getIp();
		std::string getPort();
		void send(std::string);
		std::string recive();
		connection( std::string, std::string ); //(ip, path, request's string)
		~connection();
}

class Service {
	connection DBconnection;	
	virtual void send(std::string) = 0;
	virtual std::string recive() = 0;
	virtual std::string getAction() = 0;
}










