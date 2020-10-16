#include "log.h"
#include "structs.h"
#include <psp2/kernel/clib.h>

#define println(fmt, ...) sceClibPrintf(fmt"\n",##__VA_ARGS__)
#define println_vec3(fmt, vec3) sceClibPrintf(fmt); log_Vec3(vec3); sceClibPrintf("\n")
#define println_vec4(fmt, vec4) sceClibPrintf(fmt); log_Vec4(vec4); sceClibPrintf("\n")

void log_moby_data(Moby* pMoby){
    if (pMoby == NULL) return;
    println("Dumping data of Moby at address : %p !",pMoby);
    println("Raw dump :");
    log_moby_data_RAW(pMoby);
    println("Detailed dump :");
    println_vec3(" Position : ", &(pMoby->pos) );
    println(" State : %hhu", pMoby->state);
    println(" Texture mode : %hhu", pMoby->texture_mode);
    println(" Opacity : %hhu", pMoby->opacity);
    println(" Moby model : %p", (void*)pMoby->moby_model);
    println(" Parent moby : %p", pMoby->parent_moby);
    println(" Size : %f", pMoby->size);
    println(" Visible : %hhu", pMoby->visible);
    println(" Render distance : %hu", pMoby->render_distance);
    println(" Flags1 : 0x%.4X", pMoby->flags1);
    println(" Flags2 : 0x%.4X", pMoby->flags2);
    println(" RGBA : 0x%.2X%.2X%.2X%.2X", pMoby->red, pMoby->green, pMoby->blue, pMoby->alpha);
    println(" color_shading_thing : 0x%.8X");
    println(" field_40 to field_44 : 0x%.2X%.2X%.2X%.2X",pMoby->field_40, pMoby->field_41, pMoby->field_42, pMoby->field_43);
    println(" Previous animation : 0x%.8X", pMoby->prev_anim);
    println(" Current animation : 0x%.8X", pMoby->curr_anim);
    println(" Behaviour : 0x%.8X", pMoby->behaviour);
    println(" pVars pointer : 0x%.8X", pMoby->pvar_ptr);
    println(" Collision counter : 0x%.8X", pMoby->collision_counter);
    println(" Moby oClass : %hhu", pMoby->moby_oClass);
    println(" Moby UID : %hd", pMoby->moby_UID);
    println(" Multimoby pointer : %p", pMoby->multimoby_part);
    println_vec4(" Scale X : ", &(pMoby->scale_x) );
    println_vec4(" Scale Y : ", &(pMoby->scale_y) );
    println_vec4(" Scale Z : ", &(pMoby->scale_z) );
    println_vec4(" Rotation : ", &(pMoby->rotation) );
    println("Done dumping data of Moby at address %p !",pMoby);
    return;
}

void log_moby_data_RAW(Moby* pMoby){
    if (pMoby == NULL) return;
    int* ptr = (int*)pMoby;
    for (int i = 0; i < sizeof(Moby)/4; i++){
        sceClibPrintf("%.8X ", ptr[i]);
        if ( (i % 8) == 0) sceClibPrintf("\n");  //Newline every 8 words (every 8 * 32 bits) 
    }
}

void log_Vec4(Vec4* pVec){
    if (pVec == NULL) return;
    sceClibPrintf("%f, %f, %f, %f", pVec->x, pVec->y, pVec->z, pVec->w);
}

void log_Vec3(Vec3* pVec){
    if (pVec == NULL) return;
    sceClibPrintf("%f, %f, %f", pVec->x, pVec->y, pVec->z);
}

void dump_pVars(void* pVars, unsigned int len){
    if (pVars == NULL) return;
    if (len == 0) return;
    char* ptr = (char*)pVars;
    for (int i = 0; i < len; i++){
        sceClibPrintf("%.2X", ptr[i]);
        if ( (i % 4) == 0) sceClibPrintf(" "); // Space every 32 bits dumped
        if ( (i % 32) == 0) sceClibPrintf("\n");  //Newline every 8 words (every 8 * 32 bits) 
    }
    return;
}