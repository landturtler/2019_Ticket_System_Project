#pragma once
#include <vector>
#include <string>
#include "Ticket.h"
using namespace std;
//------------------------------------------------------------------------------------
// class: SearchAuctionTicket
// Description: 경매 중인 티켓 검색시 사용되는 컨트롤 클래스
// Created: 2019/06/03 03:49 am
// Author: 정윤석
//------------------------------------------------------------------------------------
class SearchAuctionTicket {
public:
	vector<pair<int, Ticket>> showSelectedHomeTeamAuctionTicketList(string);
	void showAuctionParticipationInterface(Timer::TimeSet, string, string, int);
};