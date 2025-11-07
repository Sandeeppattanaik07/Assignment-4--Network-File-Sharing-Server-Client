#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/stat.h>
using namespace std;

void handleUpload(int, string);
void handleDownload(int, string);
void handleListFiles(int);
bool authenticateUser(int, string&);
void xorEncryptDecrypt(char*, int);
long getFileSize(string);
void logEvent(string);

char KEY = 'K';

int main() {
    system("clear");
    cout << "============================================\n";
    cout << "       SECURE NETWORK FILE SERVER\n";
    cout << "        C++ | Linux Sockets | WSL\n";
    cout << "============================================\n";

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char option[64];
    string username;

    mkdir("shared_files", 0777);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) { perror("Socket failed"); return 1; }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        return 1;
    }

    cout << "Waiting for client...\n";

    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) { perror("Accept"); return 1; }

    if (!authenticateUser(new_socket, username)) {
        cout << "[AUTH] Failed login attempt.\n";
        close(new_socket);
        close(server_fd);
        return 0;
    }

    cout << "[AUTH] Login successful. User: " << username << "\n";
    logEvent("User " + username + " logged in.");

    while (true) {
        memset(option, 0, sizeof(option));
        read(new_socket, option, sizeof(option));

        // ✅ Remove newline sent from client
        option[strcspn(option, "\n")] = 0;

        if (strcmp(option, "1") == 0) handleUpload(new_socket, username);
        else if (strcmp(option, "2") == 0) handleDownload(new_socket, username);
        else if (strcmp(option, "3") == 0) handleListFiles(new_socket);
        else if (strcmp(option, "4") == 0) break;
    }

    logEvent("User " + username + " disconnected.");
    close(new_socket);
    close(server_fd);
    return 0;
}

bool authenticateUser(int new_socket, string &username) {
    char buffer[1024] = {0};
    read(new_socket, buffer, sizeof(buffer));
    string received = buffer;

    size_t pos = received.find(',');
    if (pos == string::npos) return false;

    username = received.substr(0, pos);
    string password = received.substr(pos + 1);

    ifstream infile("users.txt");
    string user, pass;
    while (infile >> user >> pass) {
        if (user == username && pass == password)
            return true;
    }
    return false;
}

void handleUpload(int new_socket, string username) {
    char filenameBuf[1024] = {0};
    read(new_socket, filenameBuf, sizeof(filenameBuf));
    string filename = filenameBuf;

    char sizeBuf[64];
    read(new_socket, sizeBuf, sizeof(sizeBuf));
    long fileSize = stol(sizeBuf);

    string path = "shared_files/" + filename;
    ofstream outfile(path, ios::binary);

    char buffer[1024];
    long total = 0;

    while (total < fileSize) {
        int bytes = read(new_socket, buffer, sizeof(buffer));
        xorEncryptDecrypt(buffer, bytes);
        outfile.write(buffer, bytes);
        total += bytes;
    }

    outfile.close();
    logEvent("User " + username + " uploaded " + filename);
}

void handleDownload(int new_socket, string username) {
    char buffer[1024] = {0};
    read(new_socket, buffer, sizeof(buffer));
    string filename = buffer;

    string path = "shared_files/" + filename;
    ifstream infile(path, ios::binary);

    if (!infile) {
        string msg = "ERROR";
        send(new_socket, msg.c_str(), msg.size(), 0);
        return;
    }

    long fileSize = getFileSize(path);
    string sizeStr = to_string(fileSize);
    send(new_socket, sizeStr.c_str(), sizeStr.size(), 0);
    usleep(50000);

    char fileBuffer[1024];
    long total = 0;

    while (!infile.eof()) {
        infile.read(fileBuffer, sizeof(fileBuffer));
        int bytes = infile.gcount();
        xorEncryptDecrypt(fileBuffer, bytes);
        send(new_socket, fileBuffer, bytes, 0);
        total += bytes;
    }

    infile.close();
    logEvent("User " + username + " downloaded " + filename);
}

void handleListFiles(int new_socket) {
    DIR* dir = opendir("shared_files");
    struct dirent* entry;
    string list = "";

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            list += entry->d_name;
            list += "\n";
        }
    }
    closedir(dir);

    send(new_socket, list.c_str(), list.size(), 0);
}

void xorEncryptDecrypt(char* data, int size) {
    for (int i = 0; i < size; i++) data[i] ^= KEY;
}

long getFileSize(string filename) {
    ifstream infile(filename, ios::binary | ios::ate);
    return infile.tellg();
}

void logEvent(string text) {
    ofstream log("server_log.txt", ios::app);
    log << text << endl;
}
