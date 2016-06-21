#include "stdafx.h"

// 10 ���� itoa
void itoa10(int n, char *buf)
{
	char temp[10];                // �ִ� 10 ����
	int  rem, i = 0;

	if (n == 0)
		temp[i++] = '0';
	while (n != 0) {
		rem = n % 10;             // ������ ���ϱ� 
		temp[i++] = rem + '0';
		n = n / 10;               // �� ������
	}

	while (--i >= 0)              // ��� ����
		*buf++ = temp[i];
	*buf = '\0';                  // eof ����
}