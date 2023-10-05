//
// Created by Just on 05.10.2023.
//

#include "CircularBuffer.h"
#include <stdexcept>

CircularBuffer::CircularBuffer() {
    _capacity = 10;
    buffer = new value_type [_capacity];
}

CircularBuffer::~CircularBuffer() {
    delete[] buffer;
}

CircularBuffer::CircularBuffer(const CircularBuffer &cb) {
    _capacity = cb.capacity();
    buffer = new value_type [_capacity];
    for (int i = 0; i < cb.size(); i++) {
        buffer[i] = cb[i];
    }
}

CircularBuffer::CircularBuffer(int capacity) {
    _capacity = capacity;
    buffer = new value_type [capacity];
}

CircularBuffer::CircularBuffer(int capacity, const value_type &elem) {
    _capacity = capacity;
    buffer = new value_type [capacity];
    for (int i = 0; i < capacity; ++i) {
        buffer[i] = elem;
    }
}

value_type &CircularBuffer::operator[](int i) {
    return buffer[i];
}

const value_type &CircularBuffer::operator[](int i) const {
    return buffer[i];
}

value_type &CircularBuffer::at(int i) {
    if (i < 0 || i > this->size()) {
        throw std::out_of_range("Index is out of range.");
    }
    return buffer[i];
}

const value_type &CircularBuffer::at(int i) const {
    if (i < 0 || i > this->size()) {
        throw std::out_of_range("Index is out of range.");
    }
    return buffer[i];
}

value_type &CircularBuffer::front() {
    return *buffer;
}

value_type &CircularBuffer::back() {
    return *(buffer + this->size());
}

const value_type &CircularBuffer::front() const {
    return *buffer;
}

const value_type &CircularBuffer::back() const {
    return *(buffer + this->size());
}

value_type *CircularBuffer::linearize() {
    return nullptr;
}

bool CircularBuffer::is_linearized() const {
    return false;
}

void CircularBuffer::rotate(int new_begin) {

}

int CircularBuffer::size() const {
    return this->_size;
}

bool CircularBuffer::empty() const {
    return this->size() == 0;
}

bool CircularBuffer::full() const {
    return this->size() == this->capacity();
}

int CircularBuffer::reserve() const {
    return this->capacity() - this->size();
}

int CircularBuffer::capacity() const {
    return this->_capacity;
}

void CircularBuffer::set_capacity(int new_capacity) {

}

void CircularBuffer::resize(int new_size, const value_type &item) {

}

CircularBuffer &CircularBuffer::operator=(const CircularBuffer &cb) {
    return *this;
}

void CircularBuffer::swap(CircularBuffer &cb) {

}

void CircularBuffer::push_back(const value_type &item) {

}

void CircularBuffer::push_front(const value_type &item) {

}

void CircularBuffer::pop_back() {

}

void CircularBuffer::pop_front() {

}

void CircularBuffer::insert(int pos, const value_type &item) {

}

void CircularBuffer::erase(int first, int last) {

}

void CircularBuffer::clear() {

}
