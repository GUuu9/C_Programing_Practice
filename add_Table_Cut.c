#include "function.h"

void table_cut(TABLE *table, int fsize) {	
	FILE *fp2;
	int i;
	char DATA[SIZE * 6];
	char *null = NULL;	

	fopen_s(&fp2, "1MAPPINGTABLE.txt", "r");	

	for (i = 0; i < (fsize / BLOCK); i++) {
		fgets(DATA, SIZE * 6, fp2);
		strcpy_s(table[i].LBN, SIZE, strtok_s(DATA, " ", &null));		
		strcpy_s(table[i].PBN, SIZE, strtok_s(NULL, " ", &null));		
		strcpy_s(table[i].state0, SIZE, strtok_s(NULL, " ", &null));	
		strcpy_s(table[i].state1, SIZE, strtok_s(NULL, " ", &null));
		strcpy_s(table[i].state2, SIZE, strtok_s(NULL, " ", &null));
		strcpy_s(table[i].state3, SIZE, strtok_s(NULL, "\n", &null));
	}

	fclose(fp2);
}