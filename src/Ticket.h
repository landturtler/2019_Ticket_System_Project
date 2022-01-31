#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Timer.h"
using namespace std;

//---------------------------------------------------------------------------------------------
// class: Ticket
// Description: 티켓에 대한 정보를 저장하는 클래스.
//				공통적으로 출력에 필요한 정보들을 위해 내부에 BasicInfo 구조체를 public으로 갖고 있음.
//				BasicInfo 구조체는 ostream, ofstream이 오버로딩 되어있음. 모든 멤버를 형식에 맞게 출력함.
// Created: 2019/05/27 05:29 am
// Author: 정윤석
// Revisions:
//	1. When & Who : 2019/05/28 02:11 am by 정윤석
//		What: 1) getID(), getPrice(), getMatchTime(), getHomeTeam(), getBuyerID() 추가
//			  2) getRemainingTime()은 정확히 모르겠음. 논의가 필요해보임
//	2. When & Who : 2019/05/30 05:32 pm by 정윤석
//		What: 1) 논리적으로 티켓의 접근 권한을 바꿈. TicketDetail 구조체를 없앰
//			  2) 날짜, 시각을 Ticket::TimeSet구조체로 관리하기로 함
//			    그에 따라 Ticket::Date, Ticket::Time 구조체와 생성자 삭제,
//				날짜+시간 정보를 Timer::TimeSet matchTime에서 관리
//			  3) 수정(1.2)에서 논의한 getRemainingTime()은 Timer클래스가 가지기로 함
//			  4) price는 변경될 수 있어서 const를 없앰(티켓 낙찰시 price 변경). price의 setter 작성함
//	3. When & Who : 2019/05/31 08:54 pm by 정윤석
//		What: 1) 편의를 위해 BasicInfo 구조체를 만듬. 멤버로는 경기날짜+시각, 홈팀, 어웨이팀, 좌석위치가 있음
//			   그에 따라 Ticket의 멤버 중 위에서 나온 멤버들이 삭제되고, Ticket에 const BasicInfo basicInfo 멤버가 추가됨
//			  3) BasicInfo 구조체는 ostream& <<, ofstream& << 오버로딩이 되어있음. 형식에 맞게 출력되도록 함
//			  4) 티켓 클래스의 연산자 < 오버로딩함(아이디 오름차순).
//				따라서 TicketManager에서 sort시 따로 comparator를 넣지 않아도 됨
//	4. When & Who: 2019/06/03 01:07 am by 정윤석
//		What: 1) 멤버의 모든 const를 삭제함. (할당 연산자의 오버로딩이 불가능해 정렬이 불가능 함)
//			  2) Timer::TimeSet 구조체의 ostream, ofstream << 연산자 오버로딩에 따라
//				Ticket::BasicInfo 구조체의 오버로딩 함수가 위의 오버로딩을 이용하게끔 변경
//	5. When & Who: 2019/06/03 05:02 am by 정윤석
//		What: 1) Ticket::BasicInfo의 seatPosition을 string으로 변경
//			  2) Timer::TimeSet enrolledTime 변수를 추가
//				 위 변수는 등록한 날짜/시간을 저장함
//			  3) 등록시간을 반환하는 Timer::TimeSet getEnrolledTime() 함수 만듬
//---------------------------------------------------------------------------------------------

class Ticket {
public:
	struct BasicInfo {
		Timer::TimeSet matchTime;
		string homeTeam;
		string awayTeam;
		string seatPosition;
		
		BasicInfo();
		BasicInfo(Timer::TimeSet, string, string, string);
		friend ostream& operator << (ostream&, const BasicInfo&);
		friend ofstream& operator << (ofstream&, const BasicInfo&);
	};
private:
	int ID;
	int buyerPrice;
	int sellerPrice;
	Timer::TimeSet enrolledTime;
	Ticket::BasicInfo basicInfo;
	bool limitedAuction;
	string sellerID;
	string buyerID;

public:
	Ticket();
	Ticket(int ID, int sellerPrice, Timer::TimeSet enrolledTime, Timer::TimeSet matchTime, string home, string away,
		string seat, bool la, string sellerID);
	void setBuyerID(string buyerID);
	void setBuyerPrice(int price);
	int getID();
	int getBuyerPrice();
	int getSellerPrice();
	Timer::TimeSet getMatchTime();
	string getHomeTeam();
	string getBuyerID();
	string getSellerID();
	Ticket::BasicInfo getBasicInfo();
	bool getLimitedAuction();
	Timer::TimeSet getEnrolledTime();
	friend bool operator < (const Ticket &a, const Ticket &b);
}; 