#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define SIZE 60									// SIZE 60���� ����

typedef struct MEMBER {							// ȸ�� ���� ����ü
	char name[SIZE];							// �̸� 
	char id[SIZE];								// ID
	char password[SIZE];						// ��й�ȣ
	char cellphone[SIZE];						// �ڵ��� ��ȣ 
	char adress[SIZE];							// �ּ���
} MEMBER;

typedef struct VIDEO {							// ���� ����ü
	char videoname[SIZE];						// ���� ����
	char runtime[SIZE];							// �÷���Ÿ��
	char genre[SIZE];							// �帣
	char grade[SIZE];							// ��������
	char year[SIZE];							// �� ����
	char rent[SIZE];							// �뿩 ���� ����
} VIDEO;

typedef struct RENT {							// �뿩�� ����ü
	char Rvideoname[SIZE];						// ���� ����
	char Rname[SIZE];							// �뿩�� �̸�
} RENT;


// ����
void admin_main();								// ����_������
void user_main();								// ����_�����

// ���
void Create_File();								// ���ϻ���
int GetMemberCount();							// ����� ȸ�� �� ī��Ʈ
void GetMemberData(MEMBER *Member, int Count);	// ����� ȸ�� ������ �б�
int GetVideoCount();							// ����� ���� �� ī��Ʈ
void GetVideoData(VIDEO *Video, int Count);		// ����� ���� ������ �б�
int GetRentCount();								// ����� �뿩 ���� �� ī��Ʈ
void GetRentData(RENT *Rent, int Count);		// ����� �뿩 ���� ������ �б�


//ȸ�� ����
void Login(MEMBER *Member, int Count);			// �α���
void create_Member(int Count);					// ȸ������
void Manage_Member();							// ��ȸ�� ����
void Member_list(MEMBER *Member, int Count);				// -ȸ�� ���
void Member_search(MEMBER *Member, int Count);	// -ȸ�� �˻�
void Member_rename(MEMBER *Member, int Count);	// -ȸ�� ���� ����

//���� ����
void Manage_Video();							// ������ ����
void Video_add(int Count);						// -���� �߰�
void Video_delete(VIDEO *Video, int Count);		// -���� ����
void Video_rename(VIDEO *Video, int Count);		// -���� ���� ����
void Video_search(VIDEO *Video, int Count);		// ���� �˻�
void Video_list(VIDEO *Video, int Count);		// ���� ���

//�뿩 ����
void Video_rent(RENT *Rent, VIDEO * Video, MEMBER *Member, int MCount, int VCount);		// ���� �뿩
void Video_return(RENT *Rent, VIDEO * Video, MEMBER *Member, int RCount, int VCount);	// ���� �ݳ�
void Rent_list(RENT *Rent, int Count);													// �뿩 ���

//�ΰ� 
void main_logo();								// ���� �ΰ�
void user_logo();								// ����� �ΰ�
void admin_logo();								// ���� �ΰ�
void login_logo();								// �α��� ȭ��
void create_Member_logo();						// ȸ�� ���� �ΰ�
void Manage_Member_logo();						// ȸ�� ���� �ΰ�
void Member_list_logo();						// ȸ�� ��� �ΰ�
void Member_search_logo();						// ȸ�� �˻� �ΰ�
void Member_rename_logo();						// ȸ�� ���� ���� �ΰ�
void Manage_Video_logo();						// ���� ���� �ΰ�
void Create_Video_logo();						// ���� �߰� �ΰ�
void Video_delete_logo();						// ���� ���� �ΰ�
void Video_rename_logo();						// ���� ���� ���� �ΰ�
void Vidoe_rent_logo();							// ���� �뿩 �ΰ�
void Video_return_logo();						// ���� �ݳ� �ΰ�