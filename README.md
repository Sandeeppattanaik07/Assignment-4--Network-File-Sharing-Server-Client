Secure Network File Sharing System (Client–Server Model)

A secure C++ project implementing authenticated file upload & download over TCP sockets on Linux/WSL, with encryption, progress bars, and logging.

1. Project Overview

This project implements a secure client–server file sharing system using C++ and Linux socket programming.
It allows authenticated users to upload, download, and view files stored on the server.

The system includes:

Password-based authentication

Encrypted file transfer (XOR-based)

File upload with progress visualization

File download with progress visualization

File listing

Automatic server logging

Clean terminal-based UI

This project demonstrates core concepts of Linux System Programming (LSP) and network communication.

2. Features
Authentication

Users must enter a valid username and password from the users.txt file.

File Upload

Client → Server file transfer
Includes:

Encryption

Real-time progress bar

Success confirmation

File Download

Server → Client file transfer
Includes:

Encryption

Real-time progress bar

Success confirmation

File Listing

Client can view all files stored in the server’s shared_files directory.

XOR Encryption

Simple encryption applied during both upload and download operations.

Server Logging

Every upload/download is logged inside server_log.txt.

3. Folder Structure
Assignment-4--Network-File-Sharing-Server-Client/
│
├── Client/
│   ├── client.cpp
│   ├── client (binary)
│   ├── downloads/
│
├── Server/
│   ├── server.cpp
│   ├── users.txt
│   ├── server_log.txt
│   ├── shared_files/
│
├── screenshots/   ← Upload your screenshots here
├── README.md
└── LICENSE

4. How to Run
Start the Server
cd Server
g++ server.cpp -o server
./server

Start the Client

Open another terminal:

cd Client
g++ client.cpp -o client
./client

5. Screenshots

Upload all your screenshots into:

screenshots/

And rename them exactly as shown:

1. Client Login Success

2. Server Authentication Success

3. Server Waiting for Client

4. Client Username Prompt

5. Server Auth Accepted

6. Client Main Menu

7. File Upload – Progress Bar

8. Upload Completed

9. File Download – Progress Bar

10. Files on Server (List View)

11. Download Completed

12. Server After Client Exit

13. Client Folder Showing Files

14. Server Folder Showing Files

15. GitHub Repository Overview

6. Learning Outcomes

From this project, I gained hands-on experience in:

Linux socket programming

TCP client–server communication

Encryption & decryption

File handling (read/write in chunks)

Directory traversal

Logging mechanisms

Terminal UI design

WSL-based C++ development

Git & GitHub workflow

7. Future Enhancements

Multi-client support using threading

AES encryption instead of XOR

GUI interface

Integrity verification (SHA-256 hashing)

Resumeable downloads

8. License

This project is licensed under the MIT License.
