//
// Created by Just on 02.12.2023.
//

#ifndef TASK_3_SAMPLE_H
#define TASK_3_SAMPLE_H

#include <cstdint>
#include <fstream>

#define SIGN_DELTA 32768

class Sample {
    typedef char Byte;
private:
    uint16_t size;
    Byte* data;
public:
    ~Sample();
    Sample();
    Sample(const Sample& otherSample);
    explicit Sample(uint16_t size);

    Byte& operator[](int i);

    Sample& operator=(const Sample& otherSample);

    uint16_t getSize() const;

    Sample& saveAsInt(int16_t value);
    int16_t getAsInt();

    void read(std::ifstream& stream);
    void write(std::ofstream& stream);
};
#endif //TASK_3_SAMPLE_H
