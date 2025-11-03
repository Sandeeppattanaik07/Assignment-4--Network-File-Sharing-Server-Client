#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <dirent.h>
using namespace std;

void handleUpload(int);
void handleDownload(int);
void handleListFiles(int);
bool authenticateUser(int);
void xorEncryptDecrypt(char*, int);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char option[10];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        return 1;
    }

    cout << "Server ready. Waiting for client connection...\n";

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        return 1;
    }

    // Step 1: Authenticate user
    if (!authenticateUser(new_socket)) {
        cout << "Authentication failed. Closing connection.\n";
        close(new_socket);
        close(server_fd);
        return 0;
    }

    cout << "Authentication successful! Client connected.\n";

    while (true) {
        memset(option, 0, sizeof(option));
        int val = read(new_socket, option, sizeof(option));
        if (val <= 0) break;

        if (strcmp(option, "1") == 0) handleUpload(new_socket);
        else if (strcmp(option, "2") == 0) handleDownload(new_socket);
        else if (strcmp(option, "3") == 0) handleListFiles(new_socket);
        else if (strcmp(option, "4") == 0) {
            cout << "Client disconnected.\n";
            break;
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}

// XOR encryption/decryption
void xorEncryptDecrypt(char* data, int size) {
    char key = 'K';
    for (int i = 0; i < size; ++i) {
        data[i] ^= key;
    }
}

// User authentication
bool authenticateUser(int new_socket) {
    char buffer[1024] = {0};
    read(new_socket, buffer, sizeof(buffer));
    string received = buffer;

    size_t pos = received.find(',');
    if (pos == string::npos) return false;

    string username = received.substr(0, pos);
    string password = received.substr(pos + 1);

    ifstream infile("users.txt");
    string user, pass;
    while (infile >> user >> pass) {
        if (user == username && pass == password)
            return true;
    }
    return false;
}

// Upload file from client to server
void handleUpload(int new_socket) {
    char buffer[1024] = {0};
    read(new_socket, buffer, sizeof(buffer));
    string filename = buffer;

    ofstream outfile(filename, ios::binary);
    ssize_t bytesReceived;
    while ((bytesReceived = read(new_socket, buffer, sizeof(buffer))) > 0) {
        xorEncryptDecrypt(buffer, bytesReceived);
        outfile.write(buffer, bytesReceived);
        if (bytesReceived < sizeof(buffer)) break;
    }
    outfile.close();
    cout << "File '" << filename << "' uploaded successfully (decrypted on server).\n";
}

// Download file from server to client
void handleDownload(int new_socket) {
    char buffer[1024] = {0};
    read(new_socket, buffer, sizeof(buffer));
    string filename = buffer;

    ifstream infile(filename, ios::binary);
    if (!infile) {
        string msg = "ERROR: File not found!";
        send(new_socket, msg.c_str(), msg.size(), 0);
        cout << "Requested file not found.\n";
        return;
    }

    char fileBuffer[1024];
    while (!infile.eof()) {
        infile.read(fileBuffer, sizeof(fileBuffer));
        int bytes = infile.gcount();
        xorEncryptDecrypt(fileBuffer, bytes);
        send(new_socket, fileBuffer, bytes, 0);
    }
    infile.close();
    cout << "File '" << filename << "' sent (encrypted).\n";
}

// List available files
void handleListFiles(int new_socket) {
    string fileList;
    DIR* dir;
    struct dirent* entry;
    dir = opendir(".");
    if (dir == nullptr) {
        string msg = "ERROR: Could not open directory!";
        send(new_socket, msg.c_str(), msg.size(), 0);
        return;
    }

    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_REG) {
            fileList += entry->d_name;
            fileList += "\n";
        }
    }
    closedir(dir);

    send(new_socket, fileList.c_str(), fileList.size(), 0);
    cout << "Sent file list to client.\n";
}
