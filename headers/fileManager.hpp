#include <string>
#include <vector>

class fileManager {

	public:
		std::string getFileContent(std::string path);

		bool isFileExist(std::string path);
		bool isDirectory(std::string path);
		bool isRegularFile(std::string path);
		bool isSymLink(std::string path);

		int deleteFolder(std::string path);
		int deleteFile(std::string path);
		int createSymlink(std::string filePath, std::string linkPath);
		int createFile(std::string path, std::string name);
		int createFolder(std::string path);

	public:
		static fileManager* sharedManager();
	
	private:
		fileManager();
	public:
		~fileManager();
};
