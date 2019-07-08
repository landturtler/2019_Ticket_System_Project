#include <string>
#include <iostream>
#pragma once
using namespace std;

//Class:Member
//Description: Member에 대한 정보를  저장하는 클래스
// Revisions:
// 1. When & Who: 2019/06/04 11:52 am by 정윤석
//	What: 1) 멤버의 티켓 목록에서 티켓을 삭제하는
//			void deleteTicket(int) 가상함수 추가
//			Seller, Buyer에서 각각 오버라이딩됨

class Member{
protected:
	int userType;
	string name;
	int identityNumber;
	bool logInState = false;
	string savedID;
	string savedPassword;
public:
	Member(int, string, int, bool, string, string);
	string getPassword();
	string getID();
	bool getLogInState();
	int getUserType();
	void setLogInState(bool logInState);
	virtual void deleteTicket(int) = 0;
};