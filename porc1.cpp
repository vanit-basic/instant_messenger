#include "headers.hpp"

int main()
{
        //Connection serv_obj("/home/narek/socket", 4);
        Connection client_obj("/home/user/socket", 0);
        client_obj.Send("barev server");
        //serv_obj.Send("asdasdasdas");
        //std::cout<<serv_obj.Recive()<<std::endl;
        return 0;
}

