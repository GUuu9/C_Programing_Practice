#include "function.h"	//각 기능들을 불러오기 위해 모든 함수와 헤더들을 담아둔 헤더함수



/////////////////////////////////////////////////////////////////////////
//
//			▶ 기 능 별 출 력 화 면
//
/////////////////////////////////////////////////////////////////////////

// 메인화면
void main_logo() {	
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("         사용하실 기능의 번호를 입력하여 주세요.      \n\n");
	printf("   1.로그인 2.회원가입 3.검색 4.목록 5.반납 6.종료    \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

// 로그인 사용자 화면
void user_logo() {	
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                      환영합니다.			 	      \n");
	printf("         사용하실 기능의 번호를 입력하여 주세요.      \n\n");
	printf("      1.검색  2.목록  3.대여  4.반납  5.로그아웃      \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

// 어드민 사용자 화면
void admin_logo() {	
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                      환영합니다.			 	      \n");
	printf("         사용하실 기능의 번호를 입력하여 주세요.      \n\n");
	printf("              1.검색  2.목록  3.대여 목록             \n");
	printf("         4.비디오 관리 5.회원 관리 6. 로그아웃	      \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

// 로그인 화면
void login_logo() { 
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                      로  그  인			 	      \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

// 회원 가입 화면
void create_Member_logo() { 
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                      회 원 가 입			 	      \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

// 비디오 관리 화면
void Manage_Video_logo() {	
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                비 디 오 관 리 메 뉴			      \n\n");
	printf("        사용하실 기능의 번호를 입력하여 주세요.       \n\n");
	printf("      1.비디오 추가 2.비디오 삭제 3.비디오 수정       \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}
// 비디오 추가
void Create_Video_logo() {
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                    비 디 오 추 가			 	      \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

// 비디오 목록
void Video_list_logo() {
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                    비 디 오 목 록                    \n\n");
	printf("    제목 / 런타임 / 장르 / 등급 / 제작연도 / 대여     \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

// 비디오 검색
void Video_search_logo() {
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                    비 디 오 검 색                    \n\n");
	printf("               찾으실 비디오 제목 입력.               \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

// 비디오 삭제
void Video_delete_logo() {
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                    비 디 오 삭 제                    \n\n");
	printf("              삭제하실 비디오 제목 입력.              \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

// 비디오 정보 수정
void Video_rename_logo() {
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                 비 디 오 정 보 수 정                 \n\n");
	printf("              수정하실 비디오 제목 입력.              \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

// 회원 관리 화면
void Manage_Member_logo() {	
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                  회 원 관 리 메 뉴			 	      \n\n");
	printf("        사용하실 기능의 번호를 입력하여 주세요.       \n\n");
	printf("       1.회원 목록 2.회원 검색 3.회원 정보 수정       \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

// 회원 목록
void Member_list_logo() {
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                      회 원 목 록                     \n\n");
	printf("      이름 / 아이디 / 비밀번호 / 휴대전화 / 주소      \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

// 회원 검색
void Member_search_logo() {
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                      회 원 검 색                     \n\n");
	printf("               찾으실 회원님의 성함 입력.             \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

// 회원 정보 수정
void Member_rename_logo() {
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                   회 원 정 보 수 정                  \n\n");
	printf("               수정할 회원님의 성함 입력.             \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

// 대여
void Vidoe_rent_logo() {
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                      대      여                      \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

// 반납
void Video_return_logo() {
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                      반      납                      \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}

// 대여 목록
void Rent_list_logo() {
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	printf("                      대 여 목 록                     \n\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
}