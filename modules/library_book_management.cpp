#include "library_system.h"
#include <iostream>

void LibrarySystem::addBook(const std::string& isbn, const std::string& title,
                           const std::string& author, int publication_year) {
    book_map.emplace(isbn, Book(isbn, title, author, publication_year));
}

bool LibrarySystem::borrowBook(const std::string& isbn, const std::string& student_id) {
    auto it = book_map.find(isbn);
    if (it != book_map.end() && it->second.available) {
        it->second.available = false;
        it->second.borrower_id = student_id;
        return true;
    }
    return false;
}

bool LibrarySystem::returnBook(const std::string& isbn) {
    auto it = book_map.find(isbn);
    if (it != book_map.end() && !it->second.available) {
        return_stack.push(isbn);
        return true;
    }
    return false;
}

std::vector<std::string> LibrarySystem::processReturns() {
    std::vector<std::string> processed;
    while (!return_stack.empty()) {
        std::string isbn = return_stack.top();
        return_stack.pop();
        
        auto it = book_map.find(isbn);
        if (it != book_map.end()) {
            it->second.available = true;
            it->second.borrower_id = "";
            processed.push_back(isbn);
        }
    }
    return processed;
}

Book* LibrarySystem::searchBook(const std::string& isbn) {
    auto it = book_map.find(isbn);
    return it != book_map.end() ? &it->second : nullptr;
}

void LibrarySystem::displayAllBooks() const {
    std::cout << "\n=== LIBRARY BOOK COLLECTION ===\n";
    for (const auto& pair : book_map) {
        const auto& book = pair.second;
        std::cout << "ISBN: " << book.isbn
                  << ", Title: " << book.title
                  << ", Author: " << book.author
                  << ", Year: " << book.publication_year
                  << ", Status: " << (book.available ? "Available" : "Borrowed by " + book.borrower_id)
                  << "\n";
    }
    std::cout << "Total books: " << book_map.size() << "\n";
}

void LibrarySystem::displayBorrowedBooks() const {
    std::cout << "\n=== BORROWED BOOKS ===\n";
    for (const auto& pair : book_map) {
        const auto& book = pair.second;
        if (!book.available) {
            std::cout << "ISBN: " << book.isbn
                      << ", Title: " << book.title
                      << ", Borrower: " << book.borrower_id << "\n";
        }
    }
}