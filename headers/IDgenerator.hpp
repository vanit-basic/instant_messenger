#ifndef IDGENERATOR_HPP
#define IDGENERATOR_HPP
#include <fstream>
#include <string>
#include <iostream>

static std::ofstream user;
static std::ofstream group;
static std::string user_file;
static std::string group_file;

class IDgenerator
{
        public:
                static std::string getUserId();
                static std::string getGroupId();
                IDgenerator(std::string, std::string);
		IDgenerator(){}
                ~IDgenerator();
};
#endif
