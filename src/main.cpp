#include "LibraryManager.hpp"
#include <iostream>
#include <string>

const int DEFAULT_LIBRARY_USER_ID = 0;

/**
 * @brief Displays the main menu in a compact layout.
 */
void displayMenu() {
    std::cout << "\nLibrary Management System\n";
    std::cout << "1. Add Book\t\t2. Search by ID\t\t3. Search by Title\t4. Search by Author\t5. Borrow Book\n";
    std::cout << "6. Return Book\t\t7. List Books\t\t8. Save Data\t\t9. Load Data\t\t0. Exit\n";
    std::cout << "Choose an option: ";
}

/**
 * @brief Main function for the interactive menu.
 */
int main() {
    LibraryManager manager;
    std::string filename = "library_data.json";
    int choice;

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); // Clear newline character from input buffer

        switch (choice) {
        case 1: {
            std::string title, author;
            int year, quantity;

            std::cout << "Enter Title: ";
            std::getline(std::cin, title);
            std::cout << "Enter Author: ";
            std::getline(std::cin, author);
            std::cout << "Enter Year of Publication: ";
            std::cin >> year;
            std::cout << "Enter Quantity: ";
            std::cin >> quantity;
            int id = 0;

            manager.addBook(Book(title, author, year, quantity));
            std::cout << "Book added successfully.\n";
            break;
        }
        case 2: {
            int id;
            std::cout << "Enter Book ID to Search: ";
            std::cin >> id;
            Book* book = manager.findBookById(id);
            if (book) {
                book->display();
            } else {
                std::cout << "Book not found.\n";
            }
            break;
        }
        case 3: {
            std::string title;
            std::cout << "Enter Title to Search: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            auto results = manager.findBooksByTitle(title);
            if (!results.empty()) {
                for (const auto& book : results) {
                    book.display();
                }
            } else {
                std::cout << "No books found with the given title.\n";
            }
            break;
        }
        case 4: {
            std::string author;
            std::cout << "Enter Author to Search: ";
            std::cin.ignore();
            std::getline(std::cin, author);
            auto results = manager.findBooksByAuthor(author);
            if (!results.empty()) {
                for (const auto& book : results) {
                    book.display();
                }
            } else {
                std::cout << "No books found with the given author.\n";
            }
            break;
        }
        case 5: {
            int id;
            std::cout << "Enter Book ID to Borrow: ";
            std::cin >> id;
            Book::handleStatus(manager.borrowBook(id, DEFAULT_LIBRARY_USER_ID));
            break;
        }
        case 6: {
            int id;
            std::cout << "Enter Book ID to Return: ";
            std::cin >> id;
            Book::handleStatus(manager.returnBook(id, DEFAULT_LIBRARY_USER_ID));
            break;
        }
        case 7: {
            std::cout << "Listing all books:\n";
            manager.listBooks();
            break;
        }
        case 8: {
            if (manager.saveToFile(filename)) {
                std::cout << "Data saved successfully to " << filename << ".\n";
            } else {
                std::cout << "Failed to save data.\n";
            }
            break;
        }
        case 9: {
            if (manager.loadFromFile(filename)) {
                std::cout << "Data loaded successfully from " << filename << ".\n";
            } else {
                std::cout << "Failed to load data.\n";
            }
            break;
        }
        case 0:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
