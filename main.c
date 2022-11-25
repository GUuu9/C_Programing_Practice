#include "function.h"

void main() {
	char *buffer;
	TABLE *table;
	char *bufferdata;
	char Function[10];
	int fsize = 0, i = 0;
	char *null = NULL;
	int allo = 0;

	File_Create();
	printf("PRESS ENTER KEY\n");

	buffer = (char *)malloc((sizeof(char) * fsize));
	bufferdata = (char *)malloc((sizeof(char) * BLOCK));

	while (!_kbhit());
	fflush(stdin);
	system("cls");



	while (1) {

		fsize = File_Size();

		allo = fsize / BLOCK;

		table = (TABLE *)malloc((sizeof(TABLE) * allo));

		if (fsize != 0) {
			table_cut(table, fsize);
		}

		printf("Input Command // 명령어 보기 -> ?\n");
		printf(">> ");
		gets(Function);
		fflush(stdin);
		if (strcmp(Function, "?") == 0) {
			printf("init  => 파일 용량 설정    - ex) init  이후  생성할 MB 입력\n");
			printf("read  => 해당 LPN 읽기	   - ex) read  이후  LPN 입력\n");
			printf("write => PAGE에 적기       - ex) write 이후  PAGE 번호, 내용 입력\n");
			printf("table => 매핑테이블출력.\n");
			printf("end   => 프로그램 종료. \n");
		}

		else if (strcmp(Function, "init") == 0) {
			if (fsize == 0) {
				fsize = init(buffer, table, bufferdata);
			}
			else
				printf("메모리가 이미 할당 되어 있습니다.");
		}
		else if (strcmp(Function, "read") == 0) {
			FTL_read(buffer, fsize, table);
		}
		else if (strcmp(Function, "write") == 0) {
			FTL_write(buffer, fsize, table, bufferdata);
		}
		else if (strcmp(Function, "table") == 0) {
			Print_table(table, fsize);
		}
		else if (strcmp(Function, "end") == 0) {
			printf("종료합니다.");
			while (!_kbhit());
			return;
		}

		
		fflush(stdin);
		while (!_kbhit());

		system("cls");
	}
	return;
}