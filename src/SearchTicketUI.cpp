#include <iostream>
#include <fstream>
#include <string>
#include "SearchTicketUI.h"
#include "SearchTicket.h"
#include "TicketManager.h"
#include "Timer.h"
using namespace std;

// function : SearchTicketUI::selectHomeTeamToTicketList(ifstream& in_fp, ofstream& out_fp, SearchTicket& searchTicket)
// description : 선택한 hometeam에 대해 예약 가능한 티켓을 보여줌
// parameter : ifstream &in_fp :인풋파일
//						ofstream &out_fp : 아웃풋파일
//						SearchTicket& searchTicket
// return value : 없음
//revision
//1. when&who: 2019/06/04 01:56pm, 이지현
//what: 출력 수정

void SearchTicketUI::selectHomeTeamToTicketList(ifstream& in_fp, ofstream& out_fp, SearchTicket& searchTicket) {
	string homeTeam;

	out_fp << "4.1. 티켓 검색" << endl;
	in_fp >> homeTeam;

	vector<pair<int, Ticket>> homeTeamTicketList = searchTicket.showHomeTeamTicketList(homeTeam);

	for (int i = 0; i < homeTeamTicketList.size(); ++i) {
		out_fp << "> " << homeTeamTicketList[i].second.getSellerPrice() << " " << homeTeamTicketList[i].second.getBasicInfo() << endl;
	}
}

// function : selectTicketToReserve(ifstream& in_fp, ofstream& out_fp, SearchTicket& searchTicket)
// description : 선택한 티켓을 예약
// parameter : ifstream &in_fp :인풋파일
//						ofstream &out_fp : 아웃풋파일
//						SearchTicket& searchTicket
// return value : 없음

void SearchTicketUI::selectTicketToReserve(ifstream& in_fp, ofstream& out_fp, SearchTicket& searchTicket) {
	out_fp << "4.2. 티켓 예약" << endl;
	Timer::TimeSet time;
	string awayTeam, seatPos;
	in_fp >> time >> awayTeam >> seatPos;
	
	Ticket reservedTicket = searchTicket.requestReserveTicket(time, awayTeam, seatPos);

	out_fp << "> " << reservedTicket.getSellerPrice() << " " << reservedTicket.getMatchTime() << " " << reservedTicket.getHomeTeam() << " " << awayTeam << " " << seatPos << endl;
}