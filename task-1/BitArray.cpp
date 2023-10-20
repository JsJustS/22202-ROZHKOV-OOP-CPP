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

//Конструирует массив, хранящий заданное количество бит.
//Первые sizeof(long) бит можно инициализровать с помощью параметра value.
BitArray::BitArray(int num_bits, unsigned long value) {
    this->amountOfBits = 0;
    this->capacity = num_bits;
    int containerAmount = bitsToBytes(num_bits);
    this->array = new BitContainerType[containerAmount];
    this->reset();

    int valueBitsLen = ceil(log2(value));

    if (num_bits < valueBitsLen) {
        value = value << (sizeof(BitContainerType)*8 - num_bits);
    }

    int initStart = (valueBitsLen > num_bits)? valueBitsLen - 1: num_bits - 1;

    //for (int i = 0; i < num_bits; i++) {
    for (int i = initStart; i >= 0; i--) {
        this->amountOfBits++;
        bool bit = value & (unsigned long)1;
        value = value >> 1;
        this->set(i, bit);
    }
}

BitArray::BitArray(const BitArray &b) {
    this->amountOfBits = b.size();
    this->capacity = bytesToBits(bitsToBytes(b.size()));
    this->array = new BitContainerType[bitsToBytes(this->amountOfBits)];
    for (int i = 0; i < b.size(); i++) {
        this->set(i, b[i]);
    }
}

void BitArray::swap(BitArray &b) {
    //todo: redo with consideration of capacity
    int this_num_bits = this->size();
    int other_num_bits = b.size();

    BitContainerType *other_array = new BitContainerType[bitsToBytes(other_num_bits)];

    b.resize(this_num_bits);
    for (int i = 0; i < this_num_bits; i++) {
        b.set(i, this->operator[](i));
    }

    delete [] this->array;
    this->array = other_array;
    this->amountOfBits = other_num_bits;
}

BitArray &BitArray::operator=(const BitArray &b) {
    return *this;
}

//Изменяет размер массива. В случае расширения, новые элементы
//инициализируются значением value.
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

//Очищает массив.
void BitArray::clear() {
    this->amountOfBits = 0;
    delete this->array;
    this->array = new BitContainerType;
    this->array[0] = 0;
}

//Добавляет новый бит в конец массива. В случае необходимости
//происходит перераспределение памяти.
void BitArray::push_back(bool bit) {

}

//Битовые операции над массивами.
//Работают только на массивах одинакового размера.
//Обоснование реакции на параметр неверного размера входит в задачу.
BitArray &BitArray::operator&=(const BitArray &b) {
    return *this;
}

BitArray &BitArray::operator|=(const BitArray &b) {
    return *this;
}

BitArray &BitArray::operator^=(const BitArray &b) {
    return *this;
}

//Битовый сдвиг с заполнением нулями.
BitArray &BitArray::operator<<=(int n) {
    return *this;
}

BitArray &BitArray::operator>>=(int n) {
    return *this;
}

BitArray BitArray::operator<<(int n) const {
    return BitArray();
}

BitArray BitArray::operator>>(int n) const {
    return BitArray();
}

//Устанавливает бит с индексом n в значение val.
BitArray &BitArray::set(int n, bool val) {
    BitContainerType container = this->array[bitsToBytes(n + 1) - 1];
    int delta = sizeof(BitContainerType)*8 - (n % (sizeof(BitContainerType)*8)) - 1;
    container = (container & ~((BitContainerType)1 << delta)) | ((BitContainerType)val << delta);
    this->array[bitsToBytes(n + 1) - 1] = container;
    return *this;
}

//Заполняет массив истиной.
BitArray &BitArray::set() {
    int size = bitsToBytes(this->capacity);
    for (int i = 0; i < size; i++) {
        this->array[i] = ~0;
    }
    return *this;
}

//Устанавливает бит с индексом n в значение false.
BitArray &BitArray::reset(int n) {
    this->set(n, false);
    return *this;
}

//Заполняет массив ложью.
BitArray &BitArray::reset() {
    int size = bitsToBytes(this->capacity);
    for (int i = 0; i < size; i++) {
        this->array[i] = 0;
    }
    return *this;
}

//true, если массив содержит истинный бит.
bool BitArray::any() const {
    for (int i = 0; i < this->size(); i++) {
        if (this->operator[](i)) return true;
    }
    return false;
}

//true, если все биты массива ложны.
bool BitArray::none() const {
    for (int i = 0; i < this->size(); i++) {
        if (this->operator[](i)) return false;
    }
    return true;
}

//Битовая инверсия
BitArray BitArray::operator~() const {
    BitArray b(this->size());
    for (int i = 0; i < this->size(); i++) {
        b.set(i, !this->operator[](i));
    }
    return b;
}

//Подсчитывает количество единичных бит.
int BitArray::count() const {
    int amount = 0;
    for (int i = 0; i < this->size(); i++) {
        if (this->operator[](i)) {
            amount += 1;
        }
    }
    return amount;
}

//Возвращает значение бита по индексу i.
bool BitArray::operator[](int i) const {
    BitContainerType container = this->array[bitsToBytes(i + 1) - 1]; // 0
    int containerIndex = i % (sizeof(BitContainerType)*8);
    return (container & (1 << (sizeof(BitContainerType)*8 - containerIndex - 1))) != 0;
}

int BitArray::size() const {
    return this->amountOfBits;
}

bool BitArray::empty() const {
    return this->size() == 0;
}

//Возвращает строковое представление массива.
std::string BitArray::to_string() const {
    std::string string;
    for (int i = 0; i < this->size(); i++) {
        string += ((this->operator[](i))?"1":"0");
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
