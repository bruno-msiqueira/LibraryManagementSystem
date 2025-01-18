#include "Book.hpp"
#include <iostream>

Book::Book(std::string title, std::string author, int year, int id, int qty)
    : m_title(title), m_author(author), m_year(year), m_id(id), m_quantity(qty) {}

std::string Book::getTitle() const {
    return m_title;
}

std::string Book::getAuthor() const {
    return m_author;
}

int Book::getYear() const {
    return m_year;
}

int Book::getId() const {
    return m_id;
}

int Book::getQuantity() const {
    return m_quantity;
}

void Book::setQuantity(int qty) {
    m_quantity = qty;
}

bool Book::borrowBook() {
    if (m_quantity > 0) {
        --m_quantity;
        return true;
    }
    return false;
}

void Book::returnBook() {
    ++m_quantity;
}

void Book::display() const {
    std::cout << "ID: " << m_id
              << ", Title: " << m_title
              << ", Author: " << m_author
              << ", Year: " << m_year
              << ", Quantity: " << m_quantity << '\n';
}
