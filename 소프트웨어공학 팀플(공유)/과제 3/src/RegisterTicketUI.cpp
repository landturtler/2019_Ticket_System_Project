#include <iostream>
#include <fstream>
#include <string>
#include "RegisterTicketUI.h"
#include "RegisterTicket.h"
using namespace std;

// function : inputTicketInformationToRegister()
// description : 티켓 등록을 위한 정보를 입력하는 함수
// parameter : ifstream &in_fp :인풋파일
//						ofstream &out_fp : 아웃풋파일
// return value : 없음

void RegisterTicketUI::inputTicketInformationToRegister(ifstream &in_fp, ofstream &out_fp, RegisterTicket& registerTicket) {
	int price, year, month, day, hour, minute; int remainHour, remainMinute;
	string matchDateNTime; string seatPos; 
	string homeTeam, awayTeam;
	bool selectLTA, soldOut;

	out_fp << "3.1. 판매티켓 등록" << endl;
	in_fp >> price >> matchDateNTime >> homeTeam >> awayTeam >> seatPos >> selectLTA;
	// 경기 날짜와 시간 분류
	year = stoi(matchDateNTime.substr(0, 4)); month = stoi(matchDateNTime.substr(5, 2)); day = stoi(matchDateNTime.substr(8, 2));
	hour = stoi(matchDateNTime.substr(11, 2)); minute = stoi(matchDateNTime.substr(14, 2));
	
	bool success = registerTicket.requestNewTicket(price, year, month, day, hour, minute, homeTeam, awayTeam, seatPos, selectLTA);

	if (success) {
		out_fp << "> " << price << " " << matchDateNTime << " " << homeTeam << " " << awayTeam << " " << seatPos << " " << (unsigned int)selectLTA << endl;
	}
	else {
		out_fp << "티켓 등록 실패" << endl;
	}
}