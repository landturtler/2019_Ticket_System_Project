#pragma once
#include <iostream>
#include <string>
#include "SearchTicket.h"
using namespace std;

// Class : SearchTicketUI
// Description : SearchTicket Boundary클래스
// Created : 2019/06/03 06:19pm
// Author : 이지현
//
// Revision :
//	     1. When & Who : 
//         What : 

class SearchTicketUI {
public:
	void selectHomeTeamToTicketList(ifstream& in_fp, ofstream& out_fp, SearchTicket& searchTicket);
	void selectTicketToReserve(ifstream& in_fp, ofstream& out_fp, SearchTicket& searchTicket);
};