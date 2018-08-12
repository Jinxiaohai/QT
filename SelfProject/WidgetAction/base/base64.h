// 头文件 base64.h
#pragma once
/*
## 简介
此库支持字节数组，可以包含以为字符串\0导致的数据不全问题。
* data ：字节数组
* size：字节数组长度
###### 使用
关于内存释放
* data需要释放
* IBase64本身需要释放
*/

#ifndef BASE64_H
#define BASE64_H

const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

typedef struct {
    char * data;//字节数组
    int size;   //字节总数
}IBase64;

/* Base64 编码 */
IBase64 * base64_encode( IBase64 i_b );//记得释放内存

/* Base64 解码 */
IBase64 * base64_decode( IBase64 i_b );
#endif
