#include <stdio.h>								
#include <stdlib.h>								
#include <string.h>								
#include <conio.h>								
#include <memory.h>								

#define MEGABYTE 1048576						// 1024 * 1024
#define SECTOR 512	  							// 1 섹터 크기 512byte
#define BLOCK 16384								// 512 * 32  1블럭은 32개의 섹터로 구성되어 있다.
#define SIZE 10
#define PAGE 4096
#define OFFSET 4

typedef struct TABLE {
	char LBN[SIZE];
	char PBN[SIZE];
	char state0[SIZE];
	char state1[SIZE];
	char state2[SIZE];
	char state3[SIZE];
}TABLE;

int init(char * buffer, TABLE * table, char *bufferdata);	
void Print_table(TABLE * table, int fsize);
void FTL_read(char * buffer, int fsize, TABLE *table);
void FTL_write(char * buffer, int fsize, TABLE *table, char *bufferdata);
void table_cut(TABLE *table, int fsize);
void File_Create();
int File_Size();