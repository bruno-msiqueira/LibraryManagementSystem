#include "LibraryManager.hpp"
#include <iostream>

void LibraryManager::addBook(const Book& book) {
    books.push_back(book);
}

Book* LibraryManager::findBookById(int id) {
    for (auto& book : books) {
        if (book.getId() == id) {
            return &book;
        }
    }
    return nullptr;
}

std::vector<Book> LibraryManager::findBooksByTitle(const std::string& title) {
    std::vector<Book> result;
    for (const auto& book : books) {
        if (book.getTitle().find(title) != std::string::npos) {
            result.push_back(book);
        }
    }
    return result;
}

std::vector<Book> LibraryManager::findBooksByAuthor(const std::string& author) {
    std::vector<Book> result;
    for (const auto& book : books) {
        if (book.getAuthor().find(author) != std::string::npos) {
            result.push_back(book);
        }
    }
    return result;
}

void LibraryManager::listBooks() const {
    for (const auto& book : books) {
        book.display();
    }
}

bool LibraryManager::borrowBook(int id) {
    Book* book = findBookById(id);
    if (book) {
        return book->borrowBook();
    }
    return false;
}

void LibraryManager::returnBook(int id) {
    Book* book = findBookById(id);
    if (book) {
        book->returnBook();
    }
}
