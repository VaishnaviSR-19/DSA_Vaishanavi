// // #include <iostream>
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
//     double fineRatePerDay = 2.0; // Default fine rate
//     const string borrowedBooksFile = "borrowed_books.txt";
//     const string usersFile = "library_users.txt";
//     const string bankBalanceFile = "bank_balance.txt";
//     const string overdueLogFile = "overdue_books_log.txt";
//     const string finesLogFile = "daily_fines_log.txt";
//     const int gracePeriod = 2;
//     map<string, double> dailyCollectedFines;

//     // Helper functions to handle file loading and saving
//     void loadBorrowedBooks()
//     {
//         ifstream file(borrowedBooksFile);
//         if (!file.is_open())
//         {
//             cout << RED << "Warning: Could not open '" << borrowedBooksFile << "'. File might not exist." << RESET << endl;
//             return;
//         }

//         Book book;
//         while (file >> book.bookID)
//         {
//             file.ignore(); // Ignore leftover newline
//             getline(file, book.title);
//             getline(file, book.dueDate);
//             getline(file, book.borrowerName);
//             getline(file, book.genre);
//             borrowedBooks.push_back(book);
//         }
//         file.close();
//     }

//     void saveBorrowedBooks()
//     {
//         ofstream file(borrowedBooksFile);
//         if (!file.is_open())
//         {
//             cout << RED << "Error: Could not open '" << borrowedBooksFile << "' for writing." << RESET << endl;
//             return;
//         }

//         for (const auto &book : borrowedBooks)
//         {
//             file << book.bookID << "\n"
//                  << book.title << "\n"
//                  << book.dueDate << "\n"
//                  << book.borrowerName << "\n"
//                  << book.genre << "\n";
//         }
//         file.close();
//     }

//     void loadLibraryUsers()
//     {
//         ifstream file(usersFile);
//         if (!file.is_open())
//         {
//             cout << RED << "Warning: Could not open '" << usersFile << "'. File might not exist." << RESET << endl;
//             return;
//         }

//         User user;
//         while (file >> user.userID)
//         {
//             file.ignore(); // Ignore leftover newline
//             getline(file, user.userName);
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
//             cout << RED << "Error: Could not open '" << usersFile << "' for writing." << RESET << endl;
//             return;
//         }

//         for (const auto &user : libraryUsers)
//         {
//             file << user.userID << "\n"
//                  << user.userName << "\n"
//                  << user.phoneNumber << "\n"
//                  << user.email << "\n"
//                  << user.address << "\n";
//         }
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
//             cout << RED << "Error: Could not open '" << bankBalanceFile << "' for writing." << RESET << endl;
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
//             cout << RED << "Error: Could not open '" << overdueLogFile << "'." << RESET << endl;
//             return;
//         }

//         for (const auto &book : overdueBooks)
//         {
//             file << currentDate << "\n"
//                  << book.bookID << "\n"
//                  << book.title << "\n"
//                  << book.dueDate << "\n"
//                  << book.borrowerName << "\n"
//                  << book.genre << "\n";
//         }
//         file.close();
//     }

//     void logDailyFines(const string &date, double totalFines)
//     {
//         ofstream file(finesLogFile, ios::app);
//         if (!file.is_open())
//         {
//             cout << RED << "Error: Could not open '" << finesLogFile << "'." << RESET << endl;
//             return;
//         }

//         file << date << "\n" << totalFines << "\n";
//         file.close();
//     }

//     int calculateDateDifference(const string &dueDate, const string &currentDate)
//     {
//         // Placeholder logic for date difference calculation
//         return 5; // Simulate 5 days overdue
//     }

// public:
//     LibraryFineManager()
//     {
//         loadBorrowedBooks();
//         loadLibraryUsers();
//         loadBankBalance();
//     }

//     ~LibraryFineManager()
//     {
//         saveBorrowedBooks();
//         saveLibraryUsers();
//         saveBankBalance();
//     }

//     void createAccount()
//     {
//         int userID;
//         string userName, phoneNumber, email, address;

//         cout << CYAN << "\n======== Create Account ========" << RESET << endl;
//         cout << "Enter User ID: ";
//         cin >> userID;

//         if (userExists(userID))
//         {
//             cout << YELLOW << "User already exists with ID " << userID << "." << RESET << endl;
//             return;
//         }

//         cout << "Enter Name: ";
//         cin.ignore();
//         getline(cin, userName);

//         cout << "Enter Phone Number: ";
//         getline(cin, phoneNumber);

//         cout << "Enter Email: ";
//         getline(cin, email);

//         cout << "Enter Address: ";
//         getline(cin, address);

//         libraryUsers.push_back({userID, userName, phoneNumber, email, address});

//         cout << GREEN << "Account created successfully." << RESET << endl;
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

//     void displayMenu()
//     {
//         cout << CYAN << "\n======== Library Fine Management System ========" << RESET << endl;
//         cout << "1. Create Account\n";
//         cout << "2. Track Overdue Books\n";
//         cout << "3. Display Collected Fines\n";
//         cout << "4. Exit\n";
//     }

//     void trackOverdueBooks()
//     {
//         string currentDate = "2024-11-23"; // Simulated current date
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
//             return;
//         }

//         cout << CYAN << "\nOverdue Books:\n" << RESET;
//         for (const auto &book : overdueBooks)
//         {
//             cout << "Book ID: " << book.bookID
//                  << ", Title: " << book.title
//                  << ", Borrower: " << book.borrowerName
//                  << ", Fine: " << (daysLate - gracePeriod) * fineRatePerDay << endl;
//         }

//         logOverdueBooks(overdueBooks, currentDate);
//     }

//     void displayDailyFines()
//     {
//         if (dailyCollectedFines.empty())
//         {
//             cout << GREEN << "No fines collected today." << RESET << endl;
//             return;
//         }

//         for (const auto &[date, totalFine] : dailyCollectedFines)
//         {
//             cout << "Date: " << date << ", Total Fines: " << totalFine << endl;
//         }
//     }
// };

// int main()
// {
//     LibraryFineManager manager;
//     int choice;

//     do
//     {
//         manager.displayMenu();
//         cout << "Enter your choice: ";
//         cin >> choice;

//         switch (choice)
//         {
//         case 1:
//             manager.createAccount();
//             break;
//         case 2:
//             manager.trackOverdueBooks();
//             break;
//         case 3:
//             manager.displayDailyFines();
//             break;
//         case 4:
//             cout << GREEN << "Exiting program." << RESET << endl;
//             break;
//         default:
//             cout << RED << "Invalid choice." << RESET << endl;
//             break;
//         }
//     } while (choice != 4);

//     return 0;
// }


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
//             manager.createAccount();  // Call to createAccount method
//             break;

//         case 2:
//             // Implement borrow book functionality here
//             break;

//         case 3:
//             // Implement calculate fine functionality here
//             break;

//         case 4:
//             manager.trackOverdueBooks();  // Track overdue books
//             break;

//         case 5:
//             manager.displayDailyFines();  // Display collected fines
//             break;

//         case 6:
//             manager.showUserDetails();  // Show user details
//             break;

//         case 7:
//             cout << GREEN << "Exiting program." << RESET << endl;
//             break;

//         default:
//             cout << RED << "Invalid choice, please try again." << RESET << endl;
//         }
//     } while (choice != 7);

//     return 0;
// }
