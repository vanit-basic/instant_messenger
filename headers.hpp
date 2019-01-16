class request {  // harcum
	private:
		std::string type;
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
}
