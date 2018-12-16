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
		uid = "1";
		user_write << uid;
		user_write << std::endl;
		uid = "u" + uid;
	}
	else
	{
		uid = std::to_string(std::stoi(uid) + 1);
		user_write << uid;
		user_write << std::endl;
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
		gid = "1";
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

std::string IDgenerator::getMessageId()
{
	std::ifstream message_read(message_file);
	std::string mid = "";
	std::getline(message_read, mid);
	message_read.close();
	std::ofstream message_write(message_file);
	if(mid == "")
	{
		mid = "1";
		message_write << mid;
		message_write << std::endl;
		mid = "m" + mid;
	}
	else
	{
		mid = std::to_string(std::stoi(mid) + 1);
		message_write << mid;
		message_write << std::endl;
		mid ="m" + mid;
	}
	message_write.close();
	return mid;
}
IDgenerator::IDgenerator(std::string userIdtxt, std::string groupIdtxt, std::string messagetxt)
{
	group_file = "db_files/resources/" + groupIdtxt;
	user_file = "db_files/resources/" + userIdtxt;
	message_file = "db_files/resources/" + messagetxt;
	std::ifstream verification_user_file(user_file);
	if (!verification_user_file.is_open())
	{
		user = std::ofstream(user_file);
		user.close();
	}
	else
	{
		verification_user_file.close();
	}
	std::ifstream verification_group_file(group_file);
	if (!verification_group_file.is_open())
	{
		group = std::ofstream(group_file);
		group.close();
	}
	else
	{
		verification_group_file.close();
	}
	std::ifstream verification_message_file(message_file);
	if (!verification_message_file.is_open())
	{
		message = std::ofstream(message_file);
		message.close();
	}
	else
	{
		verification_message_file.close();
	}
}
IDgenerator::~IDgenerator()
{
	user.close();
	group.close();
	message.close();
}
