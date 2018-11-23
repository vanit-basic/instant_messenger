#include <string>

enum socketType {
	sInvalid = -1,
	sClient,
	sServer
};

class socketpp {
	private:
		int fd;
		socketType type;
		int port;
	public:
		std::string sread ();
		int ssend(std::string);
		bool sconnect();
		socketpp(int port, socketType type);
		~socketpp();
};
