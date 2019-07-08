#pragma once
#include <fstream>
#include <string>
#include "CheckReservedTicket.h"


// Class : CheckReservedTicketUI
// Description : use case.Check Reserved Ticket의 <<boundary>> 클래스
// Created : 2019/06/02 03:00 am
// Author : 박형준
// Revisions :
//	1.	When & Who : 2019/06/03 03:41 am by 박형준
//		What : fstream, string 헤더 추가
class CheckReservedTicketUI
{
public:
	~CheckReservedTicketUI();
	CheckReservedTicketUI();
	void startCheckReservedTicket(ifstream & in, ofstream & out);
};

