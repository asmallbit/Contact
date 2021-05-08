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

// T表，32位字，一共有64个元素，对应64次迭代，也成为加法常数
/*
const uint32_t T[64] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
                         0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                         0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
                         0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
                         0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
                         0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
                         0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
                         0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
                         0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
                         0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                         0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
                         0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
                         0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
                         0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                         0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
                         0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };
                         */

// 64次迭代运算采用的左循环移位的s值
/*
const uint32_t S[64] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                         5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                         4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                         6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };
*/

// 两个工具函数
void int2byte(uint32_t val, uint8_t *bytes);

uint32_t byte2int(const uint8_t *bytes);

// MD5主函数
int MD5(const uint8_t *filepath, uint8_t *result);

//uint8_t转int
int uint8ToBin(uint8_t *handel, int length);

#endif // !MD5_H