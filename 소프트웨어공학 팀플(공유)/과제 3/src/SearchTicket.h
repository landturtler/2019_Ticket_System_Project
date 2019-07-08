#pragma once
#include <iostream>
#include <string>
#include "TicketManager.h"
#include "Timer.h"
using namespace std;

// Class : SearchTicket
// Description : SearchTicket Control클래스
// Created : 2019/06/03 06:20pm
// Author : 이지현
//
// Revision :
//	     1. When & Who : 
//         What : 

class SearchTicket {
public:
	vector<pair<int, Ticket>> showHomeTeamTicketList(string homeTeam);
	Ticket requestReserveTicket(Timer::TimeSet time, string awayTeam, string seatPos);
};