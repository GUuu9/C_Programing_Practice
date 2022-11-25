#include "function.h"	//�� ��ɵ��� �ҷ����� ���� ��� �Լ��� ������� ��Ƶ� ����Լ�


/////////////////////////////////////////////////////////////////////////
//
//			�� �� �� ��
//
/////////////////////////////////////////////////////////////////////////

void Login(MEMBER *Member, int Count) {	 // ����ü�� ����Ű�� �����Ϳ� ������ Ȯ���� i���� �޾ƿ´�.
	char id[SIZE];	// ���� ����
	char password[SIZE];
	int i;



	login_logo();	//�ΰ�

	getchar();
	printf("   I D   : ");		// id�� password�Է¹޴´�
	gets(id);
	printf("PASSWORD : ");
	gets(password);

	for (i = 0; i < Count; i++) {								
		if (strcmp(Member[i].id, id) == 0)									
			if (strcmp(Member[i].password, password) == 0) {		// id�� Ȯ���� ��, id���� �´� ��й�ȣ�� �Է��� ��� �����Ѵ�.
				printf("�α��� ����!");
				getchar();
				system("cls");

				if (Member[i].id == Member[0].id)   // ù��° ���̵��� ��� ���� �������� �̵�
					admin_main();
				else								// �� ���� ��� �Ϲ� ����� �������� �̵�
					user_main();

				break;
			}

		if (i == Count - 1) {			// ���� �ϳ��� ����ġ�� ���
			printf("���̵� Ȥ�� ��й�ȣ �����Դϴ�.");
		}
	}

	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			�� ȸ �� ��  ��
//
/////////////////////////////////////////////////////////////////////////

void create_Member(int Count) {	// ȸ�� ����
	FILE *fp;	
	MEMBER Member; //ȸ�� ����ü

	create_Member_logo();

	fopen_s(&fp, "member_list.txt", "a");			// ȸ���� ����Ǵ� ������ �б⾲�� ���� ����.


	getchar();

	printf("  ��  ��  : "); gets_s(Member.name, SIZE);		//ȸ���� ������ �Է� �޴´�.
	printf("   I  D   : "); gets_s(Member.id, SIZE);
	printf(" PASSWORD : "); gets_s(Member.password, SIZE);
	printf(" ��ȭ��ȣ : "); gets_s(Member.cellphone, SIZE);
	printf("  ��  ��  : "); gets_s(Member.adress, SIZE);

	fprintf_s(fp, "/%s/%s/%s/%s/%s/\n", Member.name, Member.id, Member.password, Member.cellphone, Member.adress);
															// ���Ͽ� ���Ŀ� ���� �����մϴ�.
	fclose(fp);

	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			�� ȸ �� �� ��
//
/////////////////////////////////////////////////////////////////////////

void Manage_Member() {	// ȸ�� ����

	MEMBER *Member;		// MEMBER ����ü ������

	int selectNumber;
	int CountMember;

	

	fflush(stdin);	//���� ����

	while (1) {

	CountMember = GetMemberCount();	// �޾ƿ� ����� ȸ���� �� i���� CountMember�� ����
	Member = (MEMBER *)malloc((sizeof(MEMBER) * CountMember));	// Member�� (MEMBER * ����� ȸ���� ��) ��ŭ�� ���� �޸𸮸� �Ҵ��Ѵ�.
	GetMemberData(Member, CountMember);	// �����͵��� ��ū������ �и�

		Manage_Member_logo(); // ȸ�� ���� �ΰ�
		printf("		[�Է�] : ");
		scanf_s("%d", &selectNumber);											// ����� ����� ��ȣ�� �Է¹޴´�.

		switch (selectNumber) {													// �Է¹��� ��ȣ�� ���� �ش��ϴ� ����� ����
		case 1: { system("cls"); Member_list(Member, CountMember); return; }	// ȸ�� ���

		case 2: { system("cls"); Member_search(Member, CountMember); return; }	// ȸ�� �˻�
	
		case 3: { system("cls"); Member_rename(Member, CountMember); return; }	// ȸ�� ���� ����
		}

		getchar();
		system("cls");	// ȭ�� �ʱ�ȭ

	}

	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			�� ȸ �� �� ��
//
/////////////////////////////////////////////////////////////////////////

void Member_list(MEMBER *Member, int Count) {		// ȸ�� ���

	Member_list_logo();

	FILE *fp;

	int j;

	//

	int x, y, min;
	MEMBER tmp;

	for (x = 0; x < Count; x++) {											//��������
		for (y = x + 1; y < Count; y++) {
			if (strcmp((Member[y]).name, Member[x].name) < 0) {
				tmp = Member[x];
				Member[x] = Member[y];
				Member[y] = tmp;
			}
		}
	}

	//
	fopen_s(&fp, "member_list.txt", "r");	// �б� ���� member_list���� ����



	j = Count;	

	for (Count = 0; Count < j; Count++) {	// ����� ������ ����ŭ �ش��ϴ� ������ ����մϴ�.
		printf("%s / %s / %s / %s / %s \n", Member[Count].name, Member[Count].id,
				Member[Count].password, Member[Count].cellphone, Member[Count].adress);
	}

	getchar();

	fclose(fp);

	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			�� ȸ �� �� ��
//
/////////////////////////////////////////////////////////////////////////

void Member_search(MEMBER *Member, int Count) {		// ȸ�� �˻�

	Member_search_logo();

	FILE *fp;
	int i;							// ���� ����
	int userexist = 0;
	char name[SIZE];

	getchar();

	printf("\n [�Է�] : ");		// �˻��� �̸��� �Է� �޴´�.
	gets(name);

	fopen_s(&fp, "member_list.txt", "r");	// �б� ���� member_list���� ����

	for (i = 0; i < Count + 1 ; i++) {
		if (strcmp(Member[i].name, name) == 0) {	//������ ������  �ִٸ� �ش� ������ ���
			printf("%s / %s / %s / %s / %s\n", Member[i].name, Member[i].id, Member[i].password, Member[i].cellphone, Member[i].adress);
			userexist = 1;
			break;
		}

	}

	if (userexist == 0) // Ž�� ����.
		printf("�ش� �����Ͱ� �������� �ʽ��ϴ�.");


	fclose(fp);

	return;
}



/////////////////////////////////////////////////////////////////////////
//
//			�� ȸ �� �� �� �� ��
//
/////////////////////////////////////////////////////////////////////////

void Member_rename(MEMBER *Member , int Count) {		// ȸ�� ���� ����
	Member_rename_logo();	
	FILE *fp;
	int i, j;
	int userexist = 0;
	char name[SIZE];

	getchar();

	printf("\n [�Է�] : ");		// ������ ȸ���� �̸��� �Է¹���
	gets(name);

	for (i = 0; i < Count; i++) {
		if (strcmp(Member[i].name, name) == 0) { // ������ �����Ͱ� �ִٸ� ���
			printf(" �� %s / %s / %s / %s / %s\n\n", Member[i].name, Member[i].id, Member[i].password,
					Member[i].cellphone, Member[i].adress);
			userexist = 1;
			break;
		}

	}

	if (userexist == 0)
		printf(" �� �ش� �����Ͱ� �������� �ʽ��ϴ�.\n");

	else {	// �����Ͱ� ������ ��
		while (1) {

			printf(" �� ������ �ٽ� �Է� �� �ּ���\n\n");

			getchar();

			printf("  ��  ��  : "); gets_s(Member[i].name, SIZE);		// �ش� ��ġ�� ������ ���Է� �޴´�.
			printf("   I  D   : "); gets_s(Member[i].id, SIZE);
			printf(" PASSWORD : "); gets_s(Member[i].password, SIZE);
			printf(" ��ȭ��ȣ : "); gets_s(Member[i].cellphone, SIZE);
			printf("  ��  ��  : "); gets_s(Member[i].adress, SIZE);

			fopen_s(&fp, "member_list.txt", "w");		// ������ ������� ����. w���� ���� ����������� �����ȴ�.

			for (j = 0; j < Count ; j++) {	// ������ ��ġ���� ����Ǿ� ����ǰ�, ������ ���� ���� ���Ͽ� ����.
				fprintf_s(fp, "/%s/%s/%s/%s/%s/\n", Member[j].name, Member[j].id, Member[j].password,
								Member[j].cellphone, Member[j].adress);
			}

			
			printf(" �� ������ �Ϸ�Ǿ����ϴ�...\n");
			getchar();
			
			fclose(fp);

			return;
		}
	}
	return;
}