#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

void uploadFile(int);
void downloadFile(int);
void listFiles(int);
bool authenticate(int);
void xorEncryptDecrypt(char*, int);

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { cout << "Socket error\n"; return 1; }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        cout << "Connection failed\n"; return 1;
    }

    // Step 1: Authenticate first
    if (!authenticate(sock)) {
        cout << "Login failed. Disconnecting.\n";
        close(sock);
        return 0;
    }

    while (true) {
        cout << "\n==== File Sharing Menu ====\n";
        cout << "1. Upload File\n";
        cout << "2. Download File\n";
        cout << "3. List Files on Server\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        string choice;
        cin >> choice;

        send(sock, choice.c_str(), choice.size(), 0);

        if (choice == "1") uploadFile(sock);
        else if (choice == "2") downloadFile(sock);
        else if (choice == "3") listFiles(sock);
        else if (choice == "4") break;
    }

    close(sock);
    return 0;
}

void xorEncryptDecrypt(char* data, int size) {
    char key = 'K';
    for (int i = 0; i < size; ++i) {
        data[i] ^= key;
    }
}

bool authenticate(int sock) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    string credentials = username + "," + password;
    send(sock, credentials.c_str(), credentials.size(), 0);

    // No reply needed; server verifies directly.
    sleep(1);
    cout << "Authentication request sent.\n";
    return true;
}

void uploadFile(int sock) {
    string filename;
    cout << "Enter file name to upload: ";
    cin >> filename;
    ifstream infile(filename, ios::binary);
    if (!infile) { cout << "File not found!\n"; return; }

    send(sock, filename.c_str(), filename.size(), 0);
    sleep(1);
    char buffer[1024];
    while (!infile.eof()) {
        infile.read(buffer, sizeof(buffer));
        int bytes = infile.gcount();
        xorEncryptDecrypt(buffer, bytes);
        send(sock, buffer, bytes, 0);
    }
    infile.close();
    cout << "File uploaded (encrypted).\n";
}

void downloadFile(int sock) {
    string filename;
    cout << "Enter filename to download: ";
    cin >> filename;

    send(sock, filename.c_str(), filename.size(), 0);
    ofstream outfile("downloaded_" + filename, ios::binary);
    if (!outfile) { cout << "Error creating output file!\n"; return; }

    char buffer[1024];
    ssize_t bytesRead;
    while ((bytesRead = read(sock, buffer, sizeof(buffer))) > 0) {
        xorEncryptDecrypt(buffer, bytesRead);
        outfile.write(buffer, bytesRead);
        if (bytesRead < sizeof(buffer)) break;
    }
    outfile.close();
    cout << "File downloaded and decrypted: downloaded_" << filename << endl;
}

void listFiles(int sock) {
    char buffer[2048] = {0};
    int bytesRead = read(sock, buffer, sizeof(buffer));
    if (bytesRead > 0)
        cout << "\nFiles on Server:\n" << buffer << endl;
    else
        cout << "Error retrieving file list.\n";
}
