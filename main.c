#include <taihen.h>
#include <psp2/ctrl.h>  //sceCtrlPeekBufferPositive
#include <psp2/appmgr.h> //sceAppMgrAppParamGetString
#include <psp2common/types.h> //SCE_UID_INVALID_UID
#include <psp2/kernel/clib.h> //sceClibPrintf, sceClibStrncmp
#include <psp2/kernel/modulemgr.h> //SCE_KERNEL_START_xxx

#include "log.h"
#include "common.h"

//Combo to press in order for the module to not load anything
#define SKIP_COMBO (SCE_CTRL_RTRIGGER|SCE_CTRL_TRIANGLE) //R + Triangle

#define COLLECTION_MODULE_NAME "RCC"
#define RC12_MODULE_NAME "BootVita"
#define RC3_MODULE_NAME "NetBootVita"

//Forward declare routines in custom_routines.c
void CustomRoutines_OnLoad(SceUID modId, enum GameType game); //modId -> UID of the game's executable module
void CustomRoutines_OnUnload(void);

/**
 * @brief Get the game bitfield and executable's module UID
 * 
 * @param game Pointer to the variable that will recieve the game bitfield
 * @param modId Pointer to the variable that will recieve the executable's module UID
 * @return true if game is detected and module UID is obtained, false otherwise
 * @note *pGame is set to GAME_UNKNOWN, and *pModId is set to SCE_UID_INVALID_UID on failure
 */
bool GetModuleIdAndGame(enum GameType* pGame, SceUID* pModId){
    if (pGame == NULL || pModId == NULL)
        return false;

    *pGame = GAME_UNKNOWN;
    *pModId = SCE_UID_INVALID_UID;

    enum GameType game = GAME_UNKNOWN;

    char titleID[10] = {0};
    int ret = sceAppMgrAppParamGetString(0, 12, titleID, sizeof(titleID));
    if (ret < 0) return false;

    //First, check title ID to see current game
    if      (sceClibStrncmp(titleID, "PCSF00482", sizeof(titleID)) == 0) game = PAL_COLLECTION;
    else if (sceClibStrncmp(titleID, "PCSA00133", sizeof(titleID)) == 0) game = US_COLLECTION;
    else if (sceClibStrncmp(titleID, "PCSF00484", sizeof(titleID)) == 0) game = SKU_RC1_PAL;
    else if (sceClibStrncmp(titleID, "PCSF00485", sizeof(titleID)) == 0) game = SKU_RC2_PAL;
    else if (sceClibStrncmp(titleID, "PCSF00486", sizeof(titleID)) == 0) game = SKU_RC3_PAL;
    else return false;

    tai_module_info_t modInfo;
    modInfo.size = sizeof(modInfo);

    //Title ID doesn't allow us to know which game this is, so we need to investigate more
    //NOTE : Due to the current detection method, it is impossible to know if the current game is R&C1 or R&C2
    //TODO : Find a way to distinguish between R&C1 and R&C2
    if (game & IS_COLLECTION_BIT) {
        //Check if this is RCC module first
        int ret = taiGetModuleInfo(COLLECTION_MODULE_NAME, &modInfo);
        if (ret >= 0) {
            *pModId = modInfo.modid;
            *pGame = game | RCC_BIT;
            return true;
        }
        else if (ret != TAI_ERROR_NOT_FOUND)
            return false;
        
        //Check if this is RC1/RC2 module
        ret = taiGetModuleInfo(RC12_MODULE_NAME, &modInfo);
        if (ret >= 0) {
            *pModId = modInfo.modid;
            *pGame = game; //NOTE : we don't set either RC1 or RC2 bits, because it's unknown which game we're currently running
            return true;
        }
        else if (ret != TAI_ERROR_NOT_FOUND)
            return false;

        //Check if this is RC3
        ret = taiGetModuleInfo(RC3_MODULE_NAME, &modInfo);
        if (ret < 0) return false;
        else {
            *pModId = modInfo.modid;
            *pGame = game | RC3_BIT;
            return true;
        }
    }
    else { //Only try the module we're expecting
        if (game & (RC1_BIT | RC2_BIT)) { //RC1 and RC2 have the same module name, so we can do them in a single case
            int ret = taiGetModuleInfo(RC12_MODULE_NAME, &modInfo);
            if (ret < 0) return false;

            *pModId = modInfo.modid;
            *pGame = game;
            return true;
        }
        else /*if (game & RC3_BIT)*/ {
            int ret = taiGetModuleInfo(RC3_MODULE_NAME, &modInfo);
            if (ret < 0) return false;

            *pModId = modInfo.modid;
            *pGame = game;
            return true;
        }
    }

}

void _start() __attribute__((weak, alias ("module_start")));
int module_start(SceSize argc, const void* args){
    sceClibPrintf("\n\n******************************\n\n");
    println(ANSI_CYAN "RCHooker module_start - Built on " __DATE__ " at " __TIME__ ANSI_RESET);

    SceCtrlData padData;
    int ret = sceCtrlPeekBufferPositive(0, &padData, 1);
    if (ret < 0 || (padData.buttons & SKIP_COMBO) == SKIP_COMBO) {
        sceClibPrintf("User asked to not execute patches\n");
        goto exit_unload;
    }

    SceUID modId = SCE_UID_INVALID_UID;
    enum GameType game = GAME_UNKNOWN;
    if (!GetModuleIdAndGame(&game, &modId)){
        sceClibPrintf("Could not get module ID and current game bitfield.\n");
        goto exit_unload;
    }

    sceClibPrintf("Current game is " ANSI_CYAN "%s" ANSI_RESET " (0x%08X)\n", GetDescriptiveStringForCode(game), game);

    sceClibPrintf("Executing custom routines...\n");
    CustomRoutines_OnLoad(modId, game);

    sceClibPrintf(ANSI_GREEN "RCHooker started successfully !\n" ANSI_RESET);
    sceClibPrintf("\n\n******************************\n\n");
    return SCE_KERNEL_START_SUCCESS;

exit_unload:
    sceClibPrintf(ANSI_RED ANSI_BOLD "\nRCHooker is exiting......\n" ANSI_RESET);
    sceClibPrintf("\n\n******************************\n\n");
    return SCE_KERNEL_START_FAILED;
}