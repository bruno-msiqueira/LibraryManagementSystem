#ifndef LIBRARY_MANAGER_HPP
#define LIBRARY_MANAGER_HPP

#include "Book.hpp"
#include <vector>
#include <string>

/**
 * @class LibraryManager
 * @brief Manages a collection of books in the library.
 */
class LibraryManager {
private:
    std::vector<Book> books; /**< Collection of books in the library. */

public:
    /**
     * @brief Adds a book to the library collection.
     * @param book The book to add.
     */
    void addBook(const Book& book);

    /**
     * @brief Finds a book by its unique ID.
     * @param id The ID of the book.
     * @return A pointer to the book if found, nullptr otherwise.
     */
    Book* findBookById(int id);

    /**
     * @brief Finds books by their title.
     * @param title The title to search for.
     * @return A vector of books matching the title.
     */
    std::vector<Book> findBooksByTitle(const std::string& title);

    /**
     * @brief Finds books by their author.
     * @param author The author to search for.
     * @return A vector of books matching the author.
     */
    std::vector<Book> findBooksByAuthor(const std::string& author);

    /**
     * @brief Lists all books in the library.
     */
    void listBooks() const;

    /**
     * @brief Borrows a book by its ID.
     * @param id The ID of the book to borrow.
     * @return True if the book was successfully borrowed, false otherwise.
     */
    bool borrowBook(int id);

    /**
     * @brief Returns a book by its ID.
     * @param id The ID of the book to return.
     */
    void returnBook(int id);
};

#endif
