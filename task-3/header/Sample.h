//
// Created by Just on 02.12.2023.
//

#ifndef TASK_3_SAMPLE_H
#define TASK_3_SAMPLE_H

#include <cstdint>
#include <fstream>

#define SAMPLE_SIZE sizeof(int16_t)

class Sample {
    typedef char Byte;
private:
    uint16_t size;
    Byte* data;
    bool loaded;
public:
    ~Sample();
    Sample();
    Sample(const Sample& otherSample);

    Byte& operator[](int i);

    Sample& operator=(const Sample& otherSample);

    uint16_t getSize() const;

    Sample& saveAsInt(int16_t value);
    int16_t getAsInt();

    bool isLoaded() const;
    void markLoad(bool isLoaded);
};
#endif //TASK_3_SAMPLE_H
