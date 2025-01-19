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
     *
     * @param book The book to add.
     */
    void addBook(Book book);

    /**
     * @brief Finds a book by its unique ID.
     *
     * @param id The ID of the book.
     *
     * @return A pointer to the book if found, nullptr otherwise.
     */
    Book* findBookById(int id);

    /**
     * @brief Finds books by their title.
     *
     * @param title The title to search for.
     *
     * @return A vector of books matching the title.
     */
    std::vector<Book> findBooksByTitle(const std::string& title);

    /**
     * @brief Finds books by their author.
     *
     * @param author The author to search for.
     *
     * @return A vector of books matching the author.
     */
    std::vector<Book> findBooksByAuthor(const std::string& author);

    /**
     * @brief Lists all books in the library.
     */
    void listBooks() const;

    /**
     * @brief Borrows a book by its ID.
     *
     * @param id The ID of the book to borrow.
     * @param borrowerId User code who is lending the book
     *
     * @return A status indicating the result of the operation.
     */
    BookStatus borrowBook(int id, int borrowerId);

    /**
     * @brief Returns a book by its ID.
     *
     * @param id The ID of the book to return.
     * @param borrowerId User code who is lending the book
     *
     * @return A status indicating the result of the operation.
     */
    BookStatus returnBook(int id, int borrowerId);

    /**
     * @brief Saves the library collection to a JSON file.
     * @param filename The name of the file to save to.
     * @return True if the operation is successful, false otherwise.
     */
    bool saveToFile(const std::string& filename) const;

    /**
     * @brief Loads the library collection from a JSON file.
     * @param filename The name of the file to load from.
     * @return True if the operation is successful, false otherwise.
     */
    bool loadFromFile(const std::string& filename);
};

#endif
