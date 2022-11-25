#include "function.h"

void FTL_read(char * buffer, int fsize, TABLE *table) {
	FILE *fp; 
	FILE *fp2;
	int i = 0;
	int PageNum = 0;
	int blocknum = 0;
	int offsetnum = 0;
	char cPageNum[SIZE];
	int ReturnPBN = 0;

	printf("Input PageNumber\n");				
	printf(">> ");
	gets(cPageNum);	//<-�ƹ��͵� �Է����� ������ ������ ����
	fflush(stdin);

	PageNum = atoi(cPageNum); // ���ڿ� ���� ��ȯ �Լ� 

	blocknum = PageNum / OFFSET;
	offsetnum = PageNum % OFFSET;


	fopen_s(&fp, "1DATAFILE.txt", "rb+");		
	buffer = (char *)malloc(PAGE);				

	if (blocknum >= fsize / BLOCK) {				
		printf("OUT OF RANGE.");				
		fclose(fp);
		return;
	}

	fopen_s(&fp2, "1MAPPINGTABLE.txt", "r");

	for (i = 0; i < (fsize / BLOCK); i++) {
		if (offsetnum == 0) {
			if (strcmp(table[i].LBN, blocknum) == 0) {
				if (strcmp(table[i].state0, "f") == 0) {
					printf("�ش� �������� �����Ͱ� ����Ǿ����� �ʽ��ϴ�.\n");
				}
				if (strcmp(table[i].state0, "d") == 0) {
					printf("�ش� �������� �ʱ�ȭ�� �ʿ��� �����Դϴ�.\n");
					while (!_kbhit());
					free(buffer);
					fclose(fp);
					fclose(fp2);
					return;
				}
				ReturnPBN = atoi(table[i].PBN);
				break;
			}
		}
		if (offsetnum == 1) {
			if (strcmp(table[i].LBN, blocknum) == 0) {
				if (strcmp(table[i].state1, "f") == 0) {
					printf("�ش� �������� �����Ͱ� ����Ǿ����� �ʽ��ϴ�.\n");
				}
				if (strcmp(table[i].state1, "d") == 0) {
					printf("�ش� �������� �ʱ�ȭ�� �ʿ��� �����Դϴ�.\n");
					while (!_kbhit());
					free(buffer);
					fclose(fp);
					fclose(fp2);
					return;
				}
				ReturnPBN = atoi(table[i].PBN);
				break;
			}
		}
		if (offsetnum == 2) {
			if (strcmp(table[i].LBN, blocknum) == 0) {
				if (strcmp(table[i].state2, "f") == 0) {
					printf("�ش� �������� �����Ͱ� ����Ǿ����� �ʽ��ϴ�.\n");
				}
				if (strcmp(table[i].state2, "d") == 0) {
					printf("�ش� �������� �ʱ�ȭ�� �ʿ��� �����Դϴ�.\n");
					while (!_kbhit());
					free(buffer);
					fclose(fp);
					fclose(fp2);
					return;
				}
				ReturnPBN = atoi(table[i].PBN);
				break;
			}
		}
		if (offsetnum == 3) {
			if (strcmp(table[i].LBN, blocknum) == 0) {
				if (strcmp(table[i].state3, "f") == 0) {
					printf("�ش� �������� �����Ͱ� ����Ǿ����� �ʽ��ϴ�.\n");
				}
				if (strcmp(table[i].state3, "d") == 0) {
					printf("�ش� �������� �ʱ�ȭ�� �ʿ��� �����Դϴ�.\n");
					while (!_kbhit());
					free(buffer);
					fclose(fp);
					fclose(fp2);
					return;
				}
				ReturnPBN = atoi(table[i].PBN);
				break;
			}
		}
	}

	fseek(fp, PAGE * ReturnPBN, SEEK_SET);	// �ش� ��ġ�� �̵��Ѵ� 

	printf("%s �� ��� %d�� ������ �� ������ ��� �մϴ�.\n", blocknum, offsetnum);
	printf("���� ��� ��ȣ : %d\n", ReturnPBN);
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