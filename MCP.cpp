#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Structure to store book information
struct Book {
    int bookID;
    string title;
    string dueDate;
    string borrowerName;
};

// Class to manage library fines
class LibraryFineManager {
private:
    vector<Book> borrowedBooks; // Stores all borrowed books
    float fineRatePerDay;
    const int gracePeriod = 7; // Fixed grace period of 7 days
    const string borrowedBooksFile = "borrowed_books.txt";
    const string finePolicyFile = "fine_policy.txt";
    const string overdueLogFile = "overdue_books_log.txt";

    // Helper function to calculate the number of late days
    int calculateDateDifference(const string &dueDate, const string &currentDate) {
        int dueYear = stoi(dueDate.substr(0, 4));
        int dueMonth = stoi(dueDate.substr(5, 2));
        int dueDay = stoi(dueDate.substr(8, 2));

        int currentYear = stoi(currentDate.substr(0, 4));
        int currentMonth = stoi(currentDate.substr(5, 2));
        int currentDay = stoi(currentDate.substr(8, 2));

        int dueTotalDays = dueYear * 365 + dueMonth * 30 + dueDay;
        int currentTotalDays = currentYear * 365 + currentMonth * 30 + currentDay;

        return currentTotalDays - dueTotalDays;
    }

    // Function to load book data from the file
    void loadBorrowedBooks() {
        ifstream file(borrowedBooksFile);
        if (!file.is_open()) {
            cout << "Warning: Could not open 'borrowed_books.txt'. File might not exist.\n";
            return;
        }
        Book book;
        while (file >> book.bookID >> book.title >> book.dueDate >> book.borrowerName) {
            borrowedBooks.push_back(book);
        }
        file.close();
    }

    // Function to save book data to the file
    void saveBorrowedBooks() {
        ofstream file(borrowedBooksFile);
        if (!file.is_open()) {
            cout << "Error: Could not open 'borrowed_books.txt' for writing.\n";
            return;
        }
        for (const auto &book : borrowedBooks) {
            file << book.bookID << " " << book.title << " "
                 << book.dueDate << " " << book.borrowerName << endl;
        }
        file.close();
    }

    // Function to log overdue books
    void logOverdueBooks(const vector<Book> &overdueBooks, const string &currentDate) {
        ofstream file(overdueLogFile, ios::app); // Append mode
        if (!file.is_open()) {
            cout << "Error: Could not open 'overdue_books_log.txt'.\n";
            return;
        }
        for (const auto &book : overdueBooks) {
            file << currentDate << " " << book.bookID << " " << book.title << " "
                 << book.dueDate << " " << book.borrowerName << endl;
        }
        file.close();
    }

public:
    // Constructor
    LibraryFineManager() {
        loadBorrowedBooks();
        fineRatePerDay = 1.0; // Default fine rate per day
    }

    // Destructor
    ~LibraryFineManager() {
        saveBorrowedBooks();
    }

    // Function to add a borrowed book
    void addBorrowedBook() {
        Book newBook;
        cout << "Enter Book ID: ";
        cin >> newBook.bookID;
        cout << "Enter Book Title: ";
        cin.ignore();
        getline(cin, newBook.title);
        cout << "Enter Due Date (YYYY-MM-DD): ";
        cin >> newBook.dueDate;
        cout << "Enter Borrower's Name: ";
        cin.ignore();
        getline(cin, newBook.borrowerName);
        borrowedBooks.push_back(newBook);
        cout << "Book added successfully!\n";
    }

    // Function to calculate fine
    void calculateFine() {
        string dueDate, returnDate;
        cout << "Enter Due Date (YYYY-MM-DD): ";
        cin >> dueDate;
        cout << "Enter Return Date (YYYY-MM-DD): ";
        cin >> returnDate;
        int daysLate = calculateDateDifference(dueDate, returnDate);
        if (daysLate <= gracePeriod) {
            cout << "No fine. Returned within grace period.\n";
        } else {
            float fine = (daysLate - gracePeriod) * fineRatePerDay;
            cout << "Fine: $" << fine << endl;
        }
    }

    // Function to track overdue books
    void trackOverdueBooks() {
        string currentDate;
        cout << "Enter Current Date (YYYY-MM-DD): ";
        cin >> currentDate;
        cout << "\nOverdue Books:\n";
        for (const auto &book : borrowedBooks) {
            int daysLate = calculateDateDifference(book.dueDate, currentDate);
            if (daysLate > gracePeriod) {
                cout << "Book ID: " << book.bookID
                     << ", Title: " << book.title
                     << ", Borrower: " << book.borrowerName
                     << ", Due Date: " << book.dueDate << endl;
            }
        }
    }

    // Function to check overdue books by specific date
    void checkOverdueByDate() {
        string checkDate;
        cout << "Enter the date to check overdue books (YYYY-MM-DD): ";
        cin >> checkDate;
        cout << "\nBooks Overdue as of " << checkDate << ":\n";
        bool found = false;
        for (const auto &book : borrowedBooks) {
            int daysLate = calculateDateDifference(book.dueDate, checkDate);
            if (daysLate > gracePeriod) {
                found = true;
                cout << "Book ID: " << book.bookID
                     << ", Title: " << book.title
                     << ", Borrower: " << book.borrowerName
                     << ", Due Date: " << book.dueDate << endl;
            }
        }
        if (!found) {
            cout << "No books overdue by the specified date.\n";
        }
    }

    // Function to display all borrowed books
    void displayAllBorrowedBooks() {
        if (borrowedBooks.empty()) {
            cout << "No borrowed books to display.\n";
            return;
        }
        cout << "\nAll Borrowed Books:\n";
        for (const auto &book : borrowedBooks) {
            cout << "Book ID: " << book.bookID
                 << ", Title: " << book.title
                 << ", Borrower: " << book.borrowerName
                 << ", Due Date: " << book.dueDate << endl;
        }
    }
};

// Main function
int main() {
    LibraryFineManager manager;
    int choice;

    do {
        cout << "\n=== Library Fine Management System ===\n";
        cout << "1. Add Borrowed Book\n";
        cout << "2. Calculate Fine\n";
        cout << "3. Track Overdue Books\n";
        cout << "4. Display All Borrowed Books\n";
        cout << "5. Check Overdue Books by Specific Date\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.addBorrowedBook();
                break;
            case 2:
                manager.calculateFine();
                break;
            case 3:
                manager.trackOverdueBooks();
                break;
            case 4:
                manager.displayAllBorrowedBooks();
                break;
            case 5:
                manager.checkOverdueByDate();
                break;
            case 6:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}