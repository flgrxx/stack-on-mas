#include "pch.h"

#include "stackmas.h"



// 1. Базовый тест конструктора
TEST(StackTest, DefaultConstructorCreatesEmptyStack) {
    Stack<int> stack;
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
}

// 2. Проверка основного функционала push/pop/top
TEST(StackTest, PushAndTopWorkCorrectly) {
    Stack<int> stack(5);
    stack.push(10);
    EXPECT_EQ(stack.top(), 10);

    stack.push(20);
    EXPECT_EQ(stack.top(), 20);
}

// 3. Проверка LIFO порядка
TEST(StackTest, StackFollowsLIFO) {
    Stack<int> stack(5);
    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_EQ(stack.top(), 3);
    stack.pop();
    EXPECT_EQ(stack.top(), 2);
    stack.pop();
    EXPECT_EQ(stack.top(), 1);
}

// 4. Проверка исключений при пустом стеке
TEST(StackTest, ThrowsWhenPoppingEmptyStack) {
    Stack<int> stack;
    EXPECT_THROW(stack.pop(), std::logic_error);
}

TEST(StackTest, ThrowsWhenTopOnEmptyStack) {
    Stack<int> stack;
    EXPECT_THROW(stack.top(), std::logic_error);
}

// 5. Проверка исключений при полном стеке
TEST(StackTest, ThrowsWhenPushingFullStack) {
    Stack<int> stack(2);
    stack.push(1);
    stack.push(2);

    EXPECT_TRUE(stack.isFull());
    EXPECT_THROW(stack.push(3), std::logic_error);
}

// 6. Проверка работы clear
TEST(StackTest, ClearMakesStackEmpty) {
    Stack<int> stack(5);
    stack.push(1);
    stack.push(2);

    EXPECT_FALSE(stack.isEmpty());
    stack.clear();
    EXPECT_TRUE(stack.isEmpty());
}

// 7. Проверка isFull для разных случаев
TEST(StackTest, IsFullWorksCorrectly) {
    Stack<int> stack(3);
    EXPECT_FALSE(stack.isFull());

    stack.push(1);
    stack.push(2);
    stack.push(3);
    EXPECT_TRUE(stack.isFull());
}

// 8. Проверка что можно использовать после clear
TEST(StackTest, CanReuseAfterClear) {
    Stack<int> stack(3);
    stack.push(1);
    stack.push(2);
    stack.clear();

    stack.push(3);
    EXPECT_EQ(stack.top(), 3);
    EXPECT_FALSE(stack.isEmpty());
}

// 9. Проверка работы с разными типами данных
TEST(StackTest, WorksWithStrings) {
    Stack<std::string> stack(3);
    stack.push("hello");
    stack.push("world");

    EXPECT_EQ(stack.top(), "world");
    stack.pop();
    EXPECT_EQ(stack.top(), "hello");
}

// 10. Проверка граничного случая - стек размером 1
TEST(StackTest, WorksWithSizeOne) {
    Stack<int> stack(1);
    EXPECT_TRUE(stack.isEmpty());

    stack.push(42);
    EXPECT_TRUE(stack.isFull());
    EXPECT_EQ(stack.top(), 42);

    EXPECT_THROW(stack.push(43), std::logic_error);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}