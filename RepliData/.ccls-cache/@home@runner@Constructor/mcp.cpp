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
//             file << "ID:" << user.userID << "\n"
//                  << "Name:" << user.userName << "\n"
//                  << "Phone no.:" << user.phoneNumber << "\n"
//                  << "Email:" << user.email << "\n"
//                  << "Address:" << user.address << endl;
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

        
//         cout << "\nUser Details:" << endl;
//         cout << "-----------------------------" << endl;
//         cout << "User ID: " << userID << endl;
//         cout << "User Name: " << userName << endl;
//         cout << "Phone Number: " << phoneNumber << endl;
//         cout << "Email: " << email << endl;
//         cout << "Address: " << address << endl;
//         cout << "-----------------------------" << endl;
//     }

//     void borrowBook()
//     {
//         int bookID;
//         string title, dueDate, borrowerName, genre;

//         cout << CYAN << "\n======== Borrow a Book ========" << RESET << endl;
//         cout << "---------------------------------" << endl;
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

//     void trackOverdueBooks()
//     {
//         cout << CYAN << "\n======== Overdue Books ========" << RESET << endl;
//         cout << "---------------------------------" << endl;

//         string currentDate = "2024-11-22"; 

//         vector<Book> overdueBooks;

//         for (auto &book : borrowedBooks)
//         {
//             int daysLate = calculateDateDifference(book.dueDate, currentDate);

//             if (daysLate > gracePeriod)
//             {
//                 overdueBooks.push_back(book);
//             }
//         }

//         if (overdueBooks.empty())
//         {
//             cout << GREEN << "No overdue books at the moment." << RESET << endl;
//         }
//         else
//         {
//             cout << "Overdue Books List:" << endl;
//             for (auto &book : overdueBooks)
//             {
//                 cout << "Book: " << book.title << " | Borrower: " << book.borrowerName
//                      << " | Due Date: " << book.dueDate << endl;
//             }
//         }
//     }

    
//     void showDailyCollectedFines()
//     {
//         cout << CYAN << "\n===== Daily Collected Fines =====" << RESET << endl;

//         if (dailyCollectedFines.empty())
//         {
//             cout << GREEN << "No fines have been collected yet." << RESET << endl;
//             return;
//         }

//         double totalCollected = 0.0;
//         cout << BOLD << setw(15) << "Date" << setw(20) << "Fines Collected" << RESET << endl;
//         cout << "-----------------------------------" << endl;
//         for (const auto &entry : dailyCollectedFines)
//         {
//             cout << setw(15) << entry.first << setw(20) << "Rupees" << fixed << setprecision(2) << entry.second << endl;
//             totalCollected += entry.second;
//         }
//         cout << "-----------------------------------" << endl;
//         cout << BOLD << "Total Collected Fines: Rupees" << totalCollected << RESET << endl;
//     }

//     void showUserDetails()
//     {
//         cout << CYAN << "\n===== Library User Details =====" << RESET << endl;

//         if (libraryUsers.empty())
//         {
//             cout << YELLOW << "No users registered in the library." << RESET << endl;
//             return;
//         }

//         for (const auto &user : libraryUsers)
//         {
//             cout << "---------------------------------" << endl;
//             cout << BOLD << "User ID: " << RESET << user.userID << endl;
//             cout << BOLD << "Name: " << RESET << user.userName << endl;
//             cout << BOLD << "Phone: " << RESET << user.phoneNumber << endl;
//             cout << BOLD << "Email: " << RESET << user.email << endl;
//             cout << BOLD << "Address: " << RESET << user.address << endl;
//         }
//         cout << "---------------------------------" << endl;
//     }


//     void calculateFine()
//     {
//         string currentDate = "2024-11-23"; 

//         for (auto &book : borrowedBooks)
//         {
//             int daysLate = calculateDateDifference(book.dueDate, currentDate);

//             if (daysLate > gracePeriod) 
//             {
//                 int fineableDays = daysLate - gracePeriod; 
//                 double fine = fineableDays * fineRatePerDay;
//                 cout << CYAN << "Book: " << book.title << RESET
//                      << " | Borrower: " << book.borrowerName
//                      << " | Fine: Rupees" << fine << endl;
//             }
//             else
//             {
//                 cout << CYAN << "Book: " << book.title << RESET
//                      << " | Borrower: " << book.borrowerName
//                      << " | No fine (within grace period)." << RESET << endl;
//             }
//         }
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
//         return secondsDifference / (60 * 60 * 24); 
//     }

//     void exitProgram()
//     {
//         cout << CYAN << "Saving data and exiting..." << RESET << endl;
//     }

//     void displayMenu()
//     {
//         cout << CYAN << "\n===== Library Fine Manager Menu =====" << RESET << endl;
//         cout << "1. Create Account" << endl;
//         cout << "2. Borrow a Book" << endl;
//         cout << "3. Calculate Fine" << endl;
//         cout << "4. Track Overdue Books" << endl;
//         cout << "5. Show Daily Collected Fines" << endl;
//         cout << "6. Show User Details" << endl;
//         cout << "7. Exit" << endl;
//     }
// };

// int main()
// {
//     LibraryFineManager lfm;
//     int choice;

//     while (true)
//     {
//         lfm.displayMenu();
//         cout << CYAN << "\nEnter your choice: " << RESET;
//         cin >> choice;

//         switch (choice)
//         {
//         case 1:
//             lfm.createAccount();
//             break;
//         case 2:
//             lfm.borrowBook();
//             break;
//         case 3:
//             lfm.calculateFine();
//             break;
//         case 4:
//             lfm.trackOverdueBooks();
//             break;
//         case 5:
//             lfm.showDailyCollectedFines(); 
//             break;
//         case 6:
//             lfm.showUserDetails(); 
//             break;
//         case 7:
//             lfm.exitProgram();
//             return 0;
//         default:
//             cout << RED << "Invalid choice. Please try again." << RESET << endl;
//             break;
//         }
//     }

//     return 0;
// }
