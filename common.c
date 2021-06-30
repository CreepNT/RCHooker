#include "common.h"

#include <psp2/kernel/error.h>
#include <psp2/kernel/modulemgr.h>

int Module_GetAddressForOffset(SceUID module_UID, unsigned segment, unsigned offset, void* out_address){
    if (out_address == NULL) return SCE_KERNEL_ERROR_INVALID_ARGUMENT;
    if (segment > 3) return SCE_KERNEL_ERROR_INVALID_ARGUMENT;

    SceKernelModuleInfo modInfo;
    int ret = sceKernelGetModuleInfo(module_UID, &modInfo);
    if (ret < 0) return ret;

    if (offset > modInfo.segments[segment].memsz) return SCE_KERNEL_ERROR_INVALID_ARGUMENT;
    *(uintptr_t*)out_address = ((uintptr_t)modInfo.segments[segment].vaddr + offset);
    return 0;
}

char* GetDescriptiveStringForCode(unsigned code){
    switch (code) {
        case SKU_RC1_PAL:
            return "Ratchet & Clank 1 (PAL)";
        case SKU_RC2_PAL:
            return "Ratchet & Clank 2 (PAL)";
        case SKU_RC3_PAL:
            return "Ratchet & Clank 3 (PAL)";
        case SKU_RCC_PAL:
            return "The Ratchet & Clank Trilogy HD (PAL)";
        case SKU_RCC_US:
            return "Ratchet & Clank Collection (US)";
        case (US_COLLECTION | RC1_BIT):
            return "Ratchet & Clank 1 (US Collection)";
        case (US_COLLECTION | RC2_BIT):
            return "Ratchet & Clank : Going Commando (US Collection)";
        case (US_COLLECTION | RC3_BIT):
            return "Ratchet & Clank : Up Your Arsenal (US Collection)";
        case (PAL_COLLECTION | RC1_BIT):
            return "Ratchet & Clank 1 (PAL Trilogy)";
        case (PAL_COLLECTION | RC2_BIT):
            return "Ratchet & Clank 2 (PAL Trilogy)";
        case (PAL_COLLECTION | RC3_BIT):
            return "Ratchet & Clank 3 (PAL Trilogy)";
        case GAME_UNKNOWN:
            return "Unknown";
        case TAI_ERROR_NOT_FOUND:
            return "Not found";
        case TAI_ERROR_HOOK_ERROR:
            return "Hook error";
        default:
            return NULL;
    }
}