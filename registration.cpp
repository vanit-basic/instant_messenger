#include<iostream>
 std::cout<<"Enter your information\n";
                                        do
                                        {
                                                std::cout<<"Firstname: ";
                                                getline(std::cin,msg);
                                                if(!isvalid_firstname(msg))
                                                        std::cout<<"Invalid firstname!\n";
                                        }
                                        while(!isvalid_firstname(msg));
                                        info+=":firstname:"+msg;

                                        do
                                        {
                                                std::cout<<"Lastname: ";
                                                getline(std::cin,msg);
                                                if(!isvalid_lastname(msg))
                                                        std::cout<<"Invalid lastname!\n";
                                        }
                                        while(!isvalid_lastname(msg));
                                        info+=":lastname:"+msg;

                                        do
                                        {
                                                std::cout<<"Mail: ";
                                                getline(std::cin,msg);
                                                if(!isvalid_mail(msg))
                                                        std::cout<<"Invalid mail!\n";
                                        }
                                        while(!isvalid_mail(msg));
                                        info+=":mail:"+msg;

                                        do
                                        {
                                                std::cout<<"Birth date: ";
                                                getline(std::cin,msg);
                                                if(!isvalid_birth_date(msg))
                                                        std::cout<<"Invalid birth date!\n";
                                        }
                                        while(!isvalid_birth_date(msg));
                                        info+=":birth_date:"+msg;

                                        do
                                        {
                                                std::cout<<"Gender: ";
                                                getline(std::cin,msg);
                                                if(!isvalid_gender(msg))
                                                        std::cout<<"Invalid gender!\n";
                                        }
                                        while(!isvalid_gender(msg));
                                        info+=":gender:"+msg;

