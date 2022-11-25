#include "function.h"	//각 기능들을 불러오기 위해 모든 함수와 헤더들을 담아둔 헤더함수



/////////////////////////////////////////////////////////////////////////
//
//			▶ 사 용 자 메 인 함 수
//
/////////////////////////////////////////////////////////////////////////

void user_main() {
	MEMBER *Member;		// 각 구조체 포인터를 정의
	VIDEO *Video;
	RENT *Rent;

	int selectNumber;	// 기능 선택 구분 변수
	int CountMember;	// 저장된 회원의 수를 카운트하기 위한 
	int CountVideo;		// 저장된 비디오의 수를 카운트
	int CountRent;		// 대여중인 비디오의 수를 카운트

	while (1) {

		CountMember = GetMemberCount();	// 받아온 저장된 회원의 수 i값을 CountMember에 저장
		Member = (MEMBER *)malloc((sizeof(MEMBER) * CountMember));	// Member에 (MEMBER * 저장된 회원의 수) 만큼의 동적 메모리를 할당한다.
		GetMemberData(Member, CountMember);	// 데이터들을 토큰단위로 분리

		CountVideo = GetVideoCount();	// 받아온 저장된 비디오의 수 i값을 CountVideo에 저장
		Video = (VIDEO *)malloc((sizeof(VIDEO) * CountVideo));	// Video에 (VIDEO * 저장된 비디오의 수) 만큼의 동적 메모리를 할당.
		GetVideoData(Video, CountVideo);	// 데이터들을 토큰단위로 분리
		
		CountRent = GetRentCount();		// 받아온 대여된 비디오의 수 i값을 CountRent에 저장
		Rent = (RENT *)malloc((sizeof(VIDEO) * CountRent));	// Rent에 (RENT * 저장된 대여 비디오의 수) 만큼의 동적 메모리를 할당
		GetRentData(Rent, CountRent);	// 데이터들을 토큰단위로 분리


		user_logo();	// 사용자 로고 출력
		printf("		[입력] : ");
		scanf_s("%d", &selectNumber);	// 사용할 기능의 번호를 입력받는다.

		switch (selectNumber) {													// 입력받은 번호에 따라 해당하는 기능이 실행
		case 1: { system("cls"); Video_search(Video, CountVideo); break; }		// 비디오 검색

		case 2:	{ system("cls"); Video_list(Video, CountVideo); break; }		// 비디오 목록

		case 3: { system("cls"); Video_rent(Rent, Video, Member, CountMember, CountVideo); break; }		// 대여

		case 4: { system("cls"); Video_return(Rent, Video, Member, CountRent, CountVideo); break; }	// 반납

		case 5:	return;															// 로그아웃


		}

		getchar();
		system("cls");	// 화면 초기화
	}

	return;
}