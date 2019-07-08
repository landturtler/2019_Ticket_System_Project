#include <iostream>
#include "Seller.h"
using namespace std;

// Class : Seller
// Description : Seller에 대한 정보를 저장하는 클래스
// Created : 2019/05/30 09:00pm
// Author : 이지현
//
// Revision :
//	     1. When & Who : 2019/05/31 10:00pm, 이지현
//         What : ticket list 저장을 id에서 Ticket*로 수정
//                    registerTicketList형, getSellerTicketList 리턴 타입, addSellerTicketList의 매개변수 변경
//	     2. When & Who : 2019/06/03 01:00am, 이지현
//         What : ticket list 저장을 Ticket*에서 id로 수정
//                    registerTicketList형, getSellerTicketList 리턴 타입, addSellerTicketList의 매개변수 변경

// function : Seller(int userType, string name, int identityNumber, bool loginState, string savedID, string savedPassword)
// description : Seller 객체를 생성하는 생성자
// parameter : int userType - 0이면 buyer, 1이면 seller를 나타냄
//             string name - Buyer 객체의 이름
//             identityNumber - 각 member마다 부여된 고유 번호
//             loginState - true면 login된 상태, false면 logout된 상태
//             savedID - Seller의 ID
//             savedPassword - Seller의 password
// return value : 없음

Seller::Seller(int userType, string name, int identityNumber, bool loginState, string savedID, string savedPassword)
	: Member(userType, name, identityNumber, loginState, savedID, savedPassword){
	//생성자
}
//funtion : ~Seller()
//description : Seller객체 소멸자

Seller::~Seller(){}
// function : vector<int> getSellersTicketList();
// description : Seller가 등록한 티켓리스트를 리턴한다
// parameter : 없음
// return value : 등록 티켓 리스트
vector<int> Seller::getSellersTicketList() {
	return this->registerTicketList;
}

// function : void addSellerTicketList(int ticketID)
// description : Seller가 등록한 티켓을 Seller의 등록 티켓 리스트에 추가한다
// parameter : int ticketID - 새로 등록한 ticket의 ID
// return value : 없음
void Seller::addSellerTicketList(int ticketID) {
	this->registerTicketList.push_back(ticketID);
}

// function : void deleteTicket(int)
// description : 티켓id를 받아서 멤버 티켓 목록에서 삭제
// parameter : int ticketID
// return value :None
void Seller::deleteTicket(int ticketID) {
	auto fst = registerTicketList.begin();
	for (int i = 0; i < registerTicketList.size(); i++) {
		if (ticketID == registerTicketList[i]) {
			registerTicketList.erase(fst + i);
			return;
		}
	}
}