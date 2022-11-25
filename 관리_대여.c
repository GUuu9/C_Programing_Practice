#include "function.h"	//각 기능들을 불러오기 위해 모든 함수와 헤더들을 담아둔 헤더함수



/////////////////////////////////////////////////////////////////////////
//
//			▶ 비 디 오 대 여
//
/////////////////////////////////////////////////////////////////////////

void Video_rent(RENT *Rent, VIDEO * Video, MEMBER *Member, int MCount, int VCount) {	// 비디오 대여
	FILE *fp; 
	int i, j;
	char Rvideoname[SIZE];
	char Rname[SIZE];

	Vidoe_rent_logo();

	getchar();
	printf(" ▶ 대여하실 영화의 제목을 정확히 입력하여 주세요.\n");
	printf("   제  목   : ");	// 대여할 영화의 제목 입력
	gets(Rvideoname);

	for (i = 0; i < VCount; i++) {
		if (strcmp(Video[i].videoname, Rvideoname) == 0) {	// 일치 하면 실행


			if (strcmp(Video[i].rent, "대여가능") == 0) {	// 대여 가능할 시 대여기능 실행후 내용 출력
				printf(" ▶ 대여하실 비디오는 다음과 같습니다.\n");
				printf(" ▶ %s / %s / %s / %s / %s / %s\n", Video[i].videoname, Video[i].runtime,
					Video[i].genre, Video[i].grade, Video[i].year, Video[i].rent);
				break;
			}

			else {	// 아닐경우 출력
				printf(" ▶ 대여 불가.\n");
				return;
			}
		}
	}
	printf(" ▶ 대여자분의 성함 입력해 주세요.\n");
	printf("   이  름   : ");	// 대여할 회원 이름 입력
	gets(Rname);

	for (j = 0; j < MCount; j++) {
		if (strcmp(Member[j].name, Rname) == 0) {	// 회원 내용 일치시
			printf("대여가 완료 되었습니다.\n즐거운 하루 보내세요.\n");

			fopen_s(&fp, "rent_list.txt", "a"); // 읽기 쓰기 모드로 파일 열기

			fprintf_s(fp, "/%s/%s/\n", Video[i].videoname, Member[j].name);	// 파일에 비디오의 이름과 맴버의 이름 저장
			
			fclose(fp);

			strcpy_s(Video[i].rent, SIZE, "대여불가");	// 대여할 비디오 대여 여부를 대여 불가 상태로 변경해준다.

			fopen_s(&fp, "video_list.txt", "w");	

			for (i = 0; i < VCount; i++) {	// 대여 불가로 변경된 상태로 나머지 정보를 전부 다시 적는다.
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
//			▶ 비 디 오 반 납
//
/////////////////////////////////////////////////////////////////////////

void Video_return(RENT *Rent, VIDEO * Video, MEMBER *Member, int RCount, int VCount) {	// 비디오 반납
	Video_return_logo();

	FILE *fp;
	int i, j, k;
	int userexist = 0;
	char Rvideoname[SIZE];


	printf(" 반납하실 비디오의 이름을 입력"); // 반납할 비디오 이름 입력 받음
	getchar();
	
	printf("\n [입력] : ");
	gets(Rvideoname);

	for (i = 0; i < RCount; i++) {
		if (strcmp(Rent[i].Rvideoname, Rvideoname) == 0) {	// 해당 내용이 있으면 출력
			printf(" ▶ %s / %s \n", Rent[i].Rvideoname, Rent[i].Rname);
			userexist = 1;
			break;
		}

	}



	if (userexist == 0)
		printf(" ▶ 해당 데이터가 존재하지 않습니다.\n");

	else {	//데이터 존재시 실행
		while (1) {

			for (k = 0; k < VCount; k++) {
				if (strcmp(Video[k].videoname, Rvideoname) == 0) {

					strcpy_s(Video[k].rent, SIZE, "대여가능");	// 비디오의 대여 여부를 대여 가능 으로 변경해준다

					fopen_s(&fp, "video_list.txt", "w");

					for (k = 0; k < VCount; k++) {	// 대여 가능상태로 변경후 기존 데이터를 전부 다시 적어준다.
						fprintf_s(fp, "/%s/%s/%s/%s/%s/%s/\n", Video[k].videoname, Video[k].runtime,
							Video[k].genre, Video[k].grade, Video[k].year, Video[k].rent);
					}

					fclose(fp);
				}
			}

			fopen_s(&fp, "rent_list.txt", "w");

			for (j = 0; j < RCount; j++) {	// 해당 라인을 제외한 나머지를 다시 파일에 적는다.
				if (j == i) continue;
				fprintf_s(fp, "/%s/%s/\n", Rent[j].Rvideoname, Rent[j].Rname);
			}


			printf(" ▶ 반납이 완료되었습니다...\n\n");
			getchar();

			fclose(fp);

			return;
		}

	}
	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			▶ 대 여 목 록
//
/////////////////////////////////////////////////////////////////////////

void Rent_list(RENT *Rent, int Count) {	// 대여 목록

	FILE *fp;

	int j;
	char Buffer[SIZE * 2];	// 120크기의 Buffer 배열 생성
	char *null = NULL;	// NULL값 지정용 포인터

	Rent_list_logo();

	fopen_s(&fp, "rent_list.txt", "r");	// 읽기 모드로 rent_list파일 열기



	j = Count;	// 저장된 데이터 출력
	for (Count = 0; Count < j; Count++) {
		printf("%s / %s \n", Rent[Count].Rvideoname, Rent[Count].Rname);
	}
	getchar();

	fclose(fp);

	return;
}