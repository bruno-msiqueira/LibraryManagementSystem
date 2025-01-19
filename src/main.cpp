#include "LibraryManager.hpp"
#include <iostream>
#include <sstream>
#include <string>

const int DEFAULT_LIBRARY_USER_ID = 0;

template <typename T>
T getInput() {
    std::string input;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    T value;

    try {
        if (iss >> value && iss.eof()) {
            return value;
        } else {
            throw std::runtime_error("Invalid input: Unable to convert to the required type.");
        }
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("Invalid input: Unable to convert to the required type.");
    }
}

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
int main(int argc, char* argv[]) {
    LibraryManager manager;
    std::string filename = "./data/library_data.json";

    // If there is a parameter in the cli, use it as the file name
    if (argc > 1) {
        filename = argv[1];
    }

    int choice = -1;

    do {
        displayMenu();

        try {
            choice = getInput<int>();

            switch (choice) {
                case 1: {
                    std::string title, author;
                    int year, quantity;

                    std::cout << "Enter Title: ";
                    title = getInput<std::string>();
                    std::cout << "Enter Author: ";
                    author = getInput<std::string>();
                    std::cout << "Enter Year of Publication: ";
                    year = getInput<int>();
                    std::cout << "Enter Quantity: ";
                    quantity = getInput<int>();

                    if (0 >= quantity){
                        std::cout << "[ERROR] Invalid Book Quantity.\n";
                    }
                    else {
                        manager.addBook(Book(title, author, year, quantity));
                        std::cout << "Book added successfully.\n";
                    }
                    break;
                }
                case 2: {
                    if (manager.getCountUniqueBooks() <= 0){
                        std::cout << "No books\n";
                    }
                    else{
                        int id;
                        std::cout << "Enter Book ID to Search: ";
                        id  = getInput<int>();;
                        Book* book = manager.findBookById(id);
                        if (book) {
                            book->display();
                        } else {
                            std::cout << "Book not found.\n";
                        }
                    }
                    break;
                }
                case 3: {
                    if (manager.getCountUniqueBooks() <= 0){
                        std::cout << "No books\n";
                    }
                    else{
                        std::string title;
                        std::cout << "Enter Title to Search: ";
                        title = getInput<std::string>();
                        auto results = manager.findBooksByTitle(title);
                        if (!results.empty()) {
                            for (const auto& book : results) {
                                book.display();
                            }
                        } else {
                            std::cout << "No books found with the given title.\n";
                        }
                    }
                    break;
                }
                case 4: {
                    if (manager.getCountUniqueBooks() <= 0){
                        std::cout << "No books\n";
                    }
                    else{
                        std::string author;
                        std::cout << "Enter Author to Search: ";
                        author = getInput<std::string>();
                        auto results = manager.findBooksByAuthor(author);
                        if (!results.empty()) {
                            for (const auto& book : results) {
                                book.display();
                            }
                        } else {
                            std::cout << "No books found with the given author.\n";
                        }
                    }
                    break;
                }
                case 5: {
                    if (manager.getCountUniqueBooks() <= 0){
                        std::cout << "No books\n";
                    }
                    else{
                        int id;
                        std::cout << "Enter Book ID to Borrow: ";
                        id = getInput<int>();
                        Book::handleStatus(manager.borrowBook(id, DEFAULT_LIBRARY_USER_ID));
                    }
                    break;
                }
                case 6: {
                    if (manager.getCountUniqueBooks() <= 0){
                        std::cout << "No books\n";
                    }
                    else{
                        int id;
                        std::cout << "Enter Book ID to Return: ";
                        id = getInput<int>();;
                        Book::handleStatus(manager.returnBook(id, DEFAULT_LIBRARY_USER_ID));
                    }
                    break;
                }
                case 7: {
                    std::cout << "Listing all books:\n";
                    manager.listBooks();
                    break;
                }
                case 8: {
                    if (manager.saveToFile(filename)) {
                        manager.displaySummary("Save");
                        std::cout << "Data saved successfully to '" << filename << "'.\n";
                    } else {
                        std::cout << "Failed to save data.\n";
                    }
                    break;
                }
                case 9: {
                    if (manager.loadFromFile(filename)) {
                        manager.displaySummary("Load");
                        std::cout << "Data loaded successfully from '" << filename << "'.\n";
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
        } catch(const std::runtime_error& e) {
            std::cerr << e.what() << "\n";
            choice = -1;
        }
    } while (choice != 0);

    return 0;
}
