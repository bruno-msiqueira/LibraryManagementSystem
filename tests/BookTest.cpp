#include "Book.hpp"
#include <gtest/gtest.h>

// Testes existentes
TEST(BookTest, BookAttributes) {
    Book book("1984", "George Orwell", 1949, 1, 3);
    EXPECT_EQ(book.getTitle(), "1984");
    EXPECT_EQ(book.getAuthor(), "George Orwell");
    EXPECT_EQ(book.getYear(), 1949);
    EXPECT_EQ(book.getId(), 1);
    EXPECT_EQ(book.getQuantity(), 3);
}

TEST(BookTest, BorrowAndReturn) {
    Book book("1984", "George Orwell", 1949, 1, 2);

    // Borrow a copy
    EXPECT_TRUE(book.borrowBook());
    EXPECT_EQ(book.getQuantity(), 1);

    // Borrow another copy
    EXPECT_TRUE(book.borrowBook());
    EXPECT_EQ(book.getQuantity(), 0);

    // Try to borrow with no copies left
    EXPECT_FALSE(book.borrowBook());
    EXPECT_EQ(book.getQuantity(), 0);

    // Return a copy
    book.returnBook();
    EXPECT_EQ(book.getQuantity(), 1);
}

// Função main necessária para Google Test
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
