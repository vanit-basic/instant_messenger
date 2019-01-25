#include "headers_porc.hpp"

int main()
{
	Connection serv_obj("/home/narek/socket", 2);
	std::string x;
	std::list<int> sockets = serv_obj.getSocketClientFd();
	std::list<int>::iterator it;

	while(1)
	{
		for(it = sockets.begin(); it!=sockets.end(); ++it)
		{
			x = serv_obj.Recive(*it);

			if (!(x==""))
			{
				std::cout<<x<<"\n";
				serv_obj.Send("Staca", *it);
				
			}

		}
	}
	return 0;
}
