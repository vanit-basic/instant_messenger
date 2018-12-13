#include <IDgenerator.hpp>

std::string IDgenerator::getUserId()
{
	std::ifstream user_read(user_file);
	std::string uid = "";
	std::getline(user_read, uid);
	user_read.close();
	std::ofstream user_write(user_file);
	if(uid == "")
	{
		uid = "0";
		user_write << uid;
		uid = "u" + uid;
	}
	else
	{
		uid = std::to_string(std::stoi(uid) + 1);
		user_write << uid;
		uid ="u" + uid;
	}
	user_write.close();
	return uid;
}
std::string IDgenerator::getGroupId()
{
	std::ifstream group_read(group_file);
	std::string gid = "";
	std::getline(group_read, gid);
	group_read.close();
	std::ofstream group_write(group_file);
	if(gid == "")
	{
		gid = "0";
		group_write << gid;
		group_write << std::endl;
		gid = "g" + gid;
	}
	else
	{
		gid = std::to_string(std::stoi(gid) + 1);
		group_write << gid;
		group_write << std::endl;
		gid ="g" + gid;
	}
	group_write.close();
	return gid;

}

IDgenerator::IDgenerator(std::string userIdtxt, std::string groupIdtxt)
{
	group_file = "db_files/resources/" + groupIdtxt;
	user_file = "db_files/resources/" + userIdtxt;
	user = std::ofstream(user_file);
	std::string id = "0";
	user << id;
	user.close();
        group = std::ofstream(group_file);
	group << id; 
	group.close();
}
IDgenerator::~IDgenerator()
{
	user.close();
	group.close();
}
