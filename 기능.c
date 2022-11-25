#include "function.h"	//�� ��ɵ��� �ҷ����� ���� ��� �Լ��� ������� ��Ƶ� ����Լ�


/////////////////////////////////////////////////////
//
//			�� �� �� �� ��
//
/////////////////////////////////////////////////////

void Create_File() {

	FILE *fp;

	fopen_s(&fp, "member_list.txt", "a"); fclose(fp);	// a���� ������ ����, ������ ���ٸ� ������ �����˴ϴ�.
	fopen_s(&fp, "Video_list.txt", "a"); fclose(fp);
	fopen_s(&fp, "rent_list.txt", "a");	fclose(fp);

}



/////////////////////////////////////////////////////
//
//			�� �� �� �� ȸ �� �� �� ü ũ
//
/////////////////////////////////////////////////////

int GetMemberCount() {
	FILE *fp;
	int i;
	char Buffer[SIZE * 5];								// SIZE * 5 (300) ��ŭ�� ���� �迭 ����

	fopen_s(&fp, "member_list.txt", "r");				// member_list ������ �б� ���� ����

	for (i = 0; fgets(Buffer, SIZE * 5, fp); i++) {};	// ����� MEMBER�� �� Ȯ�� ��� ����ŭ i�� ����
														// �ѹ��� SIZE * 5 �� ũ�⸸ŭ�� �н��ϴ�.
	fclose(fp);											// ���� �ݱ�

	return i;										// i�� ��ȯ
}



/////////////////////////////////////////////////////
//
//			�� �� �� �� �� ��
//
/////////////////////////////////////////////////////

void GetMemberData(MEMBER *Member, int Count) {	 // ����ü�� ����Ű�� �����Ϳ� ������ Ȯ���� i���� �޾ƿ´�.
	FILE *fp;
	int i;
	char Buffer[SIZE * 5];	// 300ũ���� Buffer �迭 ����
	char *null = NULL;	// NULL�� ������ ������	 ���� ���� ���� ����Ű�� ���� �����ͷ� ����� �ݴϴ�.

	fopen_s(&fp, "member_list.txt", "r");	// �б� ���� member_list���� ����

	for (i = 0; i < Count ; i++) {	// ����� �����͸� ��ū������ �д´�.
		fgets(Buffer, SIZE * 5, fp);
		strcpy_s(Member[i].name, SIZE, strtok_s(Buffer, "/", &null));		// "/"�� �и��ڷ� ����Ͽ� �����͸� �����մϴ�..
		strcpy_s(Member[i].id, SIZE, strtok_s(NULL, "/", &null));			// ��� ��ū���� �޾ƿ����� ��� �б����� �ι�°���� NULL��
		strcpy_s(Member[i].password, SIZE, strtok_s(NULL, "/", &null));		// ����ü�� i��°�� ������ ��ū �������� ������ ����˴ϴ�.
		strcpy_s(Member[i].cellphone, SIZE, strtok_s(NULL, "/", &null));
		strcpy_s(Member[i].adress, SIZE, strtok_s(NULL, "/", &null));
	}

	fclose(fp);
}



/////////////////////////////////////////////////////
//
//			�� �� �� �� �� �� �� �� �� ü ũ
//
/////////////////////////////////////////////////////

int	GetVideoCount() {
	FILE *fp;
	int i;
	char Buffer[SIZE * 6];								// SIZE * 5 (360) ��ŭ�� ���� �迭 ����

	fopen_s(&fp, "Video_list.txt", "r");				// video_list ������ �б� ���� ����

	for (i = 0; fgets(Buffer, SIZE * 6, fp); i++) {};	// ����� VIDEO�� �� Ȯ�� ������ ����ŭ i�� ����
														// �ѹ��� SIZE * 6�� ũ�⸸ŭ�� �н��ϴ�.
	fclose(fp);											// ���� �ݱ�

	return i;											// i�� ��ȯ
}



/////////////////////////////////////////////////////
//
//			�� �� �� �� �� ��
//
/////////////////////////////////////////////////////

void GetVideoData(VIDEO *Video, int Count) {	// ����ü�� ����Ű�� �����Ϳ� ������ Ȯ���� i���� �޾ƿ´�.
	FILE *fp;
	int i;
	char Buffer[SIZE * 6];	// 360ũ���� Buffer �迭 ����
	char *null = NULL;	// NULL�� ������ ������ ���� ���� ���� ����Ű�� ���� �����ͷ� ����� �ݴϴ�.

	fopen_s(&fp, "video_list.txt", "r");	// �б� ���� video_list���� ����

	for (i = 0; i < Count ; i++) {	// ����� �����͸� ��ū������ �д´�.
		fgets(Buffer, SIZE * 6, fp);
		strcpy_s(Video[i].videoname, SIZE, strtok_s(Buffer, "/", &null));	// "/"�� �и��ڷ� ����Ͽ� �����͸� �����մϴ�..
		strcpy_s(Video[i].runtime, SIZE, strtok_s(NULL, "/", &null));		// ��� ��ū���� �޾ƿ����� ��� �б����� �ι�°���� NULL��
		strcpy_s(Video[i].genre, SIZE, strtok_s(NULL, "/", &null));			// ����ü�� i��°�� ������ ��ū �������� ������ ����˴ϴ�.
		strcpy_s(Video[i].grade, SIZE, strtok_s(NULL, "/", &null));
		strcpy_s(Video[i].year, SIZE, strtok_s(NULL, "/", &null));
		strcpy_s(Video[i].rent, SIZE, strtok_s(NULL, "/", &null));
	}

	fclose(fp);
}



/////////////////////////////////////////////////////
//
//			�� �� �� �� �� �� �� �� ü ũ
//
/////////////////////////////////////////////////////

int GetRentCount() {
	FILE *fp;
	int i;
	char Buffer[SIZE * 2];								// SIZE * 2 (120) ��ŭ�� ���� �迭 ����

	fopen_s(&fp, "rent_list.txt", "r");					// rent_list ������ �б� ���� ����

	for (i = 0; fgets(Buffer, SIZE * 2, fp); i++) {};	// ����� RENT�� �� Ȯ�� ��� ����ŭ i�� ����
														// �ѹ��� SIZE * 2�� ũ�⸸ŭ�� �н��ϴ�.
	fclose(fp);											// ���� �ݱ�

	return i;										// i�� ��ȯ
}




/////////////////////////////////////////////////////
//
//			�� �� �� �� �� ��
//
/////////////////////////////////////////////////////

void GetRentData(RENT *Rent, int Count) {	// ����ü�� ����Ű�� �����Ϳ� ������ Ȯ���� i���� �޾ƿ´�.
	FILE *fp;
	int i;
	char Buffer[SIZE * 2];	// 120ũ���� Buffer �迭 ����
	char *null = NULL;	// NULL�� ������ ������ ���� ���� ���� ����Ű�� ���� �����ͷ� ����� �ݴϴ�.

	fopen_s(&fp, "rent_list.txt", "r");	// �б� ���� rent_list���� ����

	for (i = 0; i < Count ; i++) {	// ����� �����͸� ��ū������ �д´�.
		fgets(Buffer, SIZE * 2, fp);

		strcpy_s(Rent[i].Rvideoname, SIZE, strtok_s(Buffer, "/", &null));	// "/"�� �и��ڷ� ����Ͽ� �����͸� �����մϴ�..
		strcpy_s(Rent[i].Rname, SIZE, strtok_s(NULL, "/", &null));			// ��� ��ū���� �޾ƿ����� ��� �б����� �ι�°���� NULL��
	}																		// ����ü�� i��°�� ������ ��ū �������� ������ ����˴ϴ�.

	fclose(fp);
}