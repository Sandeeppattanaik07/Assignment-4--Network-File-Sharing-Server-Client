✅ 1. Project Overview

This project implements a secure client–server file sharing system using C++ and TCP sockets on Linux/WSL.
The system supports:

User authentication

File upload

File download

File listing

Encryption

Logging

✅ 2. Features
🔐 Authentication

Users must log in using credentials from users.txt.

⬆️ Secure File Upload

Encrypted file transfer

Real-time progress bar

Chunk-based transfer

Upload confirmation

⬇️ Secure File Download

Decrypts automatically

Progress bar display

Auto-saving inside /downloads/

📂 File Listing

Users can view all files stored in server directory shared_files/.

🔒 XOR Encryption

Simple XOR-based encryption used during both upload & download.

📝 Server Logging

All events recorded in server_log.txt (uploads, downloads, logins).

✅ 3. Folder Structure
Assignment-4--Network-File-Sharing-Server-Client/
│
├── Client/
│   ├── client.cpp
│   ├── client
│   ├── downloads/
│
├── Server/
│   ├── server.cpp
│   ├── server
│   ├── users.txt
│   ├── server_log.txt
│   ├── shared_files/
│
├── screenshots/       ← All screenshots stored here
│   ├── img1.png
│   ├── img2.png
│   ├── img3.png
│   ├── …
│
├── README.md
└── LICENSE

✅ 4. How to Run
▶️ Start the Server
cd Server
g++ server.cpp -o server
./server

▶️ Start the Client
cd Client
g++ client.cpp -o client
./client

✅ 5. Screenshots (All 15 Included)
✅ Screenshot 1 — Server waiting for client

✅ Screenshot 2 — Client login screen

✅ Screenshot 3 — Server authentication success

✅ Screenshot 4 — Server waiting

✅ Screenshot 5 — Client username prompt

✅ Screenshot 6 — Client login success

✅ Screenshot 7 — Client menu

✅ Screenshot 8 — Uploading file progress

✅ Screenshot 9 — Upload completed

✅ Screenshot 10 — Download progress

✅ Screenshot 11 — Download completed

✅ Screenshot 12 — Files listed on server

✅ Screenshot 13 — Client folder view

✅ Screenshot 14 — Server folder view

✅ Screenshot 15 — GitHub project repo

✅ 6. Learning Outcomes

You will understand:

Linux socket programming

TCP client–server communication

File transfer in chunks

Encryption/decryption

Logging mechanisms

Git & GitHub workflows

WSL development environment

✅ 7. Future Enhancements

Multi-client support

Strong encryption (AES/RSA)

GUI-based interface

Hash verification

Resume upload/download

✅ 8. License

MIT License.

✅ 9. Author

Sandeep Pattanaik
CSE Student – Network Programming Project
