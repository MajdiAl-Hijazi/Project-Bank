# Bank Management Program

This project is a **Bank Management System** written in C++. The program allows you to:
- Display the list of clients.
- Add new clients.
- Delete clients.
- Update client information.
- Search for clients.

---
## 📝 Program Overview

The program uses a **text file** (`Clients.txt`) to store client data and relies on:
- `struct` to define client data.
- `vector` to temporarily store the list of clients in memory.
- Functions for each operation (add, delete, update, display, search).
- A **Main Menu** interface for navigating between operations.
- Preventing duplicate account numbers when adding new clients.

---
## ⚖️ Differences Between Your Code and Dr. Abuhaddoud’s Code

| Feature | My Code | Dr. Abuhaddoud’s Code | Notes |
|--------|-----------|-----------------------|-------|
| **Naming** | More descriptive variable and struct names (`sDataClients`, `ClientFileName`) | Simpler names (`sClient`, `ClientsFileName`) | Your code is more descriptive; Dr. Abuhaddoud’s code is simpler and easier to read |
| **Displaying Client List** | Uses separate functions for header and footer (`PrintHeaderShowAllClients`, `PrintFooterShowAllClients`) | Everything is inside `ShowAllClientsScreen` | Your code is more organized with clear separation of responsibilities |
| **Finding Clients** | Multiple overloaded functions (`FindClientUsingAccountNumber`) | Single function `FindClientByAccountNumber` | Dr. Abuhaddoud’s code is simpler and shorter |
| **Adding Clients** | `AddNewClientScreen` with a loop to add multiple clients | `AddNewClients` | Both support multiple entries, but your code separates screen and logic more clearly |
| **Updating Clients** | Uses `UpdateDataClient` and separate header function | Uses `UpdateClientByAccountNumber` | Slightly different structure, Dr. Abuhaddoud’s code is more linear |
| **File Handling** | Opens and closes file in multiple functions | File operations are more centralized | Your code is modular but slightly longer |

---

## 🎥 Watch the Program in Action

You can watch a demonstration of this program on YouTube [ here](https://youtu.be/R4BVTaY0A20).

---
🔗 **Explore the enhanced features and full details of this project** [here](https://github.com/MajdiAl-Hijazi/Project-Bank/tree/main/Bank(Extension)).
