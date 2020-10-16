#include "hooks.h"

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