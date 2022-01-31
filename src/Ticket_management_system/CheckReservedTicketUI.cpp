#include "CheckReservedTicketUI.h"

CheckReservedTicketUI::CheckReservedTicketUI()
{
}

CheckReservedTicketUI::~CheckReservedTicketUI()
{
}

// Function : void startCheckReservedTicket(ifstream & in, ofstream & out)
// Description : use case.Check Reserved Ticket를 시작하기 위한 함수.
// Parameters :
//				ifstream & in - input 텍스트 파일의 레퍼런스
//				ofstream & out - output 텍스트 파일의 레퍼런스
// Return Value : None
// Created : 2019/06/02 03:22 pm
// Author : 박형준
// Revisions :
//	1.	When & Who : 2019/06/03 03:41 am by 박형준
//		What : startCheckReservedTicket 함수에서 파일 입출력을 위한 매개 변수에 파일스트림 레퍼런스 추가 및 내용 수정
//	2.	When & Who : 2019/06/05 07:30 pm by 박형준
//		What : 예약한 티켓이 없을 경우에 "> " 이 문구만 출력되게 수정
void CheckReservedTicketUI::startCheckReservedTicket(ifstream & in, ofstream & out)
{
	CheckReservedTicket CRT;
	unsigned int price, year, month, day, hour, minute;
	string seatPos;
	string homeTeam, awayTeam;

	out << "4.5. 예약 정보 조회" << endl;
	vector<pair<int, Ticket>> list(CRT.getReservedTicketList());

	for (int i = 0; i < list.size(); i++)
	{
		price = list[i].second.getBuyerPrice();
		year = list[i].second.getMatchTime().year;
		month = list[i].second.getMatchTime().month;
		day = list[i].second.getMatchTime().day;
		hour = list[i].second.getMatchTime().hour;
		minute = list[i].second.getMatchTime().min;

		homeTeam = list[i].second.getHomeTeam(); awayTeam = list[i].second.getBasicInfo().awayTeam;
		seatPos = list[i].second.getBasicInfo().seatPosition;
		Timer::TimeSet match(year, month, day, hour, minute);

		out << "> " << price << " " << match << " " << homeTeam << " " << awayTeam << " " << seatPos << endl;
	}
}
