#include "function.h"	//�� ��ɵ��� �ҷ����� ���� ��� �Լ��� ������� ��Ƶ� ����Լ�



/////////////////////////////////////////////////////////////////////////
//
//			�� �� �� �� �� ��
//
/////////////////////////////////////////////////////////////////////////

void Manage_Video() {
	VIDEO *Video;
	int selectNumber;
	int CountVideo;

	fflush(stdin);	//���� ����

	while (1) {


		CountVideo = GetVideoCount();	// �޾ƿ� ����� ������ �� i���� CountVideo�� ����
		Video = (VIDEO *)malloc((sizeof(VIDEO) * CountVideo));	// Video�� (VIDEO * ����� ������ ��) ��ŭ�� ���� �޸𸮸� �Ҵ�.
		GetVideoData(Video, CountVideo);	// �����͵��� ��ū������ �и�

		Manage_Video_logo();													// ���� ���� �ΰ�
		printf("		[�Է�] : ");
		scanf_s("%d", &selectNumber);											// ����� ����� ��ȣ�� �Է¹޴´�.

		switch (selectNumber) {													// �Է¹��� ��ȣ�� ���� �ش��ϴ� ����� ����
		case 1: { system("cls"); Video_add(CountVideo); return; }				// ���� �߰�

		case 2: { system("cls"); Video_delete(Video, CountVideo); return; }		// ���� ����

		case 3: { system("cls"); Video_rename(Video, CountVideo); return;  }	// ���� ���� ����
		}

		getchar();
		system("cls");	// ȭ�� �ʱ�ȭ
	}

	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			�� �� �� �� �� ��
//
/////////////////////////////////////////////////////////////////////////

void Video_add(int Count) {		// ���� �߰�
	FILE *fp;
	VIDEO Video;	// ���� ����ü

	Create_Video_logo();

	fopen_s(&fp, "video_list.txt", "a");			// ������ ����Ǵ� ������ �б⾲�� ���� ����.


	getchar();

	printf("  ��  ��  : "); gets_s(Video.videoname, SIZE);		//������ ������ �Է� �޴´�.
	printf(" ����ð� : "); gets_s(Video.runtime, SIZE);
	printf("  ��  ��  : "); gets_s(Video.genre, SIZE);
	printf("  ��  ��  : "); gets_s(Video.grade, SIZE);
	printf("  ��  ��  : "); gets_s(Video.year, SIZE);
	printf(" �뿩���� : "); gets_s(Video.rent, SIZE);

	fprintf_s(fp, "/%s/%s/%s/%s/%s/%s/\n", Video.videoname, Video.runtime, Video.genre, Video.grade, Video.year, Video.rent);
															// �Է¹��� ������ ���Ŀ� ���� ����
	fclose(fp);

	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			�� �� �� �� �� ��
//
/////////////////////////////////////////////////////////////////////////

void Video_delete(VIDEO *Video, int Count) {	// ���� ����
	Video_delete_logo();
	FILE *fp;
	int i, j;
	int userexist = 0;
	char name[SIZE];

	getchar();

	printf("\n [�Է�] : ");	// ã�� ������ �̸� �Է�
	gets(name);

	for (i = 0; i < Count; i++) {
		if (strcmp(Video[i].videoname, name) == 0) {	// ������ ���� Ž��
			printf(" �� %s / %s / %s / %s / %s / %s\n", Video[i].videoname, Video[i].runtime,
					Video[i].genre, Video[i].grade, Video[i].year, Video[i].rent);
			userexist = 1;
			break;
		}

	}



	if (userexist == 0)
		printf(" �� �ش� �����Ͱ� �������� �ʽ��ϴ�.\n");

	else {	// ������ ������ �����
		while (1) {

			fopen_s(&fp, "video_list.txt", "w");	// ���� ���� ���� ����

			for (j = 0; j < Count ; j++) {
				if (j == i) continue;	// ������ �����Ͱ� �����ϴ� ������ ������ ������ ������ �ٽ� �ۼ�
				fprintf_s(fp, "/%s/%s/%s/%s/%s/%s/\n", Video[j].videoname, Video[j].runtime,
								Video[j].genre, Video[j].grade, Video[j].year, Video[j].rent);
			}


			printf(" �� ������ �Ϸ�Ǿ����ϴ�...\n\n");
			getchar();

			fclose(fp);

			return;
		}

	}
	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			�� �� �� �� �� �� �� ��
//
/////////////////////////////////////////////////////////////////////////

void Video_rename(VIDEO *Video, int Count) {	// ���� ���� ����
	Video_rename_logo();
	FILE *fp;
	int i, j;
	int userexist = 0;
	char name[SIZE];

	getchar();

	printf("\n [�Է�] : ");		// �����Ϸ��� ���� �̸� �Է�
	gets(name);

	for (i = 0; i < Count; i++) {
		if (strcmp(Video[i].videoname, name) == 0) {	// ������ ������ �����ϸ� ���
			if (strcmp(Video[i].rent, "�뿩����") == 0) {
				printf(" �� %s / %s / %s / %s / %s / %s\n\n", Video[i].videoname, Video[i].runtime,
					Video[i].genre, Video[i].grade, Video[i].year, Video[i].rent);
				userexist = 1;
				break;
			}
		}

	}



if (userexist == 0)
printf(" �� �ش� �����Ͱ� �������� �ʰų� �뿩 �� �̹Ƿ� ������ �Ұ��� �մϴ�.\n");

else {	// ���� ������ ����� 
	while (1) {

		printf(" �� ������ �ٽ� �Է� �� �ּ���\n\n");

		getchar();

		printf("  ��  ��  : "); gets_s(Video[i].videoname, SIZE);	// �� ��ġ�� ������ �ٽ� �Է� ����
		printf(" ����ð� : "); gets_s(Video[i].runtime, SIZE);
		printf("  ��  ��  : "); gets_s(Video[i].genre, SIZE);
		printf("  ��  ��  : "); gets_s(Video[i].grade, SIZE);
		printf("  ��  ��  : "); gets_s(Video[i].year, SIZE);
		printf(" �뿩���� : "); gets_s(Video[i].rent, SIZE);

		fopen_s(&fp, "video_list.txt", "w");	// w���� ���� ������ �����ϰ� ������ ����.

		for (j = 0; j < Count; j++) {	// ���� ������ִ� �����͸� �ٽ� ���´�.
			fprintf_s(fp, "/%s/%s/%s/%s/%s/%s/\n", Video[j].videoname, Video[j].runtime, Video[j].genre,
				Video[j].grade, Video[j].year, Video[j].rent);
		}


		printf(" �� ������ �Ϸ�Ǿ����ϴ�...\n");
		getchar();

		fclose(fp);

		return;
	}
}
return;
}



/////////////////////////////////////////////////////////////////////////
//
//			�� �� �� �� �� ��
//
/////////////////////////////////////////////////////////////////////////

void Video_search(VIDEO *Video, int Count) {	// ���� �˻�

	Video_search_logo();

	FILE *fp;
	int i;
	int videoexist = 0;
	char videoname[SIZE];

	getchar();

	printf("\n [�Է�] : ");	// ã���� �ϴ� ������ �̸��� �Է�
	gets(videoname);

	fopen_s(&fp, "video_list.txt", "r");	// �б� ���� member_list���� ����

	for (i = 0; i < Count; i++) {
		if (strcmp(Video[i].videoname, videoname) == 0) {	// ������ ���� ����� ���
			printf("%s / %s / %s / %s / %s / %s\n", Video[i].videoname, Video[i].runtime, Video[i].genre,
				Video[i].grade, Video[i].year, Video[i].rent);
			videoexist = 1;
		}
	}

	if (videoexist == 0)
		printf("�ش� �����Ͱ� �������� �ʽ��ϴ�.");

	getchar();

	fclose(fp);

	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			�� �� �� �� �� ��
//
/////////////////////////////////////////////////////////////////////////

void Video_list(VIDEO *Video, int Count) {		// ���� ���

	Video_list_logo();

	FILE *fp;
	int j;
	//

	int x, y, min;
	VIDEO tmp;

	for (x = 0; x < Count; x++) {											//��������
		for (y = x + 1; y < Count; y++) {									// ���� ���� ���� ���� ���ذ���
			if (strcmp ((Video[y]).videoname, Video[x].videoname) < 0){		// ���纸�� ū �� �߽߰� ������ ��ġ�� ���� �ٲپ��ش�.
			tmp = Video[x];
			Video[x] = Video[y];
			Video[y] = tmp;
}
		}
	}

//
	fopen_s(&fp, "video_list.txt", "r");	// �б� ���� video_list���� ����

	j = Count;	
	for (Count = 0; Count < j; Count++) {	// ����� ������� ����Ѵ�.
		printf("%s / %s / %s / %s / %s / %s\n", Video[Count].videoname, Video[Count].runtime,
				Video[Count].genre, Video[Count].grade, Video[Count].year, Video[Count].rent);
	}
	getchar();

	fclose(fp);

	return;
}