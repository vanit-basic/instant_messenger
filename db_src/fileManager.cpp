#include <fileManager.hpp>
#include<sys/stat.h>
#include <unistd.h>
#include <fstream>

static fileManager* shared = NULL;

void fileManager::getFileContent(std::string path, std::string& content) {
}

void fileManager::getDirectoryContent(std::string path, std::vector<std::string>& files) {
}

bool fileManager::isFileExist(std::string path) {
	struct stat buf;
	const char* exist =path.c_str();

	if(stat(exist,&buf)!=0)
		return false;
	else
		return true;

}

bool fileManager::isDirectory(std::string path) {
	return true;
}

bool fileManager::isRegularFile(std::string path) {
	return true;
}

bool fileManager::isSymLink(std::string path) {
	return true;
}

int fileManager::deleteFolder(std::string path, bool recursive) {
	return 0;
}

int fileManager::deleteFile(std::string path) {
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

int fileManager::createFolder(std::string path) {
	return 0;
}

fileManager* fileManager::sharedManager() {
	return shared;
}

fileManager::fileManager() {
	if(NULL == shared) {
		shared = this;
	}
}

fileManager::~fileManager() {

}
