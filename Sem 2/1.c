#include <stdio.h>

int main() 
{
    // Bitwise AND (&): Performs a bitwise AND operation on each bit of the operands.
    // Sets a bit in the result if the corresponding bits in both operands are set.
    int a = 60;   // 60 = 0011 1100
    int b = 13;   // 13 = 0000 1101
    int result_and = a & b;  // 12 = 0000 1100
    printf("AND: %d\n", result_and);

    // Bitwise OR (|): Performs a bitwise OR operation on each bit of the operands.
    // Sets a bit in the result if the corresponding bits in either operand are set.
    int result_or = a | b;  // 61 = 0011 1101
    printf("OR: %d\n", result_or);

    // Bitwise XOR (^): Performs a bitwise XOR (exclusive OR) operation on each bit of the operands.
    // Sets the bit in the result if only one of the corresponding bits in the operands is set.
    int result_xor = a ^ b;  // 49 = 0011 0001
    printf("XOR: %d\n", result_xor);

    // Bitwise NOT (~): Performs a bitwise NOT (complement) operation on each bit of the operand.
    // Flips each bit (0 to 1 and 1 to 0).
    int result_not = ~a;  // -61 = 1100 0011
    printf("NOT: %d\n", result_not);

    // Bitwise left shift (<<): Shifts the bits of the first operand to the left by the number of positions specified by the second operand.
    // Zeros are shifted in from the right.
    int result_left_shift = a << 2;  // 240 = 1111 0000
    printf("Left Shift: %d\n", result_left_shift);

    // Bitwise right shift (>>): Shifts the bits of the first operand to the right by the number of positions specified by the second operand.
    // The empty positions are filled with zeros if the first operand is unsigned, and with the sign bit if it's signed.
    int result_right_shift = a >> 2;  // 15 = 0000 1111
    printf("Right Shift: %d\n", result_right_shift);

    return 0;
}