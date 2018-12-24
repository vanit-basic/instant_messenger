#include <fileManager.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <dirent.h>
#include <string.h>
static fileManager* shared = NULL;

std::string fileManager::getFileContent(std::string path) {
	std::string content ="";
	std::string tmp ="";
	if(!shared->isRegularFile(path) || !shared->isSymLink(path))
		return "no such file";
	else{
		std::ifstream file(content);
		while(file >> tmp){
			content += tmp;
		}
		return content;
	}


}

bool fileManager::isFileExist(std::string path) {
	struct stat buf;
	const char* exist =path.c_str();

	if(stat(exist,&buf)!=0)
		return false;
	else
		return true;

}

bool fileManager::isDirectory(std::string stringPath) {
	const char* path = stringPath.c_str();
	struct stat buf;
	stat(path, &buf);
	return S_ISDIR(buf.st_mode);
}

bool fileManager::isRegularFile(std::string path) {
	struct stat sb;
	const char * pat = path.c_str();
	if (stat(pat, &sb) == 0 && S_ISREG(sb.st_mode)) {
		return true;
	} else {
		return false;
	}
}

bool fileManager::isSymLink(std::string path) {
	const char* Link =path.c_str();
	int tmp;
	struct stat buf;
	tmp=lstat(Link , &buf);
	if(tmp == 0 && S_ISLNK(buf.st_mode)){
		return true;
	}
	else{
		return false;
	}
	return false;
}

int fileManager::deleteFolder(std::string stringPath) {
	if(!shared->isDirectory(stringPath))
		return 1;
	struct dirent *entry = NULL;
	DIR *dir = NULL;
	const char* path = stringPath.c_str();
	dir = opendir(path);
	while(entry = readdir(dir)){
		DIR *sub_dir = NULL;
		FILE *file = NULL;
		char* abs_path = new char[256];
		if ((*(entry->d_name) != '.') || ((strlen(entry->d_name) > 1) && (entry->d_name[1] != '.'))){
			sprintf(abs_path, "%s/%s", path, entry->d_name);
			if(sub_dir = opendir(abs_path))	{
				closedir(sub_dir);
			/*	shared->*/deleteFolder(abs_path);
			}
			else{
				if(file = fopen(abs_path, "r"))	{
					fclose(file);
					remove(abs_path);
				}
			}
		}
		delete[] abs_path;
	}
	remove(path);
	return 0;
}

int fileManager::deleteFile(std::string path) {
	int status = std::remove(path.c_str());
	if(status !=0){
		if(errno == EBUSY) return 1;
		else return -1;
	}
	return 0;
}

int fileManager::createSymlink(std::string filePath, std::string linkPath) {
	if(!shared->isFileExist(filePath))
		return 1;
	symlink(filePath.c_str(), linkPath.c_str());
	return 0;
}

int fileManager::createFile(std::string path, std::string name) {

	std::ofstream outfile;
	std::string createFile = "";
	createFile = path + "/" + name;
	outfile.open(createFile.c_str());
	outfile.close();

	return 0;
}

int createFolder(std::string path) {
	const char* pat = path.c_str();
	int status = 0;
	struct stat sb;
	if (stat(pat, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		status = 1;
	}
	else
	{
		mode_t process_mask = umask (0);
		status = mkdir(pat, 0777);
		umask (process_mask);
	}
	return status;
}

fileManager* fileManager::sharedManager() {
	if(!shared) shared = new fileManager;
	return shared;
}

fileManager::fileManager() {
	shared = this;
}

fileManager::~fileManager() {

}
