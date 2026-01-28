#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H
#include <iostream>


class IndexOutOfBounds : public std::exception {
    public:
        IndexOutOfBounds() = default;

        char const *what() const noexcept override {
            return "Array index out of range";
        }
};
#endif //_EXCEPTIONS_H
