#include "headers_porc.hpp"

int main()
{
	Connection client_obj("/home/narek/socket", 0);
	Connection client_obj1("/home/narek/socket", 0);
	client_obj.Send((char*)"barev server 1_1", client_obj.getClientFd());
	client_obj.Send((char*)"barev server 1_2", client_obj.getClientFd());
	client_obj1.Send((char*)"barev server 2_1", client_obj1.getClientFd());
	client_obj1.Send((char*)"barev server 2_2", client_obj1.getClientFd());
	while(1)
	{
		std::string msg1;

		std::string msg2;
		msg1 = client_obj.Recive(client_obj.getClientFd());
		msg2 = client_obj1.Recive(client_obj1.getClientFd());
		if (!(msg1 == "")) 
		{	std::cout << "Message1: " << msg1 << std::endl;
		}
		if (!(msg2 == ""))
		{
			std::cout << "Message2: " << msg2 << std::endl;
		}
		msg1 = "";
		msg2 = "";
	}

	return 0;
}

