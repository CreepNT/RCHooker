#ifndef __STRUCTS_H
#define __STRUCTS_H

typedef unsigned char    undefined1;
typedef unsigned char    byte;
typedef unsigned short   word;
typedef unsigned int     dword;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec4;

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Moby {
    Vec3 field_0;
    float unk0;
    Vec3 pos;
    float unk1;
    byte state;
    byte field_21;
    byte texture_mode;
    byte opacity;
    dword moby_model;
    void* parent_moby;
    float size;
    byte field_30;
    byte visible;
    word render_distance;
    word flags1;
    word flags2;
    byte alpha;
    byte blue;
    byte green;
    byte red;
    dword color_shading_thing;
    byte field_40;
    byte field_41;
    byte field_42;
    byte field_43;
    float field_44;
    undefined1 field_0x48;
    undefined1 field_0x49;
    undefined1 field_0x4a;
    undefined1 field_0x4b;
    undefined1 field_0x4c;
    undefined1 field_0x4d;
    undefined1 field_0x4e;
    undefined1 field_0x4f;
    dword field_50;
    dword field_54;
    dword prev_anim;
    dword curr_anim;
    byte field_60;
    byte field_61;
    byte field_62;
    byte field_63;
    dword behaviour;
    dword pvar_ptr;
    byte field_6C;
    byte field_6D;
    byte field_6E;
    byte field_6F;
    dword field_70;
    dword field_74;
    dword field_78;
    word field_7C;
    byte field_7E;
    byte field_7F;
    float field_80;
    float field_84;
    float field_88;
    float field_8C;
    undefined1 field_0x90;
    undefined1 field_0x91;
    undefined1 field_0x92;
    undefined1 field_0x93;
    undefined1 field_0x94;
    undefined1 field_0x95;
    undefined1 field_0x96;
    undefined1 field_0x97;
    dword field_98;
    dword field_9C;
    dword collision_counter;
    byte field_A4;
    byte field_A5;
    byte field_A6;
    byte field_A7;
    byte field_A8;
    byte field_A9;
    word moby_oClass;
    dword moby_counter_indexed;
    undefined1 field_0xb0;
    undefined1 field_0xb1;
    short moby_UID;
    undefined1 field_0xb5;
    undefined1 field_0xb6;
    undefined1 field_0xb7;
    undefined1 field_0xb8;
    void* multimoby_part;
    undefined1 field_0xbc;
    byte field_BD;
    byte field_BE;
    undefined1 field_0xbf;
    Vec4 scale_x;
    Vec4 scale_y;
    Vec4 scale_z;
    Vec4 rotation;
} Moby;

#endif