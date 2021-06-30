#ifndef __LOG_H
#define __LOG_H
#include "structs.h"
#include <psp2/kernel/clib.h> //sceClibPrintf

#define LOG_ERROR(fmt, ...) sceClibPrintf( ANSI_BOLD ANSI_RED "ERROR : " ANSI_REGULAR_SIZE fmt ANSI_RESET "\n", ##__VA_ARGS__)

#define println(fmt, ...) sceClibPrintf(fmt"\n",##__VA_ARGS__)
#define println_vec3(fmt, vec3) sceClibPrintf(fmt); log_Vec3(vec3); sceClibPrintf("\n")
#define println_vec4(fmt, vec4) sceClibPrintf(fmt); log_Vec4(vec4); sceClibPrintf("\n")

#ifndef DISABLE_ANSI
//Changes foreground color
#define ANSI_BLACK              "\x1b[30m"
#define ANSI_RED                "\x1b[31m"
#define ANSI_GREEN              "\x1b[32m"
#define ANSI_YELLOW             "\x1b[33m"
#define ANSI_BLUE               "\x1b[34m"
#define ANSI_MAGENTA            "\x1b[35m"
#define ANSI_CYAN               "\x1b[36m"
#define ANSI_WHITE              "\x1b[37m"

//Changes background color
#define ANSI_BG_BLACK           "\x1b[40m"
#define ANSI_BG_RED             "\x1b[41m"
#define ANSI_BG_GREEN           "\x1b[42m"
#define ANSI_BG_YELLOW          "\x1b[43m"
#define ANSI_BG_BLUE            "\x1b[44m"
#define ANSI_BG_MAGENTA         "\x1b[45m"
#define ANSI_BG_CYAN            "\x1b[46m"
#define ANSI_BG_WHITE           "\x1b[47m"

#define ANSI_RESET              "\x1b[0m"
#define ANSI_BOLD               "\x1b[1m"
#define ANSI_FAINT              "\x1b[2m"    //Dimmed color / light weight font
#define ANSI_ITALIC             "\x1b[3m"    //Not widely supported, according to Wikipedia
#define ANSI_UNDERLINE          "\x1b[4m"
#define ANSI_INVERT             "\x1b[7m"    //Swap background and foreground color
#define ANSI_REGULAR_SIZE       "\x1b[22m"   //Disables bold, faint and italic
#define ANSI_UNDERLINE_OFF      "\x1b[24m"   //Disables underline
#define ANSI_INVERT_OFF         "\x1b[27m"   //Disables invertion

//Only supported in certain terminals. 0 <= r,g,b <= 255
#define ANSI_RGB(r, g ,b)            "\u001b[38;5;"#r";"#g";"#b"m"
#define ANSI_BG_RGB(r, g ,b)         "\u001b[48;5;"#r";"#g";"#b"m"
#define ANSI_UNDERLINE_RGB(r, g ,b)  "\u001b[58;5;"#r";"#g";"#b"m"
#define ANSI_RESET_UNDERLINE         "\u001b[59"

#else //DISABLE_ANSI
/Changes foreground color
#define ANSI_BLACK  
#define ANSI_RED    
#define ANSI_GREEN  
#define ANSI_YELLOW 
#define ANSI_BLUE   
#define ANSI_MAGENTA
#define ANSI_CYAN   
#define ANSI_WHITE  

//Changes background color
#define ANSI_BG_BLACK  
#define ANSI_BG_RED    
#define ANSI_BG_GREEN  
#define ANSI_BG_YELLOW 
#define ANSI_BG_BLUE   
#define ANSI_BG_MAGENTA
#define ANSI_BG_CYAN   
#define ANSI_BG_WHITE  

#define ANSI_RESET              
#define ANSI_BOLD               
#define ANSI_FAINT                  
#define ANSI_ITALIC                 
#define ANSI_UNDERLINE          
#define ANSI_INVERT  
#define ANSI_REGULAR_SIZE          
#define ANSI_UNDERLINE_OFF         
#define ANSI_INVERT_OFF            

#define ANSI_RGB(r, g ,b)            
#define ANSI_BG_RGB(r, g ,b)         
#define ANSI_UNDERLINE_RGB(r, g ,b)  
#define ANSI_RESET_UNDERLINE         
#endif
//TODO : add macros for cursor navigation ?

#define LogVec3(vec3) sceClibPrintf("%.3f, %.3f, %.3f", vec3.x, vec3.y, vec3.z)
#define LogVec4(vec4) sceClibPrintf("%.3f, %.3f, %.3f", vec4.x, vec4.y, vec4.z, vec4.w)

/**
 * @brief Prints the content of a memory range to the console
 * 
 * @param start Start address
 * @param len Number of bytes to print
 */
void LogMemoryRange(void* start, size_t len);

#define LogMobyRaw(pMoby) LogMemoryRange(pMoby, 0x100)

#endif