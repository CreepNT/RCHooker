#include <taihen.h>
#include <psp2/kernel/clib.h>
#include <psp2/kernel/modulemgr.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/display.h>

#include "log.h"
#include "hooks.h"

#define ERROR_INVALID_OFFSET    0xA0000001
#define ERROR_NULL_POINTER      0xA0000002

static SceUID thid;

int module_get_offset(int uid, int seg, uint32_t in_off, void *out_off) {
    SceKernelModuleInfo info;
    int ret;

    if (out_off == NULL) return ERROR_NULL_POINTER;
    ret = sceKernelGetModuleInfo(uid, &info);
    if (ret < 0) return ret;

	if (in_off > info.segments[seg].memsz) return ERROR_INVALID_OFFSET;
	*(uint32_t *)out_off = (uint32_t)(info.segments[seg].vaddr + in_off);
	return 0;
}

void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void* args){
    int ret = 0;
    sceClibPrintf("\n\n\n*******************************************\n\n\n");
    sceClibPrintf("RCHooker is here !\n");
    tai_module_info_t info;
    sceClibMemset(&info, 0, sizeof(info));
    info.size = sizeof(info);
    ret = taiGetModuleInfo("BootVita",&info); //I think module name for UYA is `NetBootVita` instead
    if (ret < 0){
        sceClibPrintf("Error in taiGetModuleInfo (0x%.8X)\n",ret);
        return SCE_KERNEL_START_FAILED;
    }

    SceUID module_id = info.modid;
    for (int i = 0; i < (sizeof(offsets) / sizeof(offsets[0])); i++){
        ret = module_get_offset(module_id, offsets[i].segment, offsets[i].offset | offsets[i].thumb, offsets[i].function);
        if (ret < 0) sceClibPrintf("Error getting address of function @ segment %u:%.8X : 0x%.8X\n", offsets[i].segment, offsets[i].offset | offsets[i].thumb, ret);
    }

    sceClibPrintf("\n\n\n*******************************************\n\n\n");
    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void* args){
    sceClibPrintf("\n\n\n\n\n\n\nmodule stop\n\n\n\n\n\n");
    return SCE_KERNEL_STOP_SUCCESS;
}
