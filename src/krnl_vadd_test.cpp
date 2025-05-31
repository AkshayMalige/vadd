// File: tb_vadd.cpp

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include "krnl_vadd.h"
// DATA_SIZE must match the kernel's DATA_SIZE (4096)


int main() {
    // 1) Allocate three arrays of length DATA_SIZE
    static uint32_t in1[DATA_SIZE];
    static uint32_t in2[DATA_SIZE];
    static uint32_t out[DATA_SIZE];

    // 2) Initialize input arrays with test values
    //    For example: in1[i] = i, in2[i] = 2*i
    for (int i = 0; i < DATA_SIZE; i++) {
        in1[i] = (uint32_t)i;
        in2[i] = (uint32_t)(2 * i);
        out[i] = 0;  // zero‐initialize output buffer
    }

    // 3) Call the HLS kernel
    krnl_vadd(in1, in2, out, DATA_SIZE);

    // 4) Verify results
    bool all_ok = true;
    for (int i = 0; i < DATA_SIZE; i++) {
        uint32_t expected = in1[i] + in2[i];
        if (out[i] != expected) {
            std::cout << "Mismatch at index " << i
                      << ": expected=" << expected
                      << ", got=" << out[i] << std::endl;
            all_ok = false;
            // If you want to stop on first error, uncomment:
            // break;
        }
    }

    // 5) Print final PASS/FAIL
    if (all_ok) {
        std::cout << "=== Test PASSED: All " << DATA_SIZE
                  << " results matched ===" << std::endl;
        return EXIT_SUCCESS;
    } else {
        std::cout << "=== Test FAILED ===" << std::endl;
        return EXIT_FAILURE;
    }
}
