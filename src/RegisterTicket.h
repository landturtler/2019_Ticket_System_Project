#pragma once
#include <iostream>
#include <string>
using namespace std;

// Class : RegisterTicketUI
// Description : RegisterTicket BoundaryŬ����
// Created : 2019/06/03 02:55pm
// Author : ������
//
// Revision :
//	     1. When & Who : 
//         What : 

class RegisterTicket {
public:
	bool requestNewTicket(int price, int year, int month, int day, int hour, int minute,
											string homeTeam, string awayTeam, string seatPos, bool selectLTA);
};