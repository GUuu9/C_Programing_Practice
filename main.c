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

		printf("Input Command // ��ɾ� ���� -> ?\n");
		printf(">> ");
		gets(Function);
		fflush(stdin);
		if (strcmp(Function, "?") == 0) {
			printf("init  => ���� �뷮 ����    - ex) init  ����  ������ MB �Է�\n");
			printf("read  => �ش� LPN �б�	   - ex) read  ����  LPN �Է�\n");
			printf("write => PAGE�� ����       - ex) write ����  PAGE ��ȣ, ���� �Է�\n");
			printf("table => �������̺����.\n");
			printf("end   => ���α׷� ����. \n");
		}

		else if (strcmp(Function, "init") == 0) {
			if (fsize == 0) {
				fsize = init(buffer, table, bufferdata);
			}
			else
				printf("�޸𸮰� �̹� �Ҵ� �Ǿ� �ֽ��ϴ�.");
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
			printf("�����մϴ�.");
			while (!_kbhit());
			return;
		}

		
		fflush(stdin);
		while (!_kbhit());

		system("cls");
	}
	return;
}