#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>

/**
 * @class Book
 * @brief Represents a book in the library system.
 *
 * The Book class provides attributes and methods to manage an individual book,
 * including its availability and quantity.
 */
class Book {
private:
    std::string m_title;   /**< Title of the book. */
    std::string m_author;  /**< Author of the book. */
    int m_year;            /**< Year of publication. */
    int m_id;              /**< Unique identifier for the book. */
    int m_quantity;        /**< Number of copies available for borrowing. */

public:
    /**
     * @brief Constructs a Book object.
     *
     * @param title Title of the book.
     * @param author Author of the book.
     * @param year Year of publication.
     * @param id Unique identifier for the book.
     * @param quantity Number of copies available.
     */
    Book(std::string title, std::string author, int year, int id, int quantity);

    /**
     * @brief Gets the title of the book.
     * @return Title as a string.
     */
    std::string getTitle() const;

    /**
     * @brief Gets the author of the book.
     * @return Author as a string.
     */
    std::string getAuthor() const;

    /**
     * @brief Gets the year of publication.
     * @return Year as an integer.
     */
    int getYear() const;

    /**
     * @brief Gets the unique identifier of the book.
     * @return ID as an integer.
     */
    int getId() const;

    /**
     * @brief Gets the number of copies available.
     * @return Quantity as an integer.
     */
    int getQuantity() const;

    /**
     * @brief Sets the number of copies available.
     * @param qty New quantity.
     */
    void setQuantity(int qty);

    /**
     * @brief Attempts to borrow a copy of the book.
     *
     * Decreases the quantity if at least one copy is available.
     *
     * @return True if a copy was successfully borrowed, false otherwise.
     */
    bool borrowBook();

    /**
     * @brief Returns a copy of the book.
     *
     * Increases the quantity by one.
     */
    void returnBook();

    /**
     * @brief Displays the details of the book.
     *
     * Prints the book's title, author, year, ID, and available quantity
     * to the standard output.
     */
    void display() const;
};

#endif
