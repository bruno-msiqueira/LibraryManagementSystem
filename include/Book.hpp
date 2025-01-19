#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include <unordered_set>

/**
 * @enum BookStatus
 * @brief Represents the result of a book operation.
 */
enum class BookStatus {
    Success,                //< Operation completed successfully
    NoBooks,                //< No books
    AlreadyBorrowed,        //< The user has already borrowed this book
    NoCopiesAvailable,      //< No copies are available for borrowing
    NotBorrowedByUser,      //< The user is not borrowing this book
    InvalidOperation        //< Invalid operation or book ID
};

/**
 * @class Book
 * @brief Represents a book in the library system.
 *
 * The Book class provides attributes and methods to manage an individual book,
 * including its availability and quantity.
 */
class Book {
private:
    std::string m_title;                 //< Title of the book
    std::string m_author;                //< Author of the book
    int m_year;                          //< Year of publication
    int m_quantity;                      //< Number of copies available for borrowing
    int m_id;                            //< Unique identifier for the book
    std::unordered_set<int> m_borrowers; //< Set of user IDs who have borrowed the book

public:
    /**
     * @brief Constructs a Book object.
     *
     * @param title Title of the book.
     * @param author Author of the book.
     * @param year Year of publication.
     * @param id Unique identifier for the book.
     *
     * @param quantity Number of copies available.
     */
    Book(std::string title, std::string author, int year, int quantity, int id = 0);

    /**
     * @brief Sets the unique identifier of the book.
     *
     * @param id Book Id.
     */
    void setId(int id);

    /**
     * @brief Gets the unique identifier of the book.
     *
     * @return ID as an integer.
     */
    int getId() const;

    /**
     * @brief Gets the title of the book.
     *
     * @return Title as a string.
     */
    std::string getTitle() const;

    /**
     * @brief Gets the author of the book.
     *
     * @return Author as a string.
     */
    std::string getAuthor() const;

    /**
     * @brief Gets the year of publication.
     *
     * @return Year as an integer.
     */
    int getYear() const;

    /**
     * @brief Gets the number of copies available.
     *
     * @return Quantity as an integer.
     */
    int getQuantity() const;

    /**
     * @brief Sets the number of copies available.
     *
     * @param quantity New quantity.
     */
    void setQuantity(int quantity);

    /**
     * @brief Gets the IDs of users who have borrowed the book.
     * @return A set of user IDs.
     */
    std::unordered_set<int> getBorrowers() const;

    /**
     * @brief Attempts to borrow a copy of the book.
     *
     * Decreases the quantity if at least one copy is available.
     *
     * @param userId The ID of the user borrowing the book.
     *
     * @return A status indicating the result of the operation.
     */
    BookStatus borrowBook(int userId);

    /**
     * @brief Returns a copy of the book.
     *
     * @param userId The ID of the user returning the book.
     *
     * @return A status indicating the result of the operation.
     */
    BookStatus returnBook(int userId);

    /**
     * @brief Gets the number of available copies for borrowing.
     *
     * @return The number of available copies.
     */
    int getAvailableQuantity() const;

    /**
     * @brief Gets the number of users currently borrowing the book.
     *
     * @return The number of borrowers.
     */
    int getBorrowerCount() const;

    /**
     * @brief Displays the details of the book.
     *
     * Prints the book's title, author, year, ID, and available quantity
     * to the standard output.
     */
    void display() const;

    /**
     * @brief Handles and displays the status of a book operation.
     *
     * @param status The status to handle.
     */
    static void handleStatus(BookStatus status);
};

#endif
