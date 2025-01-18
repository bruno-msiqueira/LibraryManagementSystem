#include "LibraryManager.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

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

bool LibraryManager::saveToFile(const std::string& filename) const {
    nlohmann::json jsonData;
    for (const auto& book : books) {
        jsonData.push_back({
            {"id", book.getId()},
            {"title", book.getTitle()},
            {"author", book.getAuthor()},
            {"year", book.getYear()},
            {"quantity", book.getQuantity()}
        });
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file << jsonData.dump(4); // Pretty-print with an indentation of 4 spaces
    file.close();
    return true;
}

bool LibraryManager::loadFromFile(const std::string& filename) {
    nlohmann::json jsonData;
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file >> jsonData;
    file.close();

    books.clear();
    for (const auto& item : jsonData) {
        books.emplace_back(
            item.at("title").get<std::string>(),
            item.at("author").get<std::string>(),
            item.at("year").get<int>(),
            item.at("id").get<int>(),
            item.at("quantity").get<int>()
        );
    }

    return true;
}
