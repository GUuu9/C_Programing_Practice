#include "function.h"

void FTL_write(char * buffer, int fsize, TABLE *table, char * bufferdata) {
	FILE *fp;
	FILE *fp2;	// 테이블 탐색
	FILE *fp3;	// 테이블 수정본 저장
	FILE *fp4;  // 서브
	int PageNum = 0, i = 0, j = 0, k = 0, kk = 0, kkk = 0, startS = 0, endS = 0, ReturnPBN = 0;
	int erase = 0, BlockCount = 0, Copy, CopyC = 0, EraseCount = 0, reWriteC = 0;
	int RETABLE, BlockCount2 = 0, Findpage = 0, write2;
	int offsetnum = 0;
	int blocknum = 0;
	char blocknum1[SIZE];
	char save[PAGE] = { 94, };
	char cPageNum[SIZE];
	char temp[SIZE];

	int TC = fsize / BLOCK;

	printf("Input PageNumber\n");
	printf(">> ");
	gets(cPageNum);
	fflush(stdin);

	PageNum = atoi(cPageNum); 


	blocknum = PageNum / OFFSET;
	offsetnum = PageNum % OFFSET;



	fopen_s(&fp, "1DATAFILE.txt", "r+");		

	buffer = (char *)malloc(fsize);		
	bufferdata = (char *)malloc(BLOCK);

	if (blocknum >= fsize / BLOCK) {			
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
		if (strcmp(table[i].LBN, blocknum) == 0) {
			if (offsetnum == 0) {// 0off
				if (strcmp(table[i].state0, "u") == 0) {
					for (k = 0; k < 4; k++) {//
						if (k == 1) {
							if (strcmp(table[i].state1, "f") == 0) {
								strcpy_s(table[i].state0, SIZE, "d");
								strcpy_s(table[i].state1, SIZE, "u");


								strcpy_s(temp, SIZE, table[j].PBN);
								strcpy_s(table[j].PBN, SIZE, table[i].PBN);
								strcpy_s(table[i].PBN, SIZE, temp);
								reWriteC++;
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}

						}
						if (k == 2) {
							if (strcmp(table[i].state2, "f") == 0) {
								strcpy_s(table[i].state2, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}

						}
						if (k == 3) {
							if (strcmp(table[i].state3, "f") == 0) {
								strcpy_s(table[i].state3, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}
						}
					}

					for (kk = 0; kk < TC; kk++) {//a
						for (k = 0; k < 4; k++) {//b
							if (k == 0) {
								if (strcmp(table[kk].state0, "f") == 0) {
									strcpy_s(table[kk].state0, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 1) {
								if (strcmp(table[kk].state1, "f") == 0) {
									strcpy_s(table[kk].state1, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 2) {
								if (strcmp(table[kk].state2, "f") == 0) {
									strcpy_s(table[kk].state2, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 3) {
								if (strcmp(table[kk].state3, "f") == 0) {
									strcpy_s(table[kk].state3, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
						}//b
						if (kk == (TC - 1)) { //더이상 빈 공간이 존재하지 않음 블록 단위로 지우기 시작 c
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
									for (kkk = 0; kkk < 4; kkk++) {
										if (offsetnum == 0) {
											if (strcmp(table[Copy].state0, "u") == 0) {
												fseek(fp4, Findpage * PAGE, SEEK_SET);
												fread(bufferdata, sizeof(char), PAGE, fp4);
												fseek(fp, Copy * PAGE, SEEK_SET);
												for (write2 = 0; write2 < PAGE; write2++) {
													fprintf_s(fp, "%c", bufferdata[write2]);
												}
												reWriteC++;
											}
											if (strcmp(table[Copy].state0, "d") == 0) {
												strcpy_s(table[Copy].state0, SIZE, "f");
											}
										}
									}
									Findpage++;
								}
								fclose(fp4);

							}
							j = -1;
							reWriteC--;

						}//c

					}//a
				}
				else if (strcmp(table[i].state0, "d") == 0) {
					for (k = 0; k < 4; k++) {//
						if (k == 1) {
							if (strcmp(table[i].state1, "f") == 0) {
								strcpy_s(table[i].state1, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}

						}
						if (k == 2) {
							if (strcmp(table[i].state2, "f") == 0) {
								strcpy_s(table[i].state2, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}

						}
						if (k == 3) {
							if (strcmp(table[i].state3, "f") == 0) {
								strcpy_s(table[i].state3, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}
						}
					}

					for (kk = 0; kk < TC; kk++) {//a
						for (k = 0; k < 4; k++) {//b
							if (k == 0) {
								if (strcmp(table[kk].state0, "f") == 0) {
									strcpy_s(table[kk].state0, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 1) {
								if (strcmp(table[kk].state1, "f") == 0) {
									strcpy_s(table[kk].state1, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 2) {
								if (strcmp(table[kk].state2, "f") == 0) {
									strcpy_s(table[kk].state2, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 3) {
								if (strcmp(table[kk].state3, "f") == 0) {
									strcpy_s(table[kk].state3, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
						}//b
						if (kk == (TC - 1)) { //더이상 빈 공간이 존재하지 않음 블록 단위로 지우기 시작 c
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
									for (kkk = 0; kkk < 4; kkk++) {
										if (offsetnum == 0) {
											if (strcmp(table[Copy].state0, "u") == 0) {
												fseek(fp4, Findpage * PAGE, SEEK_SET);
												fread(bufferdata, sizeof(char), PAGE, fp4);
												fseek(fp, Copy * PAGE, SEEK_SET);
												for (write2 = 0; write2 < PAGE; write2++) {
													fprintf_s(fp, "%c", bufferdata[write2]);
												}
												reWriteC++;
											}
											if (strcmp(table[Copy].state0, "d") == 0) {
												strcpy_s(table[Copy].state0, SIZE, "f");
											}
										}
									}
									Findpage++;
								}
								fclose(fp4);

							}
							j = -1;
							reWriteC--;

						}//c

					}//a
				}
				else if (strcmp(table[i].state0, "f") == 0) {
					strcpy_s(table[i].state0, SIZE, "u");
					ReturnPBN = atoi(table[i].PBN);
					reWriteC++;
				}
				break;
			}//0off
			if (offsetnum == 1) {// 0off
				if (strcmp(table[i].state0, "u") == 0) {
					for (k = 0; k < 4; k++) {//
						if (k == 0) {
							if (strcmp(table[i].state0, "f") == 0) {
								strcpy_s(table[i].state0, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}

						}
						if (k == 2) {
							if (strcmp(table[i].state2, "f") == 0) {
								strcpy_s(table[i].state2, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}

						}
						if (k == 3) {
							if (strcmp(table[i].state3, "f") == 0) {
								strcpy_s(table[i].state3, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}
						}
					}

					for (kk = 0; kk < TC; kk++) {//a
						for (k = 0; k < 4; k++) {//b
							if (k == 0) {
								if (strcmp(table[kk].state0, "f") == 0) {
									strcpy_s(table[kk].state0, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 1) {
								if (strcmp(table[kk].state1, "f") == 0) {
									strcpy_s(table[kk].state1, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 2) {
								if (strcmp(table[kk].state2, "f") == 0) {
									strcpy_s(table[kk].state2, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 3) {
								if (strcmp(table[kk].state3, "f") == 0) {
									strcpy_s(table[kk].state3, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
						}//b
						if (kk == (TC - 1)) { //더이상 빈 공간이 존재하지 않음 블록 단위로 지우기 시작 c
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
									for (kkk = 0; kkk < 4; kkk++) {
										if (offsetnum == 0) {
											if (strcmp(table[Copy].state0, "u") == 0) {
												fseek(fp4, Findpage * PAGE, SEEK_SET);
												fread(bufferdata, sizeof(char), PAGE, fp4);
												fseek(fp, Copy * PAGE, SEEK_SET);
												for (write2 = 0; write2 < PAGE; write2++) {
													fprintf_s(fp, "%c", bufferdata[write2]);
												}
												reWriteC++;
											}
											if (strcmp(table[Copy].state0, "d") == 0) {
												strcpy_s(table[Copy].state0, SIZE, "f");
											}
										}
									}
									Findpage++;
								}
								fclose(fp4);

							}
							j = -1;
							reWriteC--;

						}//c

					}//a
				}
				else if (strcmp(table[i].state0, "d") == 0) {
					for (k = 0; k < 4; k++) {//
						if (k == 1) {
							if (strcmp(table[i].state1, "f") == 0) {
								strcpy_s(table[i].state1, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}

						}
						if (k == 2) {
							if (strcmp(table[i].state2, "f") == 0) {
								strcpy_s(table[i].state2, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}

						}
						if (k == 3) {
							if (strcmp(table[i].state3, "f") == 0) {
								strcpy_s(table[i].state3, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}
						}
					}

					for (kk = 0; kk < TC; kk++) {//a
						for (k = 0; k < 4; k++) {//b
							if (k == 0) {
								if (strcmp(table[kk].state0, "f") == 0) {
									strcpy_s(table[kk].state0, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 1) {
								if (strcmp(table[kk].state1, "f") == 0) {
									strcpy_s(table[kk].state1, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 2) {
								if (strcmp(table[kk].state2, "f") == 0) {
									strcpy_s(table[kk].state2, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 3) {
								if (strcmp(table[kk].state3, "f") == 0) {
									strcpy_s(table[kk].state3, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
						}//b
						if (kk == (TC - 1)) { //더이상 빈 공간이 존재하지 않음 블록 단위로 지우기 시작 c
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
									for (kkk = 0; kkk < 4; kkk++) {
										if (offsetnum == 0) {
											if (strcmp(table[Copy].state0, "u") == 0) {
												fseek(fp4, Findpage * PAGE, SEEK_SET);
												fread(bufferdata, sizeof(char), PAGE, fp4);
												fseek(fp, Copy * PAGE, SEEK_SET);
												for (write2 = 0; write2 < PAGE; write2++) {
													fprintf_s(fp, "%c", bufferdata[write2]);
												}
												reWriteC++;
											}
											if (strcmp(table[Copy].state0, "d") == 0) {
												strcpy_s(table[Copy].state0, SIZE, "f");
											}
										}
									}
									Findpage++;
								}
								fclose(fp4);

							}
							j = -1;
							reWriteC--;

						}//c

					}//a
				}
				else if (strcmp(table[i].state0, "f") == 0) {
					strcpy_s(table[i].state0, SIZE, "u");
					ReturnPBN = atoi(table[i].PBN);
					reWriteC++;
				}
				break;
			}//0off
			if (offsetnum == 2) {// 0off
				if (strcmp(table[i].state0, "u") == 0) {
					for (k = 0; k < 4; k++) {//
						if (k == 0) {
							if (strcmp(table[i].state0, "f") == 0) {
								strcpy_s(table[i].state0, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}

						}
						if (k == 1) {
							if (strcmp(table[i].state1, "f") == 0) {
								strcpy_s(table[i].state1, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}

						}
						if (k == 3) {
							if (strcmp(table[i].state3, "f") == 0) {
								strcpy_s(table[i].state3, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}
						}
					}

					for (kk = 0; kk < TC; kk++) {//a
						for (k = 0; k < 4; k++) {//b
							if (k == 0) {
								if (strcmp(table[kk].state0, "f") == 0) {
									strcpy_s(table[kk].state0, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 1) {
								if (strcmp(table[kk].state1, "f") == 0) {
									strcpy_s(table[kk].state1, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 2) {
								if (strcmp(table[kk].state2, "f") == 0) {
									strcpy_s(table[kk].state2, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 3) {
								if (strcmp(table[kk].state3, "f") == 0) {
									strcpy_s(table[kk].state3, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
						}//b
						if (kk == (TC - 1)) { //더이상 빈 공간이 존재하지 않음 블록 단위로 지우기 시작 c
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
									for (kkk = 0; kkk < 4; kkk++) {
										if (offsetnum == 0) {
											if (strcmp(table[Copy].state0, "u") == 0) {
												fseek(fp4, Findpage * PAGE, SEEK_SET);
												fread(bufferdata, sizeof(char), PAGE, fp4);
												fseek(fp, Copy * PAGE, SEEK_SET);
												for (write2 = 0; write2 < PAGE; write2++) {
													fprintf_s(fp, "%c", bufferdata[write2]);
												}
												reWriteC++;
											}
											if (strcmp(table[Copy].state0, "d") == 0) {
												strcpy_s(table[Copy].state0, SIZE, "f");
											}
										}
									}
									Findpage++;
								}
								fclose(fp4);

							}
							j = -1;
							reWriteC--;

						}//c

					}//a
				}
				else if (strcmp(table[i].state0, "d") == 0) {
					for (k = 0; k < 4; k++) {//
						if (k == 1) {
							if (strcmp(table[i].state1, "f") == 0) {
								strcpy_s(table[i].state1, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}

						}
						if (k == 2) {
							if (strcmp(table[i].state2, "f") == 0) {
								strcpy_s(table[i].state2, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}

						}
						if (k == 3) {
							if (strcmp(table[i].state3, "f") == 0) {
								strcpy_s(table[i].state3, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}
						}
					}

					for (kk = 0; kk < TC; kk++) {//a
						for (k = 0; k < 4; k++) {//b
							if (k == 0) {
								if (strcmp(table[kk].state0, "f") == 0) {
									strcpy_s(table[kk].state0, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 1) {
								if (strcmp(table[kk].state1, "f") == 0) {
									strcpy_s(table[kk].state1, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 2) {
								if (strcmp(table[kk].state2, "f") == 0) {
									strcpy_s(table[kk].state2, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 3) {
								if (strcmp(table[kk].state3, "f") == 0) {
									strcpy_s(table[kk].state3, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
						}//b
						if (kk == (TC - 1)) { //더이상 빈 공간이 존재하지 않음 블록 단위로 지우기 시작 c
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
									for (kkk = 0; kkk < 4; kkk++) {
										if (offsetnum == 0) {
											if (strcmp(table[Copy].state0, "u") == 0) {
												fseek(fp4, Findpage * PAGE, SEEK_SET);
												fread(bufferdata, sizeof(char), PAGE, fp4);
												fseek(fp, Copy * PAGE, SEEK_SET);
												for (write2 = 0; write2 < PAGE; write2++) {
													fprintf_s(fp, "%c", bufferdata[write2]);
												}
												reWriteC++;
											}
											if (strcmp(table[Copy].state0, "d") == 0) {
												strcpy_s(table[Copy].state0, SIZE, "f");
											}
										}
									}
									Findpage++;
								}
								fclose(fp4);

							}
							j = -1;
							reWriteC--;

						}//c

					}//a
				}
				else if (strcmp(table[i].state0, "f") == 0) {
					strcpy_s(table[i].state0, SIZE, "u");
					ReturnPBN = atoi(table[i].PBN);
					reWriteC++;
				}
				break;
			}//0off
			if (offsetnum == 3) {// 0off
				if (strcmp(table[i].state0, "u") == 0) {
					for (k = 0; k < 4; k++) {//
						if (k == 0) {
							if (strcmp(table[i].state0, "f") == 0) {
								strcpy_s(table[i].state0, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}

						}
						if (k == 1) {
							if (strcmp(table[i].state1, "f") == 0) {
								strcpy_s(table[i].state1, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}

						}
						if (k == 2) {
							if (strcmp(table[i].state2, "f") == 0) {
								strcpy_s(table[i].state2, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}
						}
					}

					for (kk = 0; kk < TC; kk++) {//a
						for (k = 0; k < 4; k++) {//b
							if (k == 0) {
								if (strcmp(table[kk].state0, "f") == 0) {
									strcpy_s(table[kk].state0, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 1) {
								if (strcmp(table[kk].state1, "f") == 0) {
									strcpy_s(table[kk].state1, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 2) {
								if (strcmp(table[kk].state2, "f") == 0) {
									strcpy_s(table[kk].state2, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 3) {
								if (strcmp(table[kk].state3, "f") == 0) {
									strcpy_s(table[kk].state3, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
						}//b
						if (kk == (TC - 1)) { //더이상 빈 공간이 존재하지 않음 블록 단위로 지우기 시작 c
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
									for (kkk = 0; kkk < 4; kkk++) {
										if (offsetnum == 0) {
											if (strcmp(table[Copy].state0, "u") == 0) {
												fseek(fp4, Findpage * PAGE, SEEK_SET);
												fread(bufferdata, sizeof(char), PAGE, fp4);
												fseek(fp, Copy * PAGE, SEEK_SET);
												for (write2 = 0; write2 < PAGE; write2++) {
													fprintf_s(fp, "%c", bufferdata[write2]);
												}
												reWriteC++;
											}
											if (strcmp(table[Copy].state0, "d") == 0) {
												strcpy_s(table[Copy].state0, SIZE, "f");
											}
										}
									}
									Findpage++;
								}
								fclose(fp4);

							}
							j = -1;
							reWriteC--;

						}//c

					}//a
				}
				else if (strcmp(table[i].state0, "d") == 0) {
					for (k = 0; k < 4; k++) {//
						if (k == 1) {
							if (strcmp(table[i].state1, "f") == 0) {
								strcpy_s(table[i].state1, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}

						}
						if (k == 2) {
							if (strcmp(table[i].state2, "f") == 0) {
								strcpy_s(table[i].state2, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}

						}
						if (k == 3) {
							if (strcmp(table[i].state3, "f") == 0) {
								strcpy_s(table[i].state3, SIZE, "u");
								ReturnPBN = atoi(table[i].PBN);
								offsetnum = k;
								break;
							}
						}
					}

					for (kk = 0; kk < TC; kk++) {//a
						for (k = 0; k < 4; k++) {//b
							if (k == 0) {
								if (strcmp(table[kk].state0, "f") == 0) {
									strcpy_s(table[kk].state0, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 1) {
								if (strcmp(table[kk].state1, "f") == 0) {
									strcpy_s(table[kk].state1, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 2) {
								if (strcmp(table[kk].state2, "f") == 0) {
									strcpy_s(table[kk].state2, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
							if (k == 3) {
								if (strcmp(table[kk].state3, "f") == 0) {
									strcpy_s(table[kk].state3, SIZE, "u");
									ReturnPBN = atoi(table[kk].PBN);
									offsetnum = k;
									break;
								}
							}
						}//b
						if (kk == (TC - 1)) { //더이상 빈 공간이 존재하지 않음 블록 단위로 지우기 시작 c
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
									for (kkk = 0; kkk < 4; kkk++) {
										if (offsetnum == 0) {
											if (strcmp(table[Copy].state0, "u") == 0) {
												fseek(fp4, Findpage * PAGE, SEEK_SET);
												fread(bufferdata, sizeof(char), PAGE, fp4);
												fseek(fp, Copy * PAGE, SEEK_SET);
												for (write2 = 0; write2 < PAGE; write2++) {
													fprintf_s(fp, "%c", bufferdata[write2]);
												}
												reWriteC++;
											}
											if (strcmp(table[Copy].state0, "d") == 0) {
												strcpy_s(table[Copy].state0, SIZE, "f");
											}
										}
									}
									Findpage++;
								}
								fclose(fp4);

							}
							j = -1;
							reWriteC--;

						}//c

					}//a
				}
				else if (strcmp(table[i].state0, "f") == 0) {
					strcpy_s(table[i].state0, SIZE, "u");
					ReturnPBN = atoi(table[i].PBN);
					reWriteC++;
				}
				break;
			}//0off
		}
	}


	fclose(fp2);

	startS = PAGE * ReturnPBN;					// 시작 번지
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

			fseek(fp, PAGE * ReturnPBN, SEEK_SET);// 해당 위치로 이동한다 

			
			
		}
	}

	fopen_s(&fp3, "1MAPPINGTABLE.txt", "w");

	for (RETABLE = 0; RETABLE < TC; RETABLE++) {	// 기존 저장되있던 데이터를 다시 적는다.
		fprintf_s(fp3, "%s %s %s %s %s %s\n", table[RETABLE].LBN, table[RETABLE].PBN, table[RETABLE].state0, table[RETABLE].state1, table[RETABLE].state2, table[RETABLE].state3);
	}


	printf("쓰기 완료.\n");
	printf(" 실제 사용한 블록 : %d\n 실제 사용한 오프셋 : %d", ReturnPBN, offsetnum);
	printf("지우기 %d 회, 쓰기 %d 회 \n", EraseCount, reWriteC);
	while (!_kbhit());

	free(buffer);
	fclose(fp);
	fclose(fp3);
	return;
}