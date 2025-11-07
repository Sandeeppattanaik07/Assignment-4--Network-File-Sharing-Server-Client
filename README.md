# 📁 Secure Network File Sharing System (Client–Server Model)

A secure C++ project implementing a client–server file sharing system using TCP sockets in Linux/WSL, supporting authentication, encrypted upload/download, file listing, server logging, and progress bars.

---

## ✅ 1. Project Overview

This project demonstrates a secure file-sharing mechanism where:

- Users authenticate using a username & password.
- Files can be uploaded to the server.
- Files can be downloaded from the server.
- All server files can be listed.
- XOR encryption is used for secure transfer.
- Server logs all activities in `server_log.txt`.

This project covers **Linux socket programming, encryption, client–server communication**, and **file transfer over TCP**.

---

## ✅ 2. Features

### 🔐 Authentication  
Users authenticate using credentials stored in `users.txt`.

### ⬆️ Secure File Upload  
- Encrypted file transfer  
- Chunk-based upload  
- Real-time progress bar  
- Automatic save on server  

### ⬇️ Secure File Download  
- Encrypted transfer  
- Progress bar  
- Auto-save to `/downloads/` folder  

### 📂 File Listing  
View all server files inside `shared_files/`.

### 🔒 XOR Encryption  
Simple XOR-based encryption applied during upload/download.

### 📝 Server Logging  
Every login, upload, download is logged in `server_log.txt`.

---

## ✅ 3. Folder Structure

Assignment-4--Network-File-Sharing-Server-Client/
│
├── Client/
|
│ ├── client.cpp
|
│ ├── client
|
│ ├── downloads/
│
├── Server/
│ ├── server.cpp
│ ├── server
│ ├── users.txt
│ ├── server_log.txt
│ ├── shared_files/
│
├── screenshots/
│ ├── img1.png
│ ├── img2.png
│ ├── img3.png
│ ├── img4.png
│ ├── img5.png
│ ├── img6.png
│ ├── img7.png
│ ├── img8.png
│ ├── img9.png
│ ├── img10.png
│ ├── img11.png
│ ├── img12.png
│ ├── img13.png
│ ├── img14.png
│ ├── img15.png
│
├── README.md
└── LICENSE



## ✅ 4. How to Run

▶️ Start the Server

cd Server
g++ server.cpp -o server
./server

▶️ Start the Client

cd Client
g++ client.cpp -o client
./client

## ✅ 5. Screenshots (All 15 Included)

📸 1. Client Login Screen
screenshots/img1.png

📸 2. Entering Username & Password
screenshots/img2.png

📸 3. Login Successful on Client
screenshots/img3.png

📸 4. Server Authenticating User
screenshots/img4.png

📸 5. Server Login Success Message
screenshots/img5.png

📸 6. Client Main Menu
screenshots/img6.png

📸 7. Uploading File – Progress Bar
screenshots/img7.png

📸 8. Upload Completed Successfully
screenshots/img8.png

📸 9. Downloading File – Progress Bar
screenshots/img9.png

📸 10. File List on Server
screenshots/img10.png

📸 11. Download Completed
screenshots/img11.png

📸 12. Server After File Transfer Logging
screenshots/img12.png

📸 13. Client Folder Showing Downloaded Files
screenshots/img13.png

📸 14. Server Folder Showing Uploaded Files
screenshots/img14.png

📸 15. GitHub Repository Overview
screenshots/img15.png

## ✅ 6. Learning Outcomes
You will understand:

Linux socket programming

TCP client–server communication

File transfer using streams

Chunk-based transmission

XOR encryption/decryption

Logging techniques

Git & GitHub workflow

WSL/Linux development environment

## ✅ 7. Future Enhancements
Multi-client support (threaded)

AES/RSA encryption instead of XOR

GUI interface

SHA-256 integrity verification

Pause/Resume downloads

## ✅ 8. License
MIT License.

## ✅ 9. Author
Sandeep Pattanaik
CSE Student – Network Programming Project
