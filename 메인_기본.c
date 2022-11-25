#include "function.h"	//�� ��ɵ��� �ҷ����� ���� ��� �Լ��� ������� ��Ƶ� ����Լ�



/////////////////////////////////////////////////////////////////////////
//
//			�� �� �� �� �� �� ��
//
/////////////////////////////////////////////////////////////////////////

void main() {
	MEMBER *Member;		// �� ����ü �����͸� ����
	VIDEO *Video;
	RENT *Rent;

	int selectNumber;	// ��� ���� ���� ����
	int CountMember;	// ����� ȸ���� ���� ī��Ʈ�ϱ� ���� 
	int CountVideo;		// ����� ������ ���� ī��Ʈ
	int CountRent;		// �뿩���� ������ ���� ī��Ʈ

	Create_File();		// ������ ���� a��带 ����� ���� �����͸� ������ ���ϵ��� �������ش�.

	fflush(stdin);	//���� ����

	while (1) {

		CountMember = GetMemberCount();	// �޾ƿ� ����� ȸ���� �� i���� CountMember�� ����
		Member = (MEMBER *)malloc((sizeof(MEMBER) * CountMember));	// Member�� (MEMBER * ����� ȸ���� ��) ��ŭ�� ���� �޸𸮸� �Ҵ��Ѵ�.
		GetMemberData(Member, CountMember);	// �����͵��� ��ū������ �и�
		
		CountVideo = GetVideoCount();	// �޾ƿ� ����� ������ �� i���� CountVideo�� ����
		Video = (VIDEO *)malloc((sizeof(VIDEO) * CountVideo));	// Video�� (VIDEO * ����� ������ ��) ��ŭ�� ���� �޸𸮸� �Ҵ�.
		GetVideoData(Video, CountVideo);	// �����͵��� ��ū������ �и�
		
		CountRent = GetRentCount();		// �޾ƿ� �뿩�� ������ �� i���� CountRent�� ����
		Rent = (RENT *)malloc((sizeof(VIDEO) * CountRent));	// Rent�� (RENT * ����� �뿩 ������ ��) ��ŭ�� ���� �޸𸮸� �Ҵ�
		GetRentData(Rent, CountRent);	// �����͵��� ��ū������ �и�
		

		main_logo();	// ���� �ΰ� ���
		printf("		[�Է�] : ");
		scanf_s("%d", &selectNumber);	// ����� ����� ��ȣ�� �Է¹޴´�.
		
		switch (selectNumber) {													// �Է¹��� ��ȣ�� ���� �ش��ϴ� ����� ����
		case 1: { system("cls"); Login(Member, CountMember); break; }			// �α���
			
		case 2: { system("cls"); create_Member(CountMember); break; }			// ȸ������

		case 3: { system("cls"); Video_search(Video, CountVideo); break; }		// ���� �˻�

		case 4: { system("cls"); Video_list(Video, CountVideo); break; }		// ���� ���

		case 5: { system("cls"); Video_return(Rent, Video, Member, CountRent, CountVideo); break; }	// �ݳ�

		case 6:	return;															// ����

		}

		getchar();
		system("cls");	// ȭ�� �ʱ�ȭ
	}

	return;
}