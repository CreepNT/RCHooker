
#include "common.h"
#include "log.h"

/**
 * @brief Wrapper for Module_GetAddressForOffset
 * 
 * @param segment Segment in which target is located (0-3)
 * @param offset Offset in chosen segment in which target is located
 * @param out Pointer to a variable that will recieve the resolved address on success (should be pointer-sized)
 */
#define GetAddressForOffset(segment, offset, out)                                                                                                       \
    do {                                                                                                                                                \
        int __rsvd_name = Module_GetAddressForOffset(game_modId, segement, offset, out);                                                                \
        if (__rsvd_name < 0) LOG_ERROR("Module_GetAddressForOffset returned 0x%08X when getting address of (%u:0x%X).\n", __rsvd_name, segment, offset);\
        else println("Resolved (%u:0x%X) to 0x%08X successfully !\n", segment, offset, (uintptr_t)*out);                                                                                                                               \
    } while(0)
/**
 * @brief Wrapper for Module_GetAddressForOffset
 * 
 * @param segment Segment in which target function is located (0-3)
 * @param offset Offset in chosen segment in which target function is located
 * @param thumb 1 if target function runs in Thumb mode, 0 if it runs in ARM mode
 * @param out Pointer to a variable that will recieve the resolved address on success (should be pointer-sized)
 */
#define GetFunctionAddressFromOffset(segment, offset, thumb, out) GetAddressForOffset(segement, offset | thumb, out)
/**
 * @brief Wrapper for HookAtOffset
 * 
 * @param segment Segment in which the hooked function is located
 * @param offset Offset in segment where the hooked function is located
 * @param thumb 1 if Thumb code, 0 if ARM code
 * @param func_name Original function's name
 */
#define HookOffset(seg, off, thumb, func) HookAtOffset(modId, seg, off, thumb, func)
/**
 * @brief Wrapper for TAI_NEXT
 * 
 * @param func_name Original function's name
 * @param ... Function arguments
 */
#define TAI_RUN_NEXT(func_name, ...) TAI_NEXT(HOOK_FUNCTION(func_name), HOOK_REFERENCE(func_name), __VA_ARGS__)

#include "custom_routines.h" //Include all definitions needed for here

/*
NOTE : in order to make macros autocompletion more pleasant, the DeclareHook macro will
declare a unsigned with the name specified as `func_name` in the macro. This is what the
other hook macros expect as `func_name` too, and will thus assit in autocomplete.

This declaration is guarded by a #ifdef __INTELLISENSE__ and is as such not present in
the code passed to the compiler : it's purely made to assist you when autocompleting if
using Visual Studio or VSCode. Do not assign or use that variable other than in the Hook macros.
*/

//Example hook : MB_Create
DeclareHook(void*, MB_Create, uint16_t oClass){

    //Call the original function
    void* ret = TAI_RUN_NEXT(MB_Create, oClass);

    //Do some logging
    println("MB_Create(%04hu) -> %p", oClass, ret); //This goes to stdout - install PSMLogUsb/PrincessLog to see it

    //Return to the original caller
    return ret;
}
//NOTE : taiHEN allows to have multiple hooks on the same function
//In such cases, TAI_RUN_NEXT and return go respectively forward and backwards in the hook chain


//Everything in this function is ran when the module starts (right before the game itself)
void CustomRoutines_OnLoad(SceUID modId, enum GameType game) {
    if (game == SKU_RC2_PAL) {
        HookOffset(0,   0x9D30C2,   1,  MB_Create); //MB_Create in R&C2 PAL located at offset 0x9D30C2 in segment 0
        //This can be found in Ghidra by hovering on the address in the Listing window
        //The value for Thumb can be found under the function decorator - put the value next to `assume TMode = `
    }
}