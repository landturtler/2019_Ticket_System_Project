#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Member.h"
#include "Ticket.h"
using namespace std;

// Class : Buyer
// Description : Buyer에 대한 정보를 저장하는 클래스
// Created : 2019/05/30 09:00pm
// Author : 이지현
//
// Revision :
//	     1. When & Who : 2019/05/31 10:00pm, 이지현
//         What : ticket list 저장을 id에서 Ticket*로 수정
//                    reserveTicketList형, getReserveTicketList 리턴 타입, addBuyersTicketList의 매개변수 변경
//	     1. When & Who : 2019/06/03 01:00am, 이지현
//         What : ticket list 저장을 Ticket*에서 id로 수정
//                    reserveTicketList형, getReserveTicketList 리턴 타입, addBuyersTicketList의 매개변수 변경
/*       1. When & Who : 2019/06/03 6:28pm, 조윤해
What : Buyer소멸자 추가*/
// 4. When & Who: 2019/06/04 11:52 am by 정윤석
//	What: 1) 멤버의 티켓 목록에서 티켓을 삭제하는
//			void deleteTicket(int) 함수 추가
class Buyer : public Member {
private:
	vector<int> reserveTicketList;	//예약한 티켓의 아이디를 저장하는 리스트
public:
	Buyer(int userType, string name, int identityNumber, bool loginState, string savedID, string savedPassword);
	~Buyer();
	vector<int> getReserveTicketList();
	void addBuyersTicketList(int ticketID);
	virtual void deleteTicket(int);
};