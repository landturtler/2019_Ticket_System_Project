#pragma once
#include <vector>
#include <utility>
#include "MemberManager.h"
#include "TicketManager.h"

using namespace std;

// Class : CheckReservedTicketUI
// Description : use case.Check Reserved Ticket의 <<control>> 클래스
// Created : 2019/06/02 03:40 am
// Author : 박형준
class CheckReservedTicket
{
public:
	~CheckReservedTicket();
	CheckReservedTicket();
	vector<pair<int, Ticket>> getReservedTicketList();
};

