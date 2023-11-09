//
// Created by Just on 19.10.2023.
//

#ifndef INC_22202_ROZHKOV_OOP_CPP_TASK_1_BITARRAY_H
#define INC_22202_ROZHKOV_OOP_CPP_TASK_1_BITARRAY_H


#include <string>

class BitArray {
    typedef unsigned char BitContainerType;
private:
    BitContainerType* array;
    int amountOfBits;
    int capacity;

    /**
    * Convert the number of bits to the number of bytes that can contain them.
    *
    * @param amountOfBits - the number of bits we need to convert.
    * @return Converted number of bytes.
    */
    static int bitsToBytes(int amountOfBits);
    /**
    * Convert the number of bytes to the number of bits contained within them.
    *
    * @param amountOfBytes - the number of bits we need to convert.
    * @return Converted number of bites.
    */
    static int bytesToBits(int amountOfBytes);

    /**
     * The implementation of wrapper that is used when index operator is called.
     * We use this wrapper to save the pointer to original BitArray container and later get or set the bit with given index.
     * */
    class Wrapper {
    private:
        BitArray* array;
        int index;
    public:
        /**
         * Generates Wrapper object on index operator of BitArray.
         * @see BitArray::Wrapper BitArray::operator[] (int i)
         * */
        Wrapper(BitArray* arr, int ind);

        //Wrapper(const Wrapper& other);

        /**
         * Simple assignment operator.
         * We use this when we want to set new value to the BitArray on chosen index.
         * For example:
         *
         *      array[0] = true;
         *
         * @param value - the boolean representation of bit to set.
         * @return Pointer to itself.
         * */
        Wrapper& operator=(bool value);

        /**
         * Smart assignment operator.
         * We use this when we want to set new value to the BitArray on chosen index, while assigning the value of other bit from some BitArray.
         * For example:
         *
         *      firstArray[0] = secondArray[5];
         *
         * @param other - another Wrapper instance.
         * @return Pointer to itself.
         * */
        Wrapper& operator=(const Wrapper &other);

        /**
         * Bool operator.
         * We use this when we want to set new value to the BitArray on chosen index, while assigning the value of other bit from some BitArray.
         * For example:
         *
         *      fooOrBar = (array[1]) ? foo: bar;
         *
         * @return Boolean representation of bit with specified index.
         * */
        operator bool() const;
    };
public:
    /**
     * Simple BitArray constructor.
     * */
    BitArray();
    /**
     * Simple BitArray destructor.
     * We use that to free space that was dynamically allocated for the array.
     * */
    ~BitArray();

    /**
     * BitArray constructor with parameters.
     *
     * @param num_bits - the number of bits to allocate memory for.
     * @param value - a value that will be interpreted as a bit container for the first sizeof(long) bits (default = 0).
     * */
    explicit BitArray(int num_bits, unsigned long value = 0);
    /**
     * BitArray constructor for copying.
     *
     * @param b - BitArray instance to copy data from.
     * */
    BitArray(const BitArray& b);

    /**
     * Swaps data with provided BitArray instance
     *
     * @param b - BitArray instance to swap data with.
     * */
    void swap(BitArray& b);

    /**
     * Assign operator for BitArray.
     *
     * @param b - BitArray instance to copy data from.
     * @return Pointer to itself.
     * */
    BitArray& operator=(const BitArray& b);

    /**
     * Changes array size. If new size is bigger than previous,
     * new elements will be initialized with boolean representation of given value.
     *
     * @param num_bits - the number of bits to resize for.
     * @param value - boolean representation of bit to initialize new elements with (default = false).
     * */
    void resize(int num_bits, bool value = false);
    /**
     * Clears the array of bits.
     * Frees previously allocated memory and sets capacity to 0.
     * */
    void clear();
    /**
     * Push provided boolean representation of bit to the end of array.
     * If necessary, resizes array.
     *
     * @param bit - boolean representation of bit to push back.
     * */
    void push_back(bool bit);


    //Битовые операции над массивами.
    //Работают только на массивах одинакового размера.
    //Обоснование реакции на параметр неверного размера входит в задачу.
    /**
     * Assigning Bit AND operator
     * Applies bit AND to left and right values, then stores result
     * in lvalue BitArray instance.
     *
     * Both BitArrays must be of equal size. If not, throws std::length_error.
     *
     * @param b - BitArray instance to apply operator with.
     * @return Pointer to itself.
     * */
    BitArray& operator&=(const BitArray& b);
    /**
     * Assigning Bit OR operator
     * Applies bit OR to left and right values, then stores result
     * in lvalue BitArray instance.
     *
     * Both BitArrays must be of equal size. If not, throws std::length_error.
     *
     * @param b - BitArray instance to apply operator with.
     * @return Pointer to itself.
     * */
    BitArray& operator|=(const BitArray& b);
    /**
     * Assigning Bit XOR operator
     * Applies bit XOR to left and right values, then stores result
     * in lvalue BitArray instance.
     *
     * Both BitArrays must be of equal size. If not, throws std::length_error.
     *
     * @param b - BitArray instance to apply operator with.
     * @return Pointer to itself.
     * */
    BitArray& operator^=(const BitArray& b);

    //Битовый сдвиг с заполнением нулями.
    /**
     * Assigning Bit Left-Shift operator for BitArray.
     * Shifts bits inside of array to the left for specified amount of positions.
     * Freed spaces is filled with false bits (0).
     *
     * @param n - amount of positions to shift.
     * @return Pointer to itself.
     * */
    BitArray& operator<<=(int n);
    /**
     * Assigning Bit Right-Shift operator for BitArray.
     * Shifts bits inside of array to the right for specified amount of positions.
     * Freed spaces is filled with false bits (0).
     *
     * @param n - amount of positions to shift.
     * @return Pointer to itself.
     * */
    BitArray& operator>>=(int n);
    /**
     * Bit Left-Shift operator for BitArray.
     * Shifts bits inside of array to the left for specified amount of positions.
     * Freed spaces is filled with false bits (0).
     *
     * @param n - amount of positions to shift.
     * @return New BitArray instance with result.
     * */
    BitArray operator<<(int n) const;
    /**
     * Bit Right-Shift operator for BitArray.
     * Shifts bits inside of array to the right for specified amount of positions.
     * Freed spaces is filled with false bits (0).
     *
     * @param n - amount of positions to shift.
     * @return New BitArray instance with result.
     * */
    BitArray operator>>(int n) const;

    /**
     * Sets bit with provided index to specified value.
     * If value is not specified, sets bit to true (1).
     *
     * @param n - index of bit to set value to.
     * @param val - value to set bit to (default = true).
     * @return Pointer to itself.
     * */
    BitArray& set(int n, bool val = true);
    /**
     * Sets all bits inside of array to true (1).
     *
     * @return Pointer to itself.
     * */
    BitArray& set();

    /**
     * Straightforward way to get value of bit with specified index.
     *
     * @param n - index of bit.
     * @return Boolean representation of bit with provided index.
     * */
    bool get(int n) const;

    /**
     * Sets bit with provided index to false (0).
     *
     * @param n - index of bit to set value to.
     * @return Pointer to itself.
     * */
    BitArray& reset(int n);
    /**
     * Sets all bits inside of array to false (0).
     *
     * @param n - index of bit to set value to.
     * @return Pointer to itself.
     * */
    BitArray& reset();

    /**
     * @return True if there is at least one bit in array is true.
     * */
    bool any() const;
    /**
     * @return True if all bits in array are false.
     * */
    bool none() const;
    /**
     * Inverting operator for BitArray.
     *
     * @return New BitArray instance with result.
     * */
    BitArray operator~() const;
    /**
     * Counts number of bits with value of true.
     *
     * @return Int number of bits with value of true.
     * */
    int count() const;

    /**
     * Index operator for BitArray.
     *
     * @return New Wrapper instance with specified index and pointer to array
     * */
    Wrapper operator [](int i);

    /**
     * @return Number of bits stored inside.
     * */
    int size() const;
    /**
     * @return True, if array is empty.
     * */
    bool empty() const;

    /**
     * @return String representation of this BitArray instance.
     * */
    std::string to_string() const;
};


/**
 * Equality operator for BitArrays.
 * Firstly compares sizes of both instances.
 * Then, is sizes are same, checks each bit inside.
 *
 * @param a - BitArray instance to compare.
 * @param b - BitArray instance to compare.
 * @return True, if a and b are equal.
 * */
bool operator==(const BitArray & a, const BitArray & b);
/**
 * NonEquality operator for BitArrays.
 * Simply inverts result of equality operator.
 *
 * @see operator==(const BitArray & a, const BitArray & b)
 *
 * @param a - BitArray instance to compare.
 * @param b - BitArray instance to compare.
 * @return True, if a and b are not equal.
 * */
bool operator!=(const BitArray & a, const BitArray & b);

/**
 * Bit AND operator for BitArray.
 * Works only on arrays of same size.
 *
 * @param b - instance of BitArray to use AND operator with.
 * @return New BitArray instance with the result of AND operation.
 * */
BitArray operator&(const BitArray& b1, const BitArray& b2);
/**
 * Bit OR operator for BitArray.
 * Works only on arrays of same size.
 *
 * @param b - instance of BitArray to use OR operator with.
 * @return New BitArray instance with the result of OR operation.
 * */
BitArray operator|(const BitArray& b1, const BitArray& b2);
/**
 * Bit XOR operator for BitArray.
 * Works only on arrays of same size.
 *
 * @param b - instance of BitArray to use XOR operator with.
 * @return New BitArray instance with the result of XOR operation.
 * */
BitArray operator^(const BitArray& b1, const BitArray& b2);



#endif //INC_22202_ROZHKOV_OOP_CPP_TASK_1_BITARRAY_H
