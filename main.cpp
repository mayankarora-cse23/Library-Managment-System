#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>

using namespace std;

// ANSI color codes for better UI
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"

// Structure to represent a book
struct Book {
    int id;
    string title;
    string author;
    int year;
    string genre;
    bool isBorrowed;
    string reservedBy; // For reserved books, track who reserved it

    // Function to display book details
    void display() const {
        cout << CYAN << "ID: " << RESET << id << "\n" 
             << CYAN << "Title: " << RESET << title << "\n" 
             << CYAN << "Author: " << RESET << author << "\n"
             << CYAN << "Year: " << RESET << year << "\n"
             << CYAN << "Genre: " << RESET << genre << "\n"
             << CYAN << "Status: " << RESET
             << (isBorrowed ? "Borrowed" : (reservedBy.empty() ? "Available" : "Reserved by " + reservedBy)) << endl;
    }
};

// Structure to represent a user
struct User {
    string username;
    string password;
    bool isAdmin;

    // Constructor
    User(string u, string p, bool admin = false) : username(u), password(p), isAdmin(admin) {}
};

// Global variables for users and library
vector<Book> library;
vector<User> users;
User* currentUser = nullptr;

// Function to print header with color
void printHeader(const string& header) {
    cout << BLUE << BOLD << header << RESET << endl;
    cout << "-------------------------------------------" << endl;
}

// Function to list all books
void listBooks() {
    printHeader("Library Books");
    if (library.empty()) {
        cout << RED << "No books available!" << RESET << endl;
        return;
    }

    for (const auto& book : library) {
        book.display();
    }
}

// Function to search books by title, author, genre, or year
void searchBooks() {
    printHeader("Search Books");
    
    int choice;
    cout << "Search by:\n";
    cout << "1. Title\n";
    cout << "2. Author\n";
    cout << "3. Genre\n";
    cout << "4. Year\n";
    cout << "Enter your choice: ";
    cin >> choice;

    cin.ignore(); // To discard any leftover newline characters

    string query;
    int yearQuery;

    vector<Book> searchResults;

    switch (choice) {
        case 1: // Search by Title
            cout << "Enter part of the title to search for: ";
            getline(cin, query);
            for (const auto& book : library) {
                if (book.title.find(query) != string::npos) {
                    searchResults.push_back(book);
                }
            }
            break;

        case 2: // Search by Author
            cout << "Enter the author's name to search for: ";
            getline(cin, query);
            for (const auto& book : library) {
                if (book.author.find(query) != string::npos) {
                    searchResults.push_back(book);
                }
            }
            break;

        case 3: // Search by Genre
            cout << "Enter the genre to search for: ";
            getline(cin, query);
            for (const auto& book : library) {
                if (book.genre.find(query) != string::npos) {
                    searchResults.push_back(book);
                }
            }
            break;

        case 4: // Search by Year
            cout << "Enter the publication year to search for: ";
            cin >> yearQuery;
            for (const auto& book : library) {
                if (book.year == yearQuery) {
                    searchResults.push_back(book);
                }
            }
            break;

        default:
            cout << RED << "Invalid search option!" << RESET << endl;
            return;
    }

    // Display search results
    if (searchResults.empty()) {
        cout << RED << "No books found matching the search criteria." << RESET << endl;
    } else {
        for (const auto& book : searchResults) {
            book.display();
        }
    }
}

// Function to borrow a book
void borrowBook() {
    int id;
    printHeader("Borrow Book");
    cout << "Enter book ID to borrow: ";
    cin >> id;

    for (auto& book : library) {
        if (book.id == id) {
            if (book.isBorrowed) {
                cout << RED << "The book is already borrowed!" << RESET << endl;
                return;
            }
            book.isBorrowed = true;
            cout << GREEN << "You have successfully borrowed the book!" << RESET << endl;
            return;
        }
    }

    cout << RED << "Book not found!" << RESET << endl;
}

// Function to return a book
void returnBook() {
    int id;
    printHeader("Return Book");
    cout << "Enter book ID to return: ";
    cin >> id;

    for (auto& book : library) {
        if (book.id == id) {
            if (!book.isBorrowed) {
                cout << RED << "The book is not borrowed!" << RESET << endl;
                return;
            }
            book.isBorrowed = false;
            cout << GREEN << "You have successfully returned the book!" << RESET << endl;
            return;
        }
    }

    cout << RED << "Book not found!" << RESET << endl;
}

// Function to change username/password
void changeCredentials() {
    string newUsername, newPassword;
    printHeader("Change Username/Password");

    cout << "Enter new username: ";
    cin >> newUsername;
    cout << "Enter new password: ";
    cin >> newPassword;

    currentUser->username = newUsername;
    currentUser->password = newPassword;
    cout << GREEN << "Credentials updated successfully!" << RESET << endl;
}

// Function to add a new book (admin only)
void addBook() {
    string title, author, genre;
    int year;
    printHeader("Add Book");

    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter publication year: ";
    cin >> year;
    cout << "Enter book genre: ";
    cin.ignore();
    getline(cin, genre);

    int id = library.empty() ? 1 : library.back().id + 1;
    library.push_back({id, title, author, year, genre, false, ""});
    cout << GREEN << "Book added successfully!" << RESET << endl;
}

// Function to register a new user
void registerUser() {
    string username, password;
    printHeader("Register New User");

    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter new password: ";
    cin >> password;

    users.push_back(User(username, password));
    cout << GREEN << "Account created successfully!" << RESET << endl;
}

// Function to load users from a file
void loadUsers() {
    ifstream file("users.txt");
    string username, password;
    bool isAdmin;

    while (file >> username >> password >> isAdmin) {
        users.push_back(User(username, password, isAdmin));
    }
    file.close();
}

// Function to save users to a file
void saveUsers() {
    ofstream file("users.txt");
    for (const auto& user : users) {
        file << user.username << " " << user.password << " " << user.isAdmin << endl;
    }
    file.close();
}

// Function to handle user login
bool login() {
    string username, password;
    printHeader("Login");

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (auto& user : users) {
        if (user.username == username && user.password == password) {
            currentUser = &user;
            cout << GREEN << "Login successful!" << RESET << endl;
            return true;
        }
    }

    cout << RED << "Invalid username or password!" << RESET << endl;
    return false;
}

// Function to display the menu for regular users
void showUserMenu() {
    int choice;
    while (true) {
        printHeader("Library Management System");
        cout << "1. List Books\n";
        cout << "2. Search Book\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Change Username/Password\n";
        cout << "6. Logout\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listBooks();
                break;
            case 2:
                searchBooks();
                break;
            case 3:
                borrowBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                changeCredentials();
                break;
            case 6:
                currentUser = nullptr;
                cout << GREEN << "Logged out successfully!" << RESET << endl;
                return;
            case 7:
                cout << "Exiting...\n";
                exit(0);
            default:
                cout << RED << "Invalid choice! Please try again." << RESET << endl;
        }
    }
}

// Function to display the admin menu
void showAdminMenu() {
    int choice;
    while (true) {
        printHeader("Admin Menu");
        cout << "1. List Books\n";
        cout << "2. Search Book\n";
        cout << "3. Add Book\n";
        cout << "4. Logout\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listBooks();
                break;
            case 2:
                searchBooks();
                break;
            case 3:
                addBook();
                break;
            case 4:
                currentUser = nullptr;
                cout << GREEN << "Logged out successfully!" << RESET << endl;
                return;
            case 5:
                cout << "Exiting...\n";
                exit(0);
            default:
                cout << RED << "Invalid choice! Please try again." << RESET << endl;
        }
    }
}

int main() {
    // Load users from file
    loadUsers();

    // Default admin user
    if (users.empty()) {
        users.push_back(User("admin", "admin123", true));
    }

    int choice;
    while (true) {
        printHeader("Welcome to the Library Management System");
        cout << "1. Login\n";
        cout << "2. Register New User\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (login()) {
                    if (currentUser->isAdmin) {
                        showAdminMenu();
                    } else {
                        showUserMenu();
                    }
                }
                break;
            case 2:
                registerUser();
                break;
            case 3:
                saveUsers(); // Save users before exiting
                cout << "Exiting...\n";
                return 0;
            default:
                cout << RED << "Invalid choice! Please try again." << RESET << endl;
        }
    }

    return 0;
}