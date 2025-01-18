#include "LibraryManager.hpp"
#include "Book.hpp"
#include <gtest/gtest.h>

TEST(LibraryManagerTest, AddBook) {
    LibraryManager manager;
    Book book("1984", "George Orwell", 1949, 1, 3);

    manager.addBook(book);
    auto foundBook = manager.findBookById(1);

    ASSERT_NE(foundBook, nullptr);
    EXPECT_EQ(foundBook->getTitle(), "1984");
    EXPECT_EQ(foundBook->getQuantity(), 3);
}

TEST(LibraryManagerTest, FindBookById) {
    LibraryManager manager;
    Book book1("1984", "George Orwell", 1949, 1, 3);
    Book book2("Animal Farm", "George Orwell", 1945, 2, 5);

    manager.addBook(book1);
    manager.addBook(book2);

    auto foundBook = manager.findBookById(2);
    ASSERT_NE(foundBook, nullptr);
    EXPECT_EQ(foundBook->getTitle(), "Animal Farm");
}

TEST(LibraryManagerTest, FindBooksByTitle) {
    LibraryManager manager;
    Book book1("1984", "George Orwell", 1949, 1, 3);
    Book book2("1984 Redux", "Unknown Author", 2020, 2, 2);

    manager.addBook(book1);
    manager.addBook(book2);

    auto results = manager.findBooksByTitle("1984");
    EXPECT_EQ(results.size(), 2);
}

TEST(LibraryManagerTest, FindBooksByAuthor) {
    LibraryManager manager;
    Book book1("1984", "George Orwell", 1949, 1, 3);
    Book book2("Animal Farm", "George Orwell", 1945, 2, 5);

    manager.addBook(book1);
    manager.addBook(book2);

    auto results = manager.findBooksByAuthor("George Orwell");
    EXPECT_EQ(results.size(), 2);
}

TEST(LibraryManagerTest, BorrowAndReturnBook) {
    LibraryManager manager;
    Book book("1984", "George Orwell", 1949, 1, 3);

    manager.addBook(book);

    EXPECT_TRUE(manager.borrowBook(1));  // Borrow a book
    EXPECT_EQ(manager.findBookById(1)->getQuantity(), 2);

    manager.returnBook(1);  // Return the book
    EXPECT_EQ(manager.findBookById(1)->getQuantity(), 3);
}

TEST(LibraryManagerTest, ListBooks) {
    LibraryManager manager;
    Book book1("1984", "George Orwell", 1949, 1, 3);
    Book book2("Animal Farm", "George Orwell", 1945, 2, 5);

    manager.addBook(book1);
    manager.addBook(book2);

    testing::internal::CaptureStdout();
    manager.listBooks();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("1984"), std::string::npos);
    EXPECT_NE(output.find("Animal Farm"), std::string::npos);
}

TEST(LibraryManagerTest, SaveAndLoadFromFile) {
    LibraryManager manager;

    Book book1("1984", "George Orwell", 1949, 1, 3);
    Book book2("Animal Farm", "George Orwell", 1945, 2, 5);

    manager.addBook(book1);
    manager.addBook(book2);

    // Save to file
    ASSERT_TRUE(manager.saveToFile("test_library.json"));

    // Create a new manager and load from file
    LibraryManager loadedManager;
    ASSERT_TRUE(loadedManager.loadFromFile("test_library.json"));

    // Verify loaded data
    auto foundBook1 = loadedManager.findBookById(1);
    ASSERT_NE(foundBook1, nullptr);
    EXPECT_EQ(foundBook1->getTitle(), "1984");

    auto foundBook2 = loadedManager.findBookById(2);
    ASSERT_NE(foundBook2, nullptr);
    EXPECT_EQ(foundBook2->getTitle(), "Animal Farm");
}
