//
// Created by Just on 19.10.2023.
//

#include "BitArray.h"

BitArray::BitArray() {

}

BitArray::~BitArray() {

}

//Конструирует массив, хранящий заданное количество бит.
//Первые sizeof(long) бит можно инициализровать с помощью параметра value.
BitArray::BitArray(int num_bits, unsigned long value) {

}

BitArray::BitArray(const BitArray &b) {

}

void BitArray::swap(BitArray &b) {

}

BitArray &BitArray::operator=(const BitArray &b) {
    return <#initializer#>;
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
    return <#initializer#>;
}

BitArray &BitArray::operator|=(const BitArray &b) {
    return <#initializer#>;
}

BitArray &BitArray::operator^=(const BitArray &b) {
    return <#initializer#>;
}

//Битовый сдвиг с заполнением нулями.
BitArray &BitArray::operator<<=(int n) {
    return <#initializer#>;
}

BitArray &BitArray::operator>>=(int n) {
    return <#initializer#>;
}

BitArray BitArray::operator<<(int n) const {
    return BitArray();
}

BitArray BitArray::operator>>(int n) const {
    return BitArray();
}

//Устанавливает бит с индексом n в значение val.
BitArray &BitArray::set(int n, bool val) {
    return <#initializer#>;
}

//Заполняет массив истиной.
BitArray &BitArray::set() {
    return <#initializer#>;
}

//Устанавливает бит с индексом n в значение false.
BitArray &BitArray::reset(int n) {
    return <#initializer#>;
}

//Заполняет массив ложью.
BitArray &BitArray::reset() {
    return <#initializer#>;
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
