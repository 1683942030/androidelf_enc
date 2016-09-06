#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#ifndef PAGE_SIZE
#define PAGE_SIZE 0x1000
#endif

extern void decrypt_and_call(void *);
extern void decrypt_rodata(void);

void _encrypt_hello(void) __attribute__((aligned(PAGE_SIZE)));
void _encrypt_main(void)	   __attribute__((aligned(PAGE_SIZE)));
int  main(void)		   __attribute__((aligned(PAGE_SIZE)));

const char *encrypted_strings_marker = "_marker_" ; //���ڱ�Ǽ��� .rodata �ڣ���hello world�ַ����ᱻ����

void _encrypt_hello(void)
{
	puts("Hello world.");
}

void _encrypt_main(void)
{
	decrypt_and_call(_encrypt_hello);
}

int main(void)
{
	decrypt_rodata();
	decrypt_and_call(_encrypt_main);
	return 0;
}
