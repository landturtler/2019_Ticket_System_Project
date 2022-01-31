#include <iostream>
#include <fstream>
#include <string>
#include "RegisterTicket.h"
#include "Timer.h"
#include "TicketManager.h"
#include "MemberManager.h"
using namespace std;

// function : requestNewTicket(int price, int year, int month, int day, int hour, int minute,
//														string homeTeam, string awayTeam, string seatPos, bool selectLTA)
// description : 티켓 등록을 요청하는 함수
// parameter : ifstream &in_fp :인풋파일
//						ofstream &out_fp : 아웃풋파일
// return value : bool - 티켓 등록 성공하면 true, 실패하면 false

bool RegisterTicket::requestNewTicket(int price, int year, int month, int day, int hour, int minute,
																	string homeTeam, string awayTeam, string seatPos, bool selectLTA) {
	Timer::TimeSet ticketTime(year, month, day, hour, minute);
	int remainingtime = Timer::getInstance()->getRemainingTime(ticketTime);

	//오늘이 경기시작까지 이틀 이상 남았을 때만 등록
	if (remainingtime > 48*60) {
		int ticketID = TicketManager::getInstance()->addNewTicket(price, ticketTime, homeTeam, awayTeam, seatPos, selectLTA, MemberManager::getInstance()->getCurrentSessionID());
		
		((Seller*)(MemberManager::getInstance() ->getCurrentMemberPtr()))->addSellerTicketList(ticketID);

		return true;//티켓 등록 성공
	}
	else {
		return false;//티켓 등록 실패
	}
}