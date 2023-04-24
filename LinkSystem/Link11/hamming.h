#ifndef HAMMING_H
#define HAMMING_H

#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"

#define TRUE      		  1
#define FALSE			  0
#define MAX_HAM_CHECK_LEN 32 					//最大校验位个数
#define MAX_HAM_CODE_LEN  256					//最大汉明码长度

/*
汉明码校验位个数(k)应满足：
2^k >= n+k+1
其中 n 为源码长度
*/

const char* encode(const char* src_code);		//编码, 返回汉明码
int is_error(const char* ham_code);				//判断是否有错,	若有错返回错误位置,若无错返回 0
const char* check_error(const char* ham_code);	//校验错误,返回正确的汉明码
const char* decode(const char* ham_code);		//解码(带校验)

#endif
