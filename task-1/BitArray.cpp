//
// Created by Just on 19.10.2023.
//

#include <iostream>
#include "BitArray.h"

BitArray::BitArray() {
    this->array = new BitContainerType;
    this->clear();
}

BitArray::~BitArray() {
    delete this->array;
}

//Конструирует массив, хранящий заданное количество бит.
//Первые sizeof(long) бит можно инициализровать с помощью параметра value.
BitArray::BitArray(int num_bits, unsigned long value) {
    this->array = new BitContainerType[num_bits / sizeof(BitContainerType)
                                         + ((num_bits % sizeof(BitContainerType))? 1: 0)];
    int last_ind = num_bits - 1;
    for (int i = last_ind; i >= 0; i--) {
        bool bit = value % 2;
        value = value >> 1;
        this->set(i, bit);
    }
}

BitArray::BitArray(const BitArray &b) {
    int num_bits = b.size();
    this->array = new BitContainerType[num_bits / sizeof(BitContainerType)
                                       + ((num_bits % sizeof(BitContainerType))? 1: 0)];
    for (int i = 0; i < b.size(); i++) {
        this->set(i, b[i]);
    }
}

void BitArray::swap(BitArray &b) {

}

BitArray &BitArray::operator=(const BitArray &b) {
    return *this;
}

//Изменяет размер массива. В случае расширения, новые элементы
//инициализируются значением value.
void BitArray::resize(int num_bits, bool value) {

}

//Очищает массив.
void BitArray::clear() {

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
    return *this;
}

//Заполняет массив истиной.
BitArray &BitArray::set() {
    return *this;
}

//Устанавливает бит с индексом n в значение false.
BitArray &BitArray::reset(int n) {
    return *this;
}

//Заполняет массив ложью.
BitArray &BitArray::reset() {
    return *this;
}

//true, если массив содержит истинный бит.
bool BitArray::any() const {
    return false;
}

//true, если все биты массива ложны.
bool BitArray::none() const {
    return false;
}

//Битовая инверсия
BitArray BitArray::operator~() const {
    return BitArray();
}

//Подсчитывает количество единичных бит.
int BitArray::count() const {
    return 0;
}

//Возвращает значение бита по индексу i.
bool BitArray::operator[](int i) const {
    return false;
}

int BitArray::size() const {
    return 0;
}

bool BitArray::empty() const {
    return false;
}

//Возвращает строковое представление массива.
std::string BitArray::to_string() const {
    return std::string();
}
