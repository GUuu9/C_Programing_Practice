#include "function.h"	//�� ��ɵ��� �ҷ����� ���� ��� �Լ��� ������� ��Ƶ� ����Լ�



/////////////////////////////////////////////////////////////////////////
//
//			�� �� �� �� �� ��
//
/////////////////////////////////////////////////////////////////////////

void Video_rent(RENT *Rent, VIDEO * Video, MEMBER *Member, int MCount, int VCount) {	// ���� �뿩
	FILE *fp; 
	int i, j;
	char Rvideoname[SIZE];
	char Rname[SIZE];

	Vidoe_rent_logo();

	getchar();
	printf(" �� �뿩�Ͻ� ��ȭ�� ������ ��Ȯ�� �Է��Ͽ� �ּ���.\n");
	printf("   ��  ��   : ");	// �뿩�� ��ȭ�� ���� �Է�
	gets(Rvideoname);

	for (i = 0; i < VCount; i++) {
		if (strcmp(Video[i].videoname, Rvideoname) == 0) {	// ��ġ �ϸ� ����


			if (strcmp(Video[i].rent, "�뿩����") == 0) {	// �뿩 ������ �� �뿩��� ������ ���� ���
				printf(" �� �뿩�Ͻ� ������ ������ �����ϴ�.\n");
				printf(" �� %s / %s / %s / %s / %s / %s\n", Video[i].videoname, Video[i].runtime,
					Video[i].genre, Video[i].grade, Video[i].year, Video[i].rent);
				break;
			}

			else {	// �ƴҰ�� ���
				printf(" �� �뿩 �Ұ�.\n");
				return;
			}
		}
	}
	printf(" �� �뿩�ں��� ���� �Է��� �ּ���.\n");
	printf("   ��  ��   : ");	// �뿩�� ȸ�� �̸� �Է�
	gets(Rname);

	for (j = 0; j < MCount; j++) {
		if (strcmp(Member[j].name, Rname) == 0) {	// ȸ�� ���� ��ġ��
			printf("�뿩�� �Ϸ� �Ǿ����ϴ�.\n��ſ� �Ϸ� ��������.\n");

			fopen_s(&fp, "rent_list.txt", "a"); // �б� ���� ���� ���� ����

			fprintf_s(fp, "/%s/%s/\n", Video[i].videoname, Member[j].name);	// ���Ͽ� ������ �̸��� �ɹ��� �̸� ����
			
			fclose(fp);

			strcpy_s(Video[i].rent, SIZE, "�뿩�Ұ�");	// �뿩�� ���� �뿩 ���θ� �뿩 �Ұ� ���·� �������ش�.

			fopen_s(&fp, "video_list.txt", "w");	

			for (i = 0; i < VCount; i++) {	// �뿩 �Ұ��� ����� ���·� ������ ������ ���� �ٽ� ���´�.
				fprintf_s(fp, "/%s/%s/%s/%s/%s/%s/\n", Video[i].videoname,
					Video[i].runtime, Video[i].genre, Video[i].grade, Video[i].year, Video[i].rent);
			}

			fclose(fp);

		}
	}
	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			�� �� �� �� �� ��
//
/////////////////////////////////////////////////////////////////////////

void Video_return(RENT *Rent, VIDEO * Video, MEMBER *Member, int RCount, int VCount) {	// ���� �ݳ�
	Video_return_logo();

	FILE *fp;
	int i, j, k;
	int userexist = 0;
	char Rvideoname[SIZE];


	printf(" �ݳ��Ͻ� ������ �̸��� �Է�"); // �ݳ��� ���� �̸� �Է� ����
	getchar();
	
	printf("\n [�Է�] : ");
	gets(Rvideoname);

	for (i = 0; i < RCount; i++) {
		if (strcmp(Rent[i].Rvideoname, Rvideoname) == 0) {	// �ش� ������ ������ ���
			printf(" �� %s / %s \n", Rent[i].Rvideoname, Rent[i].Rname);
			userexist = 1;
			break;
		}

	}



	if (userexist == 0)
		printf(" �� �ش� �����Ͱ� �������� �ʽ��ϴ�.\n");

	else {	//������ ����� ����
		while (1) {

			for (k = 0; k < VCount; k++) {
				if (strcmp(Video[k].videoname, Rvideoname) == 0) {

					strcpy_s(Video[k].rent, SIZE, "�뿩����");	// ������ �뿩 ���θ� �뿩 ���� ���� �������ش�

					fopen_s(&fp, "video_list.txt", "w");

					for (k = 0; k < VCount; k++) {	// �뿩 ���ɻ��·� ������ ���� �����͸� ���� �ٽ� �����ش�.
						fprintf_s(fp, "/%s/%s/%s/%s/%s/%s/\n", Video[k].videoname, Video[k].runtime,
							Video[k].genre, Video[k].grade, Video[k].year, Video[k].rent);
					}

					fclose(fp);
				}
			}

			fopen_s(&fp, "rent_list.txt", "w");

			for (j = 0; j < RCount; j++) {	// �ش� ������ ������ �������� �ٽ� ���Ͽ� ���´�.
				if (j == i) continue;
				fprintf_s(fp, "/%s/%s/\n", Rent[j].Rvideoname, Rent[j].Rname);
			}


			printf(" �� �ݳ��� �Ϸ�Ǿ����ϴ�...\n\n");
			getchar();

			fclose(fp);

			return;
		}

	}
	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			�� �� �� �� ��
//
/////////////////////////////////////////////////////////////////////////

void Rent_list(RENT *Rent, int Count) {	// �뿩 ���

	FILE *fp;

	int j;
	char Buffer[SIZE * 2];	// 120ũ���� Buffer �迭 ����
	char *null = NULL;	// NULL�� ������ ������

	Rent_list_logo();

	fopen_s(&fp, "rent_list.txt", "r");	// �б� ���� rent_list���� ����



	j = Count;	// ����� ������ ���
	for (Count = 0; Count < j; Count++) {
		printf("%s / %s \n", Rent[Count].Rvideoname, Rent[Count].Rname);
	}
	getchar();

	fclose(fp);

	return;
}