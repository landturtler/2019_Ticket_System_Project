#pragma once
#include "TicketManager.h"
#include <utility>
#include <algorithm>
TicketManager* TicketManager::ticketManager = nullptr;

TicketManager::TicketManager() :nextID(1) {}

TicketManager::~TicketManager() {}

//-------------------------------------------------------
// Function: TicketManager:: getInstance()
// Description: 싱글톤으로 구현하기 위한 함수
// Parameters: None
// Return Value: TicketManager
//-------------------------------------------------------
TicketManager* TicketManager::getInstance() {
	if (ticketManager == NULL)
		ticketManager = new TicketManager();
	return ticketManager;
}


//-------------------------------------------------------
// Function: TicketManager:: addNewTicket
// Description:새로운 티켓에 대한 정보를 입력받아 티켓을 새로 등록하는 함수
// Parameters: 티켓 정보
// Return Value:None
// 상의 내용:ID값을 누가 지정해주는지(파라미터로 입력받을지 혹은 함수 내에서 만들어서 넣을지)
//Revision
//1.when&who:2019.06.04 01:33pm, 이지현
//what:등록한 티켓의 아이디를 리턴하게 수정
//-------------------------------------------------------
int TicketManager::addNewTicket(int price, Timer::TimeSet matchTime,
	string home, string away, string seat, bool la, string sellerID) {
	
	Timer::TimeSet curTime = Timer::getInstance()->getCurrentTime();
	Ticket* ticket = new Ticket(nextID++, price, curTime, matchTime, home, away, seat, la, sellerID);
	tickets.push_back(ticket);

	return ticket->getID();
}


//-------------------------------------------------------
// Function: TicketManager:: addTicketToSortedList
// Description:sortList에 해당 티켓과 남은시간을 넣는 함수
// Parameters:remain T, ticket
// Return Value:None
//--------------------------------------------------------
void TicketManager::addTicketToSortedList(int remainT, Ticket ticket) {
	sortLists.push_back(make_pair(remainT, ticket));
}


//-------------------------------------------------------
// Function: Ticket* TicketManager::getTicketPointer(int ticketID)
// Description: 특정 티켓의 id를 받아서 해당 티켓의 포인터를 반환
// Parameters: int ticketID - 받아올 티켓의 ID
// Return Value: 해당하는 ID가 있을 시 - 해당 티켓의 포인터
//							 없을 시 - NULL
//--------------------------------------------------------
Ticket* TicketManager::getTicketPointer(int ticketID) {
	for (Ticket* ticket : tickets) {
		if (ticket->getID() == ticketID) {
			return ticket;
		}
	}
	return NULL;
}


//-------------------------------------------------------
// Function: Ticket* TicketManager::getTicketPointer(int ticketID)
// Description: 특정 티켓의 id를 받아서 해당 티켓 객체를 반환
// Parameters: int ticketID - 받아올 티켓의 ID
// Return Value: 해당하는 ID가 있을 시 - 해당 티켓 객체
//							 없을 시 - 빈 티켓 객체 
//--------------------------------------------------------
Ticket TicketManager::getTicket(int ticketID) {
	Ticket ret;
	for (Ticket* ticket : tickets) {
		if (ticket->getID() == ticketID) {
			return *ticket;
		}
	}
	return Ticket();
}

//-------------------------------------------------------
// Function: TicketManager:: reserveTicket
// Description:특정 티켓을 예약해달라는 메세지 전달하는 함수
// Parameters:티켓 아이디
// Return Value:None
//--------------------------------------------------------
void TicketManager::reserveTicket(int ticketID, string buyerID) {
	Ticket* ticket = getTicketPointer(ticketID);
	if (!ticket) {
		cout << "void TicketManager::reserveTicket(int ticketID, string buyerID)\n";
		cout << ": nullptr error\n";
		return;
	}
	ticket->setBuyerID(buyerID);
}


//-------------------------------------------------------
// Function: void reserveTicket(int ticketID, int price, string buyerID)
// Description:특정 티켓을 예약해달라는 메세지 전달하는 함수
//				이 함수는 경매 낙찰시 쓰이게 됨
// Parameters: int ticketID - 정보 변경할 티켓id
//				int price - 구매한 가격
//				string buyerID - 구매자 ID
// Return Value:None
//--------------------------------------------------------
void TicketManager::reserveTicket(int ticketID, int price, string buyerID) {
	Ticket* ticket = getTicketPointer(ticketID);

	ticket->setBuyerPrice(price);
	ticket->setBuyerID(buyerID);
	//cout << "reserveTicket: " << ticket->getID() << ' ' << ticket->getBasicInfo() << endl;
}


//-------------------------------------------------------
// Function: TicketManager:: sortList
// Description:sortLists에 있는 티켓 목록들을 경기날짜 및 시각이 빠른 티켓부터 정렬하여 출력
// Parameters:None
// Return Value:SortLists
//--------------------------------------------------------
void TicketManager::sortList() {
	sort(sortLists.begin(), sortLists.end());
}

// Function: void setTicketList(string home)
// Description: 모든 티켓 목록을 sortLists에 저장함
//				남은 시간을 실시간으로 구하여 함께 저장함
// Parameters: None
// Return Value: None
void TicketManager::setTicketList() {
	sortLists.clear();

	for (Ticket *tp : tickets) {
		Ticket ticket = *tp;
		Timer::TimeSet matchTime = ticket.getMatchTime();
		int remainTime = Timer::getInstance()->getRemainingTime(matchTime);
		addTicketToSortedList(remainTime, ticket);
	}

	sortList();
}
// Function: void setTicketList(string home)
// Description: home팀을 받아 해당 홈팀의 *예약 가능한* 티켓 목록을 sortLists에 저장함
//				남은 시간을 실시간으로 구하여 함께 저장함
// Parameters: string home - 홈팀
// Return Value: None
void TicketManager::setTicketList(string home) {
	sortLists.clear();

	for (Ticket* tp : tickets) {
		Ticket ticket = *tp;

		string ticketHome = ticket.getHomeTeam();
		string buyerID = ticket.getBuyerID();
		if ((ticketHome != home) || (buyerID != "")) continue;

		int id = ticket.getID();
		if (AuctionManager::getInstance()->isAuctionList(id)) continue;

		Timer::TimeSet matchTime = ticket.getMatchTime();
		int remainTime = Timer::getInstance()->getRemainingTime(matchTime);
		if (remainTime <= 60 * 24) continue;

		addTicketToSortedList(remainTime, ticket);
	}

	sortList();
}


// Function: void setTicketList(vector<int> lst)
// Description: 티켓 ID들을 리스트로 받아 해당 티켓을 sortLists에 추가함
//				남은 시간을 실시간으로 구하여 함께 저장
// Parameters: vector<int> lst - 추가할 티켓의 ID 리스트
// Return Value: None
void TicketManager::setTicketList(vector<int> lst) {
	sortLists.clear();

	for (int id : lst) {
		Ticket ticket = getTicket(id);
		Timer::TimeSet matchTime = ticket.getMatchTime();
		int remainTime = Timer::getInstance()->getRemainingTime(matchTime);

		addTicketToSortedList(remainTime, ticket);
	}

	sortList();
}


// Function: void setTicketList(string home, vector<int> lst)
// Description: 홈팀과 티켓 ID들을 리스트로 받은 뒤 해당되는 홈팀의 티켓이라면 티켓을 sortLists에 추가함
//				남은 시간을 실시간으로 구하여 함께 저장함
// Parameters:	string home - 원하는 홈팀
//				vector<int> lst - 추가할 티켓의 ID 리스트
// Return Value: None
void TicketManager::setTicketList(string home, vector<int> lst) {
	sortLists.clear();

	for (int id : lst) {
		Ticket ticket = getTicket(id);
		Timer::TimeSet matchTime = ticket.getMatchTime();
		string ticketHomeTeam = ticket.getHomeTeam();
		int remainTime = Timer::getInstance()->getRemainingTime(matchTime);

		if (home == ticketHomeTeam)
			addTicketToSortedList(remainTime, ticket);
	}

	sortList();
}

// Function: vector<pair<int, Ticket>> getTicketList()
// Description: setTicketList()를 통해 설정된 sortLists를 반환함
// Parameters: None
// Return Value: 멤버 변수 sortLists
vector<pair<int, Ticket>> TicketManager::getTicketList() {
	return sortLists;
}

void TicketManager::deleteTicket(int ticketID) {
	Ticket *pticket = getTicketPointer(ticketID);
	for (int i = 0; i < tickets.size(); i++) {
		Ticket *t = tickets[i];
		if (t->getID() == ticketID) {
			tickets.erase(tickets.begin() + i);
			break;
		}
	}
	delete pticket;
}
