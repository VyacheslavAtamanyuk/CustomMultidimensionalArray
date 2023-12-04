#include "labwork_class.h"

SubSubArr& SubSubArr::operator=(size_t new_num) {
    size_t location = ind_of_arr * parent_for_sub_sub_arr->y * parent_for_sub_sub_arr->z +
            ind_of_sub_arr*parent_for_sub_sub_arr->z + ind_of_sub_sub_arr;
    parent_for_sub_sub_arr->arr[location] = new_num & 0xFFFF;
    parent_for_sub_sub_arr->one_bit[location / 8] |= (((new_num >> 16) & 1) << (location % 8));
    return *this;
}

SubSubArr& SubArr::operator[](size_t ind) {
    sub_sub_array.ind_of_sub_sub_arr = ind;
    sub_sub_array.ind_of_sub_arr = ind_of_sub_arr;
    sub_sub_array.ind_of_arr = ind_of_arr;
    sub_sub_array.parent_for_sub_sub_arr = parent_for_sub_arr;
    return sub_sub_array;
}

SubArr& Arr::operator[](size_t ind) {
    sub_array.ind_of_sub_arr = ind;
    sub_array.ind_of_arr = ind_of_arr;
    sub_array.parent_for_sub_arr = parent_for_arr;
    return sub_array;
}

Arr& SeventeenBits::operator[](size_t ind) {
    array.ind_of_arr = ind;
    array.parent_for_arr = this;
    return array;
}

SeventeenBits SeventeenBits::make_array(size_t size1, size_t size2, size_t size3) {
    SeventeenBits new_class;
    new_class.arr = new uint16_t[size1 * size2 * size3];
    new_class.one_bit = new uint8_t[(size1 * size2 * size3) / 8 + 1]{};
    new_class.x = size1;
    new_class.y = size2;
    new_class.z = size3;
    return new_class;
}

SeventeenBits SeventeenBits::operator+(const SeventeenBits& rhs) {
    SeventeenBits new_class;
    new_class.arr = new uint16_t[x * y * z];
    new_class.one_bit = new uint8_t[x * y * z / 8 + 1]{};
    new_class.x = x;
    new_class.y = y;
    new_class.z = z;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                size_t location = i * y * z + j*z + k;
                uint32_t left = ((((one_bit[location / 8] >> location%8) & 1) << 16) + arr[location]);
                uint32_t right = ((((rhs.one_bit[location / 8] >> location%8) & 1) << 16) + rhs.arr[location]);
                new_class.arr[location] = (left + right) & 0xFFFF;
                new_class.one_bit[location / 8] |= (((left + right) >> 16) & 1) << (location % 8);
            }
        }
    }
    return new_class;
}

SeventeenBits SeventeenBits::operator-(const SeventeenBits& rhs) {
    SeventeenBits new_class;
    new_class.arr = new uint16_t[x * y * z];
    new_class.one_bit = new uint8_t[x * y * z / 8 + 1]{};
    new_class.x = x;
    new_class.y = y;
    new_class.z = z;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                size_t location = i * y * z + j*z + k;
                uint32_t left = ((((one_bit[location / 8] >> location%8) & 1) << 16) + arr[location]);
                uint32_t right = ((((rhs.one_bit[location / 8] >> location%8) & 1) << 16) + rhs.arr[location]);
                if (left > right) {
                    new_class.arr[location] = (left - right) & 0xFFFF;
                    new_class.one_bit[location / 8] |= (((left - right) >> 16) & 1) << (location % 8);
                } else {
                    new_class.arr[location] = 1;
                }
            }
        }
    }
    return new_class;
}

//int, т.к хочу обработать случаи, когда на вход подается число <= 0, а size_t - unsigned
SeventeenBits SeventeenBits::operator*(int num) {
    SeventeenBits new_class;
    new_class.arr = new uint16_t[x * y * z];
    new_class.one_bit = new uint8_t[x * y * z / 8 + 1]{};
    new_class.x = x;
    new_class.y = y;
    new_class.z = z;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                size_t location = i * y * z + j*z + k;
                uint32_t old = ((((one_bit[location / 8] >> location%8) & 1) << 16) + arr[location]);
                if (num > 0) {
                    new_class.arr[location] = (old * num) & 0xFFFF;
                    new_class.one_bit[location / 8] |= (((old * num) >> 16) & 1) << (location % 8);
                } else {
                    new_class.arr[location] = 1;
                }
            }
        }
    }
    return new_class;
}

std::ostream& operator<<(std::ostream& output, const SubSubArr& data) {
    size_t location = data.ind_of_arr * data.parent_for_sub_sub_arr->y * data.parent_for_sub_sub_arr->z +
            data.ind_of_sub_arr * data.parent_for_sub_sub_arr->z + data.ind_of_sub_sub_arr;
    output << (data.parent_for_sub_sub_arr->arr[location] +
    (((data.parent_for_sub_sub_arr->one_bit[location / 8] >> (location % 8)) & 1) << 16));
    return output;
}

std::ostream& operator<<(std::ostream& output, const SubArr& data) {
    size_t location = data.ind_of_arr * data.parent_for_sub_arr->y * data.parent_for_sub_arr->z +
                      data.ind_of_sub_arr * data.parent_for_sub_arr->z;
    output << '[';
    for (size_t i = 0; i < data.parent_for_sub_arr->z; ++i) {
        output << (data.parent_for_sub_arr->arr[location + i] +
        (((data.parent_for_sub_arr->one_bit[(location + i) / 8] >> (location + 1 % 8)) & 1) << 16));
        if (i == data.parent_for_sub_arr->z - 1) {
            output << ']';
            continue;
        }
        output << ", ";
    }
    return output;
}

std::ostream& operator<<(std::ostream& output, const Arr& data) {
    size_t location = data.ind_of_arr * data.parent_for_arr->y * data.parent_for_arr->z;
    output << '[';
    for (size_t i = 0; i < data.parent_for_arr->y; ++i) {
        output << '[';
        for (size_t j = 0; j < data.parent_for_arr->z; ++j) {
            output << (data.parent_for_arr->arr[location + i*data.parent_for_arr->z + j] +
            (((data.parent_for_arr->one_bit[(location + i) / 8] >> (location + 1 % 8)) & 1) << 16));
            if (j == data.parent_for_arr->z - 1) {
                output << ']';
                continue;
            }
            output << ", ";
        }
        if (i == data.parent_for_arr->y - 1) {
            output << ']';
            continue;
        }
        output << ", ";
    }
    return output;
}

std::ostream& operator<<(std::ostream& output, const SeventeenBits& data) {
    output << '[';
    for (int i = 0; i < data.x; ++i) {
        output << '[';
        for (int j = 0; j < data.y; ++j) {
            output << '[';
            for (int k = 0; k < data.z; ++k) {
                output << (data.arr[i * data.y * data.z + j * data.z + k] +
                (((data.one_bit[(i * data.y * data.z + j * data.z + k) / 8] >> (i * data.y * data.z + j * data.z + k % 8)) & 1) << 16));
                if (k == data.z - 1) {
                    output << ']';
                    continue;
                }
                output << ", ";
            }
            if (j == data.y - 1) {
                output << ']';
                continue;
            }
            output << ", ";
        }
        if (i == data.x - 1) {
            output << "]";
            continue;
        }
        output << ",\n";
    }
    return output;
}

std::istream& operator>>(std::istream& input, SeventeenBits& data) {
    size_t new_x;
    size_t new_y;
    size_t new_z;
    input >> new_x >> new_y >> new_z;
    data.x = new_x;
    data.y = new_y;
    data.z = new_z;
    data.arr = new uint16_t[new_x * new_y * new_z];
    data.one_bit = new uint8_t[(new_x * new_y * new_z) / 8 + 1];
    uint32_t num;
    for (int i = 0; i < new_x; ++i) {
        for (int j = 0; j < new_y; ++j) {
            for (int k = 0; k < new_z; ++k) {
                input >> num;
                data.arr[i * new_y * new_z + j * new_z + k] = num & 0xFFFF;
                data.one_bit[(i * new_y * new_z + j * new_z + k) / 8] |= ((num >> 16) & 1) << ((i * new_y * new_z + j * new_z + k) % 8);
            }
        }
    }
    return input;
}

bool operator==(const SubSubArr& object, size_t num) {
    size_t location = object.ind_of_arr * object.parent_for_sub_sub_arr->y * object.parent_for_sub_sub_arr->z +
                      object.ind_of_sub_arr * object.parent_for_sub_sub_arr->z + object.ind_of_sub_sub_arr;
    return object.parent_for_sub_sub_arr->arr[location] + (((object.parent_for_sub_sub_arr->one_bit[location / 8] >> (location % 8)) & 1) << 16) == num;
}


