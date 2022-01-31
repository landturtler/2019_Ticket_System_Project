#include "CheckReservedTicket.h"



CheckReservedTicket::CheckReservedTicket()
{
}

CheckReservedTicket::~CheckReservedTicket()
{
}


// Function : vector<pair<int, Ticket>> getReservedTicketList()
// Description : 예약한 티켓 목록 반환
// Parameters : None
// Return Value : vector<pair<int, Ticket>> returnList
// Created : 2019/06/03 09:50 pm
// Author : 박형준
vector<pair<int, Ticket>> CheckReservedTicket::getReservedTicketList()
{
	TicketManager * ticketManagerInstance;
	MemberManager * memberManagerInstance;
	ticketManagerInstance = TicketManager::getInstance();
	memberManagerInstance = MemberManager::getInstance();
	Buyer * currentBuyer = (Buyer *)memberManagerInstance->getCurrentMemberPtr();
	vector<int> reserveTicketList(currentBuyer->getReserveTicketList());
	ticketManagerInstance->setTicketList(reserveTicketList);
	vector<pair<int, Ticket>> returnList(ticketManagerInstance->getTicketList());

	return returnList;
}