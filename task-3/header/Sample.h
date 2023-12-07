//
// Created by Just on 02.12.2023.
//

#ifndef TASK_3_SAMPLE_H
#define TASK_3_SAMPLE_H

#include <cstdint>
#include <fstream>

class Sample {
    typedef char Byte;
private:
    uint16_t size;
    Byte* data;

    static void writeByte(std::ofstream& stream, Byte value);
public:
    ~Sample();
    explicit Sample(uint16_t size);

    //todo: operator[]
    //todo: operator=

    Sample& operator=(const Sample& otherSample);

    uint16_t getSize() const;

    void read(std::ifstream& stream);
    void write(std::ofstream& stream);
};
#endif //TASK_3_SAMPLE_H
