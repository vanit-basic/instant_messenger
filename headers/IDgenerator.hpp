#ifndef IDGENERATOR_HPP
#define IDGENERATOR_HPP
#include <fstream>
#include <string>
#include <iostream>

static std::ofstream user;
static std::ofstream group;
static std::ofstream message;
static std::string user_file;
static std::string group_file;
static std::string message_file;

class IDgenerator
{
        public:
                static std::string getUserId();
                static std::string getGroupId();
                static std::string getMessageId();
                IDgenerator(std::string, std::string, std::string);
		IDgenerator(){}
                ~IDgenerator();
};
#endif
