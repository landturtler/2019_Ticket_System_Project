#include <iostream>
#pragma once
#include <string>
#include <map>
#include <vector>
#include "Member.h"
#include "Buyer.h"
#include "Seller.h"

using namespace std;

//Class : MemberManager
//description : MemberManager에 대한 정보 저장
//Revisions:
// 1.When & Who 2019/6/2 19:34 pm by 조윤해
// What : 접근제한자 수정, iter삭제, 
//		getLogInMember 리턴타입수정,getMember수정, requestLogOut수정
//		getMember삭제
// 2. When & Who: 2019/06/03 05:23 am by 정윤석
// ****** 회원가입, 회원탈퇴 관련 함수들 추가/수정한 다음에 꼭 알려주세요 ******
// ****** 저는 일단 아래 내용만 수정했습니다 *****
// ****** 회원가입 관련 기능이 구현 안돼있어서 테스트는 안해봤습니다 *****
//	What: 1) string currentSession 추가
//			 void changeSession(string memberID) 추가
//			 string getCurrentSession() 추가
//		  2) requestLogOut()함수 대부분 수정
//			 requestLogIn()함수 대부분 수정
//			 logInMembers의 타입을 map<string, Member*>에서 vector<string> 으로 변경
//		  3) map<string, Member*> getLogInMember() 삭제
// 3. When & Who: 2019/06/03 08:03 am by 정윤석
//	What: 1) 경매티켓 낙찰의 경우 낙찰자와 현재 세션의 멤버가 다름.
//			따라서 buyerID와 티켓 정보를 받아 티켓을 구매하는 역할을 하는 함수를 만듬
//			void reserveTicket(int, string) 함수임
// 4. When & Who : 2019/06/03 2:29pm, 이지현
//	What: requestSignUp구현
// 5. When & Who: 2019/06/03 09:13 pm by 정윤석
//	What: 1) Login시 세션을 로그인한 멤버로 변경
//		  2) Logout시 세션을 빈 문자열로 변경
// 6. When & Who : 2019/06/03 10:04 pm by 박형준
//	What :	현재 세션의 멤버에 접근할 수 있는 포인터 반환 함수 작성
// 7. When & Who : 2019/06/04 11:03 am by 정윤석
//	What: 1) 멤버 아이디와 티켓 아이디를 받아 해당 멤버의 티켓리스트에서 티켓을 삭제하는 함수 추가
//			void deleteMembersTicket(int ticketID, string memberID);
// 8. When & Who : 2019/06/05 08:04 pm by 박형준
//  What : 입력 받은 ID에 해당하는 멤버 삭제 함수 추가


class MemberManager{
private:
	string currentSessionID;
	map< string, Member* > members;//string이 savedID
	vector<string> logInMembers;
	MemberManager();
	static MemberManager * memberManagerInstance;
	

public:
	static MemberManager *getInstance();
	bool requestLogIn(string, string);
	void requestLogOut();
	void requestSignUp(string savedID, string savedPassword, string name, int identityNumber, int userType);
	void changeSession(string);
	string getCurrentSessionID();
	void eraseMember(string ID);

	void reserveTicket(int, string);
	void deleteMembersTicket(int, string);

	Member * getCurrentMemberPtr();
};