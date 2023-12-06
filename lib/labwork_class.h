#ifndef LAB5_LABWORK_CLASS_H
#define LAB5_LABWORK_CLASS_H

#include <iostream>
#include <cstdint>

class Array3D;

class Element {
public:
    Element(size_t new_ind_of_sub_sub_arr, size_t new_ind_of_sub_arr, size_t new_ind_of_arr, Array3D* new_parent_for_sub_sub_arr);

    Element& operator=(size_t new_num);

    friend std::ostream& operator<<(std::ostream& output, const Element& data);

    friend bool operator==(const Element& object, size_t num);

    friend class Array;
private:
    size_t ind_of_sub_sub_arr;
    size_t ind_of_sub_arr;
    size_t ind_of_arr;
    Array3D* parent_for_sub_sub_arr;
};

class Array {
public:
    Array(size_t new_ind_of_sub_arr, size_t new_ind_of_arr, Array3D* new_parent_for_sub_arr);

    Element operator[](size_t ind);

    friend std::ostream& operator<<(std::ostream& output, const Array& data);

    friend class Array2D;
private:
    size_t ind_of_sub_arr;
    size_t ind_of_arr;
    Array3D* parent_for_sub_arr;
};

class Array2D {
public:
    Array2D(size_t new_ind_of_arr, Array3D* new_parent_for_arr);

    Array operator[](size_t ind);

    friend std::ostream& operator<<(std::ostream& output, const Array2D& data);

    friend class Array3D;
private:
    size_t ind_of_arr;
    Array3D* parent_for_arr;
};

class Array3D {
public:
    static Array3D make_array(size_t size1, size_t size2, size_t size3);

    Array3D();
    Array3D(size_t new_x, size_t new_y, size_t new_z);
    ~Array3D();
    Array3D(const Array3D& other);
    Array3D& operator=(const Array3D& other);

    Array2D operator[](size_t ind);

    Array3D operator+(const Array3D& rhs);
    Array3D operator-(const Array3D& rhs);
    Array3D operator*(int num);

    friend std::istream& operator>>(std::istream& data, Array3D& input);

    friend std::ostream& operator<<(std::ostream& output, const Element& data);
    friend std::ostream& operator<<(std::ostream& output, const Array& data);
    friend std::ostream& operator<<(std::ostream& output, const Array2D& data);
    friend std::ostream& operator<<(std::ostream& output, const Array3D& data);

    friend bool operator==(const Element& object, size_t num);

    friend class Element;
private:
    size_t x;
    size_t y;
    size_t z;
    uint16_t* arr = nullptr;
    uint8_t* one_bit = nullptr;
    //Ставим везде nullptr, чтобы конструктор присваивания всегда работал корректно
};

#endif //LAB5_LABWORK_CLASS_H