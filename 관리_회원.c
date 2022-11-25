#include "function.h"	//각 기능들을 불러오기 위해 모든 함수와 헤더들을 담아둔 헤더함수


/////////////////////////////////////////////////////////////////////////
//
//			▶ 로 그 인
//
/////////////////////////////////////////////////////////////////////////

void Login(MEMBER *Member, int Count) {	 // 구조체를 가리키는 포인터와 이전에 확인한 i값을 받아온다.
	char id[SIZE];	// 변수 선언
	char password[SIZE];
	int i;



	login_logo();	//로고

	getchar();
	printf("   I D   : ");		// id와 password입력받는다
	gets(id);
	printf("PASSWORD : ");
	gets(password);

	for (i = 0; i < Count; i++) {								
		if (strcmp(Member[i].id, id) == 0)									
			if (strcmp(Member[i].password, password) == 0) {		// id를 확인한 후, id값에 맞는 비밀번호가 입력됬을 경우 실행한다.
				printf("로그인 성공!");
				getchar();
				system("cls");

				if (Member[i].id == Member[0].id)   // 첫번째 아이디일 경우 어드민 메인으로 이동
					admin_main();
				else								// 그 외의 경우 일반 사용자 메인으로 이동
					user_main();

				break;
			}

		if (i == Count - 1) {			// 둘중 하나라도 불일치시 출력
			printf("아이디 혹은 비밀번호 오류입니다.");
		}
	}

	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			▶ 회 원 가  입
//
/////////////////////////////////////////////////////////////////////////

void create_Member(int Count) {	// 회원 가입
	FILE *fp;	
	MEMBER Member; //회원 구조체

	create_Member_logo();

	fopen_s(&fp, "member_list.txt", "a");			// 회원이 저장되는 파일을 읽기쓰기 모드로 연다.


	getchar();

	printf("  성  함  : "); gets_s(Member.name, SIZE);		//회원의 정보를 입력 받는다.
	printf("   I  D   : "); gets_s(Member.id, SIZE);
	printf(" PASSWORD : "); gets_s(Member.password, SIZE);
	printf(" 전화번호 : "); gets_s(Member.cellphone, SIZE);
	printf("  주  소  : "); gets_s(Member.adress, SIZE);

	fprintf_s(fp, "/%s/%s/%s/%s/%s/\n", Member.name, Member.id, Member.password, Member.cellphone, Member.adress);
															// 파일에 형식에 맞춰 저장합니다.
	fclose(fp);

	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			▶ 회 원 관 리
//
/////////////////////////////////////////////////////////////////////////

void Manage_Member() {	// 회원 관리

	MEMBER *Member;		// MEMBER 구조체 포인터

	int selectNumber;
	int CountMember;

	

	fflush(stdin);	//버퍼 삭제

	while (1) {

	CountMember = GetMemberCount();	// 받아온 저장된 회원의 수 i값을 CountMember에 저장
	Member = (MEMBER *)malloc((sizeof(MEMBER) * CountMember));	// Member에 (MEMBER * 저장된 회원의 수) 만큼의 동적 메모리를 할당한다.
	GetMemberData(Member, CountMember);	// 데이터들을 토큰단위로 분리

		Manage_Member_logo(); // 회원 관리 로고
		printf("		[입력] : ");
		scanf_s("%d", &selectNumber);											// 사용할 기능의 번호를 입력받는다.

		switch (selectNumber) {													// 입력받은 번호에 따라 해당하는 기능이 실행
		case 1: { system("cls"); Member_list(Member, CountMember); return; }	// 회원 목록

		case 2: { system("cls"); Member_search(Member, CountMember); return; }	// 회원 검색
	
		case 3: { system("cls"); Member_rename(Member, CountMember); return; }	// 회원 정보 수정
		}

		getchar();
		system("cls");	// 화면 초기화

	}

	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			▶ 회 원 목 록
//
/////////////////////////////////////////////////////////////////////////

void Member_list(MEMBER *Member, int Count) {		// 회원 목록

	Member_list_logo();

	FILE *fp;

	int j;

	//

	int x, y, min;
	MEMBER tmp;

	for (x = 0; x < Count; x++) {											//선택정렬
		for (y = x + 1; y < Count; y++) {
			if (strcmp((Member[y]).name, Member[x].name) < 0) {
				tmp = Member[x];
				Member[x] = Member[y];
				Member[y] = tmp;
			}
		}
	}

	//
	fopen_s(&fp, "member_list.txt", "r");	// 읽기 모드로 member_list파일 열기



	j = Count;	

	for (Count = 0; Count < j; Count++) {	// 저장된 정보의 수만큼 해당하는 내용을 출력합니다.
		printf("%s / %s / %s / %s / %s \n", Member[Count].name, Member[Count].id,
				Member[Count].password, Member[Count].cellphone, Member[Count].adress);
	}

	getchar();

	fclose(fp);

	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			▶ 회 원 검 색
//
/////////////////////////////////////////////////////////////////////////

void Member_search(MEMBER *Member, int Count) {		// 회원 검색

	Member_search_logo();

	FILE *fp;
	int i;							// 변수 선언
	int userexist = 0;
	char name[SIZE];

	getchar();

	printf("\n [입력] : ");		// 검색할 이름을 입력 받는다.
	gets(name);

	fopen_s(&fp, "member_list.txt", "r");	// 읽기 모드로 member_list파일 열기

	for (i = 0; i < Count + 1 ; i++) {
		if (strcmp(Member[i].name, name) == 0) {	//동일한 내용이  있다면 해당 데이터 출력
			printf("%s / %s / %s / %s / %s\n", Member[i].name, Member[i].id, Member[i].password, Member[i].cellphone, Member[i].adress);
			userexist = 1;
			break;
		}

	}

	if (userexist == 0) // 탐색 실패.
		printf("해당 데이터가 존재하지 않습니다.");


	fclose(fp);

	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			▶ 회 원 정 보 수 정
//
/////////////////////////////////////////////////////////////////////////

void Member_rename(MEMBER *Member , int Count) {		// 회원 정보 수정
	Member_rename_logo();	
	FILE *fp;
	int i, j;
	int userexist = 0;
	char name[SIZE];

	getchar();

	printf("\n [입력] : ");		// 수정할 회원의 이름을 입력받음
	gets(name);

	for (i = 0; i < Count; i++) {
		if (strcmp(Member[i].name, name) == 0) { // 동일한 데이터가 있다면 출력
			printf(" ▶ %s / %s / %s / %s / %s\n\n", Member[i].name, Member[i].id, Member[i].password,
					Member[i].cellphone, Member[i].adress);
			userexist = 1;
			break;
		}

	}

	if (userexist == 0)
		printf(" ▶ 해당 데이터가 존재하지 않습니다.\n");

	else {	// 데이터가 존재할 시
		while (1) {

			printf(" ▶ 정보를 다시 입력 해 주세요\n\n");

			getchar();

			printf("  성  함  : "); gets_s(Member[i].name, SIZE);		// 해당 위치에 정보를 재입력 받는다.
			printf("   I  D   : "); gets_s(Member[i].id, SIZE);
			printf(" PASSWORD : "); gets_s(Member[i].password, SIZE);
			printf(" 전화번호 : "); gets_s(Member[i].cellphone, SIZE);
			printf("  주  소  : "); gets_s(Member[i].adress, SIZE);

			fopen_s(&fp, "member_list.txt", "w");		// 파일을 쓰기모드로 연다. w모드로 열시 기존내용들이 삭제된다.

			for (j = 0; j < Count ; j++) {	// 수정한 위치값만 변경되어 저장되고, 나머지 값은 새로 파일에 쓴다.
				fprintf_s(fp, "/%s/%s/%s/%s/%s/\n", Member[j].name, Member[j].id, Member[j].password,
								Member[j].cellphone, Member[j].adress);
			}

			
			printf(" ▶ 수정이 완료되었습니다...\n");
			getchar();
			
			fclose(fp);

			return;
		}
	}
	return;
}