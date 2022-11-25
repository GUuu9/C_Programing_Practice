#include "function.h"

void FTL_read(char * buffer, int fsize, TABLE *table) {
	FILE *fp; 
	FILE *fp2;
	int i = 0;
	int PageNum = 0;
	char cPageNum[SIZE];
	int ReturnPPN = 0;

	printf("Input PageNumber\n");				
	printf(">> ");
	gets(cPageNum);	//<-�ƹ��͵� �Է����� ������ ������ ����
	fflush(stdin);

	PageNum = atoi(cPageNum); // ���ڿ� ���� ��ȯ �Լ� 

	fopen_s(&fp, "1DATAFILE.txt", "rb+");		
	buffer = (char *)malloc(PAGE);				

	if (PageNum >= fsize / PAGE) {				
		printf("OUT OF RANGE.");				
		fclose(fp);
		return;
	}

	fopen_s(&fp2, "1MAPPINGTABLE.txt", "r");

	for (i = 0; i < (fsize / PAGE); i++) {
		if (strcmp(table[i].LPN, cPageNum) == 0) {
			if (strcmp(table[i].state, "f") == 0) {
				printf("�ش� �������� �����Ͱ� ����Ǿ����� �ʽ��ϴ�.\n");
			}
			if (strcmp(table[i].state, "d") == 0) {
				printf("�ش� �������� �ʱ�ȭ�� �ʿ��� �����Դϴ�.\n");
				while (!_kbhit());
				free(buffer);
				fclose(fp);
				fclose(fp2);
				return;
			}
			ReturnPPN = atoi(table[i].PPN);
			break;
		}
	}

	fseek(fp, PAGE * ReturnPPN, SEEK_SET);	// �ش� ��ġ�� �̵��Ѵ� 

	printf("%d �� �������� ������ ��� �մϴ�.\n", PageNum);
	printf("���� ������ ��ȣ : %d\n", ReturnPPN);
	fread(buffer, sizeof(char), PAGE, fp);	// ���� ����, �ѹ��� ���� ũ��, ���� ��, �о�� ��ġ

	for (i = 0; i < PAGE; i++) {
		if (buffer[i] == '^')
			break;
		if (i % 64 == 0)						
			printf("\n");
		printf("%c", buffer[i]);					
	}
	printf("\n������ ��� �Ϸ�.");

	free(buffer);
	fclose(fp);
	fclose(fp2);
	return;
}