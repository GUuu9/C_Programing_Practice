#include "function.h"	//�� ��ɵ��� �ҷ����� ���� ��� �Լ��� ������� ��Ƶ� ����Լ�



/////////////////////////////////////////////////////////////////////////
//
//			�� �� �� �� �� �� �� ��
//
/////////////////////////////////////////////////////////////////////////

void admin_main() {
	MEMBER *Member;		// �� ����ü �����͸� ����
	VIDEO *Video;
	RENT *Rent;

	int selectNumber;	// ��� ���� ���� ����
	int CountMember;	// ����� ȸ���� ���� ī��Ʈ�ϱ� ���� 
	int CountVideo;		// ����� ������ ���� ī��Ʈ
	int CountRent;		// �뿩���� ������ ���� ī��Ʈ

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
		

		admin_logo();	// ������ �ΰ� ���
		printf("		[�Է�] : ");
		scanf_s("%d", &selectNumber);	// ����� ����� ��ȣ�� �Է¹޴´�.


		switch (selectNumber) {													// �Է¹��� ��ȣ�� ���� �ش��ϴ� ����� ����
			
		case 1: { system("cls"); Video_search(Video, CountVideo); break; }		// ���� �˻�
	
		case 2: { system("cls"); Video_list(Video, CountVideo); break; }		// ���� ���

		case 3: { system("cls"); Rent_list(Rent, CountRent); break; }			// �뿩 ���

		case 4: { system("cls"); Manage_Video(); break; }						// ���� ����
				
		case 5: { system("cls"); Manage_Member(); break; }						// ȸ�� ����
		
		case 6:	return;															// �α׾ƿ�
		
		}

		getchar();
		system("cls");
	}

	return;
}