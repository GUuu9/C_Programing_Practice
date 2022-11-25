#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define SIZE 60									// SIZE 60으로 정의

typedef struct MEMBER {							// 회원 정보 구조체
	char name[SIZE];							// 이름 
	char id[SIZE];								// ID
	char password[SIZE];						// 비밀번호
	char cellphone[SIZE];						// 핸드폰 번호 
	char adress[SIZE];							// 주소지
} MEMBER;

typedef struct VIDEO {							// 비디오 구조체
	char videoname[SIZE];						// 비디오 제목
	char runtime[SIZE];							// 플레이타임
	char genre[SIZE];							// 장르
	char grade[SIZE];							// 연령제한
	char year[SIZE];							// 상영 연도
	char rent[SIZE];							// 대여 가능 여부
} VIDEO;

typedef struct RENT {							// 대여중 구조체
	char Rvideoname[SIZE];						// 비디오 제목
	char Rname[SIZE];							// 대여자 이름
} RENT;


// 메인
void admin_main();								// 메인_관리자
void user_main();								// 메인_사용자

// 기능
void Create_File();								// 파일생성
int GetMemberCount();							// 저장된 회원 수 카운트
void GetMemberData(MEMBER *Member, int Count);	// 저장된 회원 데이터 읽기
int GetVideoCount();							// 저장된 비디오 수 카운트
void GetVideoData(VIDEO *Video, int Count);		// 저장된 비디오 데이터 읽기
int GetRentCount();								// 저장된 대여 비디오 수 카운트
void GetRentData(RENT *Rent, int Count);		// 저장된 대여 비디오 데이터 읽기


//회원 관리
void Login(MEMBER *Member, int Count);			// 로그인
void create_Member(int Count);					// 회원가입
void Manage_Member();							// ▶회원 관리
void Member_list(MEMBER *Member, int Count);				// -회원 목록
void Member_search(MEMBER *Member, int Count);	// -회원 검색
void Member_rename(MEMBER *Member, int Count);	// -회원 정보 수정

//비디오 관리
void Manage_Video();							// ▶비디오 관리
void Video_add(int Count);						// -비디오 추가
void Video_delete(VIDEO *Video, int Count);		// -비디오 삭제
void Video_rename(VIDEO *Video, int Count);		// -비디오 정보 수정
void Video_search(VIDEO *Video, int Count);		// 비디오 검색
void Video_list(VIDEO *Video, int Count);		// 비디오 목록

//대여 관리
void Video_rent(RENT *Rent, VIDEO * Video, MEMBER *Member, int MCount, int VCount);		// 비디오 대여
void Video_return(RENT *Rent, VIDEO * Video, MEMBER *Member, int RCount, int VCount);	// 비디오 반납
void Rent_list(RENT *Rent, int Count);													// 대여 목록

//로고 
void main_logo();								// 메인 로고
void user_logo();								// 사용자 로고
void admin_logo();								// 어드민 로고
void login_logo();								// 로그인 화면
void create_Member_logo();						// 회원 가입 로고
void Manage_Member_logo();						// 회원 관리 로고
void Member_list_logo();						// 회원 목록 로고
void Member_search_logo();						// 회원 검색 로고
void Member_rename_logo();						// 회원 정보 수정 로고
void Manage_Video_logo();						// 비디오 관리 로고
void Create_Video_logo();						// 비디오 추가 로고
void Video_delete_logo();						// 비디오 삭제 로고
void Video_rename_logo();						// 비디오 정보 수정 로고
void Vidoe_rent_logo();							// 비디오 대여 로고
void Video_return_logo();						// 비디오 반납 로고