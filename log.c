#include "log.h"
#include "structs.h"
#include <psp2/kernel/clib.h>

#define println(fmt, ...) sceClibPrintf(fmt"\n",##__VA_ARGS__)
#define println_vec3(fmt, vec3) sceClibPrintf(fmt); log_Vec3(vec3); sceClibPrintf("\n")
#define println_vec4(fmt, vec4) sceClibPrintf(fmt); log_Vec4(vec4); sceClibPrintf("\n")

/**
 * @brief Prints the content of a memory range to the console
 * 
 * @param start Start address
 * @param len Number of bytes to print
 */
void LogMemoryRange(void* start, size_t len) {
    if (start == NULL || !len) return;

    uint8_t* ptr = (uint8_t*)start;
    size_t qqwordsDumpNum = len / 32; //Number of quad-qwords (4 * 8-byte = 32-byte "words") to dump
    size_t remainingLen = len - (qqwordsDumpNum * 32); //Remaining amount of bytes

    sceClibPrintf("Going to dump %d bytes (expected %d) starting at address 0x%08X.\n", qqwordsDumpNum*32 + remainingLen, len, (uintptr_t)ptr);

    //First, print all qqwords
    size_t curOffset = 0;
    for (size_t i = 0; i < qqwordsDumpNum; i++, curOffset += 32){
        sceClibPrintf("0x%08X : %02hhX%02hhX%02hhX%02hhX %02hhX%02hhX%02hhX%02hhX %02hhX%02hhX%02hhX%02hhX %02hhX%02hhX%02hhX%02hhX\n",
            (uintptr_t)&ptr[curOffset], ptr[curOffset], ptr[curOffset+1], ptr[curOffset+2], ptr[curOffset+3], ptr[curOffset+4], ptr[curOffset+5], ptr[curOffset+6], ptr[curOffset+7],
            ptr[curOffset+8], ptr[curOffset+9], ptr[curOffset+10], ptr[curOffset+11], ptr[curOffset+12], ptr[curOffset+13], ptr[curOffset+14], ptr[curOffset+15],
            ptr[curOffset+16], ptr[curOffset+17], ptr[curOffset+18], ptr[curOffset+19], ptr[curOffset+20], ptr[curOffset+21], ptr[curOffset+22], ptr[curOffset+23],
            ptr[curOffset+24], ptr[curOffset+25], ptr[curOffset+26], ptr[curOffset+27], ptr[curOffset+28], ptr[curOffset+29], ptr[curOffset+30], ptr[curOffset+31]
        );
    }

    //Then, print the remaining bytes
    sceClibPrintf("0x%08X : ", (uintptr_t)&ptr[curOffset]);
    for (size_t i = 0; i < remainingLen; i++, curOffset++){
        sceClibPrintf("%02hhX", ptr[curOffset + i]);
        if ((curOffset+1) % 4) sceClibPrintf(" ");
    }
    sceClibPrintf("\n");
}