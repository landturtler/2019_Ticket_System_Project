#include <iostream>
#include "Buyer.h"
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


// function : Buyer(int userType, string name, int identityNumber, bool loginState, string savedID, string savedPassword)
// description : Buyer 객체를 생성하는 생성자
// parameter : int userType - 0이면 buyer, 1이면 seller를 나타냄
//             string name - Buyer 객체의 이름
//             identityNumber - 각 member마다 부여된 고유 번호
//             loginState - true면 login된 상태, false면 logout된 상태
//             savedID - Buyer의 ID
//             savedPassword - Buyer의 password
// return value : 없음

Buyer::Buyer(int userType, string name, int identityNumber, bool loginState, string savedID, string savedPassword)
	: Member(userType, name, identityNumber, loginState, savedID, savedPassword){

}

//fuction : ~Buyer()
//description : Buyer객체 소멸자

Buyer::~Buyer(){}
// function : 
// description : Buyer가 예약한 티켓 리스트를 리턴한다
// parameter : 없음
// return value : 예약 티켓 리스트
vector<int> Buyer::getReserveTicketList() {
	return this->reserveTicketList;
}

// function : void addBuyersTicketList(int TicketID)
// description : Buyer의 티켓리스트에 새로 예약한 티켓의 아이디를 추가한다
// parameter : int TicketID - 새로 추가하는 티켓의 ID
// return value : 없음
void Buyer::addBuyersTicketList(int ticketID) {
	this->reserveTicketList.push_back(ticketID);
}


// function : void deleteTicket(int)
// description : 티켓id를 받아서 멤버 티켓 목록에서 삭제
// parameter : int ticketID
// return value :None
void Buyer::deleteTicket(int ticketID) {
	auto fst = reserveTicketList.begin();
	for (int i = 0; i < reserveTicketList.size(); i++) {
		if (ticketID == reserveTicketList[i]) {
			reserveTicketList.erase(fst + i);
			return;
		}
	}
}
