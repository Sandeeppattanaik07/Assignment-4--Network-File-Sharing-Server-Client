# 📁 Secure Network File Sharing System (Client–Server Model)

A secure C++ project implementing authenticated file upload & download over TCP sockets on Linux/WSL, with encryption, progress bars, and logging.

---

## ✅ 1. Project Overview

This project implements a secure **client–server file sharing system** using **C++ and TCP sockets** on Linux/WSL.  
The system supports:

- User authentication  
- Secure file upload  
- Secure file download  
- File listing  
- XOR encryption  
- Terminal progress bars  
- Server-side logging  

---

## ✅ 2. Features

### 🔐 Authentication  
Users must log in using credentials stored in `users.txt`.

### ⬆️ Secure File Upload  
- Encrypted upload  
- Progress bar  
- Chunk-based transfer  

### ⬇️ Secure File Download  
- Decrypts automatically  
- Progress bar  
- Auto-save to `downloads/`

### 📂 File Listing  
View all files stored in `shared_files/`.

### 🔒 XOR Encryption  
Basic encryption applied to both upload & download.

### 📝 Server Logging  
Stored in `server_log.txt`.

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
├── screenshots/
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
✅ 5. Screenshots (With Captions)
✅ Make sure all images are inside /screenshots/.

📸 1. Client Login Screen

📸 2. Entering Username & Password

📸 3. Login Successful on Client

📸 4. Server Authenticating User

📸 5. Server Login Success Message

📸 6. Client Main Menu (Upload / Download / List Files)

📸 7. Uploading File – Progress Bar Display

📸 8. Upload Completed Successfully

📸 9. Downloading File – Progress Bar

📸 10. File List on Server (shared_files/)

📸 11. Download Completed Successfully

📸 12. Server After File Transfer Logging Output

📸 13. Client Folder Showing Downloaded Files

📸 14. Server Folder Showing Uploaded Files

📸 15. GitHub Repository Overview

✅ 6. Learning Outcomes
TCP socket programming

Client–server architecture

File transfer using streams

Encryption & decryption

WSL/Linux development

Logging mechanisms

Git & GitHub workflow

✅ 7. Future Enhancements
Multi-client support

AES/RSA encryption

GUI-based interface

File integrity check (SHA-256)

Resume-able downloads

✅ 8. License
MIT License.

✅ 9. Author
Sandeep Pattanaik
CSE Student – Network Programming Project

yaml
Copy code

---

✅ **This README is now perfect for submission + GitHub.**  
✅ If you want, I can also prepare:  
✅ Full **PDF project report**  
✅ **Viva questions & answers**  
✅ **Google Form answers**  

Just tell me!
