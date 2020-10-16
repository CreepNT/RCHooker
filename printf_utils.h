#ifndef _CREEPNT_PRINTF_UTILS
#define _CREEPNT_PRINTF_UTILS

#include <psp2/kernel/clib.h>

#define MODULE_NAME "RCHooker"
#define BRACKETED_MODULE_NAME "["MODULE_NAME"]"

#define dbg_print(fmt,...) sceClibPrintf(BRACKETED_MODULE_NAME"DEBUG - "fmt"\n", ##__VA_ARGS__)
#define print_error(fmt,...) sceClibPrintf(BRACKETED_MODULE_NAME"ERROR - "fmt"\n", ##__VA_ARGS__)
#define print_error_ex(fmt,...) sceClibPrintf(BRACKETED_MODULE_NAME"ERROR in function %s (File : %s, line %d) :\n  "fmt"\n", __func__, __FILE__, __LINE__, ##__VA_ARGS__)
#define log_startup() sceClibPrintf(BRACKETED_MODULE_NAME"(DEBUG BUILD) Module starting...\n")
#define log_stopping() sceClibPrintf(BRACKETED_MODULE_NAME"module stopping...\n")

#endif