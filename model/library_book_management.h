#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include <string>
#include <vector>
#include <stack>
#include <unordered_map>

struct Book {
    std::string isbn;
    std::string title;
    std::string author;
    int publication_year;
    bool available;
    std::string borrower_id;
    
    Book(const std::string& i, const std::string& t, const std::string& a, int year)
        : isbn(i), title(t), author(a), publication_year(year), available(true), borrower_id("") {}
};

class LibrarySystem {
private:
    std::unordered_map<std::string, Book> book_map;  // ISBN -> Book
    std::stack<std::string> return_stack;           // For processing returns (LIFO)
    
public:
    void addBook(const std::string& isbn, const std::string& title, 
                const std::string& author, int publication_year);
    bool borrowBook(const std::string& isbn, const std::string& student_id);
    bool returnBook(const std::string& isbn);
    std::vector<std::string> processReturns();
    Book* searchBook(const std::string& isbn);
    void displayAllBooks() const;
    void displayBorrowedBooks() const;
    int getTotalBooks() const { return book_map.size(); }
};

#endif