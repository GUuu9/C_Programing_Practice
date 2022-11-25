#include "function.h"	//각 기능들을 불러오기 위해 모든 함수와 헤더들을 담아둔 헤더함수


/////////////////////////////////////////////////////
//
//			▶ 파 일 생 성
//
/////////////////////////////////////////////////////

void Create_File() {

	FILE *fp;

	fopen_s(&fp, "member_list.txt", "a"); fclose(fp);	// a모드로 파일을 열때, 파일이 없다면 파일이 생성됩니다.
	fopen_s(&fp, "Video_list.txt", "a"); fclose(fp);
	fopen_s(&fp, "rent_list.txt", "a");	fclose(fp);

}



/////////////////////////////////////////////////////
//
//			▶ 저 장 된 회 원 의 수 체 크
//
/////////////////////////////////////////////////////

int GetMemberCount() {
	FILE *fp;
	int i;
	char Buffer[SIZE * 5];								// SIZE * 5 (300) 만큼의 버퍼 배열 생성

	fopen_s(&fp, "member_list.txt", "r");				// member_list 파일을 읽기 모드로 열기

	for (i = 0; fgets(Buffer, SIZE * 5, fp); i++) {};	// 저장된 MEMBER의 수 확인 사람 수만큼 i값 증가
														// 한번에 SIZE * 5 의 크기만큼씩 읽습니다.
	fclose(fp);											// 파일 닫기

	return i;										// i값 반환
}



/////////////////////////////////////////////////////
//
//			▶ 데 이 터 분 리
//
/////////////////////////////////////////////////////

void GetMemberData(MEMBER *Member, int Count) {	 // 구조체를 가리키는 포인터와 이전에 확인한 i값을 받아온다.
	FILE *fp;
	int i;
	char Buffer[SIZE * 5];	// 300크기의 Buffer 배열 생성
	char *null = NULL;	// NULL값 지정용 포인터	 파일 내부 값을 가리키기 위해 포인터로 만들어 줍니다.

	fopen_s(&fp, "member_list.txt", "r");	// 읽기 모드로 member_list파일 열기

	for (i = 0; i < Count ; i++) {	// 저장된 데이터를 토큰단위로 읽는다.
		fgets(Buffer, SIZE * 5, fp);
		strcpy_s(Member[i].name, SIZE, strtok_s(Buffer, "/", &null));		// "/"를 분리자로 사용하여 데이터를 복사합니다..
		strcpy_s(Member[i].id, SIZE, strtok_s(NULL, "/", &null));			// 계속 토큰값을 받아옴으로 계속 읽기위해 두번째부턴 NULL값
		strcpy_s(Member[i].password, SIZE, strtok_s(NULL, "/", &null));		// 구조체의 i번째의 값에는 토큰 전까지의 값들이 저장됩니다.
		strcpy_s(Member[i].cellphone, SIZE, strtok_s(NULL, "/", &null));
		strcpy_s(Member[i].adress, SIZE, strtok_s(NULL, "/", &null));
	}

	fclose(fp);
}



/////////////////////////////////////////////////////
//
//			▶ 저 장 된 비 디 오 의 수 체 크
//
/////////////////////////////////////////////////////

int	GetVideoCount() {
	FILE *fp;
	int i;
	char Buffer[SIZE * 6];								// SIZE * 5 (360) 만큼의 버퍼 배열 생성

	fopen_s(&fp, "Video_list.txt", "r");				// video_list 파일을 읽기 모드로 열기

	for (i = 0; fgets(Buffer, SIZE * 6, fp); i++) {};	// 저장된 VIDEO의 수 확인 비디오의 수만큼 i값 증가
														// 한번에 SIZE * 6의 크기만큼씩 읽습니다.
	fclose(fp);											// 파일 닫기

	return i;											// i값 반환
}



/////////////////////////////////////////////////////
//
//			▶ 데 이 터 분 리
//
/////////////////////////////////////////////////////

void GetVideoData(VIDEO *Video, int Count) {	// 구조체를 가리키는 포인터와 이전에 확인한 i값을 받아온다.
	FILE *fp;
	int i;
	char Buffer[SIZE * 6];	// 360크기의 Buffer 배열 생성
	char *null = NULL;	// NULL값 지정용 포인터 파일 내부 값을 가리키기 위해 포인터로 만들어 줍니다.

	fopen_s(&fp, "video_list.txt", "r");	// 읽기 모드로 video_list파일 열기

	for (i = 0; i < Count ; i++) {	// 저장된 데이터를 토큰단위로 읽는다.
		fgets(Buffer, SIZE * 6, fp);
		strcpy_s(Video[i].videoname, SIZE, strtok_s(Buffer, "/", &null));	// "/"를 분리자로 사용하여 데이터를 복사합니다..
		strcpy_s(Video[i].runtime, SIZE, strtok_s(NULL, "/", &null));		// 계속 토큰값을 받아옴으로 계속 읽기위해 두번째부턴 NULL값
		strcpy_s(Video[i].genre, SIZE, strtok_s(NULL, "/", &null));			// 구조체의 i번째의 값에는 토큰 전까지의 값들이 저장됩니다.
		strcpy_s(Video[i].grade, SIZE, strtok_s(NULL, "/", &null));
		strcpy_s(Video[i].year, SIZE, strtok_s(NULL, "/", &null));
		strcpy_s(Video[i].rent, SIZE, strtok_s(NULL, "/", &null));
	}

	fclose(fp);
}



/////////////////////////////////////////////////////
//
//			▶ 대 여 된 비 디 오 수 체 크
//
/////////////////////////////////////////////////////

int GetRentCount() {
	FILE *fp;
	int i;
	char Buffer[SIZE * 2];								// SIZE * 2 (120) 만큼의 버퍼 배열 생성

	fopen_s(&fp, "rent_list.txt", "r");					// rent_list 파일을 읽기 모드로 열기

	for (i = 0; fgets(Buffer, SIZE * 2, fp); i++) {};	// 저장된 RENT의 수 확인 사람 수만큼 i값 증가
														// 한번에 SIZE * 2의 크기만큼씩 읽습니다.
	fclose(fp);											// 파일 닫기

	return i;										// i값 반환
}




/////////////////////////////////////////////////////
//
//			▶ 데 이 터 분 리
//
/////////////////////////////////////////////////////

void GetRentData(RENT *Rent, int Count) {	// 구조체를 가리키는 포인터와 이전에 확인한 i값을 받아온다.
	FILE *fp;
	int i;
	char Buffer[SIZE * 2];	// 120크기의 Buffer 배열 생성
	char *null = NULL;	// NULL값 지정용 포인터 파일 내부 값을 가리키기 위해 포인터로 만들어 줍니다.

	fopen_s(&fp, "rent_list.txt", "r");	// 읽기 모드로 rent_list파일 열기

	for (i = 0; i < Count ; i++) {	// 저장된 데이터를 토큰단위로 읽는다.
		fgets(Buffer, SIZE * 2, fp);

		strcpy_s(Rent[i].Rvideoname, SIZE, strtok_s(Buffer, "/", &null));	// "/"를 분리자로 사용하여 데이터를 복사합니다..
		strcpy_s(Rent[i].Rname, SIZE, strtok_s(NULL, "/", &null));			// 계속 토큰값을 받아옴으로 계속 읽기위해 두번째부턴 NULL값
	}																		// 구조체의 i번째의 값에는 토큰 전까지의 값들이 저장됩니다.

	fclose(fp);
}