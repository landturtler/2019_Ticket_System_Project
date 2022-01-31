#pragma once
#include "CheckEnrolledTicketUI.h"
#include "CheckEnrolledTicket.h"
#include "TicketManager.h"
#include "Member.h"
#include "TicketManager.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;
// function : startCheckEnrolledTicket(ifstream &in_fp, ofstream &out_fp, CheckEnrolledTicket& enrolledTicketList)
// description : 액터가 등록 티켓 조회를 시작하도록 요청하는 함수
// parameter :ifstream &in_fp, ofstream &out_fp, CheckEnrolledTicket& enrolledTicketList
// return value : None
//revision:
//1.when&who:2019/06/04 02:01pm, 이지현
//what :출력문 형식 맞추기 위해 수정
//1.when&who:2019/06/04 02:01pm, 이지현
//what :시간 출력 부분 변경

void CheckEnrolledTicketUI::startCheckEnrolledTicket(ifstream &in_fp, ofstream &out_fp) {
	CheckEnrolledTicket ticketList;
	vector<pair <int, Ticket>> enrolledTicketList = ticketList.getSellersTIcketList();
	unsigned int price;
	string matchDateNTime; string seatPos;
	string homeTeam, awayTeam;
	Timer::TimeSet time;

	int i = 0;
	out_fp << "3.2. 등록티켓 조회" << endl;
	for (i; i < enrolledTicketList.size(); i++) {
		price = enrolledTicketList[i].second.getSellerPrice();
		time = enrolledTicketList[i].second.getMatchTime();
		homeTeam = enrolledTicketList[i].second.getHomeTeam();
		awayTeam = enrolledTicketList[i].second.getBasicInfo().awayTeam;
		seatPos = enrolledTicketList[i].second.getBasicInfo().seatPosition;
		bool la = enrolledTicketList[i].second.getLimitedAuction();
		out_fp << "> "
			<< price << " "
			<< time << " "
			<< homeTeam << " "
			<< awayTeam << " "
			<< seatPos << " "
			<< la << " ";
		if (enrolledTicketList[i].second.getBuyerID() != "")
			out_fp << "1" << endl;
		else
			out_fp << "0" << endl;
	}
}

