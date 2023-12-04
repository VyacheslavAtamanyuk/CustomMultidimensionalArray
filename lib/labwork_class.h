#ifndef LAB5_LABWORK_CLASS_H
#define LAB5_LABWORK_CLASS_H

#include <iostream>
#include <cstdint>

class SeventeenBits;

class SubSubArr {
private:
    size_t ind_of_sub_sub_arr;
    size_t ind_of_sub_arr;
    size_t ind_of_arr;
    SeventeenBits* parent_for_sub_sub_arr;
public:
    SubSubArr& operator=(size_t new_num);

    friend std::ostream& operator<<(std::ostream& output, const SubSubArr& data);

    friend bool operator==(const SubSubArr& object, size_t num);

    friend class SubArr;
};

class SubArr {
private:
    SubSubArr sub_sub_array;
    size_t ind_of_sub_arr;
    size_t ind_of_arr;
    SeventeenBits* parent_for_sub_arr;
public:
    SubSubArr& operator[](size_t ind);

    friend std::ostream& operator<<(std::ostream& output, const SubArr& data);

    friend class Arr;
};

class Arr {
private:
    SubArr sub_array;
    size_t ind_of_arr;
    SeventeenBits* parent_for_arr;
public:
    SubArr& operator[](size_t ind);

    friend std::ostream& operator<<(std::ostream& output, const Arr& data);

    friend class SeventeenBits;
};

class SeventeenBits {
private:
    Arr array;
    size_t x;
    size_t y;
    size_t z;
    uint16_t* arr;
    uint8_t* one_bit;
public:
    static SeventeenBits make_array(size_t size1, size_t size2, size_t size3);

    Arr& operator[](size_t ind);

    SeventeenBits operator+(const SeventeenBits& rhs);
    SeventeenBits operator-(const SeventeenBits& rhs);
    SeventeenBits operator*(int num);

    friend std::istream& operator>>(std::istream& data, SeventeenBits& input);

    friend std::ostream& operator<<(std::ostream& output, const SubSubArr& data);
    friend std::ostream& operator<<(std::ostream& output, const SubArr& data);
    friend std::ostream& operator<<(std::ostream& output, const Arr& data);
    friend std::ostream& operator<<(std::ostream& output, const SeventeenBits& data);

    friend bool operator==(const SubSubArr& object, size_t num);

    friend class SubSubArr;
};

#endif //LAB5_LABWORK_CLASS_H
