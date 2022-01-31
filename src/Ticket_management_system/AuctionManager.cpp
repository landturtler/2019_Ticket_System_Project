#pragma once
//#include <iostream>
#include "AuctionManager.h"
#include "Ticket.h"
#include <algorithm>
using namespace std;



AuctionManager* AuctionManager::instance = nullptr;

AuctionManager::AuctionManager() {}


//-----------------------------------------------------------------------------
// Function: AuctionManager* getInstance()
// Description: 싱글톤 패턴을 적용하기 위한 함수
//				인스턴스가 만들어져 있다면 해당 인스턴스의 주소를,
//				그렇지 않다면 인스턴스를 새로 동적할당해 그 주소를 반환함
// Parameters: None
// Return Value: AuctionManager 인스턴스의 포인터
//-----------------------------------------------------------------------------
AuctionManager* AuctionManager::getInstance() {
	if (!instance) instance = new AuctionManager();
	return instance;
}


//-----------------------------------------------------------------------------
// Function: bool isAuctionList(int ticketID)
// Description: 경매중인 티켓 리스트에 파라미터로 들어온 티켓이 포함되는지 확인
// Parameters: int ticketID - 포함되는지 확인할 티켓의 ID
// Return Value: boolean - 포함되면 true, or false;
//-----------------------------------------------------------------------------
bool AuctionManager::isAuctionList(int ticketID) {
	bool hasTicket = binary_search(tickets.begin(), tickets.end(), ticketID);
	if (hasTicket) return true;
	return false;
}


//-----------------------------------------------------------------------------
// Function: vector<int> getAuctionTicketList()
// Description: 현재 경매 중인 티켓 리스트를 반환한다
// Parameters: None
// Return Value: vector<int> tickets - 현재 경매 중인 티켓ID 리스트
//-----------------------------------------------------------------------------
vector<int> AuctionManager::getAuctionTicketList() {
	return tickets;
}


//-----------------------------------------------------------------------------
// Function: void addBiddingInfo(int ticketID, int price, string buyerID)
// Description: 구매자가 입찰 시도시 입찰 정보를 저장함.
//				단, ID가 같은 티켓에 대해 입찰을 시도한 입찰가보다 이미 등록된 입찰가가 더 높다면
//				아무일도 하지 않고 종료.
//				입찰 정보들은 항상 티켓ID를 기준으로 오름차순임이 보장되도록 추가됨
// Parameters:	int ticketID - 입찰을 시도하는 티켓의 ID
//				int price - 입찰가
//				string buyerID - 입찰을 시도한 구매자의 ID
// Return Value: None
//-----------------------------------------------------------------------------
void AuctionManager::addBiddingInfo(int ticketID, int price, string buyerID) {
	if (!isAuctionList(ticketID)) return;

	auto it = lower_bound(biddingInfoList.begin(), biddingInfoList.end(), make_tuple(ticketID, 0, ""));
	int id = 0;

	if (it != biddingInfoList.end())
		id = get<0>(*it);

	auto info = make_tuple(ticketID, price, buyerID);

	// 아직 입찰자가 없는 경우
	if (id != ticketID) {
		biddingInfoList.insert(it, info);
	}
	else {
		int old_price = get<1>(*it);
		// 새로운 입찰가가 이전 입찰가보다 크면 info 정보를 대체 
		if (price > old_price) {
			*it = info;
		}
	}
}


//------------------------------------------------------------------------------
// Function: void updateAuctionTicketList(vector<int> newAuctionList)
// Description: 새로운 경매 중인 티켓 리스트를 받아 리스트를 새로 만듬
//				티켓을 중복해서 저장하지 않으며, 항상 오름차순으로 정렬됨
// Parameters: vector<int> newAuctionList - 새로운 경매 중인 티켓 리스트
// Return Value: None
//------------------------------------------------------------------------------
void AuctionManager::updateAuctionTicketList(vector<int> newAuctionList) {
	// tickets 초기화
	tickets.clear();

	// 입력으로 들어온 리스트 중복 제거
	sort(newAuctionList.begin(), newAuctionList.end());
	newAuctionList.erase(unique(newAuctionList.begin(), newAuctionList.end()), newAuctionList.end());

	tickets = newAuctionList;

	sort(tickets.begin(), tickets.end());
}


//------------------------------------------------------------------------------
// Function: tuple<int, int, string> getBiddingInfo(int ticketID)
// Description: ticketID를 받아 해당 티켓에 대한 정보가 biddingInfoList에 있으면 그 튜플을 반환함
// Parameters: int ticketID - 찾기를 원하는 티켓 id
// Return Value: 성공시 - 해당 티켓의 입찰정보
//				실패시 - 기본 생성자로 초기화된 튜플
//------------------------------------------------------------------------------
tuple<int, int, string> AuctionManager::getBiddingInfo(int ticketID) {
	for (auto biddingInfo : biddingInfoList) {
		int id = get<0>(biddingInfo);
		if (id == ticketID)
			return biddingInfo;
	}
	return tuple<int, int, string>();
}


/*
// Test code ------------------------------------------------
int main() {
	AuctionManager* am = AuctionManager::getInstance();
	vector<int> p;
	p.push_back(1); p.push_back(2); p.push_back(10); p.push_back(5); p.push_back(2);
	am->updateAuctionTicketList(p);
	//cout << "ID: " << *am << '\n';
	am->addBiddingInfo(4, 999, "이게나오면안됨");
	am->addBiddingInfo(5, 555, "5번1");
	am->addBiddingInfo(2, 222, "2번1");
	am->addBiddingInfo(1, 123, "1번1");
	am->addBiddingInfo(5, 666, "5번2");
	am->addBiddingInfo(5, 333, "5번x");
	am->addBiddingInfo(1, 321, "1번2");
	cout << *am;
}
*/