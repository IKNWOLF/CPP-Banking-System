# 🏦 Banking Management System (C++)

A console-based **Banking Management System** built with **C++ (OOP)**.  
The system supports **file-based storage**, **user authentication with permissions**, **client account management**, **transactions**, **currency exchange**, **audit logging**, and **password encryption** for secure user data.

---

## 📌 Features

### 🔑 User Authentication & Permissions
- Login system validates users from `Users.txt` (username, password, email, phone, etc.).
- **Password encryption/decryption** ensures that stored passwords are not readable if the file is compromised.
- User roles defined with **bitmask permissions** (`enum enPermissions`).
- Supports permissions for:
  - Listing, adding, deleting, updating, finding clients  
  - Managing users  
  - Transactions  
  - Viewing login register  
  - Currency exchange  

### 👥 Client Management
- List all clients (Account No, Name, Phone, Email, PIN, Balance).  
- Add new client records.  
- Delete existing clients (confirmation required).  
- Update client details.  
- Find client by Account Number and display client card.  

### 💰 Transactions
- Deposit and Withdraw from accounts.  
- Transfer funds between clients.  
- Transaction log (with date & time).  
- View **total balances** across all accounts.  

### 👤 User Management
- List all users.  
- Add, update, delete, and search users.  
- Assign permissions during user creation.  

### 📝 Login Register
- Tracks all login attempts with:  
  - Date & time  
  - Username  
  - Encrypted Password  
  - Granted permissions  

### 💱 Currency Exchange
- File-based currency data management.  
- Features include:  
  - List currencies (country, code, rate).  
  - Find currency (by code or country).  
  - Update exchange rate.  
  - Currency calculator (convert between any two currencies).  

### 🔄 System Flow
- Main menu displayed after login.  
- Loops continuously until user logs out.  
- Supports multiple user sessions in the same runtime.  

---

## 📂 Data Persistence

- **Users.txt** → stores user data (username, name, email, phone, encrypted password, permissions).  
- **Clients.txt** → stores client account information.  
- **Transactions.txt / TransferLog.txt** → tracks financial transactions with timestamps.  
- **Currencies.txt** → stores currency information (country, code, rate).  
- All data is persisted between runs using text files (line-based object serialization).  

---

## 🛠️ Technologies Used
- **C++** (Object-Oriented Programming, Enums, File I/O, Vectors)  
- **File-based storage** for persistence  
- **Password encryption & decryption**  

---

