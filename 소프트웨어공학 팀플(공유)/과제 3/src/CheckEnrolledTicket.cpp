#pragma once
#include "TicketManager.h"
#include "Seller.h"
#include "CheckEnrolledTicket.h"
#include "Ticket.h"
#include <vector>
#include "MemberManager.h"
using namespace std;

// function : getSellersTIcketList()
// description : 특정 셀러가 등록한 티켓 리스트를 정렬하여 리턴해주는 함수
// parameter : None
// return value : vector<pair<int, TIcket*>>sortedList
vector<pair<int,Ticket>> CheckEnrolledTicket:: getSellersTIcketList() {
	MemberManager *sellerManager = MemberManager::getInstance();
	TicketManager *ticketManager = TicketManager::getInstance();
	Seller * seller =(Seller*)sellerManager->getCurrentMemberPtr();
	vector<int> sellerList = seller->getSellersTicketList();
	ticketManager -> setTicketList(sellerList);
	vector<pair<int, Ticket>> sortedList = ticketManager->getTicketList();
	return sortedList;
}
