#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "SearchAuctionTicketUI.h"
#include "SearchAuctionTicket.h"
#include "Timer.h"
#include <iomanip>
using namespace std;

void SearchAuctionTicketUI::selectHomeTeam(ifstream &infile, ofstream &outfile, SearchAuctionTicket control){
	outfile << "4.3. 경매 중인 티켓 검색" << endl;

	string home;
	infile >> home;
	vector<pair<int, Ticket>> tickets = control.showSelectedHomeTeamAuctionTicketList(home);
	for (auto ticketPair : tickets) {
		// 6시간 전 마감이므로 마감까지 남은 시간을 뺀다
		int remainTime = ticketPair.first - 60*6;
		Ticket ticket = ticketPair.second;
		
		pair<int, int> time = Timer::getInstance()->minToHour_Min(remainTime);
		outfile << "> " << ticket.getBasicInfo() << " ";
		outfile << setw(2) << setfill('0') << time.first << ':' << setw(2) << setfill('0') << time.second << endl;
	}
}
void SearchAuctionTicketUI::participateAuction(ifstream &infile, ofstream &outfile, SearchAuctionTicket control) {
	outfile << "4.4. 경매 참여" << endl;

	Timer::TimeSet matchTime;
	string away;
	string seat;
	int price;

	infile >> matchTime >> away >> seat >> price;
	control.showAuctionParticipationInterface(matchTime, away, seat, price);
	outfile << "> " << price << endl;
}

