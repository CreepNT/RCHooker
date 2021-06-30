#ifndef __COMMON_H
#define __COMMON_H

#include "log.h"
#include <stdbool.h>
#include <taihen.h>

#define TAI_ERROR_NOT_FOUND 0x90010002
#define TAI_ERROR_HOOK_ERROR 0x90010006

enum GameType{
    //Game types
    RC1_BIT = 1 << 0,   //If this bit is set, the current game is R&C 1
    RC2_BIT = 1 << 1,   //If this bit is set, the current game is R&C 2
    RC3_BIT = 1 << 2,   //If this bit is set, the current game is R&C 3
    RCC_BIT = 1 << 3,   //If this bit is set, the current game is the R&C Collection (game selection menu)

    //Region
    US_REGION_BIT = 1 << 4,     //If this bit is set, the current game is from the american region
    PAL_REGION_BIT = 1 << 5,    //If this bit is set, the current game is from the european region

    //Misc.
    IS_COLLECTION_BIT = 1 << 6, //If this bit is set, the current game is running in the context of the collection

    //SKUs
    SKU_RC1_PAL = RC1_BIT | PAL_REGION_BIT,
    SKU_RC2_PAL = RC2_BIT | PAL_REGION_BIT,
    SKU_RC3_PAL = RC3_BIT | PAL_REGION_BIT,
    SKU_RCC_US  = RCC_BIT | US_REGION_BIT | IS_COLLECTION_BIT,
    SKU_RCC_PAL = RCC_BIT | PAL_REGION_BIT | IS_COLLECTION_BIT,

    //Convenient constants
    US_COLLECTION = US_REGION_BIT | IS_COLLECTION_BIT,
    PAL_COLLECTION = PAL_REGION_BIT | IS_COLLECTION_BIT,

    GAME_UNKNOWN = ~(RC1_BIT | RC2_BIT | RC3_BIT | US_REGION_BIT | PAL_REGION_BIT | IS_COLLECTION_BIT) //No valid bits set
} GameType;

#define HOOK_UID(func_name)         func_name ##_hook_UID
#define HOOK_REFERENCE(func_name)   func_name ##_hook_reference
#define HOOK_FUNCTION(func_name)    func_name ##_hook_function

#ifdef __INTELLISENSE__
#define FAKE_VARIABLE(x) unsigned x
#else
#define FAKE_VARIABLE(...)
#endif

/**
 * @brief Helper macro to create hooks
 * @param type Return type of the function
 * @param func_name Original function's name
 * @param ... Arguments the function takes
 * @note Add brackets after the macro, contents of the brackets are the hook function's body
 */
#define DeclareHook(type, func_name, ...)           \
    static SceUID HOOK_UID(func_name);              \
    static tai_hook_ref_t HOOK_REFERENCE(func_name);\
    FAKE_VARIABLE(func_name);                       \
    type HOOK_FUNCTION(func_name) (__VA_ARGS__)     



/**
 * @brief Helper macro to add hooks
 * 
 * @param modID UID of the module the hooked function is located in
 * @param segment Segment in which the hooked function is located
 * @param offset Offset in segment where the hooked function is located
 * @param thumb 1 if Thumb code, 0 if ARM code
 * @param func_name Original function's name
 */
#define HookAtOffset(modID, segment, offset, thumb, func_name) \
    HOOK_UID(func_name) = taiHookFunctionOffset(&HOOK_REFERENCE(func_name), modID, segment, offset, thumb, HOOK_FUNCTION(func_name)); \
    if (HOOK_UID(func_name) < 0) LOG_ERROR("taiHookFunctionOffset returned 0x%08X hooking function '" #func_name "' !", HOOK_UID(func_name))


/**
 * @brief Helper macro to release hooks
 * 
 * @param func_name Original function's name
 */
#define ReleaseHook(func_name)\
    if (HOOK_UID(func_name) > 0) taiHookRelease(HOOK_UID(func_name), HOOK_REFERENCE(func_name))


/**
 * @brief Get the address of a segement:offset location
 * 
 * @param module_UID UID of the module in which the segement:offset should be resolved
 * @param segment Segment in which target is located (0-3)
 * @param offset Offset in chosen segment in which target is located
 * @param out_address Pointer to a variable that will recieve the resolved address on success (should be pointer-sized)
 * @return 0 on success, < 0 on error
 */
int Module_GetAddressForOffset(SceUID module_UID, unsigned segment, unsigned offset, void* out_address);

/**
 * @brief Get a string describing what a certain value corresponds to
 * 
 * @param code Either a GameID or a HookXXX error
 * @return NULL on failure, pointer to the string on success
 */
char* GetDescriptiveStringForCode(unsigned code);
#endif