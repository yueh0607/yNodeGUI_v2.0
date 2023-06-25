#pragma once
#include<vector>
#include<string>
#include<sstream>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include<filesystem>
#include<Windows.h>
using namespace std;



inline vector<string>* split_tovector(const string& str, char c)
{
	vector<string>* tokens = new vector<string>();
	stringstream builder(str);
	string temp;
	while (getline(builder, temp, c))
	{
		tokens->push_back(temp);
	}
	return tokens;
}


inline bool checkPathExists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

inline bool createDirectory(const std::string& directoryPath) {
    int status = CreateDirectory(directoryPath.c_str(), NULL);
    return (status == 0);
}

inline void createFileIfNotExists(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::ofstream newFile(filePath);
        if (newFile) {
            //std::cout << "文件创建成功：" << filePath << std::endl;
            // 可以在这里写入文件内容
            newFile.close();
        }
        else {
            //std::cout << "无法创建文件：" << filePath << std::endl;
        }
    }
    else {
        //std::cout << "文件已存在：" << filePath << std::endl;
    }
}

inline void createPathIfNotExists(const std::string& path) {
    std::istringstream iss(path);
    std::string directory;
    std::string currentPath = "";

    while (std::getline(iss, directory, '/')) {
        currentPath += directory;
        if (!checkPathExists(currentPath)) {
            if (createDirectory(currentPath)) {
                //std::cout << "目录创建成功：" << currentPath << std::endl;
            }
            else {
                //std::cout << "无法创建目录：" << currentPath << std::endl;
                break;
            }
        }
        else {
            //std::cout << "目录已存在：" << currentPath << std::endl;
        }
        currentPath += "/";
    }
}

inline void checkAndCreatePathAndFile(const std::string& filePath) {
    // 获取目录路径
    size_t lastSlashPos = filePath.find_last_of('/');
    std::string directoryPath = filePath.substr(0, lastSlashPos);

    // 检查并创建目录
    createPathIfNotExists(directoryPath);

    // 检查并创建文件
    createFileIfNotExists(filePath);
}


// 打开文件选择窗口
inline string OpenFileSelectionWindow() 
{
    OPENFILENAME ofn;
    char fileName[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "CSV Files (*.csv)\0*.csv\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE) {
        return fileName;
    }
    else {
        return "";
    }
}