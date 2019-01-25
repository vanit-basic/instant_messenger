#include "headers_porc.hpp"
#include "con_porc.cpp"

int main()
{
	Connection client_obj("/home/narek/socket", 0);
//	Connection client_obj1("/home/narek/socket", 0);
	std::string message = "barev server 1_1";
//	std::string message1 = "barev server1_2";
	client_obj.Send((char*)"barev server 1_1", client_obj.getClientFd());
//	client_obj1.Send((char*)"barev server 2_1", client_obj.getClientFd());
	client_obj.Send((char*)"barev server 1_2", client_obj.getClientFd());
//	client_obj1.Send((char*)"barev server 2_2", client_obj.getClientFd());
	while(1)
	{
		std::string msg;

		std::string msg1;
		msg = client_obj.Recive(client_obj.getClientFd());
//		msg1 = client_obj1.Recive(client_obj.getClientFd());
		if (!(msg == ""))// || !(msg1=="")) {
		{	std::cout << "Message1: " << msg << std::endl;
			std::cout << "Message2: " << msg1 << std::endl;
		}
/*		if (!(msg=="") )&& !(msg1==""))
		{
			break;
		}*/
	}

	return 0;
}

