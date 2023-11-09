//
// Created by Just on 19.10.2023.
//

#include <iostream>
#include <cmath>
#include "BitArray.h"

BitArray::BitArray() {
    this->array = new BitContainerType;
    this->capacity = bytesToBits(sizeof(BitContainerType));
    this->reset();
    this->amountOfBits = 0;
}

BitArray::~BitArray() {
    delete [] this->array;
}

BitArray::BitArray(int num_bits, unsigned long value) {
    this->amountOfBits = 0;
    this->capacity = num_bits;
    int containerAmount = bitsToBytes(num_bits);
    this->array = new BitContainerType[containerAmount];
    this->reset();

    int valueBitsLen = ceil(log2(value));

    if (num_bits < valueBitsLen) {
        value = value >> (valueBitsLen - num_bits);
    }
    
    for (int i = num_bits - 1; i >= 0; i--) {
        bool bit = value & (unsigned long)1;
        value = value >> 1;
        if (i < num_bits) {
            this->set(i, bit);
            this->amountOfBits++;
        }
    }
}

BitArray::BitArray(const BitArray &b) {
    this->amountOfBits = b.size();
    this->capacity = bytesToBits(bitsToBytes(b.size()));
    this->array = new BitContainerType[bitsToBytes(this->amountOfBits)];
    for (int i = 0; i < b.size(); i++) {
        this->set(i, b.get(i));
    }
}

void BitArray::swap(BitArray &b) {
    int thisNumBits = this->size();
    int otherNumBits = b.size();

    BitContainerType *other_array = new BitContainerType[bitsToBytes(otherNumBits)];

    b.resize(thisNumBits);
    for (int i = 0; i < thisNumBits; i++) {
        b.set(i, this->operator[](i));
    }

    delete [] this->array;
    this->array = other_array;
    this->amountOfBits = otherNumBits;
    this->capacity = bitsToBytes(bytesToBits(otherNumBits));
}

BitArray &BitArray::operator=(const BitArray &b) {
    this->amountOfBits = b.size();
    this->capacity = bytesToBits(bitsToBytes(b.size()));

    delete [] this->array;

    this->array = new BitContainerType[bitsToBytes(this->amountOfBits)];
    for (int i = 0; i < b.size(); i++) {
        this->set(i, b.get(i));
    }
    return *this;
}

void BitArray::resize(int num_bits, bool value) {
    int newSize = bitsToBytes(num_bits);
    BitContainerType *newArray = new BitContainerType[newSize];

    memcpy(newArray, this->array, newSize * sizeof(BitContainerType));

    this->capacity = num_bits;
    delete [] this->array;
    this->array = newArray;

    for (int i = this->size(); i < num_bits; i++) {
        this->set(i, value);
    }
}

void BitArray::clear() {
    this->amountOfBits = 0;
    delete this->array;
    this->array = new BitContainerType;
    this->array[0] = 0;
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
    if ((n+1) > this->capacity) {
        this->resize(n+1);
    }
    BitContainerType container = this->array[bitsToBytes(n + 1) - 1];
    int delta = sizeof(BitContainerType)*8 - (n % (sizeof(BitContainerType)*8)) - 1;
    container = (container & ~((BitContainerType)1 << delta)) | ((BitContainerType)val << delta);
    this->array[bitsToBytes(n + 1) - 1] = container;
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
    if (i < 0 || i >= size()) {throw std::out_of_range("invalid index");}
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
    BitContainerType container = this->array[bitsToBytes(n + 1) - 1];
    int containerIndex = n % (sizeof(BitContainerType)*8);
    return (container & (1 << (sizeof(BitContainerType)*8 - containerIndex - 1))) != 0;
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
