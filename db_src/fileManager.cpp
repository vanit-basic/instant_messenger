#include <fileManager.hpp>

static fileManager* shared = NULL;

void fileManager::getFileContent(std::string path, std::string& content) {
}

void fileManager::getDirectoryContent(std::string path, std::vector<std::string>& files) {
}

bool fileManager::isFileExist(std::string path) {
	bool flag = false;
        std::ifstream file(path);
        if(file.is_open()){
                flag = true;
        }
        file.close();
        return flag;

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
	return 0;
}

int fileManager::createFile(std::string path) {
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
