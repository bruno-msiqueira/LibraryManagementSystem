#include "LibraryManager.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

int LibraryManager::getCountUniqueBooks(){
    return books.size();
}

void LibraryManager::addBook(Book book) {
    book.setId(books.size() + 1);
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
    if (books.empty())
    {
        std::cout << "No books\n";
        return;
    }

    for (const auto& book : books) {
        book.display();
    }
}

BookStatus LibraryManager::borrowBook(int id, int borrowerId) {
    if (books.size() <= 0) {
        return BookStatus::NoBooks;
    }
    Book* book = findBookById(id);
    if (book) {
        return book->borrowBook(borrowerId);
    }
    return BookStatus::InvalidOperation;
}

BookStatus LibraryManager::returnBook(int id, int borrowerId) {
    if (books.size() <= 0) {
        return BookStatus::NoBooks;
    }
    Book* book = findBookById(id);
    if (book) {
        return book->returnBook(borrowerId);
    }
    return BookStatus::InvalidOperation;
}

bool LibraryManager::saveToFile(const std::string& filename) const {
    nlohmann::json jsonData;

    // Add nextBookId to JSON
    jsonData["nextBookId"] = books.size() + 1;

    // Save data
    for (const auto& book : books) {
        std::vector<int> borrowersVector(book.getBorrowers().begin(), book.getBorrowers().end());
        jsonData["books"].push_back({
            {"title", book.getTitle()},
            {"author", book.getAuthor()},
            {"year", book.getYear()},
            {"quantity", book.getQuantity()},
            {"id", book.getId()},
            {"borrowers", borrowersVector}
        });
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "[ERROR] Could not open file: " << filename << "\n";
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
        std::cout << "[ERROR] Could not open file: " << filename << "\n";
        return false;
    }

    file >> jsonData;
    file.close();

    books.clear();

    for (const auto& item : jsonData["books"]) {
        // Extract book information
        std::string title = item.at("title").get<std::string>();

        int id = item.at("id").get<int>();
        if (books.size() >= id){
            std::cout << "[ERROR] Duplicate book ID " << id << " (" << title << ")\n";
            continue;
        }

        int quantity = item.at("quantity").get<int>();
        if (0 >= quantity){
            std::cout << "[ERROR] Invalid Book Quantity " << quantity << " (ID " << id << ": " << title << ")\n";
            continue;
        }

        std::string author = item.at("author").get<std::string>();
        int year = item.at("year").get<int>();
        std::unordered_set<int> borrowers;

        for (int userId : item.at("borrowers")) {
            if (!borrowers.insert(userId).second) {
                std::cout << "[ERROR] Duplicate borrower ID " << userId
                          << " for book ID " << id << " (" << title << ")\n";
            }
        }

        if (borrowers.size() > static_cast<size_t>(quantity)) {
            std::cout << "[ERROR] Number of borrowers (" << borrowers.size()
                      << ") exceeds quantity (" << quantity
                      << ") for book ID " << id << " (" << title << ")\n";
            continue; // Skip this book
        }

        Book book(title, author, year, quantity, id);
        for (int userId : borrowers) {
            book.borrowBook(userId);
        }

        books.push_back(book);
    }

    return true;
}

void LibraryManager::displaySummary(const std::string& summaryTitle) const{
    // Statistics
    int totalBooks = 0;
    int availableBooks = 0;
    int borrowedBooks = 0;
    for (const auto& book : books) {
        totalBooks += book.getQuantity();
        availableBooks += book.getAvailableQuantity();
        borrowedBooks += book.getQuantity() - book.getAvailableQuantity();
    }

    std::cout << summaryTitle  << ((0 == summaryTitle.length()) ? "" : " ") << "Summary" << ":\n";
    std::cout << "  Total unique books:\t "   << books.size()   << "\n";
    std::cout << "  Total books (general): "  << totalBooks     << "\n";
    std::cout << "  Total available books: "  << availableBooks << "\n";
    std::cout << "  Total borrowed books:\t " << borrowedBooks  << "\n";
}
