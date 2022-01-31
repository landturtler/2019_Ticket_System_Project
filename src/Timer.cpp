#include "Timer.h"
#include <iomanip>
#include <string>
#include "TicketManager.h"
#include "AuctionManager.h"
#include "MemberManager.h"
#pragma warning(disable : 4996)

Timer* Timer::singletonInstance = nullptr;
Timer::Timer() {}
Timer::~Timer() {}


// Function : static Timer * getInstance()
// Description : Timer의 싱글톤 클래스 인스턴스가 없다면 생성하고, 해당 인스턴스의 포인터 반환.
// Parameters : None
// Return Value : Timer * instance;
// Created : 2019/05/30 09:01 pm
// Author : 박형준
Timer * Timer::getInstance() {
	if (!singletonInstance) singletonInstance = new Timer();
	return singletonInstance;
}


// Function : void timeRelatedAutomationFunction()
// Description : 이름 그대로 시간에 관련된 자동화 함수임
//				경매 낙찰/유찰, 새로운 경매 중 티켓 업데이트, 판매한지 1년이 지난 티켓 삭제를
//				순서대로 수행함
// Parameters : None
// Return Value : None 
// Created : 2019/06/03 07:21 am 
// Author : 정윤석
void Timer::timeRelatedAutomationFunction() {
	/*
	! 주의 !
	항상 endAuction, deleteOneYearTickets, updateAuctionTicketList 의 순서로 실행시켜야 함
	*/
	this->endAuction();
	this->deleteOneYearTickets();
	this->updateAuctionTicketList();
}


// Function : void endAuction()
// Description : 경기 시작까지 6시간 이하로 남아 경매가 종료된 티켓들을 낙찰/유찰 처리함
// Parameters : None
// Return Value : None 
// Created : 2019/06/03 07:21 am 
// Author : 정윤석
void Timer::endAuction() {
	TicketManager *tm = TicketManager::getInstance();
	AuctionManager *am = AuctionManager::getInstance();
	MemberManager *mm = MemberManager::getInstance();

	// 경매 중인 티켓 ID 리스트 받아옴
	vector<int> auctionTicketIDList = am->getAuctionTicketList();

	// 위에서 받은 리스트의 실제 티켓 객체를 리스트로 받아옴
	tm->setTicketList(auctionTicketIDList);
	vector<pair<int, Ticket>> tickets = tm->getTicketList();

	for (auto ticketPair : tickets) {
		int remainTime = ticketPair.first;
		Ticket ticket = ticketPair.second;
		int ticketID = ticket.getID();
		
		// 남은 시간이 6시간 이하일떄 낙찰/유찰 처리함
		if (remainTime <= 60 * 6) {
			tuple<int, int, string> biddingInfo = am->getBiddingInfo(ticketID);
			
			// 입찰자가 존재함 -> 낙찰
			int id = get<0>(biddingInfo);
			if (ticketID == id) {
				int price = get<1>(biddingInfo);
				string buyerID = get<2>(biddingInfo);
				
				// 티켓 구매가격, 구매자 변경
				tm->reserveTicket(ticketID, price, buyerID);
				// 구매자의 구매한 티켓 목록에 추가
				mm->reserveTicket(ticketID, buyerID);
			}
		}
	}
}


// Function : void updateAuctionTicketList()
// Description : 시간의 흐름에 따라 새로 경매에 나오게 된 티켓들을 업데이트함
// Parameters : None
// Return Value : none
// Created : 2019/06/03 07:21 am 
// Author : 정윤석
void Timer::updateAuctionTicketList() {
	TicketManager *tm = TicketManager::getInstance();
	AuctionManager *am = AuctionManager::getInstance();

	// 모든 티켓 받아오기
	tm->setTicketList();
	vector<pair<int, Ticket>> tickets = tm->getTicketList();

	vector<int> newAuctionTicketIDList;
	for (auto ticketPair : tickets) {
		int remainTime = ticketPair.first;
		Ticket ticket = ticketPair.second;
		Timer::TimeSet matchTime = ticket.getMatchTime();
		string buyerID = ticket.getBuyerID();

		if (buyerID != "") continue;
		// 남은 시간이 6시간 초과, 24시간 이하일때 업데이트 목록에 추가함
		if (60 * 6 < remainTime && remainTime <= 60 * 24) {
			newAuctionTicketIDList.push_back(ticket.getID());
		}
	}
	
	//AuctionManager의 경매 중 티켓 리스트에 추가
	am->updateAuctionTicketList(newAuctionTicketIDList);
}


// Function : deleteOneYearTickets()
// Description : 1년 지난 티켓이 있으면 삭제함
// Parameters : None
// Return Value : None 
// Created : 2019/06/03 07:21 am 
// Author : 정윤석
void Timer::deleteOneYearTickets() {
	TicketManager *tm = TicketManager::getInstance();
	AuctionManager *am = AuctionManager::getInstance();
	MemberManager *mm = MemberManager::getInstance();

	tm->setTicketList();
	vector<pair<int, Ticket>> ticketList = tm->getTicketList();
	for (auto ticketPair : ticketList) {
		Ticket ticket = ticketPair.second;

		TimeSet enrolledTime = ticket.getEnrolledTime();
		int remainTime = getRemainingTime(enrolledTime);
		//cout << "시간: " << remainTime << '\n';
		// 365일 -> 24시간 -> 60분
		if (remainTime > -(365 * 24 * 60))
			continue;
		//cout << "true\n";

		int ticketID = ticket.getID();
		string sellerID = ticket.getSellerID();
		string buyerID = ticket.getBuyerID();
		
		Ticket t = tm->getTicket(ticketID);
		//cout << "남은 시간: " << remainTime << endl;
		//cout << "1년 지나서 삭제: " << t.getPrice() << ' ' << t.getBasicInfo() << endl;

		tm->deleteTicket(ticketID);
		
		mm->deleteMembersTicket(ticketID, sellerID);
		if(buyerID != "")
			mm->deleteMembersTicket(ticketID, buyerID);
	}
}



// Function : TimeSet getCurrentTime()
// Description : 현재 시간에 대한 값을 반환.
// Parameters : None
// Return Value : (struct) TimeSet currentTime
// Created : 2019/05/29 01:13 am
// Author : 박형준
Timer::TimeSet Timer::getCurrentTime() {
	return currentTime;
}


// Function : void setCurrentTime(int y, int m, int d, int h, int mi)
// Description : Timer의 멤버 구조체인 currentTime에 입력 받은 시간을 저장.
// Parameters : int y - year
//				int m - month
//				int d - day
//				int h - hour
//				int mi - minute
// Return Value : None
// Created : 2019/05/29 01:14 am
// Author : 박형준
// Revisions:
//	1. When & Who : 2019/06/03 07:55 am by 정윤석
//		What: 1) 함수의 마지막에 void Timer::timeRelatedAutomationFunction()을 실행시키도록 함
//	2.	When & Who : 2019/06/03 05:06 pm by 박형준
//		What : 함수 내에서 파일 스트림을 레퍼런스로 입력 받아 파싱을 통해 현재 시간을 설정할 수 있도록,
//			매개 변수를 파일 스트림으로 수정 및 내용 수정
void Timer::setCurrentTime(ifstream & in, ofstream & out)
{
	unsigned int year, month, day, hour, minute;
	string matchDateNTime;

	out << "5.1. 현재시간 설정" << endl;
	in >> matchDateNTime;
	// 날짜와 시간 분류
	year = stoi(matchDateNTime.substr(0, 4)); month = stoi(matchDateNTime.substr(5, 2)); day = stoi(matchDateNTime.substr(8, 2));
	hour = stoi(matchDateNTime.substr(11, 2)); minute = stoi(matchDateNTime.substr(14, 2));

	currentTime.year = year;
	currentTime.month = month;
	currentTime.day = day;
	currentTime.hour = hour;
	currentTime.min = minute;

	out << "> " << currentTime << endl;

	this->timeRelatedAutomationFunction();
}



// Function : pair<int, int> minToHour_Min(int)
// Description : 분으로 나타낸 시간을 시:분 의 형식으로 반환함
//				입력으로 들어올 인자는 24*60(시간*분)을 넘지 않음
// Param: int curTime - 분으로 나타낸 시간
//
// Created : 2019/06/03 10:10 pm
// Author : 정윤석
pair<int, int> Timer::minToHour_Min(int time) {
	return { time / 60, time % 60 };
}

// Function : int getRemainingTime(TimeSet t)
// Description : TimeSet 구조체 타입으로 티켓의 경기 시간 정보를 받아와,
//				현재 저장된 시간과의 남은 시간을 계산하여 반환.
// Parameters : TimeSet t
// Return Value : (int) remainT
// Created : 2019/05/30 09:36 pm
// Author : 박형준
// Revisions :
//	1.	When & Who : 2019 / 06 / 03 02 : 50 am by 박형준
//		What: 로컬 변수명, 반복문 조건 수정
int Timer::getRemainingTime(TimeSet t)
{
	TimeSet local_timeSet(t.year - 1900, t.month - 1, t.day, t.hour, t.min);
	TimeSet local_currentTimeSet(currentTime.year - 1900, currentTime.month - 1, currentTime.day, currentTime.hour, currentTime.min);
	unsigned int remainT;
	int mday[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	local_timeSet.month += local_timeSet.year * 12;
	for (; local_timeSet.month > 11; local_timeSet.month -= 12) local_timeSet.day += 365;
	for (int i = 0; i < local_timeSet.month; i++) local_timeSet.day += mday[i];
	local_timeSet.hour += local_timeSet.day * 24;
	local_timeSet.min += local_timeSet.hour * 60;

	local_currentTimeSet.month += local_currentTimeSet.year * 12;
	for (; local_currentTimeSet.month > 11; local_currentTimeSet.month -= 12) local_currentTimeSet.day += 365;
	for (int i = 0; i < local_currentTimeSet.month; i++) local_currentTimeSet.day += mday[i];
	local_currentTimeSet.hour += local_currentTimeSet.day * 24;
	local_currentTimeSet.min += local_currentTimeSet.hour * 60;

	remainT = local_timeSet.min - local_currentTimeSet.min;

	return remainT;
}


// Function : ostream& operator <<(ostream& os, const Timer::TimeSet& time)
// Description : Timer::TimeSet 구조체의 ostream << 오버로딩 함수
//				형식에 맞게끔 출력하도록 함
// Created : 2019/06/03 02:10 am
// Author : 정윤석
ostream& operator << (ostream& os, const Timer::TimeSet& time) {
	int year = time.year;
	int mon = time.month;
	int day = time.day;
	int hour = time.hour;
	int min = time.min;

	os << setw(4) << setfill('0') << year << ":" << setw(2) << setfill('0') << mon << ":" << setw(2) << setfill('0') << day
		<< ":" << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << min;

	return os;
}


// Function : ofstream& operator <<(ofstream& os, const Timer::TimeSet& time)
// Description : Timer::TimeSet 구조체의 ofstream << 오버로딩
//				형식에 맞게끔 파일출력하도록 함
// Created : 2019/06/03 02:10 am
// Author : 정윤석
ofstream& operator << (ofstream& ofs, const Timer::TimeSet& time) {
	int year = time.year;
	int mon = time.month;
	int day = time.day;
	int hour = time.hour;
	int min = time.min;

	ofs << setw(4) << setfill('0') << year << ":" << setw(2) << setfill('0') << mon << ":" << setw(2) << setfill('0') << day
		<< ":" << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << min;

	return ofs;
}


// Function : ifstream& operator <<(ifstream& ifs, const Timer::TimeSet& time)
// Description : Timer::TimeSet 구조체의 ifstream >> 오버로딩
//				형식에 맞게끔 파일출력하도록 함
// Created : 2019/06/03 02:10 am
// Author : 정윤석
ifstream& operator >> (ifstream& ifs, Timer::TimeSet& time) {
	string tmp;

	getline(ifs, tmp, ':');
	time.year = stoi(tmp);
	getline(ifs, tmp, ':');
	time.month = stoi(tmp);
	getline(ifs, tmp, ':');
	time.day = stoi(tmp);
	getline(ifs, tmp, ':');
	time.hour = stoi(tmp);
	ifs >> tmp;
	time.min = stoi(tmp);

	return ifs;
}


// Function : istream& operator <<(istream& is, const Timer::TimeSet& time)
// Description : Timer::TimeSet 구조체의 istream >> 오버로딩
//				형식에 맞게끔 파일입력 받도록 함
// Created : 2019/06/03 04:45 am
// Author : 정윤석
istream& operator >> (istream& is, Timer::TimeSet& time) {
	string tmp;

	getline(is, tmp, ':');
	time.year = stoi(tmp);
	getline(is, tmp, ':');
	time.month = stoi(tmp);
	getline(is, tmp, ':');
	time.day = stoi(tmp);
	getline(is, tmp, ':');
	time.hour = stoi(tmp);
	is >> tmp;
	time.min = stoi(tmp);

	return is;
}

bool Timer::TimeSet::operator == (const TimeSet& oth) {
	if (year != oth.year) return false;
	if (month != oth.month) return false;
	if (day != oth.day) return false;
	if (hour != oth.hour) return false;
	if (min != oth.min) return false;
	return true;
}