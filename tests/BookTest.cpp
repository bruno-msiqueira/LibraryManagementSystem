#include "Book.hpp"
#include <gtest/gtest.h>

// Testes existentes
TEST(BookTest, BookAttributes) {
    Book book("1984", "George Orwell", 1949, 3, 1);
    EXPECT_EQ(book.getTitle(), "1984");
    EXPECT_EQ(book.getAuthor(), "George Orwell");
    EXPECT_EQ(book.getYear(), 1949);
    EXPECT_EQ(book.getId(), 1);
    EXPECT_EQ(book.getQuantity(), 3);
}

TEST(BookTest, BorrowAndReturn) {
    Book book("1984", "George Orwell", 1949, 3, 1);

    EXPECT_EQ(book.getAvailableQuantity(), 3);

    EXPECT_EQ(book.borrowBook(101), BookStatus::Success);
    EXPECT_EQ(book.getAvailableQuantity(), 2);

    EXPECT_EQ(book.borrowBook(101), BookStatus::AlreadyBorrowed);
    EXPECT_EQ(book.borrowBook(102), BookStatus::Success);
    EXPECT_EQ(book.getAvailableQuantity(), 1);

    EXPECT_EQ(book.returnBook(101), BookStatus::Success);
    EXPECT_EQ(book.getAvailableQuantity(), 2);

    EXPECT_EQ(book.returnBook(101), BookStatus::NotBorrowedByUser);
}

TEST(BookTest, HandleStatus) {
    testing::internal::CaptureStdout();
    Book::handleStatus(BookStatus::Success);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Operation completed successfully.\n");
}
// Função main necessária para Google Test
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
