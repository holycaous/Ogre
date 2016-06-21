#include "stdafx.h"

// 10 진수 itoa
void itoa10(int n, char *buf)
{
	char temp[10];                // 최대 10 진수
	int  rem, i = 0;

	if (n == 0)
		temp[i++] = '0';
	while (n != 0) {
		rem = n % 10;             // 나머지 구하기 
		temp[i++] = rem + '0';
		n = n / 10;               // 몫 나누기
	}

	while (--i >= 0)              // 결과 반전
		*buf++ = temp[i];
	*buf = '\0';                  // eof 문자
}