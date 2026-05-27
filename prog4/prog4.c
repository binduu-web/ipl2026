#include <stdio.h>
#include <stdint.h>

// Define a structure with bitfields
struct Bitfield {
    unsigned int firstbit : 1;   // 1 bit for firstbit
    unsigned int secondbit : 1;  // 1 bit for secondbit
    unsigned int rest : 30;      // remaining 30 bits in a 32-bit int
};

int main() {
    struct Bitfield a;
    
    // Initialize the bitfield
    a.firstbit = 1;
    a.secondbit = 0;
    a.rest = 0;
    
    // Print the value of firstbit
    printf("a.firstbit = %u\n", a.firstbit);
    
    // Print the entire structure size and contents
    printf("Structure size: %zu bytes\n", sizeof(a));
    printf("Structure contents (hex): ");
    unsigned char *p = (unsigned char *)&a;
    for (size_t i = 0; i < sizeof(a); i++) {
        printf("%02X ", p[i]);
    }
    printf("\n");
    
    // Test setting firstbit to 0
    a.firstbit = 0;
    printf("After setting to 0, a.firstbit = %u\n", a.firstbit);
    
    // Test setting firstbit back to 1
    a.firstbit = 1;
    printf("After setting back to 1, a.firstbit = %u\n", a.firstbit);
    
    // Test multiple bits
    a.secondbit = 1;
    printf("After setting secondbit=1: firstbit=%u, secondbit=%u\n", 
           a.firstbit, a.secondbit);
    
    return 0;
}