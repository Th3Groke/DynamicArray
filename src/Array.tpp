#ifndef ARRAY_TPP
#define ARRAY_TPP

#include "../inc/Serializer.h"
#include "../inc/Array.h"
#include <fstream>


template<typename T>
typename Array<T>::iterator Array<T>::begin() {
    return storage.get();
}

template<typename T>
typename Array<T>::iterator Array<T>::end() {
    return storage.get() + size;
}

template<typename T>
typename Array<T>::const_iterator Array<T>::begin() const {
    return storage.get();
}

template<typename T>
typename Array<T>::const_iterator Array<T>::end() const {
    return storage.get() + size;
}

template<typename T>
typename Array<T>::const_iterator Array<T>::cbegin() const {
    return begin();
}

template<typename T>
typename Array<T>::const_iterator Array<T>::cend() const {
    return end();
}

template<typename T>
void Array<T>::ResizeStorage() {
    size_t newCapacity = this->capacity * 2;
    std::unique_ptr<T[]> newStorage = std::make_unique<T[]>(newCapacity);
    for (int i = 0; i < size; i++) {
        newStorage[i] = std::move(this->storage[i]);
    }
    storage = std::move(newStorage);
    this->capacity = newCapacity;
}

template<typename T>
Array<T>::Array() : size(0), capacity(8) {
    this->storage = std::make_unique<T[]>(capacity);
}

template<typename T>
Array<T>::Array(const size_t capacity) : storage{std::make_unique<T[]>(capacity)}, size(0), capacity(capacity) {
}

template<typename T>
Array<T>::Array(Array &arr) : size(arr.Size()), capacity(arr.Capacity()) {
    this->storage = std::make_unique<T[]>(arr.capacity);
    for (size_t i = 0; i < arr.Size(); i++) {
        this->storage[i] = arr[i];
    }
}

template<typename T>
Array<T>::Array(Array &&arr) noexcept
:storage(std::move(arr.storage)),size(arr.size),capacity(arr.capacity){
    arr.size = 0;
    arr.capacity = 0;
}

template<typename T>
Array<T>::Array(std::initializer_list<T> list): size(list.size()), capacity(list.size()) {
    this->storage = std::make_unique<T[]>(capacity);
    size_t i = 0;
    for (const T &element : list) {
        this->storage[i] = element;
        i++;
    }
}


template<typename T>
Array<T> &Array<T>::operator=(const Array<T> &arr) {
    if (this == &arr) {
    return *this;
    }
    std::unique_ptr<T[]> newStorage = std::make_unique<T[]>(arr.Capacity());
    for (size_t i = 0; i < arr.Size(); i++) {
        newStorage[i] = arr.storage[i];
    }
    this->storage = std::move(newStorage);
    this->capacity = arr.Capacity();
    this->size = arr.Size();
    return *this;
}

template<typename T>
Array<T> &Array<T>::operator=(Array<T> &&arr) noexcept {
    if (this == &arr) {
    return *this;
    }
    this->storage = std::move(arr.storage);
    this->capacity = arr.capacity;
    this->size = arr.size;
    arr.size = 0;
    arr.capacity = 0;
    return *this;
}

template<typename T>
T &Array<T>::operator[](int index) {
    if (index >= size) {
        throw IndexOutOfBounds();
    }
    return storage[index];
}

template<typename T>
size_t Array<T>::Size() const {
    return size;
}

template<typename T>
size_t Array<T>::Capacity() const {
    return capacity;
};

template<typename T>
void Array<T>::push_back(T element) {
    if (size >= capacity) {
        ResizeStorage();
    }
    size++;
    (*this)[size - 1] = element;
}


template<typename T>
T &Array<T>::pop_back() {
    if (size == 0) {
        throw IndexOutOfBounds();
    }
    return storage[--size];
}

template<typename T>
bool Array<T>::IsEmpty() {
    return size == 0;
}

template<typename T>
 size_t Array<T>::Find(T element){
    for(size_t i =0;i<this->size;i++){
        if (storage[i] == element){
            return i;
        }
    }
    return this->size;
 }

template<typename T>
void Array<T>::Save(const std::string &filename) const {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (size_t i = 0; i < this->size; i++) {
        Serializer<T>::Save(outFile,storage[i]);
    }
    outFile.close();
}


template<typename T>
void Array<T>::Load(const std::string &filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile.is_open()) {
        throw std::runtime_error("Cannot open file for reading");
    }

    size_t newSize;
    inFile.read(reinterpret_cast<char*>(&newSize),sizeof(newSize));
    if (newSize > capacity) {
        capacity = newSize;
        storage = std::make_unique<T[]>(capacity);
    }
    size = newSize;

    for (size_t i = 0; i < this->size; i++) {
        Serializer<T>::Load(inFile,storage[i]);
    }
    inFile.close();
}

template<typename T> 
void Array<T>::Sort(){
Sorting<T>::IntroSort(this->begin(), this->end());
}

#endif // ARRAY_TPP
