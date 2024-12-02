#include <iostream>
#include <fstream>
using namespace std;

// Book class to represent a book in the library
class Book {
public:
    string title;
    string author;
    int borrowDay, borrowMonth, borrowYear;
    int returnDay, returnMonth, returnYear;

    Book(string t, string a, int bd, int bm, int by, int rd, int rm, int ry)
        : title(t), author(a), borrowDay(bd), borrowMonth(bm), borrowYear(by),
          returnDay(rd), returnMonth(rm), returnYear(ry) {}
};

// Helper function to calculate the difference in days between two dates
int calculateDays(int d1, int m1, int y1, int d2, int m2, int y2) {
    int days1 = y1 * 365 + d1;
    for (int i = 0; i < m1 - 1; i++) days1 += (i == 1) ? 28 : (i == 3 || i == 5 || i == 8 || i == 10) ? 30 : 31;
    int days2 = y2 * 365 + d2;
    for (int i = 0; i < m2 - 1; i++) days2 += (i == 1) ? 28 : (i == 3 || i == 5 || i == 8 || i == 10) ? 30 : 31;
    return days2 - days1;
}

// Function to calculate the fine based on overdue days
int calculateFine(int overdueDays) {
    int fine = 0;
    if (overdueDays > 0) {
        if (overdueDays <= 10) {
            fine = overdueDays * 1; // 1 per day for the first 10 days
        } else if (overdueDays <= 30) {
            fine = 10 + (overdueDays - 10) * 2; // 2 per day for the next 20 days
        } else {
            fine = 50 + (overdueDays - 30) * 4; // 4 per day after 30 days
        }
    }
    return fine;
}

// Function to view borrowed books and calculate fines
void viewBorrowedBooks() {
    ifstream file("borrowed_books.txt");
    if (!file) {
        cout << "No borrowed books data found.\n";
        return;
    }

    string title, author;
    int bd, bm, by, rd, rm, ry;
    while (file >> title >> author >> bd >> bm >> by >> rd >> rm >> ry) {
        int overdueDays = calculateDays(bd, bm, by, rd, rm, ry);
        int fine = calculateFine(overdueDays);

        cout << "Book: " << title << " by " << author << endl;
        cout << "Borrowed Date: " << bd << "/" << bm << "/" << by << endl;
        cout << "Return Date: " << rd << "/" << rm << "/" << ry << endl;
        cout << "Overdue Days: " << (overdueDays > 0 ? overdueDays : 0) << endl;
        cout << "Fine: $" << fine << endl << endl;
    }

    file.close();
}

// Function to add a borrowed book
void addBorrowedBook() {
    string title, author;
    int bd, bm, by, rd, rm, ry;

    cout << "Enter book title: ";
    cin >> ws; // Clear whitespace
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter borrow date (dd mm yyyy): ";
    cin >> bd >> bm >> by;
    cout << "Enter return date (dd mm yyyy): ";
    cin >> rd >> rm >> ry;

    ofstream file("borrowed_books.txt", ios::app);
    file << title << " " << author << " " << bd << " " << bm << " " << by << " " << rd << " " << rm << " " << ry << endl;
    file.close();

    cout << "Book borrowed successfully!\n";
}

// Main function to display the menu and handle user input
int main() {
    int choice;
    do {
        cout << "\nLibrary Fine Calculator\n";
        cout << "1. View Borrowed Books and Fines\n";
        cout << "2. Add Borrowed Book\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewBorrowedBooks();
                break;
            case 2:
                addBorrowedBook();
                break;
            case 3:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}


