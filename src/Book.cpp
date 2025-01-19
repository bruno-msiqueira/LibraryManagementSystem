#include "Book.hpp"
#include <iostream>

Book::Book(std::string title, std::string author, int year, int qty, int id)
    : m_title(title), m_author(author), m_year(year), m_quantity(qty),  m_id(id) {}

std::string Book::getTitle() const {
    return m_title;
}

void Book::setId(int id)
{
    m_id = id;
}

int Book::getId() const {
    return m_id;
}

std::string Book::getAuthor() const {
    return m_author;
}

int Book::getYear() const {
    return m_year;
}

int Book::getQuantity() const {
    return m_quantity;
}

void Book::setQuantity(int quantity) {
    m_quantity = quantity;
}

std::unordered_set<int> Book::getBorrowers() const {
    return m_borrowers;
}
BookStatus Book::borrowBook(int userId) {
    if (getAvailableQuantity() <= 0) {
        return BookStatus::NoCopiesAvailable;
    }
    if (m_borrowers.find(userId) != m_borrowers.end()) {
        return BookStatus::AlreadyBorrowed;
    }

    m_borrowers.insert(userId);
    return BookStatus::Success;
}

BookStatus Book::returnBook(int userId) {
    auto it = m_borrowers.find(userId);
    if ((getBorrowerCount() <= 0) || (m_borrowers.end() == it)) {
        return BookStatus::NotBorrowedByUser;
    }

    m_borrowers.erase(it);
    return BookStatus::Success;
}

int Book::getAvailableQuantity() const {
    return ((m_quantity <= static_cast<int>(m_borrowers.size())) ?
                0 : m_quantity - static_cast<int>(m_borrowers.size()));
}

int Book::getBorrowerCount() const {
    return m_borrowers.size();
}

void Book::display() const {
    std::cout << "ID: " << m_id
              << ", Title: " << m_title
              << ", Author: " << m_author
              << ", Year: " << m_year
              << ", Quantity: " << m_quantity
              << ", Available: " << getAvailableQuantity()
              << ", Borrowed: " << getBorrowerCount() << std::endl;
}

void Book::handleStatus(BookStatus status) {
    switch (status) {
    case BookStatus::Success:
        std::cout << "Operation completed successfully.\n";
        break;
    case BookStatus::AlreadyBorrowed:
        std::cout << "You have already borrowed this book.\n";
        break;
    case BookStatus::NoCopiesAvailable:
        std::cout << "No copies available to borrow.\n";
        break;
    case BookStatus::NotBorrowedByUser:
        std::cout << "You cannot return a book you haven't borrowed.\n";
        break;
    case BookStatus::InvalidOperation:
        std::cout << "Invalid operation. Please check the book ID.\n";
        break;
    }
}