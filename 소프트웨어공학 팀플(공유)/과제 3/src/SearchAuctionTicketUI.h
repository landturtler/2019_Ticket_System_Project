#pragma once
#include <fstream>
#include "SearchAuctionTicket.h"
using namespace std;

//---------------------------------------------------------------------------------------------
// class: SearchAuctionTicketUI
// Description: 경매 중인 티켓 검색에 사용되는 boudary 클래스
// Created:2019/06/03 03:50 am
// Author: 정윤석
//---------------------------------------------------------------------------------------------
class SearchAuctionTicketUI {
public:
	void selectHomeTeam(ifstream&, ofstream&, SearchAuctionTicket);
	void participateAuction(ifstream& infile, ofstream& outfile, SearchAuctionTicket);
};

