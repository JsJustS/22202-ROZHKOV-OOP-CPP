//
// Created by Just on 19.10.2023.
//

#include <iostream>
#include <cmath>
#include <iterator>
#include "BitArray.h"

BitArray::BitArray() {
    this->array = nullptr;
    this->capacity = bytesToBits(sizeof(BitContainerType));
    this->reset();
    this->amountOfBits = 0;
}

BitArray::~BitArray() {
    if (this->amountOfBits > 0) {
        delete [] this->array;
    }
}

BitArray::BitArray(int num_bits, unsigned long value) {
    int valueBitsLen = ceil(log2(value));
    this->amountOfBits = (num_bits > valueBitsLen) ? valueBitsLen: num_bits;

    this->capacity = roundBitsToContainer(this->amountOfBits);
    int containerAmount = bitsToBytes(num_bits);
    this->array = new BitContainerType[containerAmount];
    this->reset();

    if (num_bits < valueBitsLen) {
        value = value >> (valueBitsLen - num_bits);
    }
    
    for (int i = num_bits - 1; i >= 0; i--) {
        bool bit = value & (unsigned long)1;
        value = value >> 1;
        if (i < num_bits) {
            this->set(i, bit);
        }
    }
}

BitArray::BitArray(const BitArray &b) {
    this->amountOfBits = b.size();
    this->capacity = roundBitsToContainer(b.size());
    this->array = new BitContainerType[bitsToBytes(this->amountOfBits)];
    for (int i = 0; i < b.size(); i++) {
        this->set(i, b.get(i));
    }
}

void BitArray::swap(BitArray &b) {
    int thisNumBits = this->size();
    int otherNumBits = b.size();

    BitContainerType *other_array = new BitContainerType[bitsToBytes(otherNumBits)];
    std::vector<BitContainerType> other_vector = b.to_vector();
    for (int i = 0; i < bitsToBytes(otherNumBits); i++) {
        other_array[i] = other_vector[i];
    }

    b.resize(thisNumBits);
    for (int i = 0; i < thisNumBits; i++) {
        b.set(i, this->get(i));
    }

    delete [] this->array;
    this->array = other_array;
    this->amountOfBits = otherNumBits;
    this->capacity = roundBitsToContainer(otherNumBits);
}

BitArray &BitArray::operator=(const BitArray &b) {
    if (this == &b) {
        return *this;
    }
    
    this->amountOfBits = b.size();
    this->capacity = roundBitsToContainer(b.size());

    delete [] this->array;

    this->array = new BitContainerType[bitsToBytes(this->amountOfBits)];
    for (int i = 0; i < b.size(); i++) {
        this->set(i, b.get(i));
    }
    return *this;
}

void BitArray::resize(int num_bits, bool value) {
    int newSize = bitsToBytes(num_bits);
    BitContainerType *newArray = new BitContainerType[newSize]();

    if (this->array != nullptr) {
        int copySize = (newSize < bitsToBytes(this->capacity)) ? newSize : bitsToBytes(this->capacity);
        memcpy(newArray, this->array, copySize * sizeof(BitContainerType));
        delete [] this->array;
    }

    this->capacity = roundBitsToContainer(num_bits);
    this->array = newArray;

    if (value) {
        for (int i = this->size(); i < num_bits; i++) {
            this->set(i, true);
        }
    }
    this->amountOfBits = num_bits;
}

void BitArray::clear() {
    this->amountOfBits = 0;
    this->capacity = 0;
    delete this->array;
    this->array = nullptr;
}

void BitArray::push_back(bool bit) {
    this->set(this->size(), bit);
}

BitArray &BitArray::operator&=(const BitArray &b) {
    if (this->size() != b.size()) {throw std::length_error {"Size difference between two BitArrays."};}
    for (int i = 0; i < this->size(); i++) {
        this->set(i, (this->get(i) & b.get(i)));
    }
    return *this;
}

BitArray &BitArray::operator|=(const BitArray &b) {
    if (this->size() != b.size()) {throw std::length_error {"Size difference between two BitArrays."};}
    for (int i = 0; i < this->size(); i++) {
        this->set(i, (this->get(i) | b.get(i)));
    }
    return *this;
}

BitArray &BitArray::operator^=(const BitArray &b) {
    if (this->size() != b.size()) {throw std::length_error {"Size difference between two BitArrays."};}
    for (int i = 0; i < this->size(); i++) {
        this->set(i, (this->get(i) ^ b.get(i)));
    }
    return *this;
}

BitArray &BitArray::operator<<=(int n) {
    for (int i = 0; i < this->size() - n; i++) {
        this->set(i, this->get(i+n));
    }
    for (int i = this->size() - n; i < this->size(); i++) {
        this->set(i, false);
    }
    return *this;
}

BitArray &BitArray::operator>>=(int n) {
    for (int i = this->size() - 1; i > n - 1; i--) {
        this->set(i, this->operator[](i-n));
    }
    for (int i = 0; i < n; i++) {
        this->set(i, false);
    }
    return *this;
}

BitArray BitArray::operator<<(int n) const {
    BitArray newArray(*this);
    newArray <<= n;
    return newArray;
}

BitArray BitArray::operator>>(int n) const {
    BitArray newArray(*this);
    newArray >>= n;
    return newArray;
}

BitArray &BitArray::set(int n, bool val) {
    this->amountOfBits = (n+1 > this->amountOfBits) ? n+1 : this->amountOfBits;

    if ((n+1) > this->capacity) {
        if (!val) {
            // Бит с индексом False, запоминать не обязательно
            return *this;
        }
        // Бит с индексом True, его надо запомнить
        this->resize(n+1);
    }

    BitContainerType container = this->array[bitsToBytes(n + 1) - 1];
    int delta = sizeof(BitContainerType)*8 - (n % (sizeof(BitContainerType)*8)) - 1;
    container = (container & ~((BitContainerType)1 << delta)) | ((BitContainerType)val << delta);
    this->array[bitsToBytes(n + 1) - 1] = container;

    if (!val) {
        int toFree = 0;
        for (int i = bitsToBytes(this->capacity) - 1; i > 0; i--) {
            if (this->array[i] != 0) {
                break;
            }
            toFree++;
        }
        if (toFree > 0) {
            shrink(bitsToBytes(this->capacity) - toFree);
        }
    }
    return *this;
}

BitArray &BitArray::set() {
    int size = bitsToBytes(this->capacity);
    for (int i = 0; i < size; i++) {
        this->array[i] = ~0;
    }
    return *this;
}

BitArray &BitArray::reset(int n) {
    this->set(n, false);
    return *this;
}

BitArray &BitArray::reset() {
    int size = bitsToBytes(this->capacity);
    for (int i = 0; i < size; i++) {
        this->array[i] = 0;
    }
    return *this;
}

bool BitArray::any() const {
    for (int i = 0; i < this->size(); i++) {
        if (this->get(i)) return true;
    }
    return false;
}

bool BitArray::none() const {
    for (int i = 0; i < this->size(); i++) {
        if (this->get(i)) return false;
    }
    return true;
}

BitArray BitArray::operator~() const {
    BitArray b(this->size());
    for (int i = 0; i < this->size(); i++) {
        b.set(i, !this->get(i));
    }
    return b;
}

int BitArray::count() const {
    int amount = 0;
    for (int i = 0; i < this->size(); i++) {
        if (this->get(i)) {
            amount += 1;
        }
    }
    return amount;
}

BitArray::Wrapper BitArray::operator[] (int i) {
    if (i < 0) {throw std::out_of_range("invalid index");}
    return Wrapper(this, i);
}

int BitArray::size() const {
    return this->amountOfBits;
}

bool BitArray::empty() const {
    return this->size() == 0;
}

std::string BitArray::to_string() const {
    std::string string;
    for (int i = 0; i < this->size(); i++) {
        string += ((this->get(i))?"1":"0");
    }
    return string;
}

int BitArray::bitsToBytes(int amountOfBits) {
    if (amountOfBits < 0) return 0;
    return amountOfBits / (sizeof(BitContainerType)*8) + ((amountOfBits % (sizeof(BitContainerType)*8))? 1: 0);
}

int BitArray::bytesToBits(int amountOfBytes) {
    if (amountOfBytes < 0) return 0;
    return sizeof(BitContainerType) * 8 * amountOfBytes;
}

bool BitArray::get(int n) const{
    if (n + 1> this->capacity || n > this->amountOfBits) {
        return false;
    }
    BitContainerType container = this->array[bitsToBytes(n + 1) - 1];
    int containerIndex = n % (sizeof(BitContainerType)*8);
    return (container & (1 << (sizeof(BitContainerType)*8 - containerIndex - 1))) != 0;
}

int BitArray::roundBitsToContainer(int amountOfBits) {
    return bytesToBits(bitsToBytes(amountOfBits));
}

std::vector<BitArray::BitContainerType> BitArray::to_vector() const {
    if (this->size() == 0) return std::vector<BitContainerType>();
    return std::vector<BitContainerType>(this->array, this->array + bitsToBytes(this->capacity));
}

int BitArray::cap() const {
    return this->capacity;
}

void BitArray::shrink(int size) {
    if (this->array == nullptr) {throw std::runtime_error("Trying to shrink empty array");}

    BitContainerType *newArray = new BitContainerType[size]();
    memcpy(newArray, this->array, size * sizeof(BitContainerType));
    delete [] this->array;

    this->capacity = bytesToBits(size);
    this->array = newArray;
}

BitArray::Wrapper &BitArray::Wrapper::operator=(bool value) {
    this->array->set(this->index, value);
    return *this;
}

BitArray::Wrapper &BitArray::Wrapper::operator=(const BitArray::Wrapper &other) {
    this->array->set(this->index, other.operator bool());
    return *this;
}

BitArray::Wrapper::operator bool() const {
    // Берём бит вне выделенной памяти
    // Очевидно, что мы его либо не вносили, либо сузили
    // Значит, что там false по определению.
    if (this->index > this->array->size()-1) {
        return false;
    }
    return this->array->get(this->index);
}

BitArray::Wrapper::Wrapper(BitArray *arr, int ind) {
    this->array = arr;
    this->index = ind;
}

bool operator==(const BitArray &a, const BitArray &b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); i++) {
        if (a.get(i) != b.get(i)) return false;
    }
    return true;
}

bool operator!=(const BitArray &a, const BitArray &b) {
    return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    BitArray newArray = BitArray(b1);
    newArray &= b2;
    return newArray;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) {
    BitArray newArray = BitArray(b1);
    newArray |= b2;
    return newArray;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    BitArray newArray = BitArray(b1);
    newArray ^= b2;
    return newArray;
}
