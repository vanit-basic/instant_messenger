#include "headers.hpp"

int main()
{
	Connection serv_obj("/home/user/socket", 4);
	//Connection client_obj("/home/narek/socket", 0);
	//client_obj.Send("barev server");
	//serv_obj.Send("asdasdasdas");
	std::string x;
	while(x=="")
	{
	x=serv_obj.Recive();
	}
	std::cout<<x<<"\n";
	return 0;
}
