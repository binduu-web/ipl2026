#include <stdio.h>
#include <stdint.h>

// Print bits of an integer
void printBits(unsigned int n) {
    for (int i = sizeof(n) * 8 - 1; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
    printf("\n");
}

// Count number of 1 bits
int countOnes(unsigned int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// Check endianness
void checkEndianness() {
    unsigned int x = 0x12345678;
    unsigned char *p = (unsigned char*)&x;
    printf("Stored bytes: ");
    for (int i = 0; i < sizeof(x); i++) {
        printf("%02x ", p[i]);
    }
    printf("\n");
    if (p[0] == 0x78) {
        printf("Little Endian\n");
    } else {
        printf("Big Endian\n");
    }
}

// Print bits of a float (IEEE 754)
void printFloatBits(float f) {
    unsigned int *p = (unsigned int*)&f;
    printBits(*p);
}

int main() {
    unsigned int n = 29; // example integer
    printf("Bits of %u: ", n);
    printBits(n);
    printf("Number of 1s: %d\n", countOnes(n));

    int neg = -29;
    printf("Bits of %d: ", neg);
    printBits((unsigned int)neg);

    checkEndianness();

    float f = -3.5;
    printf("Bits of %f: ", f);
    printFloatBits(f);

    return 0;
}
