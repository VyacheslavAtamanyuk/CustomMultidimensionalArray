#include <lib/labwork_class.h>
#include <gtest/gtest.h>

TEST(SeventeenBitsTests, IndexTest) {
    SeventeenBits obj = SeventeenBits::make_array(1, 2, 3);
    obj[0][0][0] = 2;
    obj[0][0][0] = 3;
    ASSERT_EQ(obj[0][0][0], 3);
}

TEST(SeventeenBitsTests, AddTest) {
    SeventeenBits obj1 = SeventeenBits::make_array(2, 2, 2);
    SeventeenBits obj2 = SeventeenBits::make_array(2, 2, 2);
    obj1[0][0][0] = 2023;
    obj2[0][0][0] = 2024;
    SeventeenBits obj3 = obj1 + obj2;
    ASSERT_EQ(obj3[0][0][0], 4047);
}

TEST(SeventeenBitsTests, DiffTest) {
    SeventeenBits obj1 = SeventeenBits::make_array(2, 2, 2);
    SeventeenBits obj2 = SeventeenBits::make_array(2, 2, 2);
    obj1[0][0][0] = 2024;
    obj2[0][0][0] = 2023;
    SeventeenBits obj3 = obj1 - obj2;
    ASSERT_EQ(obj3[0][0][0], 1);
}

TEST(SeventeenBitsTests, OverflowTest) {
    SeventeenBits obj1 = SeventeenBits::make_array(2, 2, 2);
    obj1[0][0][0] = 123123123;
    SeventeenBits obj2 = obj1 * 123123;
    obj1[0][0][1] = 2023;
    obj1[1][1][1] = 1;
    obj2[0][0][1] = 3000;
    obj2[1][1][1] = 1;
    SeventeenBits obj3 = obj1 - obj2;
    ASSERT_EQ(obj1[0][0][0], 0b01011010110110011);
    ASSERT_EQ(obj2[0][0][0], 0b00001100011101001);
    ASSERT_EQ(obj3[0][0][1], 1);
    ASSERT_EQ(obj3[1][1][1], 1);
}

TEST(SeventeenBitsTests, MultiTest) {
    SeventeenBits obj1 = SeventeenBits::make_array(2, 2, 2);
    SeventeenBits obj2 = SeventeenBits::make_array(2, 2, 2);
    SeventeenBits obj3 = SeventeenBits::make_array(2, 2, 2);
    obj1[0][0][0] = 2023;
    obj2 = obj1 * 5;
    obj3 = obj1 * -5;
    ASSERT_EQ(obj2[0][0][0], 10115);
    ASSERT_EQ(obj3[0][0][0], 1);
}