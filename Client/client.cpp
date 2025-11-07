#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/stat.h>
using namespace std;

void uploadFile(int);
void downloadFile(int);
void listFiles(int);
bool authenticate(int);
void xorEncryptDecrypt(char*, int);
long getFileSize(string);
void showProgress(long, long);

char KEY = 'K';

int main() {
    system("clear");
    cout << "============================================\n";
    cout << "        SECURE FILE SHARING CLIENT\n";
    cout << "============================================\n";

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr);

    connect(sock, (struct sockaddr*)&serv, sizeof(serv));

    if (!authenticate(sock)) {
        cout << "[AUTH] Login failed.\n";
        return 0;
    }

    cout << "[AUTH] Login successful!\n";

    mkdir("downloads", 0777);

    while (true) {
        cout << "\n============ MENU ============\n";
        cout << "1. Upload File\n";
        cout << "2. Download File\n";
        cout << "3. List Files on Server\n";
        cout << "4. Exit\n";
        cout << "==============================\n";
        cout << "Enter choice: ";

        string choice;
        cin >> choice;

        choice += "\n";  // ✅ FIX: send newline
        send(sock, choice.c_str(), choice.size(), 0);

        if (choice[0] == '1') uploadFile(sock);
        else if (choice[0] == '2') downloadFile(sock);
        else if (choice[0] == '3') listFiles(sock);
        else if (choice[0] == '4') break;
    }

    close(sock);
    return 0;
}

bool authenticate(int sock) {
    string user, pass;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    string data = user + "," + pass;
    send(sock, data.c_str(), data.size(), 0);
    sleep(1);
    return true;
}

void uploadFile(int sock) {
    string filename;
    cout << "Enter file to upload: ";
    cin >> filename;

    ifstream infile(filename, ios::binary);
    if (!infile) { cout << "File not found!\n"; return; }

    send(sock, filename.c_str(), filename.size(), 0);
    usleep(50000);

    long totalSize = getFileSize(filename);
    string sizeStr = to_string(totalSize);
    send(sock, sizeStr.c_str(), sizeStr.size(), 0);
    usleep(50000);

    char buffer[1024];
    long total = 0;

    while (!infile.eof()) {
        infile.read(buffer, sizeof(buffer));
        int bytes = infile.gcount();
        xorEncryptDecrypt(buffer, bytes);
        send(sock, buffer, bytes, 0);
        total += bytes;
        showProgress(total, totalSize);
    }

    cout << "\n[UPLOAD] Completed ✅\n";
    infile.close();
}

void downloadFile(int sock) {
    string filename;
    cout << "Enter file to download: ";
    cin >> filename;

    send(sock, filename.c_str(), filename.size(), 0);

    char sizeBuf[64];
    read(sock, sizeBuf, sizeof(sizeBuf));

    if (strcmp(sizeBuf, "ERROR") == 0) {
        cout << "File not found on server!\n";
        return;
    }

    long fileSize = stol(sizeBuf);
    long total = 0;

    string savePath = "downloads/downloaded_" + filename;
    ofstream outfile(savePath, ios::binary);

    char buffer[1024];
    while (total < fileSize) {
        int bytes = read(sock, buffer, sizeof(buffer));
        xorEncryptDecrypt(buffer, bytes);
        outfile.write(buffer, bytes);
        total += bytes;
        showProgress(total, fileSize);
    }

    outfile.close();
    cout << "\n[DOWNLOAD] Saved as: " << savePath << " ✅\n";
}

void listFiles(int sock) {
    char buffer[8192] = {0};  // ✅ FIX: bigger buffer
    int bytes = read(sock, buffer, sizeof(buffer));
    cout << "\n--- Files on Server ---\n";
    cout << buffer << endl;
}

void xorEncryptDecrypt(char* data, int size) {
    for (int i = 0; i < size; i++) data[i] ^= KEY;
}

long getFileSize(string filename) {
    ifstream infile(filename, ios::binary | ios::ate);
    return infile.tellg();
}

void showProgress(long current, long total) {
    int barWidth = 30;
    float progress = (float)current / total;
    int pos = progress * barWidth;

    cout << "\r[";
    for (int i = 0; i < barWidth; ++i)
        cout << (i < pos ? "█" : "-");
    cout << "] " << int(progress * 100) << "%";
    cout.flush();
}
