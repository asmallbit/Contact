/*This header is from https://danielxuuuuu.github.io/2019/11/18/MD5%E7%AE%97%E6%B3%95%E7%9A%84C%E8%AF%AD%E8%A8%80%E5%AE%9E%E7%8E%B0/
 *Thanks him again
*/

#ifndef MD5CHECK_H
#define MD5CHECK_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// MD5压缩函数4轮循环中使用的生成函数，每轮不同
#define F(b, c, d) (((b) & (c)) | ((~b) & (d)))
#define G(b, c, d) (((b) & (d)) | ((c) & (~d)))
#define H(b, c, d) ((b) ^ (c) ^ (d))
#define I(b, c, d) ((c) ^ ((b) | (~d)))

// 循环左移
#define LEFTROTATE(num, n) (((num) << n) | ((num >> (32 - n))))

// 两个工具函数
void int2byte(uint32_t val, uint8_t *bytes);
uint32_t byte2int(const uint8_t *bytes);
//获取MD5值
int MD5(const char *filepath, uint8_t *result);
//uint8_t转int
int uint8ToBin(uint8_t *handel, int length);

#endif // !MD5_H