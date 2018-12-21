#include <fileManager.hpp>
<<<<<<< HEAD
#include<sys/stat.h>
#include <unistd.h>
#include <fstream>

=======
#include <sys/stat.h>
#include <unistd.h>
>>>>>>> 7d0c1023801209c62eba9fdad0bd82383bffae8c
static fileManager* shared = NULL;

void fileManager::getFileContent(std::string path, std::string& content) {
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
