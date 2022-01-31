#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Member.h"
#include "Ticket.h"
using namespace std;

// Class : Seller
// Description : Seller에 대한 정보를 저장하는 클래스
// Created : 2019/05/30 09:00pm
// Author : 이지현
//
// Revision :
//	1. When & Who : 2019/05/31 10:00pm, 이지현
//         What : ticket list 저장을 id에서 Ticket*로 수정
//                    registerTicketList형, getSellerTicketList 리턴 타입, addSellerTicketList의 매개변수 변경
//	2. When & Who : 2019/06/03 10:00pm, 이지현
//         What : ticket list 저장을 Ticket*에서 id로 수정
//                    registerTicketList형, getSellerTicketList 리턴 타입, addSellerTicketList의 매개변수 변경
//  3. When & Who : 2019/06/03 6:28pm, 조윤해
//         What : Seller소멸자 추가
// 4. When & Who: 2019/06/04 11:52 am by 정윤석
//	What: 1) 멤버의 티켓 목록에서 티켓을 삭제하는
//			void deleteTicket(int) 함수 추가
class Seller : public Member {
private:
	vector<int> registerTicketList;
public:
	Seller(int userType, string name, int identityNumber, bool loginState, string savedID, string savedPassword);
	vector<int> getSellersTicketList();
	void addSellerTicketList(int ticketID);
	~Seller();

	virtual void deleteTicket(int);
};