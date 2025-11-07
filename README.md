# 📁 Secure Network File Sharing System (Client–Server Model)

A secure C++ project implementing an authenticated file sharing system using Linux socket programming.

---

## ✅ 1. Project Overview

This project implements a secure **client–server file sharing system** using **C++ and TCP sockets** on Linux/WSL.  
The system supports:

- User authentication  
- File upload  
- File download  
- File listing  
- Logging  
- Simple XOR encryption  

---

## ✅ 2. Features

### 🔐 Authentication  
Users must log in using credentials from `users.txt`.

### ⬆️ Secure File Upload  
- Client → Server file transfer  
- XOR encryption applied  
- Chunk-based transfer  
- ✅ Upload progress bar  
- ✅ Success confirmation  

### ⬇️ Secure File Download  
- Server → Client transfer  
- Decryption handled automatically  
- ✅ Download progress bar  
- ✅ Auto-save to `/downloads/`

### 📂 File Listing  
Client can see all server-stored files inside `shared_files/`.

### 🔒 XOR Encryption  
A simple XOR-based encryption layer is applied on both upload and download.

### 📝 Server Logging  
All uploads/downloads and authentication events are stored in `server_log.txt`.

---

## ✅ 3. Folder Structure

Assignment-4--Network-File-Sharing-Server-Client/
│
├── Client/
│ ├── client.cpp
│ ├── client
│ ├── downloads/
│
├── Server/
│ ├── server.cpp
│ ├── server
│ ├── users.txt
│ ├── server_log.txt
│ ├── shared_files/
│
├── screenshots/ ← Add all screenshots here
├── README.md
└── LICENSE

yaml
Copy code

---

## ✅ 4. How to Run

### ▶️ Start the Server
```bash
cd Server
g++ server.cpp -o server
./server
▶️ Start the Client
bash
Copy code
cd Client
g++ client.cpp -o client
./client
✅ 5. Screenshots
⚠️ Replace these imgX.png names with the actual screenshot file names you upload inside /screenshots/.

✅ Client Login

✅ Server Authentication

✅ Server Waiting

✅ Client Username

✅ Server Login Success

✅ Client Menu

✅ File Upload Progress

✅ Upload Completed

✅ File Download Progress

✅ File List on Server

✅ Download Completed

✅ Client Folder

✅ Server Folder

✅ GitHub Repository

✅ 6. Learning Outcomes
Networking & socket programming

Client-server architecture

File systems & binary transfer

Encryption & decryption

Logging & monitoring

WSL/Linux environment

Git & GitHub version control

✅ 7. Future Enhancements
Multi-client support using threads

AES/RSA encryption

GUI/File Explorer

Integrity verification (hashing)

Pause/Resume file transfer

✅ 8. License
This project is licensed under the MIT License.

✅ 9. Author
Sandeep Pattanaik
CSE Student – Network Programming Project

yaml
Copy code

---

✅ This is **final, clean, and ready** for GitHub.  
✅ Now just **paste it inside README.md** and upload your screenshots inside `/screenshots/`.

If you want, I can also prepare a **PDF full project report** based on this README + screenshots.






