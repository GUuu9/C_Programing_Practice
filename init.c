#include "function.h"

int init(char * buffer, TABLE * table, char *bufferdata) {
	FILE * fp;
	FILE * fp2;
	FILE * fp3;
	int MB = 0;
	int allo = 0;
	int i;
	int PSN = 256;
	int LSN = 0;

	printf("Input Disk size( 1 = 1MB(1048576bytes))\n");
	printf(">> ");							
	scanf_s("%d", &MB);
	fflush(stdin);

	allo = (MEGABYTE * MB);
	PSN *= MB;

	fopen_s(&fp, "1DATAFILE.txt", "rb+");		
	fopen_s(&fp2, "1MAPPINGTABLE.txt", "r+");
	fopen_s(&fp3, "1SUBBLOCK.txt", "r+");

	buffer = (char *)malloc((sizeof(char) * allo));
	table = (char *)malloc((sizeof(char) * PSN));
	bufferdata = (char *)malloc((sizeof(char)) * BLOCK);

	fseek(fp, 0, SEEK_SET);

	memset(buffer, 94, sizeof(char) * allo);											
	fwrite(buffer, sizeof(char), allo, fp);		

	

	for (i = 0; i < 256 * MB; i++) {
		PSN--;
		fprintf_s(fp2, "%d %d f\n", LSN, PSN);
		LSN++;
	}

	fseek(fp3, 0, SEEK_SET);
	memset(bufferdata, 94, sizeof(char) * BLOCK);
	fwrite(bufferdata, sizeof(char), BLOCK, fp3);
	
	

	printf("%d megabytes flash memory", (ftell(fp) / MEGABYTE)); 


	free(buffer);
	free(table);
	free(bufferdata);
	fclose(fp);										
	fclose(fp2);
	fclose(fp3);
	return allo;
}

