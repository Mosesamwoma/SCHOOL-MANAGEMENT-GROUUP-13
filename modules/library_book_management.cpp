/*
===============================================
MODULE: LIBRARY SYSTEM
DATA STRUCTURE: HASH MAP + STACK
REASON: 
  - HashMap: O(1) book lookup by ISBN
  - Stack: LIFO for recent borrows
TIME COMPLEXITY:
  - Book lookup: O(1)
  - Borrow/Return: O(1)
  - Recent history: O(1) peek
===============================================
*/

#include <iostream>
#include <unordered_map>
#include <stack>
#include <string>
using namespace std;

class LibrarySystem {
private:
    // HASH MAP USED HERE
    unordered_map<string, string> books; // ISBN -> bookTitle
    // STACK USED HERE
    stack<string> recentBorrows; // ISBNs of recently borrowed books
    
public:
    // O(1) operation
    void addBook(string isbn, string title) {
        books[isbn] = title;
        cout << "Book added: " << title << endl;
    }
    
    // O(1) operation
    bool borrowBook(string isbn) {
        // HASH MAP LOOKUP
        if (books.find(isbn) != books.end()) {
            // STACK PUSH
            recentBorrows.push(isbn);
            cout << "Borrowed: " << books[isbn] << endl;
            return true;
        }
        cout << "Book not found." << endl;
        return false;
    }
    
    // O(1) operation
    void returnBook() {
        if (!recentBorrows.empty()) {
            // STACK POP
            string isbn = recentBorrows.top();
            recentBorrows.pop();
            cout << "Returned: " << books[isbn] << endl;
        } else {
            cout << "No books to return." << endl;
        }
    }
    
    // O(1) operation
    string lastBorrowed() {
        if (!recentBorrows.empty()) {
            // STACK PEEK
            return books[recentBorrows.top()];
        }
        return "None";
    }
    
    // O(1) operation
    bool checkAvailability(string isbn) {
        return books.find(isbn) != books.end();
    }
};

int main() {
    LibrarySystem library;
    
    library.addBook("ISBN001", "Data Structures");
    library.addBook("ISBN002", "Algorithms");
    
    library.borrowBook("ISBN001");
    library.borrowBook("ISBN002");
    
    cout << "Last borrowed: " << library.lastBorrowed() << endl;
    
    library.returnBook();
    
    cout << "Check ISBN001: " 
         << (library.checkAvailability("ISBN001") ? "Available" : "Not Available") 
         << endl;
    
    return 0;
}