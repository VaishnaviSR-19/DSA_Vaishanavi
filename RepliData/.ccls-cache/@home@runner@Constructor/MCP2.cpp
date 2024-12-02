// #include <iostream>
// #include <vector>
// #include <string>
// #include <fstream>
// #include <iomanip>  // for std::setw, std::left
// using namespace std;

// class LibraryFineManager {
// private:
//     struct Book {
//         int bookID;
//         string title;
//         string dueDate;
//         string borrowerName;
//         string genre;
//     };

//     struct User {
//         int userID;
//         string userName;
//     };

//     vector<Book> borrowedBooks;
//     vector<User> libraryUsers;
//     double bankBalance = 0.0;
//     double fineRatePerDay;
//     const string borrowedBooksFile = "borrowed_books.txt";
//     const string usersFile = "library_users.txt";
//     const string bankBalanceFile = "bank_balance.txt";
//     const string overdueLogFile = "overdue_books_log.txt";
//     const int gracePeriod = 2; // Grace period in days

//     // Function to load borrowed books from file
//     void loadBorrowedBooks() {
//         ifstream file(borrowedBooksFile);
//         if (!file.is_open()) {
//             cout << "Warning: Could not open 'borrowed_books.txt'. File might not exist.\n";
//             return;
//         }
//         Book book;
//         while (file >> book.bookID >> book.title >> book.dueDate >> book.borrowerName >> book.genre) {
//             borrowedBooks.push_back(book);
//         }
//         file.close();
//     }

//     // Function to save borrowed books to file
//     void saveBorrowedBooks() {
//         ofstream file(borrowedBooksFile);
//         if (!file.is_open()) {
//             cout << "Error: Could not open 'borrowed_books.txt' for writing.\n";
//             return;
//         }
//         for (const auto &book : borrowedBooks) {
//             file << book.bookID << " " << book.title << " "
//                  << book.dueDate << " " << book.borrowerName << " " << book.genre << endl;
//         }
//         file.close();
//     }

//     // Function to load user data from the file
//     void loadLibraryUsers() {
//         ifstream file(usersFile);
//         if (!file.is_open()) {
//             cout << "Warning: Could not open 'library_users.txt'. File might not exist.\n";
//             return;
//         }
//         User user;
//         while (file >> user.userID >> user.userName) {
//             libraryUsers.push_back(user);
//         }
//         file.close();
//     }

//     // Function to save user data to the file
//     void saveLibraryUsers() {
//         ofstream file(usersFile);
//         if (!file.is_open()) {
//             cout << "Error: Could not open 'library_users.txt' for writing.\n";
//             return;
//         }
//         for (const auto &user : libraryUsers) {
//             file << user.userID << " " << user.userName << endl;
//         }
//         file.close();
//     }

//     // Function to load bank balance from the file
//     void loadBankBalance() {
//         ifstream file(bankBalanceFile);
//         if (!file.is_open()) {
//             bankBalance = 0.0;  // Initialize with zero if file doesn't exist
//             return;
//         }
//         file >> bankBalance;
//         file.close();
//     }

//     // Function to save bank balance to the file
//     void saveBankBalance() {
//         ofstream file(bankBalanceFile);
//         if (!file.is_open()) {
//             cout << "Error: Could not open 'bank_balance.txt' for writing.\n";
//             return;
//         }
//         file << bankBalance;
//         file.close();
//     }

//     // Function to log overdue books
//     void logOverdueBooks(const vector<Book> &overdueBooks, const string &currentDate) {
//         ofstream file(overdueLogFile, ios::app);  // Append mode
//         if (!file.is_open()) {
//             cout << "Error: Could not open 'overdue_books_log.txt'.\n";
//             return;
//         }
//         for (const auto &book : overdueBooks) {
//             file << currentDate << " " << book.bookID << " " << book.title << " "
//                  << book.dueDate << " " << book.borrowerName << " " << book.genre << endl;
//         }
//         file.close();
//     }

// public:
//     // Constructor
//     LibraryFineManager() {
//         loadBorrowedBooks();
//         loadLibraryUsers();
//         loadBankBalance();
//         fineRatePerDay = 2.0;  // Default fine rate per day
//     }

//     // Destructor
//     ~LibraryFineManager() {
//         saveBorrowedBooks();
//         saveLibraryUsers();
//         saveBankBalance();
//     }

//     // Function to check if a user exists
//     bool userExists(int userID) {
//         for (const auto &user : libraryUsers) {
//             if (user.userID == userID) {
//                 return true;
//             }
//         }
//         return false;
//     }

//     // Function to create a new user account
//     void createAccount() {
//         int userID;
//         string userName;

//         cout << "Enter User ID: ";
//         cin >> userID;
//         if (userExists(userID)) {
//             cout << "Account already exists for User ID " << userID << ".\n";
//             return;
//         }

//         cout << "Enter User Name: ";
//         cin.ignore();
//         getline(cin, userName);

//         libraryUsers.push_back({userID, userName});
//         cout << "Account created successfully!\n";
//     }

//     // Function to add a borrowed book
//     void addBorrowedBook() {
//         int userID;
//         string userName;

//         cout << "Enter your User ID: ";
//         cin >> userID;

//         if (!userExists(userID)) {
//             cout << "No account found for this User ID. Please create an account first.\n";
//             return;
//         }

//         cout << "Enter your Name: ";
//         cin.ignore();
//         getline(cin, userName);

//         Book newBook;
//         cout << "Enter Book ID: ";
//         cin >> newBook.bookID;
//         cout << "Enter Book Title: ";
//         cin.ignore();
//         getline(cin, newBook.title);

//         cout << "Enter Due Date (YYYY-MM-DD): ";
//         cin >> newBook.dueDate;

//         cout << "Enter Book Genre (e.g., Novel, Science, etc.): ";
//         cin.ignore();
//         getline(cin, newBook.genre);  // New field to specify genre

//         newBook.borrowerName = userName;
//         borrowedBooks.push_back(newBook);
//         cout << "Book added successfully!\n";
//     }

//     // Function to calculate fine and update the bank balance
//     void calculateFine() {
//         string dueDate, returnDate;
//         cout << "\n=========== Fine Calculation ================" << endl;
//         cout << "Enter Due Date (YYYY-MM-DD): ";
//         cin >> dueDate;
//         cout << "Enter Return Date (YYYY-MM-DD): ";
//         cin >> returnDate;

//         int daysLate = calculateDateDifference(dueDate, returnDate);
//         string genre;

//         cout << "Enter Book Genre (e.g., Novel, Science, etc.): ";
//         cin.ignore();
//         getline(cin, genre);  // Get the genre for the current book

//         if (genre == "Novel") {
//             cout << "This is a novel, no fine is applicable.\n";
//         } else if (daysLate <= gracePeriod) {
//             cout << "No fine. Returned within grace period.\n";
//         } else {
//             float fine = (daysLate - gracePeriod) * fineRatePerDay;
//             cout << "Fine: " << fine << " Rupees\n";
//             cout << "Do you want to pay the fine? (yes/no): ";
//             string response;
//             cin >> response;

//             if (response == "yes") {
//                 bankBalance += fine;
//                 cout << "Fine paid successfully!\n";
//                 cout << "Library Bank Balance: " << bankBalance << " Rupees\n";
//             } else {
//                 cout << "Fine not paid.\n";
//             }
//         }
//     }

//     // Function to track overdue books
//     void trackOverdueBooks() {
//         string currentDate;
//         cout << "\n=========== Overdue Books Tracker ============" << endl;
//         cout << "Enter today's date (YYYY-MM-DD): ";
//         cin >> currentDate;

//         vector<Book> overdueBooks;
//         for (const auto &book : borrowedBooks) {
//             int daysLate = calculateDateDifference(book.dueDate, currentDate);
//             if (daysLate > gracePeriod) {
//                 overdueBooks.push_back(book);
//             }
//         }

//         if (overdueBooks.empty()) {
//             cout << "No overdue books.\n";
//         } else {
//             cout << "Overdue books:\n";
//             for (const auto &book : overdueBooks) {
//                 cout << "Book ID: " << book.bookID << ", Title: " << book.title
//                      << ", Borrower: " << book.borrowerName << ", Due Date: " << book.dueDate << endl;
//             }
//             logOverdueBooks(overdueBooks, currentDate);
//         }
//     }

//     // Function to display all borrowed books
//     void displayAllBorrowedBooks() {
//         cout << "\n=========== Borrowed Books List =============" << endl;
//         if (borrowedBooks.empty()) {
//             cout << "No borrowed books available." << endl;
//         } else {
//             for (const auto& book : borrowedBooks) {
//                 cout << left << setw(10) << "Book ID:" << setw(25) << book.bookID 
//                      << setw(10) << "Title:" << setw(25) << book.title
//                      << setw(15) << "Due Date:" << setw(15) << book.dueDate 
//                      << setw(15) << "Borrower:" << setw(15) << book.borrowerName
//                      << endl;
//             }
//         }
//         cout << "===============================================" << endl;
//     }

//     // Utility to calculate the number of days between two dates
//     int calculateDateDifference(const string &dueDate, const string &returnDate) {
//         // Assume date format is YYYY-MM-DD for simplicity
//         int dueYear, dueMonth, dueDay;
//         int returnYear, returnMonth, returnDay;

//         sscanf(dueDate.c_str(), "%d-%d-%d", &dueYear, &dueMonth, &dueDay);
//         sscanf(returnDate.c_str(), "%d-%d-%d", &returnYear, &returnMonth, &returnDay);

//         // Simple date difference calculation (not accounting for months/days complexity)
//         return (returnYear - dueYear) * 365 + (returnMonth - dueMonth) * 30 + (returnDay - dueDay);
//     }
// };

// // Function to display the main menu and handle user choices
// void displayMenu(LibraryFineManager &manager) {
//     int choice;
//     do {
//         cout << "===============================================" << endl;
//         cout << "=         LIBRARY FINE MANAGEMENT            =" << endl;
//         cout << "===============================================" << endl;
//         cout << "\n================= MENU ========================" << endl;
//         cout << "1. Create Account                           " << endl;
//         cout << "2. Add Borrowed Book                        " << endl;
//         cout << "3. Calculate Fine                           " << endl;
//         cout << "4. Track Overdue Books                      " << endl;
//         cout << "5. Display All Borrowed Books               " << endl;
//         cout << "6. Exit                                     " << endl;
//         cout << "===============================================" << endl;
//         cout << "Enter your choice: ";
//         cin >> choice;

//         switch (choice) {
//             case 1: manager.createAccount(); break;
//             case 2: manager.addBorrowedBook(); break;
//             case 3: manager.calculateFine(); break;
//             case 4: manager.trackOverdueBooks(); break;
//             case 5: manager.displayAllBorrowedBooks(); break;
//             case 6: cout << "Exiting..."; break;
//             default: cout << "Invalid choice. Please try again.\n"; break;
//         }
//     } while (choice != 6);
// }

// int main() {
//     LibraryFineManager manager;
//     displayMenu(manager);
//     return 0;
// }

// // #include <iostream>
// // #include <vector>
// // #include <string>
// // #include <fstream>
// // #include <iomanip>
// // #include <sstream>

// // using namespace std;

// // class LibraryFineManager {
// // private:
// //     struct Book {
// //         int bookID;
// //         string title;
// //         string dueDate;
// //         string borrowerName;
// //         string genre;
// //     };

// //     struct User {
// //         int userID;
// //         string userName;
// //     };

// //     vector<Book> borrowedBooks;
// //     vector<User> libraryUsers;
// //     double bankBalance = 0.0;
// //     double fineRatePerDay = 2.0;
// //     const string borrowedBooksFile = "borrowed_books.csv";
// //     const string usersFile = "library_users.csv";
// //     const string bankBalanceFile = "bank_balance.txt";
// //     const int gracePeriod = 2; // Grace period in days

// //     // Load borrowed books from file
// //     void loadBorrowedBooks() {
// //         ifstream file(borrowedBooksFile);
// //         string line;
// //         while (getline(file, line)) {
// //             istringstream iss(line);
// //             Book book;
// //             if (getline(iss, line, ',')) book.bookID = stoi(line);
// //             getline(iss, book.title, ',');
// //             getline(iss, book.dueDate, ',');
// //             getline(iss, book.borrowerName, ',');
// //             getline(iss, book.genre, ',');
// //             borrowedBooks.push_back(book);
// //         }
// //     }

// //     // Save borrowed books to file
// //     void saveBorrowedBooks() {
// //         ofstream file(borrowedBooksFile);
// //         for (const auto &book : borrowedBooks) {
// //             file << book.bookID << "," << book.title << "," << book.dueDate << ","
// //                  << book.borrowerName << "," << book.genre << endl;
// //         }
// //     }

// //     // Load users from file
// //     void loadLibraryUsers() {
// //         ifstream file(usersFile);
// //         string line;
// //         while (getline(file, line)) {
// //             istringstream iss(line);
// //             User user;
// //             if (getline(iss, line, ',')) user.userID = stoi(line);
// //             getline(iss, user.userName, ',');
// //             libraryUsers.push_back(user);
// //         }
// //     }

// //     // Save users to file
// //     void saveLibraryUsers() {
// //         ofstream file(usersFile);
// //         for (const auto &user : libraryUsers) {
// //             file << user.userID << "," << user.userName << endl;
// //         }
// //     }

// //     // Load bank balance from file
// //     void loadBankBalance() {
// //         ifstream file(bankBalanceFile);
// //         if (file.is_open()) file >> bankBalance;
// //     }

// //     // Save bank balance to file
// //     void saveBankBalance() {
// //         ofstream file(bankBalanceFile);
// //         file << bankBalance;
// //     }

// // public:
// //     LibraryFineManager() {
// //         loadBorrowedBooks();
// //         loadLibraryUsers();
// //         loadBankBalance();
// //     }

// //     ~LibraryFineManager() {
// //         saveBorrowedBooks();
// //         saveLibraryUsers();
// //         saveBankBalance();
// //     }

// //     // Check if a user exists by ID
// //     bool userExists(int userID) {
// //         for (const auto &user : libraryUsers) {
// //             if (user.userID == userID) {
// //                 return true;
// //             }
// //         }
// //         return false;
// //     }

// //     // Create a new user account
// //     void createAccount() {
// //         int userID;
// //         string userName;
// //         cout << "Enter User ID: ";
// //         cin >> userID;

// //         if (userExists(userID)) {
// //             cout << "Account already exists for User ID " << userID << ".\n";
// //             return;
// //         }

// //         cout << "Enter User Name: ";
// //         cin.ignore();
// //         getline(cin, userName);

// //         libraryUsers.push_back({userID, userName});
// //         cout << "Account created successfully!\n";
// //     }

// //     // Add a new borrowed book
// //     void addBorrowedBook() {
// //         int userID;
// //         cout << "Enter your User ID: ";
// //         cin >> userID;

// //         if (!userExists(userID)) {
// //             cout << "No account found for this User ID. Please create an account first.\n";
// //             return;
// //         }

// //         Book newBook;
// //         cout << "Enter Book ID: ";
// //         cin >> newBook.bookID;
// //         cout << "Enter Book Title: ";
// //         cin.ignore();
// //         getline(cin, newBook.title);
// //         cout << "Enter Due Date (YYYY-MM-DD): ";
// //         cin >> newBook.dueDate;
// //         cout << "Enter Book Genre (e.g., Novel, Science, etc.): ";
// //         cin.ignore();
// //         getline(cin, newBook.genre);

// //         cout << "Enter Borrower's Name: ";
// //         getline(cin, newBook.borrowerName);

// //         borrowedBooks.push_back(newBook);
// //         cout << "Book added successfully!\n";
// //     }

// //     // Calculate fine based on late return
// //     void calculateFine() {
// //         string dueDate, returnDate;
// //         cout << "Enter Due Date (YYYY-MM-DD): ";
// //         cin >> dueDate;
// //         cout << "Enter Return Date (YYYY-MM-DD): ";
// //         cin >> returnDate;

// //         int daysLate = stoi(returnDate.substr(8, 2)) - stoi(dueDate.substr(8, 2)); // Simple calculation based on days
// //         if (daysLate > gracePeriod) {
// //             double fine = (daysLate - gracePeriod) * fineRatePerDay;
// //             cout << "Fine: " << fine << " Rupees\n";
// //             bankBalance += fine;
// //             cout << "Fine added to library balance. Current balance: " << bankBalance << " Rupees\n";
// //         } else {
// //             cout << "No fine. Returned within grace period.\n";
// //         }
// //     }

// //     // Display all borrowed books
// //     void displayAllBorrowedBooks() {
// //         cout << "=========== Borrowed Books =============\n";
// //         for (const auto &book : borrowedBooks) {
// //             cout << "Book ID: " << book.bookID << ", Title: " << book.title
// //                  << ", Due Date: " << book.dueDate << ", Borrower: " << book.borrowerName
// //                  << ", Genre: " << book.genre << endl;
// //         }
// //         cout << "=========================================\n";
// //     }
// // };

// // // Main function to display menu
// // int main() {
// //     LibraryFineManager manager;
// //     int choice;
// //     do {
// //         cout << "\n1. Create Account\n2. Borrow Book\n3. Calculate Fine\n4. Display Books\n5. Exit\n";
// //         cout << "Enter your choice: ";
// //         cin >> choice;

// //         switch (choice) {
// //             case 1: manager.createAccount(); break;
// //             case 2: manager.addBorrowedBook(); break;
// //             case 3: manager.calculateFine(); break;
// //             case 4: manager.displayAllBorrowedBooks(); break;
// //             case 5: cout << "Exiting...\n"; break;
// //             default: cout << "Invalid choice. Try again.\n"; break;
// //         }
// //     } while (choice != 5);

// //     return 0;
// // }
