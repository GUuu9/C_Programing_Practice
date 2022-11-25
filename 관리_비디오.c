#include "function.h"	//각 기능들을 불러오기 위해 모든 함수와 헤더들을 담아둔 헤더함수



/////////////////////////////////////////////////////////////////////////
//
//			▶ 비 디 오 관 리
//
/////////////////////////////////////////////////////////////////////////

void Manage_Video() {
	VIDEO *Video;
	int selectNumber;
	int CountVideo;

	fflush(stdin);	//버퍼 삭제

	while (1) {


		CountVideo = GetVideoCount();	// 받아온 저장된 비디오의 수 i값을 CountVideo에 저장
		Video = (VIDEO *)malloc((sizeof(VIDEO) * CountVideo));	// Video에 (VIDEO * 저장된 비디오의 수) 만큼의 동적 메모리를 할당.
		GetVideoData(Video, CountVideo);	// 데이터들을 토큰단위로 분리

		Manage_Video_logo();													// 비디오 관리 로고
		printf("		[입력] : ");
		scanf_s("%d", &selectNumber);											// 사용할 기능의 번호를 입력받는다.

		switch (selectNumber) {													// 입력받은 번호에 따라 해당하는 기능이 실행
		case 1: { system("cls"); Video_add(CountVideo); return; }				// 비디오 추가

		case 2: { system("cls"); Video_delete(Video, CountVideo); return; }		// 비디오 삭제

		case 3: { system("cls"); Video_rename(Video, CountVideo); return;  }	// 비디오 정보 수정
		}

		getchar();
		system("cls");	// 화면 초기화
	}

	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			▶ 비 디 오 추 가
//
/////////////////////////////////////////////////////////////////////////

void Video_add(int Count) {		// 비디오 추가
	FILE *fp;
	VIDEO Video;	// 비디오 구조체

	Create_Video_logo();

	fopen_s(&fp, "video_list.txt", "a");			// 비디오가 저장되는 파일을 읽기쓰기 모드로 연다.


	getchar();

	printf("  제  목  : "); gets_s(Video.videoname, SIZE);		//비디오의 정보를 입력 받는다.
	printf(" 재생시간 : "); gets_s(Video.runtime, SIZE);
	printf("  장  르  : "); gets_s(Video.genre, SIZE);
	printf("  등  급  : "); gets_s(Video.grade, SIZE);
	printf("  연  도  : "); gets_s(Video.year, SIZE);
	printf(" 대여여부 : "); gets_s(Video.rent, SIZE);

	fprintf_s(fp, "/%s/%s/%s/%s/%s/%s/\n", Video.videoname, Video.runtime, Video.genre, Video.grade, Video.year, Video.rent);
															// 입력받은 정보를 형식에 맞춰 저장
	fclose(fp);

	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			▶ 비 디 오 삭 제
//
/////////////////////////////////////////////////////////////////////////

void Video_delete(VIDEO *Video, int Count) {	// 비디오 삭제
	Video_delete_logo();
	FILE *fp;
	int i, j;
	int userexist = 0;
	char name[SIZE];

	getchar();

	printf("\n [입력] : ");	// 찾을 비디오의 이름 입력
	gets(name);

	for (i = 0; i < Count; i++) {
		if (strcmp(Video[i].videoname, name) == 0) {	// 동일한 비디오 탐색
			printf(" ▶ %s / %s / %s / %s / %s / %s\n", Video[i].videoname, Video[i].runtime,
					Video[i].genre, Video[i].grade, Video[i].year, Video[i].rent);
			userexist = 1;
			break;
		}

	}



	if (userexist == 0)
		printf(" ▶ 해당 데이터가 존재하지 않습니다.\n");

	else {	// 동일한 데이터 존재시
		while (1) {

			fopen_s(&fp, "video_list.txt", "w");	// 쓰기 모드로 파일 실행

			for (j = 0; j < Count ; j++) {
				if (j == i) continue;	// 동일한 데이터가 존재하는 라인을 제외한 나머지 라인을 다시 작성
				fprintf_s(fp, "/%s/%s/%s/%s/%s/%s/\n", Video[j].videoname, Video[j].runtime,
								Video[j].genre, Video[j].grade, Video[j].year, Video[j].rent);
			}


			printf(" ▶ 삭제가 완료되었습니다...\n\n");
			getchar();

			fclose(fp);

			return;
		}

	}
	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			▶ 비 디 오 정 보 수 정
//
/////////////////////////////////////////////////////////////////////////

void Video_rename(VIDEO *Video, int Count) {	// 비디오 정보 수정
	Video_rename_logo();
	FILE *fp;
	int i, j;
	int userexist = 0;
	char name[SIZE];

	getchar();

	printf("\n [입력] : ");		// 수정하려는 비디오 이름 입력
	gets(name);

	for (i = 0; i < Count; i++) {
		if (strcmp(Video[i].videoname, name) == 0) {	// 동일한 내용이 존재하면 출력
			if (strcmp(Video[i].rent, "대여가능") == 0) {
				printf(" ▶ %s / %s / %s / %s / %s / %s\n\n", Video[i].videoname, Video[i].runtime,
					Video[i].genre, Video[i].grade, Video[i].year, Video[i].rent);
				userexist = 1;
				break;
			}
		}

	}



if (userexist == 0)
printf(" ▶ 해당 데이터가 존재하지 않거나 대여 중 이므로 수정이 불가능 합니다.\n");

else {	// 동일 데이터 존재시 
	while (1) {

		printf(" ▶ 정보를 다시 입력 해 주세요\n\n");

		getchar();

		printf("  제  목  : "); gets_s(Video[i].videoname, SIZE);	// 현 위치에 정보를 다시 입력 받음
		printf(" 재생시간 : "); gets_s(Video[i].runtime, SIZE);
		printf("  장  르  : "); gets_s(Video[i].genre, SIZE);
		printf("  등  급  : "); gets_s(Video[i].grade, SIZE);
		printf("  연  도  : "); gets_s(Video[i].year, SIZE);
		printf(" 대여여부 : "); gets_s(Video[i].rent, SIZE);

		fopen_s(&fp, "video_list.txt", "w");	// w모드로 기존 내용을 삭제하고 파일을 연다.

		for (j = 0; j < Count; j++) {	// 기존 저장되있던 데이터를 다시 적는다.
			fprintf_s(fp, "/%s/%s/%s/%s/%s/%s/\n", Video[j].videoname, Video[j].runtime, Video[j].genre,
				Video[j].grade, Video[j].year, Video[j].rent);
		}


		printf(" ▶ 수정이 완료되었습니다...\n");
		getchar();

		fclose(fp);

		return;
	}
}
return;
}



/////////////////////////////////////////////////////////////////////////
//
//			▶ 비 디 오 검 색
//
/////////////////////////////////////////////////////////////////////////

void Video_search(VIDEO *Video, int Count) {	// 비디오 검색

	Video_search_logo();

	FILE *fp;
	int i;
	int videoexist = 0;
	char videoname[SIZE];

	getchar();

	printf("\n [입력] : ");	// 찾으려 하는 비디오의 이름을 입력
	gets(videoname);

	fopen_s(&fp, "video_list.txt", "r");	// 읽기 모드로 member_list파일 열기

	for (i = 0; i < Count; i++) {
		if (strcmp(Video[i].videoname, videoname) == 0) {	// 동일한 내용 존재시 출력
			printf("%s / %s / %s / %s / %s / %s\n", Video[i].videoname, Video[i].runtime, Video[i].genre,
				Video[i].grade, Video[i].year, Video[i].rent);
			videoexist = 1;
		}
	}

	if (videoexist == 0)
		printf("해당 데이터가 존재하지 않습니다.");

	getchar();

	fclose(fp);

	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			▶ 비 디 오 목 록
//
/////////////////////////////////////////////////////////////////////////

void Video_list(VIDEO *Video, int Count) {		// 비디오 목록

	Video_list_logo();

	FILE *fp;
	int j;
	//

	int x, y, min;
	VIDEO tmp;

	for (x = 0; x < Count; x++) {											//선택정렬
		for (y = x + 1; y < Count; y++) {									// 현재 값과 뒤의 값을 비교해가며
			if (strcmp ((Video[y]).videoname, Video[x].videoname) < 0){		// 현재보다 큰 값 발견시 파일의 위치를 서로 바꾸어준다.
			tmp = Video[x];
			Video[x] = Video[y];
			Video[y] = tmp;
}
		}
	}

//
	fopen_s(&fp, "video_list.txt", "r");	// 읽기 모드로 video_list파일 열기

	j = Count;	
	for (Count = 0; Count < j; Count++) {	// 저장된 내용들을 출력한다.
		printf("%s / %s / %s / %s / %s / %s\n", Video[Count].videoname, Video[Count].runtime,
				Video[Count].genre, Video[Count].grade, Video[Count].year, Video[Count].rent);
	}
	getchar();

	fclose(fp);

	return;
}