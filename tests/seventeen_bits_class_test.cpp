#include <lib/labwork_class.h>
#include <gtest/gtest.h>

#include <sstream>

//Тесты для проверки функционала

TEST(Array3DTests, IndexTest) {
    Array3D obj = Array3D::make_array(1, 2, 3);
    obj[0][0][0] = 2;
    obj[0][0][0] = 3;
    ASSERT_EQ(obj[0][0][0], 3);
}

TEST(Array3DTests, OverflowIndexTest) {
    Array3D obj1 = Array3D::make_array(2, 2, 2);
    obj1[0][0][0] = 123123000;
    ASSERT_EQ(obj1[0][0][0], 0b01011010100111000);
}

TEST(Array3DTests, DiffTest) {
    Array3D obj1 = Array3D::make_array(2, 2, 2);
    Array3D obj2 = Array3D::make_array(2, 2, 2);
    obj1[0][0][0] = 2024;
    obj2[0][0][0] = 2023;
    Array3D obj3 = obj1 - obj2;
    ASSERT_EQ(obj3[0][0][0], 1);
}

TEST(Array3DTests, OverflowDiffTest) {
    Array3D obj1 = Array3D::make_array(2, 2, 2);
    Array3D obj2 = Array3D::make_array(2, 2, 2);
    obj1[0][0][0] = 2020;
    obj2[0][0][0] = 2023;
    Array3D obj3 = obj1 - obj2;
    ASSERT_EQ(obj3[0][0][0], 1);
}

TEST(Array3DTests, AddTest) {
    Array3D obj1 = Array3D::make_array(2, 2, 2);
    Array3D obj2 = Array3D::make_array(2, 2, 2);
    obj1[0][0][0] = 2023;
    obj2[0][0][0] = 2024;
    Array3D obj3 = obj1 + obj2;
    ASSERT_EQ(obj3[0][0][0], 4047);
}

TEST(Array3DTests, OverflowAddTest) {
    Array3D obj1 = Array3D::make_array(2, 2, 2);
    Array3D obj2 = Array3D::make_array(2, 2, 2);
    obj1[0][0][0] = 123123000;
    obj2[0][0][0] = 123;
    Array3D obj3 = obj1 + obj2;
    ASSERT_EQ(obj3[0][0][0], 0b01011010110110011);
}

TEST(Array3DTests, MultiTest) {
    Array3D obj1 = Array3D::make_array(2, 2, 2);
    Array3D obj2 = Array3D::make_array(2, 2, 2);
    Array3D obj3 = Array3D::make_array(2, 2, 2);
    obj1[0][0][0] = 2023;
    obj2 = obj1 * 5;
    ASSERT_EQ(obj2[0][0][0], 10115);
}

TEST(Array3DTests, OverflowMultiTest) {
    Array3D obj1 = Array3D::make_array(2, 2, 2);
    obj1[0][0][0] = 2023;
    obj1 = obj1 * -5;
    Array3D obj2 = Array3D::make_array(2, 2, 2);
    obj2[0][0][0] = 123123123;
    Array3D obj3 = obj2 * 123123;
    ASSERT_EQ(obj1[0][0][0], 1);
    ASSERT_EQ(obj2[0][0][0], 0b01011010110110011);
    ASSERT_EQ(obj3[0][0][0], 0b00001100011101001);
}

TEST(Array3DTests, OutTest) {
    Array3D obj1 = Array3D::make_array(3, 3, 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                obj1[i][j][k] = 1;
            }
        }
    }
    std::stringstream output1;
    std::stringstream output2;
    std::stringstream output3;
    std::stringstream output4;
    output1 << obj1;
    output2 << obj1[0];
    output3 << obj1[0][0];
    output4 << obj1[0][0][0];
    ASSERT_EQ(output1.str(),
              "[[[1, 1, 1], [1, 1, 1], [1, 1, 1]],\n"
              "[[1, 1, 1], [1, 1, 1], [1, 1, 1]],\n"
              "[[1, 1, 1], [1, 1, 1], [1, 1, 1]]]");
    ASSERT_EQ(output2.str(),
              "[[1, 1, 1], [1, 1, 1], [1, 1, 1]]");
    ASSERT_EQ(output3.str(), "[1, 1, 1]");
    ASSERT_EQ(output4.str(), "1");
}

TEST(Array3DTests, InTest) {
    std::stringstream input;
    input << 3 << ' ' << 3 << ' ' << 3 << ' ';
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int z = 0; z < 3; ++z) {
                input << 2023 << ' ';
            }
        }
    }
    Array3D obj1 = Array3D::make_array(3, 3, 3);
    input >> obj1;
    obj1[0][0][0] = 1;
    ASSERT_EQ(obj1[0][0][0], 1);
    ASSERT_EQ(obj1[0][0][1], 2023);
    ASSERT_EQ(obj1[1][1][1], 2023);
}

//Тесты для проверки деструктора, конструкторов копирования и присваивания

TEST(Array3DTests, Destructor) {
    int i = 0;
    while (i < 1000) {
        Array3D obj = Array3D::make_array(100, 100, 100);
        ++i;
    }
    //Если дошло до сюда, то программа не умерла => деструктор работает
    ASSERT_EQ(1, 1);
}

TEST(Array3DTests, CopyConstructor) {
    Array3D obj1 = Array3D::make_array(2, 2, 2);
    obj1[0][0][0] = 2023;
    Array3D obj2 = obj1;
    ASSERT_EQ(obj2[0][0][0], 2023);
}

TEST(Array3DTests, AssignmentConstructor) {
    Array3D obj1 = Array3D::make_array(2, 2, 2);
    obj1[0][0][0] = 2023;
    Array3D obj2;
    obj2 = obj1;
    Array3D obj3 = Array3D::make_array(2, 2, 2);
    obj3[0][0][0] = 123123123;
    obj3 = obj1;
    ASSERT_EQ(obj2[0][0][0], 2023);
    ASSERT_EQ(obj3[0][0][0], 2023);
}