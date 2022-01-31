#pragma once
#include "Ticket.h"
#include "Timer.h"
#include <vector>
#include <tuple>
#include <string>
using namespace std;
#define ttis tuple<Ticket*, int, string>

//---------------------------------------------------------------------------------------------
// class: AuctionManager
// Description: 옥션중인 티켓을 관리하는 클래스.
//				어디서든 클래스에 접근 가능하도록 싱글톤 패턴을 적용함
//				멤버변수인 tickets, bidderList는 항상 티켓id순으로 오름차순임이 보장됨
// Created: 2019/05/28 04:10 am
// Author: 정윤석
// Revisions:
//	1. When & Who: 2019/06/13 08:13 am by 정윤석
//		What: 1) bidderList 변수명을 biddinginfoList로 변경
//			  2) tuple<int, int, string> getBiddingInfo(int) 함수 추가
//				위 함수는 티켓id를 받아서 해당 티켓이 biddingInfoList에 있으면 그 튜플을 반환,
//				그렇지 않으면 기본 생성자로 생성된 튜플을 반환함
//---------------------------------------------------------------------------------------------
class AuctionManager {
private:
	vector<int> tickets;
	vector<tuple<int, int, string>> biddingInfoList; // 티켓 id, 입찰가격, buyerID
	
	static AuctionManager* instance;

	AuctionManager();
public:
	static AuctionManager* getInstance();
	bool isAuctionList(int);
	vector<int> getAuctionTicketList();
	void addBiddingInfo(int, int, string);
	void updateAuctionTicketList(vector<int>);
	tuple<int, int, string> getBiddingInfo(int);

};