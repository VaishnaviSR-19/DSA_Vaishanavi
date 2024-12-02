// #include <iostream>
// #include <vector>
// #include <string>
// #include <fstream>
// #include <iomanip>
// #include <map>
// #include <sstream>
// #include <ctime>

// using namespace std;

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
//     string currentDate = "2024-11-23"; // Default current date for example

//     void loadBorrowedBooks()
//     {
//         ifstream file(borrowedBooksFile);
//         if (!file.is_open())
//         {
//             cout << RED << "Warning: Could not open 'borrowed_books.txt'. File might not exist." << RESET << endl;
//             return;
//         }

//         Book book;
//         while (file >> book.bookID)
//         {
//             file.ignore(); // Ignore the space after the bookID
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
//             cout << RED << "Error: Could not open 'borrowed_books.txt' for writing." << RESET << endl;
//             return;
//         }

//         for (const auto &book : borrowedBooks)
//         {
//             file << book.bookID << endl;
//             file << book.title << endl;
//             file << book.dueDate << endl;
//             file << book.borrowerName << endl;
//             file << book.genre << endl;
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
//         while (file >> user.userID)
//         {
//             file.ignore(); // Ignore the space after userID
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
//             cout << RED << "Error: Could not open 'library_users.txt' for writing." << RESET << endl;
//             return;
//         }

//         for (const auto &user : libraryUsers)
//         {
//             file << user.userID << endl;
//             file << user.userName << endl;
//             file << user.phoneNumber << endl;
//             file << user.email << endl;
//             file << user.address << endl;
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
//             cout << RED << "Error: Could not open 'bank_balance.txt' for writing." << RESET << endl;
//             return;
//         }

//         file << bankBalance;
//         file.close();
//     }

//     void logOverdueBooks()
//     {
//         ofstream file(overdueLogFile, ios::app);
//         if (!file.is_open())
//         {
//             cout << RED << "Error: Could not open 'overdue_books_log.txt'." << RESET << endl;
//             return;
//         }

//         for (const auto &book : borrowedBooks)
//         {
//             int daysLate = calculateDateDifference(book.dueDate, currentDate);
//             if (daysLate > gracePeriod && book.genre != "novel") // Skip novels
//             {
//                 int fineableDays = daysLate - gracePeriod;
//                 double fine = fineableDays * fineRatePerDay;
//                 file << "Book: " << book.title
//                      << " | Borrower: " << book.borrowerName
//                      << " | Days Late: " << fineableDays
//                      << " | Fine: " << fine << endl;
//             }
//         }
//         file.close();
//         cout << GREEN << "Overdue books logged successfully!" << RESET << endl;
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

//     int calculateDateDifference(const string &dueDate, const string &currentDate)
//     {
//         tm due = {}, current = {};
//         stringstream dueStream(dueDate), currentStream(currentDate);
//         dueStream >> get_time(&due, "%Y-%m-%d");
//         currentStream >> get_time(&current, "%Y-%m-%d");

//         time_t dueTime = mktime(&due);
//         time_t currentTime = mktime(&current);

//         double secondsDifference = difftime(currentTime, dueTime);
//         return secondsDifference / (60 * 60 * 24); // Convert seconds to days
//     }

// public:
//     LibraryFineManager()
//     {
//         loadBorrowedBooks();
//         loadLibraryUsers();
//         loadBankBalance();
//         fineRatePerDay = 2.0;  // Default fine rate
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
//         cin.ignore(); 
//         getline(cin, userName);

//         cout << CYAN << "Enter Phone Number: " << RESET;
//         getline(cin, phoneNumber);

//         cout << CYAN << "Enter Email: " << RESET;
//         getline(cin, email);

//         cout << CYAN << "Enter Address: " << RESET;
//         getline(cin, address);

//         libraryUsers.push_back({userID, userName, phoneNumber, email, address});
//         cout << GREEN << "Account created successfully!" << RESET << endl;
//     }

//     void borrowBook()
//     {
//         int userID, bookID;
//         string title, dueDate, borrowerName, genre;

//         cout << CYAN << "\n======== Borrow a Book ========" << RESET << endl;
//         cout << "---------------------------------" << endl;

//         cout << CYAN << "Enter User ID: " << RESET;
//         cin >> userID;

//         if (!userExists(userID))
//         {
//             cout << RED << "User does not exist. Please create an account first." << RESET << endl;
//             return;
//         }

//         cout << CYAN << "Enter Book ID: " << RESET;
//         cin >> bookID;

//         cout << CYAN << "Enter Book Title: " << RESET;
//         cin.ignore(); 
//         getline(cin, title);

//         cout << CYAN << "Enter Due Date (YYYY-MM-DD): " << RESET;
//         getline(cin, dueDate);

//         cout << CYAN << "Enter Borrower's Name: " << RESET;
//         getline(cin, borrowerName);

//         cout << CYAN << "Enter Genre: " << RESET;
//         getline(cin, genre);

//         borrowedBooks.push_back({bookID, title, dueDate, borrowerName, genre});
//         cout << GREEN << "Book borrowed successfully!" << RESET << endl;
//     }

//     void viewBorrowedBooks()
//     {
//         cout << CYAN << "\n======== Borrowed Books ========" << RESET << endl;
//         if (borrowedBooks.empty())
//         {
//             cout << YELLOW << "No books have been borrowed yet." << RESET << endl;
//             return;
//         }

//         for (const auto &book : borrowedBooks)
//         {
//             cout << "Book ID: " << book.bookID
//                  << " | Title: " << book.title
//                  << " | Borrower: " << book.borrowerName
//                  << " | Due Date: " << book.dueDate
//                  << " | Genre: " << book.genre << endl;
//         }
//     }

//     void returnBook()
//     {
//         int bookID;
//         cout << CYAN << "\n======== Return a Book ========" << RESET << endl;
//         cout << CYAN << "Enter the Book ID to return: " << RESET;
//         cin >> bookID;

//         auto it = find_if(borrowedBooks.begin(), borrowedBooks.end(),
//                           [bookID](const Book &book) { return book.bookID == bookID; });

//         if (it != borrowedBooks.end())
//         {
//             borrowedBooks.erase(it);
//             cout << GREEN << "Book returned successfully!" << RESET << endl;
//         }
//         else
//         {
//             cout << RED << "Book not found!" << RESET << endl;
//         }
//     }

//     void viewAllUsers()
//     {
//         cout << CYAN << "\n======== Library Users ========" << RESET << endl;
//         if (libraryUsers.empty())
//         {
//             cout << YELLOW << "No users registered yet." << RESET << endl;
//             return;
//         }
//         for (const auto &user : libraryUsers)
//         {
//             cout << "User ID: " << user.userID
//                  << " | Name: " << user.userName
//                  << " | Phone: " << user.phoneNumber
//                  << " | Email: " << user.email
//                  << " | Address: " << user.address << endl;
//         }
//     }

//     void calculateFine()
//     {
//         double totalFine = 0.0;
//         for (const auto &book : borrowedBooks)
//         {
//             int daysLate = calculateDateDifference(book.dueDate, currentDate);
//             if (daysLate > gracePeriod && book.genre != "novel")
//             {
//                 int fineableDays = daysLate - gracePeriod;
//                 double fine = fineableDays * fineRatePerDay;
//                 totalFine += fine;
//             }
//         }

//         cout << CYAN << "\n======== Fine Calculation ========" << RESET << endl;
//         cout << "Total Fine: Rupees " << totalFine << endl;
//     }

//     void adjustFineRate()
//     {
//         double newRate;
//         cout << CYAN << "\n======== Adjust Fine Rate ========" << RESET << endl;
//         cout << CYAN << "Enter the new fine rate per day: " << RESET;
//         cin >> newRate;

//         if (newRate <= 0)
//         {
//             cout << RED << "Fine rate must be positive." << RESET << endl;
//             return;
//         }

//         fineRatePerDay = newRate;
//         cout << GREEN << "Fine rate updated to Rupees " << fineRatePerDay << RESET << endl;
//     }

//     void exitProgram()
//     {
//         cout << GREEN << "Exiting the program..." << RESET << endl;
//     }
// };

// void displayMenu()
// {
//     cout << CYAN << "\n===== Library Fine Manager Menu =====" << RESET << endl;
//     cout << "1. Create Account" << endl;
//     cout << "2. Borrow a Book" << endl;
//     cout << "3. Return a Book" << endl;
//     cout << "4. View Borrowed Books" << endl;
//     cout << "5. View All Users" << endl;
//     cout << "6. Calculate Fine" << endl;
//     cout << "7. Adjust Fine Rate" << endl;
//     cout << "8. Log Overdue Books" << endl;
//     cout << "9. Exit" << endl;
// }

// int main()
// {
//     LibraryFineManager manager;
//     int choice;

//     while (true)
//     {
//         displayMenu();
//         cout << CYAN << "\nEnter your choice: " << RESET;
//         cin >> choice;

//         switch (choice)
//         {
//         case 1:
//             manager.createAccount();
//             break;
//         case 2:
//             manager.borrowBook();
//             break;
//         case 3:
//             manager.returnBook();
//             break;
//         case 4:
//             manager.viewBorrowedBooks();
//             break;
//         case 5:
//             manager.viewAllUsers();
//             break;
//         case 6:
//             manager.calculateFine();
//             break;
//         case 7:
//             manager.adjustFineRate();
//             break;
//         case 8:
//             manager.logOverdueBooks();
//             break;
//         case 9:
//             manager.exitProgram();
//             return 0;
//         default:
//             cout << RED << "Invalid choice. Please try again." << RESET << endl;
//         }
//     }

//     return 0;
// }
