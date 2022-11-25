#include "function.h"

void FTL_write(char * buffer, int fsize, TABLE *table, char * bufferdata) {
	FILE *fp;
	FILE *fp2;	// 테이블 탐색
	FILE *fp3;	// 테이블 수정본 저장
	FILE *fp4;  // 서브
	int PageNum = 0, i = 0, j = 0, startS = 0, endS = 0, ReturnPPN = 0;
	int erase = 0, BlockCount = 0, Copy, CopyC = 0, EraseCount = 0, reWriteC = 0;
	int RETABLE, BlockCount2 = 0, Findpage = 0, write2, k = 0;
	char save[PAGE] = { 94, };
	char cPageNum[SIZE];
	char temp[SIZE];
	int TC = fsize / PAGE;

	printf("Input PageNumber\n");
	printf(">> ");
	gets(cPageNum);
	fflush(stdin);

	PageNum = atoi(cPageNum); 

	fopen_s(&fp, "1DATAFILE.txt", "r+");		

	buffer = (char *)malloc(fsize);		
	bufferdata = (char *)malloc(BLOCK);

	if (PageNum >= fsize / PAGE) {			
		printf("OUT OF RANGE.");				
		fclose(fp);
		return;
	}

	printf("Input Data (Max 4KB) \n");
	printf(">> ");
	gets(save);
	fflush(stdin);



	fopen_s(&fp2, "1MAPPINGTABLE.txt", "r+");
	for (i = 0; i < TC; i++) {
		if (strcmp(table[i].LPN, cPageNum) == 0) {
			if (strcmp(table[i].state, "u") == 0) {
				for (j = 0; j < TC; j++) {
					if (strcmp(table[j].state, "f") == 0) {
						ReturnPPN = atoi(table[j].PPN);

						strcpy_s(table[j].state, SIZE, "d");
						strcpy_s(table[i].state, SIZE, "u");

					
						strcpy_s(temp, SIZE, table[j].PPN);
						strcpy_s(table[j].PPN, SIZE, table[i].PPN);
						strcpy_s(table[i].PPN, SIZE, temp);
						reWriteC++;
						break;
					}
					if (j == (TC - 1)) { //더이상 빈 공간이 존재하지 않음 블록 단위로 지우기 시작
						for (; erase < fsize / BLOCK; erase++) {
							BlockCount = erase * BLOCK;
							BlockCount2 = BlockCount + BLOCK;
							fopen_s(&fp4, "1SUBBLOCK.txt", "wb");
							EraseCount++;

							fseek(fp, BlockCount, SEEK_SET);	//옮기기
							fseek(fp4, 0, SEEK_SET);
							for (; BlockCount < BlockCount2; BlockCount++) {
								fprintf_s(fp4, "%c", buffer[BlockCount]);
							}

							fclose(fp4);

							BlockCount = erase * BLOCK;			//블록 비우기
							fseek(fp, BlockCount, SEEK_SET);
							memset(buffer, 94, sizeof(char) * BLOCK);
							fwrite(buffer, sizeof(char), BLOCK, fp);

							fopen_s(&fp4, "1SUBBLOCK.txt", "r");

							Copy = erase * 4;
							CopyC = Copy + 4;
							
							fflush(stdin);
							while (!_kbhit());

							for (Findpage = 0; Copy < CopyC; Copy++) {
								if (strcmp(table[Copy].state, "u") == 0) {
									fseek(fp4, Findpage * PAGE, SEEK_SET);
									fread(bufferdata, sizeof(char), PAGE, fp4);
									fseek(fp, Copy * PAGE, SEEK_SET);
									for (write2 = 0; write2 < PAGE; write2++) {
										fprintf_s(fp, "%c", bufferdata[write2]);
									}
									reWriteC++;
								}
								if (strcmp(table[Copy].state, "d") == 0) {
									strcpy_s(table[Copy].state, SIZE, "f");
								}
								Findpage++;
							}
							fclose(fp4);

						}
						j = -1;
						reWriteC--;
					}

				}
			}
			else if (strcmp(table[i].state, "d") == 0) {
				for (j = 0; j < TC; j++) {
					if (strcmp(table[j].state, "f") == 0) {
						ReturnPPN = atoi(table[j].PPN);

						strcpy_s(table[j].state, SIZE, "d");
						strcpy_s(table[i].state, SIZE, "u");


						strcpy_s(temp, SIZE, table[j].PPN);
						strcpy_s(table[j].PPN, SIZE, table[i].PPN);
						strcpy_s(table[i].PPN, SIZE, temp);
						reWriteC++;
						break;
					}
					if (j == (TC - 1)) { //더이상 빈 공간이 존재하지 않음 블록 단위로 지우기 시작
						for (; erase < fsize / BLOCK; erase++) {
							BlockCount = erase * BLOCK;
							BlockCount2 = BlockCount + BLOCK;
							fopen_s(&fp4, "1SUBBLOCK.txt", "w");
							EraseCount++;

							fseek(fp, BlockCount, SEEK_SET);	//옮기기
							fseek(fp4, 0, SEEK_SET);
							for (; BlockCount < BlockCount2; BlockCount++) {
								fprintf_s(fp4, "%c", buffer[BlockCount]);
							}

							fclose(fp4);

							BlockCount = erase * BLOCK;			//블록 비우기
							fseek(fp, BlockCount, SEEK_SET);
							memset(buffer, 94, sizeof(char) * BLOCK);
							fwrite(buffer, sizeof(char), BLOCK, fp);

							fopen_s(&fp4, "1SUBBLOCK.txt", "r");

							Copy = erase * 4;
							CopyC = Copy + 4;

							for (Findpage = 0; Copy < CopyC; Copy++) {						
								if (strcmp(table[Copy].state, "u") == 0) {
									fseek(fp4, Findpage * PAGE, SEEK_SET);
									fread(bufferdata, sizeof(char), PAGE, fp4);
									fseek(fp, Copy * PAGE, SEEK_SET);
									for (write2 = 0; write2 < PAGE; write2++) {
										fprintf_s(fp, "%c", bufferdata[write2]);
									}
									reWriteC++;
								}
								if (strcmp(table[Copy].state, "d") == 0) {
									strcpy_s(table[Copy].state, SIZE, "f");
								}
								Findpage++;
							}
							fclose(fp4);

						}
						j = -1;
						reWriteC--;
					}
				}
			}
			else if (strcmp(table[i].state, "f") == 0) {
				strcpy_s(table[i].state, SIZE,"u");
				ReturnPPN = atoi(table[i].PPN);
				reWriteC++;
			}	
			break;
		}
	}


	fclose(fp2);

	startS = PAGE * ReturnPPN;					// 시작 번지
	endS = startS + PAGE;						// 종료 번지

	fseek(fp, startS, SEEK_SET);				// 해당 위치로 이동한다 
	fread(buffer, sizeof(char), PAGE, fp);

	for (i = 0; i < PAGE; i++) {
		if (i = PAGE - 1) {					// 해당 섹터가 하나라도 차있다면 저장 실패
			fseek(fp, startS, SEEK_SET);		// 해당 위치로 이동한다 
			for (j = 0; j < PAGE; j++) {
				if (save[j] == 0) {
					save[j] = '^';
				}
				buffer[j] = save[j];
				fprintf_s(fp, "%c", buffer[j]);
			}

			fseek(fp, PAGE * ReturnPPN, SEEK_SET);// 해당 위치로 이동한다 

			
			
		}
	}

	fopen_s(&fp3, "1MAPPINGTABLE.txt", "w");

	for (RETABLE = 0; RETABLE < TC; RETABLE++) {	// 기존 저장되있던 데이터를 다시 적는다.
		fprintf_s(fp3, "%s %s %s\n", table[RETABLE].LPN, table[RETABLE].PPN, table[RETABLE].state);
	}


	printf("쓰기 완료.\n");
	printf("사용한 페이지 : %d\n", ReturnPPN);
	printf("지우기 %d 회, 쓰기 %d 회 \n", EraseCount, reWriteC);
	while (!_kbhit());

	free(buffer);
	fclose(fp);
	fclose(fp3);
	return;
}