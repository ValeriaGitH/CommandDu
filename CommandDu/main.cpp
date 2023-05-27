//
//  main.cpp
//  CommandDu
//
//  Created by Valeria Keshishyan on 24.05.2023.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

#define BLOCK_SIZE 512

void printSize(long long size, string path) {
    cout << size << "\t" << path << endl;
}

void du(string path, bool all, bool bytes, bool summary, long long *size) {
    
    DIR* dir = opendir(path.c_str());
    if (dir == NULL) {
        cerr << "Error: cannot open directory " << path << endl;
        return;
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        string name = entry->d_name;
        if (name == "." || name == "..") {
            continue;
        }
        string full_path = path + "/" + name;
        struct stat st;
        if (stat(full_path.c_str(), &st) != 0) {
            cerr << "Error: cannot get information about " << full_path << endl;
            continue;
        }
        if (S_ISDIR(st.st_mode)) {
            du(full_path, all, bytes, summary, size);
        } else {
            long long file_size = st.st_size;
            if (!bytes) {
                file_size = ((file_size + BLOCK_SIZE - 1) / BLOCK_SIZE);
            }
            *size += file_size;
            if (all) {
                if (summary) printSize(*size, full_path);
                else printSize(file_size, full_path);
            }
        }
    }
    closedir(dir);

    if (!bytes) *size+=1;
}

int main(int argc, const char * argv[]) {
    vector<string> paths;
    bool all = false; //данные и для каждого файла;
    bool bytes = false; //точный размер в байтах;
    bool total = false; //в конце общий размер;
    bool summary = false; //только общий размер
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-a") {
            all = true;
        } else if (arg == "-b") {
            bytes = true;
        } else if (arg == "-c") {
            total = true;
        } else if (arg == "-s") {
            summary = true;
        } else if (arg.substr(0, 12) == "--files-from") { //пути из файла
            string file_path = arg.substr(13);
            ifstream file(file_path);
            if (!file.is_open()) {
                cerr << "Error: cannot open file " << file_path << endl;
                return 1;
            }
            string line;
            while (getline(file, line)) {
                paths.push_back(line);
            }
            file.close();
        } else {
            paths.push_back(arg);
        }
    }
    if (paths.empty()) {
        paths.push_back(".");
    }
    for (string path : paths) {
        long long size = 0;
        du(path, all, bytes, summary, &size);
        if (total) cout << size << "\ttotal" << endl;
    }

    return 0;
}
