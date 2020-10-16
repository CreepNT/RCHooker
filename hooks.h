#ifndef __HOOKS_H
#define __HOOKS_H

#include <taihen.h> //For NULL macro

typedef struct s{
    unsigned int segment;   //Segment in binary (see Ghidra)
    unsigned int offset;    //Offset in segment (see Ghidra)
    unsigned int thumb;     //0 for ARM code, 1 for Thumb code
    void* function;         //Pointer to the function pointer
} offset_struct;

//Put your function pointers under here
static void(*guiDrawText)(int posX, int posY, unsigned int colour, unsigned int unk, char * text, int param_6) = NULL;

offset_struct offsets[] = {
    {
        .segment = 0,
        .offset = 0x9A5558,
        .thumb = 1,
        .function = &guiDrawText
    }
};

#endif