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
	gets(cPageNum);	//<-아무것도 입력하지 않으면 에러로 종료
	fflush(stdin);

	PageNum = atoi(cPageNum); // 문자열 정수 변환 함수 

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
					printf("해당 페이지는 데이터가 저장되어있지 않습니다.\n");
				}
				if (strcmp(table[i].state0, "d") == 0) {
					printf("해당 페이지는 초기화가 필요한 공간입니다.\n");
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
					printf("해당 페이지는 데이터가 저장되어있지 않습니다.\n");
				}
				if (strcmp(table[i].state1, "d") == 0) {
					printf("해당 페이지는 초기화가 필요한 공간입니다.\n");
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
					printf("해당 페이지는 데이터가 저장되어있지 않습니다.\n");
				}
				if (strcmp(table[i].state2, "d") == 0) {
					printf("해당 페이지는 초기화가 필요한 공간입니다.\n");
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
					printf("해당 페이지는 데이터가 저장되어있지 않습니다.\n");
				}
				if (strcmp(table[i].state3, "d") == 0) {
					printf("해당 페이지는 초기화가 필요한 공간입니다.\n");
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

	fseek(fp, PAGE * ReturnPBN, SEEK_SET);	// 해당 위치로 이동한다 

	printf("%s 번 블록 %d번 오프셋 의 내용을 출력 합니다.\n", blocknum, offsetnum);
	printf("실제 블록 번호 : %d\n", ReturnPBN);
	fread(buffer, sizeof(char), PAGE, fp);	// 읽을 내용, 한번에 읽을 크기, 읽을 양, 읽어올 위치

	for (i = 0; i < PAGE; i++) {
		if (buffer[i] == '^')
			break;
		if (i % 64 == 0)						
			printf("\n");
		printf("%c", buffer[i]);					
	}
	printf("\n페이지 출력 완료.");

	free(buffer);
	fclose(fp);
	fclose(fp2);
	return;
}