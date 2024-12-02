// // // #include <iostream>
// // // #include <vector>
// // // #include <string>
// // // #include <fstream>
// // // #include <iomanip>
// // // #include <map>
// // // #include <sstream>
// // // #include <ctime>

// // // using namespace std;

// // // // ANSI escape codes for color
// // // #define RESET   "\033[0m"
// // // #define BOLD    "\033[1m"
// // // #define BLUE    "\033[34m"
// // // #define GREEN   "\033[32m"
// // // #define RED     "\033[31m"
// // // #define CYAN    "\033[36m"
// // // #define YELLOW  "\033[33m"
// // // #define MAGENTA "\033[35m"

// // // class LibraryFineManager
// // // {

// // // private:
// // //     struct Book
// // //     {
// // //         int bookID;
// // //         string title;
// // //         string dueDate;
// // //         string borrowerName;
// // //         string genre;
// // //     };

// // //     struct User
// // //     {
// // //         int userID;
// // //         string userName;
// // //         string phoneNumber;
// // //         string email;
// // //         string address;
// // //     };

// // //     vector<Book> borrowedBooks;
// // //     vector<User> libraryUsers;
// // //     double bankBalance = 0.0;
// // //     double fineRatePerDay;
// // //     const string borrowedBooksFile = "borrowed_books.txt";
// // //     const string usersFile = "library_users.txt";
// // //     const string bankBalanceFile = "bank_balance.txt";
// // //     const string overdueLogFile = "overdue_books_log.txt";
// // //     const string finesLogFile = "daily_fines_log.txt";
// // //     const int gracePeriod = 2;
// // //     map<string, double> dailyCollectedFines;

// // //     void loadBorrowedBooks()
// // //     {
// // //         ifstream file(borrowedBooksFile);
// // //         if (!file.is_open())
// // //         {
// // //             cout << RED << "Warning: Could not open 'borrowed_books.txt'. File might not exist." << RESET << endl;
// // //             return;
// // //         }

// // //         Book book;
// // //         while (file >> book.bookID >> book.title >> book.dueDate >> book.borrowerName >> book.genre)
// // //         {
// // //             borrowedBooks.push_back(book);
// // //         }
// // //         file.close();
// // //     }

// // //     void saveBorrowedBooks()
// // //     {
// // //         ofstream file(borrowedBooksFile);
// // //         if (!file.is_open())
// // //         {
// // //             cout << RED << "Error: Could not open 'borrowed_books.txt' for writing." << RESET << endl;
// // //             return;
// // //         }

// // //         for (const auto &book : borrowedBooks)
// // //         {
// // //             file << book.bookID << " " << book.title << " "
// // //                  << book.dueDate << " " << book.borrowerName << " " << book.genre << endl;
// // //         }
// // //         file.close();
// // //     }

// // //     void loadLibraryUsers()
// // //     {
// // //         ifstream file(usersFile);
// // //         if (!file.is_open())
// // //         {
// // //             cout << RED << "Warning: Could not open 'library_users.txt'. File might not exist." << RESET << endl;
// // //             return;
// // //         }

// // //         User user;
// // //         while (file >> user.userID >> user.userName)
// // //         {
// // //             // For simplicity, skipping extra details for now
// // //             getline(file, user.phoneNumber);
// // //             getline(file, user.email);
// // //             getline(file, user.address);
// // //             libraryUsers.push_back(user);
// // //         }
// // //         file.close();
// // //     }

// // //     void saveLibraryUsers()
// // //     {
// // //         ofstream file(usersFile);
// // //         if (!file.is_open())
// // //         {
// // //             cout << RED << "Error: Could not open 'library_users.txt' for writing." << RESET << endl;
// // //             return;
// // //         }

// // //         for (const auto &user : libraryUsers)
// // //         {
// // //             file << "ID:"<<user.userID<<"\n" 
// // //                  << "Name:"<< user.userName << "\n"
// // //                  << "Phone no.:"<<user.phoneNumber << "\n"
// // //                  << "Email:"<<user.email << "\n"
// // //                  << "Address:"<<user.address << endl;
// // //         }
// // //         cout<<endl;
// // //         file.close();
// // //     }

// // //     void loadBankBalance()
// // //     {
// // //         ifstream file(bankBalanceFile);
// // //         if (!file.is_open())
// // //         {
// // //             bankBalance = 0.0;
// // //             return;
// // //         }

// // //         file >> bankBalance;
// // //         file.close();
// // //     }

// // //     void saveBankBalance()
// // //     {
// // //         ofstream file(bankBalanceFile);
// // //         if (!file.is_open())
// // //         {
// // //             cout << RED << "Error: Could not open 'bank_balance.txt' for writing." << RESET << endl;
// // //             return;
// // //         }

// // //         file << bankBalance;
// // //         file.close();
// // //     }

// // //     void logOverdueBooks(const vector<Book> &overdueBooks, const string &currentDate)
// // //     {
// // //         ofstream file(overdueLogFile, ios::app);
// // //         if (!file.is_open())
// // //         {
// // //             cout << RED << "Error: Could not open 'overdue_books_log.txt'." << RESET << endl;
// // //             return;
// // //         }

// // //         for (const auto &book : overdueBooks)
// // //         {
// // //             file << currentDate << " " << book.bookID << " " << book.title << " "
// // //                  << book.dueDate << " " << book.borrowerName << " " << book.genre << endl;
// // //         }
// // //         file.close();
// // //     }

// // //     void logDailyFines(const string &date, double totalFines)
// // //     {
// // //         ofstream file(finesLogFile, ios::app);
// // //         if (!file.is_open())
// // //         {
// // //             cout << RED << "Error: Could not open 'daily_fines_log.txt'." << RESET << endl;
// // //             return;
// // //         }

// // //         file << date << " " << totalFines << endl;
// // //         file.close();
// // //     }

// // // public:
// // //     LibraryFineManager()
// // //     {
// // //         loadBorrowedBooks();
// // //         loadLibraryUsers();
// // //         loadBankBalance();
// // //         fineRatePerDay = 2.0;
// // //     }

// // //     ~LibraryFineManager()
// // //     {
// // //         saveBorrowedBooks();
// // //         saveLibraryUsers();
// // //         saveBankBalance();
// // //     }

// // //     bool userExists(int userID)
// // //     {
// // //         for (const auto &user : libraryUsers)
// // //         {
// // //             if (user.userID == userID)
// // //             {
// // //                 return true;
// // //             }
// // //         }
// // //         return false;
// // //     }

// // //     void createAccount()
// // //     {
// // //         int userID;
// // //         string userName, phoneNumber, email, address;

// // //         cout << CYAN << "\n======== Create Account ========" << RESET << endl;
// // //         cout << "---------------------------------" << endl;
// // //         cout << CYAN << "Enter User ID: " << RESET;
// // //         cin >> userID;

// // //         if (userExists(userID))
// // //         {
// // //             cout << YELLOW << "Account already exists for User ID " << userID << "." << RESET << endl;
// // //             return;
// // //         }

// // //         cout << CYAN << "Enter User Name: " << RESET;
// // //         cin.ignore(); // To clear the newline left by previous input
// // //         getline(cin, userName);

// // //         // New fields for user details
// // //         cout << CYAN << "Enter Phone Number: " << RESET;
// // //         getline(cin, phoneNumber);

// // //         cout << CYAN << "Enter Email: " << RESET;
// // //         getline(cin, email);

// // //         cout << CYAN << "Enter Address: " << RESET;
// // //         getline(cin, address);

// // //         libraryUsers.push_back({userID, userName, phoneNumber, email, address});
// // //         cout << GREEN << "Account created successfully!" << RESET << endl;

// // //         // Displaying the new user details for confirmation
// // //         cout << "\nUser Details:" << endl;
// // //         cout << "-----------------------------" << endl;
// // //         cout << "User ID: " << userID << endl;
// // //         cout << "User Name: " << userName << endl;
// // //         cout << "Phone Number: " << phoneNumber << endl;
// // //         cout << "Email: " << email << endl;
// // //         cout << "Address: " << address << endl;
// // //         cout << "-----------------------------" << endl;
// // //     }

// // //     void displayMenu()
// // //     {
// // //         cout << CYAN << "\n======== LIBRARY FINE MANAGEMENTSYSTEM ========" << RESET << endl;
// // //         cout << "---------------------------------" << endl;
// // //         cout << "1. Create Account\n";
// // //         cout << "2. Borrow a Book\n";
// // //         cout << "3. Calculate Fine\n";
// // //         cout << "4. Track Overdue Books\n";
// // //         cout << "5. Show Daily Collected Fines\n";
// // //         cout << "6. Show User Details\n";
// // //         cout << "7. Exit\n";
// // //     }

// // //     void trackOverdueBooks()
// // //     {
// // //         cout << CYAN << "\n======== Overdue Books ========" << RESET << endl;
// // //         cout << "---------------------------------" << endl;

// // //         string currentDate = "2024-11-22"; // Simulating the current date

// // //         vector<Book> overdueBooks;

// // //         for (const auto &book : borrowedBooks)
// // //         {
// // //             int daysLate = calculateDateDifference(book.dueDate, currentDate);
// // //             if (daysLate > gracePeriod)
// // //             {
// // //                 overdueBooks.push_back(book);
// // //             }
// // //         }

// // //         if (overdueBooks.empty())
// // //         {
// // //             cout << GREEN << "No overdue books." << RESET << endl;
// // //         }
// // //         else
// // //         {
// // //             cout << left << setw(10) << "Book ID" << setw(30) << "Book Title" << setw(20) << "Borrowed By"
// // //                  << setw(15) << "Due Date" << setw(10) << "Fine" << endl;
// // //             cout << "---------------------------------------------------------------" << endl;

// // //             double totalFines = 0.0;
// // //             for (const auto &book : overdueBooks)
// // //             {
// // //                 int daysLate = calculateDateDifference(book.dueDate, currentDate);
// // //                 double fine = (daysLate - gracePeriod) * fineRatePerDay;
// // //                 totalFines += fine;

// // //                 cout << left << setw(10) << book.bookID << setw(30) << book.title << setw(20) << book.borrowerName
// // //                      << setw(15) << book.dueDate << setw(15) << fixed << setprecision(2) << fine << endl;
// // //             }
// // //             cout << "---------------------------------------------------------------" << endl;
// // //             cout << YELLOW << "\nTotal Fine: " << RESET << fixed << setprecision(2) << totalFines << " Rupees\n";
// // //             dailyCollectedFines[currentDate] += totalFines;
// // //             logOverdueBooks(overdueBooks, currentDate);
// // //             logDailyFines(currentDate, totalFines);
// // //         }
// // //     }

// // //     void displayDailyFines()
// // //     {
// // //         cout << CYAN << "\n======== Daily Collected Fines ========" << RESET << endl;
// // //         cout << "---------------------------------" << endl;

// // //         if (dailyCollectedFines.empty())
// // //         {
// // //             cout << GREEN << "No fines collected yet." << RESET << endl;
// // //         }
// // //         else
// // //         {
// // //             cout << left << setw(15) << "Date" << setw(15) << "Total Fine" << endl;
// // //             cout << "-------------------------------------------------" << endl;
// // //             for (const auto &entry : dailyCollectedFines)
// // //             {
// // //                 cout << left << setw(15) << entry.first << setw(15) << fixed << setprecision(2) << entry.second << endl;
// // //             }
// // //         }
// // //     }

// // //     void showUserDetails()
// // //     {
// // //         cout << CYAN << "\n======== User Details ========" << RESET << endl;
// // //         cout << "---------------------------------" << endl;

// // //         if (libraryUsers.empty())
// // //         {
// // //             cout << GREEN << "No users available." << RESET << endl;
// // //         }
// // //         else
// // //         {
// // //             cout << left << setw(15) << "User ID" << setw(30) << "User Name" << endl;
// // //             cout << "-------------------------------------------------" << endl;
// // //             for (const auto &user : libraryUsers)
// // //             {
// // //                 cout << left << setw(15) << user.userID << setw(30) << user.userName << endl;
// // //             }
// // //         }
// // //     }

// // //     int calculateDateDifference(const string &dueDate, const string &currentDate)
// // //     {
// // //         // Simple placeholder, this can be improved using actual date libraries
// // //         return 5; // Assuming the book is 5 days late
// // //     }
// // // };

// // // int main()
// // // {
// // //     LibraryFineManager manager;
// // //     int choice;

// // //     do
// // //     {
// // //         manager.displayMenu();
// // //         cout << CYAN << "Enter your choice: " << RESET;
// // //         cin >> choice;

// // //         switch (choice)
// // //         {
            
// // //         case 1:
// // //             manager.createAccount();
// // //             break;
            
// // //         case 2:
// // //             // Implement borrow book functionality here
// // //             break;
            
// // //         case 3:
// // //             // Implement calculate fine functionality here
// // //             break;
            
// // //         case 4:
// // //             manager.trackOverdueBooks();
// // //             break;
            
// // //         case 5:
// // //             manager.displayDailyFines();
// // //             break;
            
// // //         case 6:
// // //             manager.showUserDetails();
// // //             break;
            
// // //         case 7:
// // //             cout << GREEN << "Exiting program." << RESET << endl;
// // //             break;
            
// // //         default:
// // //           cout << RED << "Invalid choice, please try again." << RESET << endl;
            
// // //         }
// // //     } while (choice != 7);

// // //     return 0;
// // // }

// // #include <iostream>
// // #include <vector>
// // #include <string>
// // #include <fstream>
// // #include <iomanip>
// // #include <map>

// // using namespace std;

// // // ANSI escape codes for color
// // #define RESET   "\033[0m"
// // #define GREEN   "\033[32m"
// // #define RED     "\033[31m"
// // #define CYAN    "\033[36m"
// // #define YELLOW  "\033[33m"

// // // Struct for Book details
// // struct Book {
// //     int bookID;
// //     string title;
// //     string dueDate;
// //     string borrowerName;
// //     string genre;
// // };

// // // Struct for User details
// // struct User {
// //     int userID;
// //     string userName;
// //     string phoneNumber;
// //     string email;
// //     string address;
// // };

// // class LibraryFineManager {
// // private:
// //     vector<Book> borrowedBooks;
// //     vector<User> libraryUsers;
// //     double bankBalance = 0.0;
// //     const double fineRatePerDay = 2.0; // Fine per day after grace period
// //     const int gracePeriod = 2;

// //     const string borrowedBooksFile = "borrowed_books.txt";
// //     const string usersFile = "library_users.txt";
// //     const string bankBalanceFile = "bank_balance.txt";

// //     void loadBorrowedBooks() {
// //         ifstream file(borrowedBooksFile);
// //         if (!file.is_open()) {
// //             cout << YELLOW << "Warning: Could not open '" << borrowedBooksFile << "' for reading." << RESET << endl;
// //             return;
// //         }
// //         Book book;
// //         while (file >> book.bookID) {
// //             file.ignore();
// //             getline(file, book.title);
// //             getline(file, book.dueDate);
// //             getline(file, book.borrowerName);
// //             getline(file, book.genre);
// //             borrowedBooks.push_back(book);
// //         }
// //         file.close();
// //     }

// //     void saveBorrowedBooks() {
// //         ofstream file(borrowedBooksFile);
// //         if (!file.is_open()) {
// //             cout << RED << "Error: Could not open '" << borrowedBooksFile << "' for writing." << RESET << endl;
// //             return;
// //         }
// //         for (const auto &book : borrowedBooks) {
// //             file << book.bookID << "\n"
// //                  << book.title << "\n"
// //                  << book.dueDate << "\n"
// //                  << book.borrowerName << "\n"
// //                  << book.genre << "\n";
// //         }
// //         file.close();
// //     }

// //     void loadLibraryUsers() {
// //         ifstream file(usersFile);
// //         if (!file.is_open()) {
// //             cout << YELLOW << "Warning: Could not open '" << usersFile << "' for reading." << RESET << endl;
// //             return;
// //         }
// //         User user;
// //         while (file >> user.userID) {
// //             file.ignore();
// //             getline(file, user.userName);
// //             getline(file, user.phoneNumber);
// //             getline(file, user.email);
// //             getline(file, user.address);
// //             libraryUsers.push_back(user);
// //         }
// //         file.close();
// //     }

// //     void saveLibraryUsers() {
// //         ofstream file(usersFile);
// //         if (!file.is_open()) {
// //             cout << RED << "Error: Could not open '" << usersFile << "' for writing." << RESET << endl;
// //             return;
// //         }
// //         for (const auto &user : libraryUsers) {
// //             file << user.userID << "\n"
// //                  << user.userName << "\n"
// //                  << user.phoneNumber << "\n"
// //                  << user.email << "\n"
// //                  << user.address << "\n";
// //         }
// //         file.close();
// //     }

// //     void loadBankBalance() {
// //         ifstream file(bankBalanceFile);
// //         if (!file.is_open()) {
// //             bankBalance = 0.0; // Default value if file doesn't exist
// //             return;
// //         }
// //         file >> bankBalance;
// //         file.close();
// //     }

// //     void saveBankBalance() {
// //         ofstream file(bankBalanceFile);
// //         if (!file.is_open()) {
// //             cout << RED << "Error: Could not open '" << bankBalanceFile << "' for writing." << RESET << endl;
// //             return;
// //         }
// //         file << bankBalance;
// //         file.close();
// //     }

// //     int calculateDateDifference(const string &dueDate, const string &currentDate) {
// //         // Placeholder: Replace with actual date difference logic
// //         return 5; // Assume a fixed overdue duration for demonstration
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

// //     void createAccount() {
// //         User user;
// //         cout << CYAN << "=== Create New User Account ===" << RESET << endl;
// //         cout << "Enter User ID: ";
// //         cin >> user.userID;
// //         cin.ignore();
// //         cout << "Enter Name: ";
// //         getline(cin, user.userName);
// //         cout << "Enter Phone Number: ";
// //         getline(cin, user.phoneNumber);
// //         cout << "Enter Email: ";
// //         getline(cin, user.email);
// //         cout << "Enter Address: ";
// //         getline(cin, user.address);
// //         libraryUsers.push_back(user);
// //         cout << GREEN << "User account created successfully!" << RESET << endl;
// //     }

// //     void trackOverdueBooks() {
// //         string currentDate = "2024-11-23"; // Placeholder for current date
// //         vector<Book> overdueBooks;

// //         for (const auto &book : borrowedBooks) {
// //             int daysLate = calculateDateDifference(book.dueDate, currentDate);
// //             if (daysLate > gracePeriod) {
// //                 overdueBooks.push_back(book);
// //             }
// //         }

// //         if (overdueBooks.empty()) {
// //             cout << GREEN << "No overdue books!" << RESET << endl;
// //         } else {
// //             cout << CYAN << "=== Overdue Books ===" << RESET << endl;
// //             for (const auto &book : overdueBooks) {
// //                 double fine = (calculateDateDifference(book.dueDate, currentDate) - gracePeriod) * fineRatePerDay;
// //                 cout << "Book ID: " << book.bookID
// //                      << ", Title: " << book.title
// //                      << ", Borrower: " << book.borrowerName
// //                      << ", Fine: $" << fine << endl;
// //             }
// //         }
// //     }

// //     void displayMenu() {
// //         cout << CYAN << "\n=== Library Management System ===" << RESET << endl;
// //         cout << "1. Create Account\n";
// //         cout << "2. Track Overdue Books\n";
// //         cout << "3. Exit\n";
// //     }
// // };

// // int main() {
// //     LibraryFineManager manager;
// //     int choice;

// //     do {
// //         manager.displayMenu();
// //         cout << "Enter your choice: ";
// //         cin >> choice;

// //         switch (choice) {
// //             case 1:
// //                 manager.createAccount();
// //                 break;
// //             case 2:
// //                 manager.trackOverdueBooks();
// //                 break;
// //             case 3:
// //                 cout << GREEN << "Exiting program. Goodbye!" << RESET << endl;
// //                 break;
// //             default:
// //                 cout << RED << "Invalid choice. Please try again." << RESET << endl;
// //                 break;
// //         }
// //     } while (choice != 3);

// //     return 0;
// // }


// #include <iostream>
// #include <vector>
// #include <string>
// #include <fstream>
// #include <iomanip>
// #include <map>
// #include <sstream>
// #include <ctime>

// using namespace std;

// // ANSI escape codes for color
// #define RESET   "\033[0m"
// #define BOLD    "\033[1m"
// #define BLUE    "\033[34m"
// #define GREEN   "\033[32m"
// #define RED     "\033[31m"
// #define CYAN    "\033[36m"
// #define YELLOW  "\033[33m"
// #define MAGENTA "\033[35m"

// class LibraryFineManager
// {

// private:
//     struct Book
//     {
//         int bookID;
//         string title;
//         string dueDate;
//         string borrowerName;
//         string genre;
//     };

//     struct User
//     {
//         int userID;
//         string userName;
//         string phoneNumber;
//         string email;
//         string address;
//     };

//     vector<Book> borrowedBooks;
//     vector<User> libraryUsers;
//     double bankBalance = 0.0;
//     double fineRatePerDay;
//     const string borrowedBooksFile = "borrowed_books.txt";
//     const string usersFile = "library_users.txt";
//     const string bankBalanceFile = "bank_balance.txt";
//     const string overdueLogFile = "overdue_books_log.txt";
//     const string finesLogFile = "daily_fines_log.txt";
//     const int gracePeriod = 2;
//     map<string, double> dailyCollectedFines;

//     void loadBorrowedBooks()
//     {
//         ifstream file(borrowedBooksFile);
//         if (!file.is_open())
//         {
//             cout << RED << "Warning: Could not open 'borrowed_books.txt'. File might not exist." << RESET << endl;
//             return;
//         }

//         Book book;
//         while (file >> book.bookID >> book.title >> book.dueDate >> book.borrowerName >> book.genre)
//         {
//             borrowedBooks.push_back(book);
//         }
//         file.close();
//     }

//     void saveBorrowedBooks()
//     {
//         ofstream file(borrowedBooksFile);
//         if (!file.is_open())
//         {
//             cout << RED << "Error: Could not open 'borrowed_books.txt' for writing." << RESET << endl;
//             return;
//         }

//         for (const auto &book : borrowedBooks)
//         {
//             file << book.bookID << " " << book.title << " "
//                  << book.dueDate << " " << book.borrowerName << " " << book.genre << endl;
//         }
//         file.close();
//     }

//     void loadLibraryUsers()
//     {
//         ifstream file(usersFile);
//         if (!file.is_open())
//         {
//             cout << RED << "Warning: Could not open 'library_users.txt'. File might not exist." << RESET << endl;
//             return;
//         }

//         User user;
//         while (file >> user.userID >> user.userName)
//         {
//             // For simplicity, skipping extra details for now
//             getline(file, user.phoneNumber);
//             getline(file, user.email);
//             getline(file, user.address);
//             libraryUsers.push_back(user);
//         }
//         file.close();
//     }

//     void saveLibraryUsers()
//     {
//         ofstream file(usersFile);
//         if (!file.is_open())
//         {
//             cout << RED << "Error: Could not open 'library_users.txt' for writing." << RESET << endl;
//             return;
//         }

//         for (const auto &user : libraryUsers)
//         {
//             file << "ID:"<<user.userID<<"\n" 
//                  << "Name:"<< user.userName << "\n"
//                  << "Phone no.:"<<user.phoneNumber << "\n"
//                  << "Email:"<<user.email << "\n"
//                  << "Address:"<<user.address << endl;
//         }
//         cout<<endl;
//         file.close();
//     }

//     void loadBankBalance()
//     {
//         ifstream file(bankBalanceFile);
//         if (!file.is_open())
//         {
//             bankBalance = 0.0;
//             return;
//         }

//         file >> bankBalance;
//         file.close();
//     }

//     void saveBankBalance()
//     {
//         ofstream file(bankBalanceFile);
//         if (!file.is_open())
//         {
//             cout << RED << "Error: Could not open 'bank_balance.txt' for writing." << RESET << endl;
//             return;
//         }

//         file << bankBalance;
//         file.close();
//     }

//     void logOverdueBooks(const vector<Book> &overdueBooks, const string &currentDate)
//     {
//         ofstream file(overdueLogFile, ios::app);
//         if (!file.is_open())
//         {
//             cout << RED << "Error: Could not open 'overdue_books_log.txt'." << RESET << endl;
//             return;
//         }

//         for (const auto &book : overdueBooks)
//         {
//             file << currentDate << " " << book.bookID << " " << book.title << " "
//                  << book.dueDate << " " << book.borrowerName << " " << book.genre << endl;
//         }
//         file.close();
//     }

//     void logDailyFines(const string &date, double totalFines)
//     {
//         ofstream file(finesLogFile, ios::app);
//         if (!file.is_open())
//         {
//             cout << RED << "Error: Could not open 'daily_fines_log.txt'." << RESET << endl;
//             return;
//         }

//         file << date << " " << totalFines << endl;
//         file.close();
//     }

// public:
//     LibraryFineManager()
//     {
//         loadBorrowedBooks();
//         loadLibraryUsers();
//         loadBankBalance();
//         fineRatePerDay = 2.0;
//     }

//     ~LibraryFineManager()
//     {
//         saveBorrowedBooks();
//         saveLibraryUsers();
//         saveBankBalance();
//     }

//     bool userExists(int userID)
//     {
//         for (const auto &user : libraryUsers)
//         {
//             if (user.userID == userID)
//             {
//                 return true;
//             }
//         }
//         return false;
//     }

//     void createAccount()
//     {
//         int userID;
//         string userName, phoneNumber, email, address;

//         cout << CYAN << "\n======== Create Account ========" << RESET << endl;
//         cout << "---------------------------------" << endl;
//         cout << CYAN << "Enter User ID: " << RESET;
//         cin >> userID;

//         if (userExists(userID))
//         {
//             cout << YELLOW << "Account already exists for User ID " << userID << "." << RESET << endl;
//             return;
//         }

//         cout << CYAN << "Enter User Name: " << RESET;
//         cin.ignore(); // To clear the newline left by previous input
//         getline(cin, userName);

//         // New fields for user details
//         cout << CYAN << "Enter Phone Number: " << RESET;
//         getline(cin, phoneNumber);

//         cout << CYAN << "Enter Email: " << RESET;
//         getline(cin, email);

//         cout << CYAN << "Enter Address: " << RESET;
//         getline(cin, address);

//         libraryUsers.push_back({userID, userName, phoneNumber, email, address});
//         cout << GREEN << "Account created successfully!" << RESET << endl;

//         // Displaying the new user details for confirmation
//         cout << "\nUser Details:" << endl;
//         cout << "-----------------------------" << endl;
//         cout << "User ID: " << userID << endl;
//         cout << "User Name: " << userName << endl;
//         cout << "Phone Number: " << phoneNumber << endl;
//         cout << "Email: " << email << endl;
//         cout << "Address: " << address << endl;
//         cout << "-----------------------------" << endl;
//     }

//     void displayMenu()
//     {
//         cout << CYAN << "\n======== LIBRARY FINE MANAGEMENTSYSTEM ========" << RESET << endl;
//         cout << "---------------------------------" << endl;
//         cout << "1. Create Account\n";
//         cout << "2. Borrow a Book\n";
//         cout << "3. Calculate Fine\n";
//         cout << "4. Track Overdue Books\n";
//         cout << "5. Show Daily Collected Fines\n";
//         cout << "6. Show User Details\n";
//         cout << "7. Exit\n";
//     }

//     void trackOverdueBooks()
//     {
//         cout << CYAN << "\n======== Overdue Books ========" << RESET << endl;
//         cout << "---------------------------------" << endl;

//         string currentDate = "2024-11-22"; // Simulating the current date

//         vector<Book> overdueBooks;

//         for (const auto &book : borrowedBooks)
//         {
//             int daysLate = calculateDateDifference(book.dueDate, currentDate);
//             if (daysLate > gracePeriod)
//             {
//                 overdueBooks.push_back(book);
//             }
//         }

//         if (overdueBooks.empty())
//         {
//             cout << GREEN << "No overdue books." << RESET << endl;
//         }
//         else
//         {
//             cout << left << setw(10) << "Book ID" << setw(30) << "Book Title" << setw(20) << "Borrowed By"
//                  << setw(15) << "Due Date" << setw(10) << "Fine" << endl;
//             cout << "---------------------------------------------------------------" << endl;

//             double totalFines = 0.0;
//             for (const auto &book : overdueBooks)
//             {
//                 int daysLate = calculateDateDifference(book.dueDate, currentDate);
//                 double fine = (daysLate - gracePeriod) * fineRatePerDay;
//                 totalFines += fine;

//                 cout << left << setw(10) << book.bookID << setw(30) << book.title << setw(20) << book.borrowerName
//                      << setw(15) << book.dueDate << setw(15) << fixed << setprecision(2) << fine << endl;
//             }
//             cout << "---------------------------------------------------------------" << endl;
//             cout << YELLOW << "\nTotal Fine: " << RESET << fixed << setprecision(2) << totalFines << " Rupees\n";
//             dailyCollectedFines[currentDate] += totalFines;
//             logOverdueBooks(overdueBooks, currentDate);
//             logDailyFines(currentDate, totalFines);
//         }
//     }

//     void displayDailyFines()
//     {
//         cout << CYAN << "\n======== Daily Collected Fines ========" << RESET << endl;
//         cout << "---------------------------------" << endl;

//         if (dailyCollectedFines.empty())
//         {
//             cout << GREEN << "No fines collected yet." << RESET << endl;
//         }
//         else
//         {
//             cout << left << setw(15) << "Date" << setw(15) << "Total Fine" << endl;
//             cout << "-------------------------------------------------" << endl;
//             for (const auto &entry : dailyCollectedFines)
//             {
//                 cout << left << setw(15) << entry.first << setw(15) << fixed << setprecision(2) << entry.second << endl;
//             }
//         }
//     }

//     void showUserDetails()
//     {
//         cout << CYAN << "\n======== User Details ========" << RESET << endl;
//         cout << "---------------------------------" << endl;

//         if (libraryUsers.empty())
//         {
//             cout << GREEN << "No users available." << RESET << endl;
//         }
//         else
//         {
//             cout << left << setw(15) << "User ID" << setw(30) << "User Name" << endl;
//             cout << "-------------------------------------------------" << endl;
//             for (const auto &user : libraryUsers)
//             {
//                 cout << left << setw(15) << user.userID << setw(30) << user.userName << endl;
//             }
//         }
//     }

//     int calculateDateDifference(const string &dueDate, const string &currentDate)
//     {
//         // Simple placeholder, this can be improved using actual date libraries
//         return 5; // Assuming the book is 5 days late
//     }
// };

// int main()
// {
//     LibraryFineManager manager;
//     int choice;

//     do
//     {
//         manager.displayMenu();
//         cout << CYAN << "Enter your choice: " << RESET;
//         cin >> choice;

//         switch (choice)
//         {

//         case 1:
//             manager.createAccount();
//             break;

//         case 2:
//             // Implement borrow book functionality here
//             break;

//         case 3:
//             // Implement calculate fine functionality here
//             break;

//         case 4:
//             manager.trackOverdueBooks();
//             break;

//         case 5:
//             manager.displayDailyFines();
//             break;

//         case 6:
//             manager.showUserDetails();
//             break;

//         case 7:
//             cout << GREEN << "Exiting program." << RESET << endl;
//             break;

//         default:
//           cout << RED << "Invalid choice, please try again." << RESET << endl;

//         }
//     } while (choice != 7);

//     return 0;
// }
