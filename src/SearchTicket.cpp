#include <iostream>
#include <fstream>
#include <string>
#include "SearchTicket.h"
#include "TicketManager.h"
#include "MemberManager.h"
using namespace std;

// function : showHomeTeamTicketList(string homeTeam)
// description : 선택한 홈팀에 대한 예약 가능한 티켓 목록 출력
// parameter : string homeTeam : 보고 싶은 홈팀
// return value : 없음

vector<pair<int, Ticket>> SearchTicket::showHomeTeamTicketList(string homeTeam) {
	TicketManager::getInstance()->setTicketList(homeTeam);
	
	return TicketManager::getInstance()->getTicketList();
}

// function : requestReserveTicket(Timer::TimeSet time, string awayTeam, string seatPos)
// description : 선택한 티켓의 예약 요청
// parameter : Timer::TimeSet time
//						string awayTeam
//						string seatPos
// return value : 없음
// revision :
//1.when&who: 2019/06/04 01:45pm, 이지현
//what:예약 리스트 추가

Ticket SearchTicket::requestReserveTicket(Timer::TimeSet time, string awayTeam, string seatPos) {
	vector<pair<int, Ticket>> homeTeamTicketList = TicketManager::getInstance()->getTicketList();

	for (int i = 0; i < homeTeamTicketList.size(); ++i) {
		Ticket::BasicInfo ticketInfo = homeTeamTicketList[i].second.getBasicInfo();
		if (awayTeam == ticketInfo.awayTeam && seatPos == ticketInfo.seatPosition && (time == ticketInfo.matchTime)) {
			TicketManager::getInstance()->reserveTicket(homeTeamTicketList[i].second.getID(), MemberManager::getInstance()->getCurrentSessionID());
			MemberManager::getInstance()->reserveTicket(homeTeamTicketList[i].second.getID(), MemberManager::getInstance()->getCurrentSessionID());

			return homeTeamTicketList[i].second;
		}
	}
}