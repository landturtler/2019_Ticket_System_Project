#pragma once
#include "SearchAuctionTicket.h"
#include "AuctionManager.h"
#include "TicketManager.h"
#include "MemberManager.h"

vector<pair<int, Ticket>> SearchAuctionTicket::showSelectedHomeTeamAuctionTicketList(string homeTeam) {
	vector<int> auctionTicketIDList = AuctionManager::getInstance()->getAuctionTicketList();
	
	TicketManager* tm = TicketManager::getInstance();
	tm->setTicketList(homeTeam, auctionTicketIDList);
	return tm->getTicketList();
}
void SearchAuctionTicket::showAuctionParticipationInterface(Timer::TimeSet time, string away, string seat, int price) {
	AuctionManager* am = AuctionManager::getInstance();
	TicketManager* tm = TicketManager::getInstance();
	MemberManager* mm = MemberManager::getInstance();

	vector<pair<int, Ticket>> tickets = tm->getTicketList();
	for (auto ticketPair : tickets) {
		Ticket ticket = ticketPair.second;
		
		Ticket::BasicInfo bi = ticket.getBasicInfo();
		Timer::TimeSet ticketTime = bi.matchTime;
		string ticketAway = bi.awayTeam;
		string ticketSeat = bi.seatPosition;
		
		if (time == ticketTime && away == ticketAway && seat == ticketSeat) {
			int ticketID = ticket.getID();
			am->addBiddingInfo(ticketID, price, mm->getCurrentSessionID());
		}
	}
}