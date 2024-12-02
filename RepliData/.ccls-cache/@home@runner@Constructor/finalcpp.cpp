#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>  // for std::setw, std::left
using namespace std;

class LibraryFineManager {
private:
    struct Book {
        int bookID;
        string title;
        string dueDate;
        string borrowerName;
        string genre;
    };

    struct User {
        int userID;
        string userName;
    };

    vector<Book> borrowedBooks;
    vector<User> libraryUsers;
    double bankBalance = 0.0;
    double fineRatePerDay;
    const string borrowedBooksFile = "borrowed_books.txt";
    const string usersFile = "library_users.txt";
    const string bankBalanceFile = "bank_balance.txt";
    const string overdueLogFile = "overdue_books_log.txt";
    const int gracePeriod = 2; // Grace period in days

    // Function to load borrowed books from file
    void loadBorrowedBooks() {
        ifstream file(borrowedBooksFile);
        if (!file.is_open()) {
            cout << "Warning: Could not open 'borrowed_books.txt'. File might not exist.\n";
            return;
        }
        Book book;
        while (file >> book.bookID >> book.title >> book.dueDate >> book.borrowerName >> book.genre) {
            borrowedBooks.push_back(book);
        }
        file.close();
    }

    // Function to save borrowed books to file
    void saveBorrowedBooks() {
        ofstream file(borrowedBooksFile);
        if (!file.is_open()) {
            cout << "Error: Could not open 'borrowed_books.txt' for writing.\n";
            return;
        }
        for (const auto &book : borrowedBooks) {
            file << book.bookID << " " << book.title << " "
                 << book.dueDate << " " << book.borrowerName << " " << book.genre << endl;
        }
        file.close();
    }

    // Function to load user data from the file
    void loadLibraryUsers() {
        ifstream file(usersFile);
        if (!file.is_open()) {
            cout << "Warning: Could not open 'library_users.txt'. File might not exist.\n";
            return;
        }
        User user;
        while (file >> user.userID >> user.userName) {
            libraryUsers.push_back(user);
        }
        file.close();
    }

    // Function to save user data to the file
    void saveLibraryUsers() {
        ofstream file(usersFile);
        if (!file.is_open()) {
            cout << "Error: Could not open 'library_users.txt' for writing.\n";
            return;
        }
        for (const auto &user : libraryUsers) {
            file << user.userID << " " << user.userName << endl;
        }
        file.close();
    }

    // Function to load bank balance from the file
    void loadBankBalance() {
        ifstream file(bankBalanceFile);
        if (!file.is_open()) {
            bankBalance = 0.0;  // Initialize with zero if file doesn't exist
            return;
        }
        file >> bankBalance;
        file.close();
    }

    // Function to save bank balance to the file
    void saveBankBalance() {
        ofstream file(bankBalanceFile);
        if (!file.is_open()) {
            cout << "Error: Could not open 'bank_balance.txt' for writing.\n";
            return;
        }
        file << bankBalance;
        file.close();
    }

    // Function to log overdue books
    void logOverdueBooks(const vector<Book> &overdueBooks, const string &currentDate) {
        ofstream file(overdueLogFile, ios::app);  // Append mode
        if (!file.is_open()) {
            cout << "Error: Could not open 'overdue_books_log.txt'.\n";
            return;
        }
        for (const auto &book : overdueBooks) {
            file << currentDate << " " << book.bookID << " " << book.title << " "
                 << book.dueDate << " " << book.borrowerName << " " << book.genre << endl;
        }
        file.close();
    }

    // Function to calculate the number of days between two dates
    int calculateDateDifference(const string &dueDate, const string &returnDate) {
        // Assuming the format is YYYY-MM-DD (e.g., 2024-11-30)
        int dueYear, dueMonth, dueDay;
        int returnYear, returnMonth, returnDay;

        sscanf(dueDate.c_str(), "%d-%d-%d", &dueYear, &dueMonth, &dueDay);
        sscanf(returnDate.c_str(), "%d-%d-%d", &returnYear, &returnMonth, &returnDay);

        // Simple date difference (ignoring months with different days, leap years, etc.)
        int dueTotalDays = dueYear * 365 + dueMonth * 30 + dueDay;
        int returnTotalDays = returnYear * 365 + returnMonth * 30 + returnDay;

        return returnTotalDays - dueTotalDays;
    }

public:
    // Constructor
    LibraryFineManager() {
        loadBorrowedBooks();
        loadLibraryUsers();
        loadBankBalance();
        fineRatePerDay = 2.0;  // Default fine rate per day
    }

    // Destructor
    ~LibraryFineManager() {
        saveBorrowedBooks();
        saveLibraryUsers();
        saveBankBalance();
    }

    // Function to display daily fines for all overdue books
    void displayDailyFine(const string &currentDate) {
        cout << "\n=========== Daily Fines for Overdue Books =============" << endl;
        bool foundOverdueBooks = false;

        for (const auto &book : borrowedBooks) {
            int daysLate = calculateDateDifference(book.dueDate, currentDate);
            if (daysLate > gracePeriod) {
                float fine = (daysLate - gracePeriod) * fineRatePerDay;
                cout << "Book ID: " << book.bookID << ", Title: " << book.title
                     << ", Borrower: " << book.borrowerName << ", Days Late: " << daysLate
                     << ", Fine: " << fine << " Rupees\n";
                foundOverdueBooks = true;
            }
        }

        if (!foundOverdueBooks) {
            cout << "No overdue books to display fines for.\n";
        }
    }

    // Function to track overdue books
    void trackOverdueBooks() {
        string currentDate;
        cout << "\n=========== Overdue Books Tracker ============" << endl;
        cout << "Enter today's date (YYYY-MM-DD): ";
        cin >> currentDate;

        vector<Book> overdueBooks;
        for (const auto &book : borrowedBooks) {
            int daysLate = calculateDateDifference(book.dueDate, currentDate);
            if (daysLate > gracePeriod) {
                overdueBooks.push_back(book);
            }
        }

        if (overdueBooks.empty()) {
            cout << "No overdue books.\n";
        } else {
            cout << "Overdue books:\n";
            for (const auto &book : overdueBooks) {
                cout << "Book ID: " << book.bookID << ", Title: " << book.title
                     << ", Borrower: " << book.borrowerName << ", Due Date: " << book.dueDate << endl;
            }
            logOverdueBooks(overdueBooks, currentDate);
        }
    }

    // Function to display all borrowed books
    void displayAllBorrowedBooks() {
        cout << "\n=========== Borrowed Books List =============" << endl;
        if (borrowedBooks.empty()) {
            cout << "No borrowed books available." << endl;
        } else {
            for (const auto &book : borrowedBooks) {
                cout << "Book ID: " << book.bookID << ", Title: " << book.title
                     << ", Borrower: " << book.borrowerName << ", Due Date: " << book.dueDate << endl;
            }
        }
    }

    // Function to create a new user account
    void createAccount() {
        int userID;
        string userName;

        cout << "Enter User ID: ";
        cin >> userID;
        if (userExists(userID)) {
            cout << "Account already exists for User ID " << userID << ".\n";
            return;
        }

        cout << "Enter User Name: ";
        cin.ignore();
        getline(cin, userName);

        libraryUsers.push_back({userID, userName});
        cout << "Account created successfully!\n";
    }

    // Function to check if a user exists
    bool userExists(int userID) {
        for (const auto &user : libraryUsers) {
            if (user.userID == userID) {
                return true;
            }
        }
        return false;
    }

    // Function to add a borrowed book
    void addBorrowedBook() {
        int userID;
        string userName;

        cout << "Enter your User ID: ";
        cin >> userID;

        if (!userExists(userID)) {
            cout << "No account found for this User ID. Please create an account first.\n";
            return;
        }

        cout << "Enter your Name: ";
        cin.ignore();
        getline(cin, userName);

        Book newBook;
        cout << "Enter Book ID: ";
        cin >> newBook.bookID;
        cout << "Enter Book Title: ";
        cin.ignore();
        getline(cin, newBook.title);

        cout << "Enter Due Date (YYYY-MM-DD): ";
        cin >> newBook.dueDate;

        cout << "Enter Book Genre (e.g., Novel, Science, etc.): ";
        cin.ignore();
        getline(cin, newBook.genre);  // New field to specify genre

        newBook.borrowerName = userName;
        borrowedBooks.push_back(newBook);
        cout << "Book added successfully!\n";
    }
};

int main() {
    LibraryFineManager manager;

    while (true) {
        cout << "\n=========== Library Fine Manager ============" << endl;
        cout << "1. Add Borrowed Book\n";
        cout << "2. Display Borrowed Books\n";
        cout << "3. Create Account\n";
        cout << "4. Track Overdue Books\n";
        cout << "5. Display Daily Fine\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                manager.addBorrowedBook();
                break;
            case 2:
                manager.displayAllBorrowedBooks();
                break;
            case 3:
                manager.createAccount();
                break;
            case 4:
                manager.trackOverdueBooks();
                break;
            case 5:
                {
                    string currentDate;
                    cout << "Enter today's date (YYYY-MM-DD): ";
                    cin >> currentDate;
                    manager.displayDailyFine(currentDate);
                    break;
                }
            case 6:
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
