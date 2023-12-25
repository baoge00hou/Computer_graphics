#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include<gl/glut.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define BITMAP_ID 0x4D42
const int texture_number = 11;

//声明纹理映射
extern unsigned int texture[texture_number];

void init_texture();

// 纹理标示符数组，保存两个纹理的标示符
// 描述: 通过指针，返回filename 指定的bitmap文件中数据。
// 同时也返回bitmap信息头.（不支持-bit位图）
unsigned char* LoadBitmapFile(char* filename, BITMAPINFOHEADER* bitmapInfoHeader);

void texload(int i, char* filename);

#endif // !TEXTURE_H
