#ifndef __LOG_H
#define __LOG_H
#include "structs.h"

#define println(fmt, ...) sceClibPrintf(fmt"\n",##__VA_ARGS__)
#define println_vec3(fmt, vec3) sceClibPrintf(fmt); log_Vec3(vec3); sceClibPrintf("\n")
#define println_vec4(fmt, vec4) sceClibPrintf(fmt); log_Vec4(vec4); sceClibPrintf("\n")

void log_moby_data(Moby* pMoby);
void log_moby_data_RAW(Moby* pMoby);
void log_Vec4(Vec4* pVec);
void log_Vec3(Vec3* pVec);
// len : number of bytes to dump
void dump_pVars(void* pVars, unsigned int len);

#endif