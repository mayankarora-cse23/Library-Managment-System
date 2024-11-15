# Library Management System

A simple console-based Library Management System built in C++ that allows users to borrow, return, search, and manage books in the library. The system also includes an admin interface to add new books and manage user accounts. This project helps to simulate a real-world library system for educational purposes.

## Features
- **User Interface**: Interactive console interface with color-coded output for better UX.
- **Book Management**: 
  - List all books.
  - Search books by title, author, genre, or year.
  - Borrow and return books.
- **Admin Interface**: 
  - Admin can add new books to the system.
  - Admin can manage user accounts (add new users).
- **User Authentication**: 
  - Login functionality for both regular users and admins.

## Requirements
To run this project, you need:
- **C++ compiler** (e.g., GCC or MSVC)
- **Text editor or IDE** (e.g., Visual Studio Code, Code::Blocks)
- Basic knowledge of **C++ programming** and **command-line interface** (CLI) operations.

## How to Run

### 1. Clone the Repository:
Clone this repository to your local machine using the following command:
```bash
git clone https://github.com/your-username/library-management-system.git
```
### 2. Compile the Code:
After cloning the repository, navigate to the project folder in the terminal/command prompt.

Use the following command to compile the code:

```bash
g++ main.cpp -o library_system
```

This command tells the **GCC** compiler to compile the ```main.cpp``` file and generate an executable file named ```library_system```.

If you are using an IDE like **Code Blocks** or **Visual Studio Code**, follow these steps:

Open the IDE and load the ```main.cpp``` file.
Press the "Build" or "Compile" button in the IDE.
The IDE will automatically create an executable.

### 3. Run the Executable:
After compiling, you can run the executable from your terminal/command prompt:

```bash
./library_system
```
On Windows, the command will be:

```bash
library_system.exe
```
Alternatively, you can run the program directly from your IDE.

## How It Works
### 1. User Interface:
- Once the system starts, users can log in or register.
- Regular users can:
    - List available books.
    - Search for books by title, author, genre, or year.
    - Borrow or return books.
    - Change their credentials.
- Admin users can:
    - Add new books to the library.
    - View and manage all users.
### 2. Data Storage:
- Users and book data are stored temporarily in memory.
- User data is saved to a file (```users.txt```) on your system.
### 3. User Authentication:
- The system supports user login. Both regular users and admins can log in with a username and password.
- Admin users have additional permissions to add books and manage user accounts.
## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments
- This project is a simple simulation of a real-world library management system.
- The design and logic are inspired by real-world library systems.
- Special thanks to open-source contributors and resources for helping with C++ learning.
## Future Improvements
- **Database Integration**: Integrate with a database for permanent storage of books and user data.
- **Advanced Search**: Add advanced search filters (e.g., by availability, author rating).
- **GUI**: Develop a graphical user interface (GUI) for more interactive user experience.
- **Book Reservation**: Allow users to reserve books that are currently borrowed.
Feel free to contribute to this project by forking the repository, submitting issues, and creating pull requests!

## Contact
- **Author**: Mayank Arora
- **GitHub**: mayankarora-cse23