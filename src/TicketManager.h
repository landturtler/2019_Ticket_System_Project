#pragma once
#include <vector>
#include <string>
#include "Ticket.h"
#include "Timer.h"
#include "AuctionManager.h"

using namespace std;


//---------------------------------------------------------------------------------------------
// class: TicketManager
// Description: 티켓 접근을 용이하게 하기 위한 클래스(?). 티켓들을 티켓 리스트로 저장하며 해당 기준으로 sorting함
//				 티켓포인터를 가진 티켓 리스트와 sorting된 정보를 가진 sortList를 갖고있음
// Created: 2019/05/31 02:29 am
// Author: 유지혁
// Revisions:
//	1. When & Who : 2019/05/31 02:30 am by 유지혁
//		What: 1) sorting기준을 usecase마다 다르게 하는데 이를 어떻게 처리할지에 대해 생각해볼 것 
//			  2) 티켓 클래스로부터 detail구조체가 아닌 tickets를 받는 것으로 변경.
//			  3) set함수 추가해야함
//			  4) 남은 시간은 타이머로부터 받아옴
//			  5) tickets리스트를 pair가 아닌 ticket 포인터만 가지는 것으로 변경
//  2. When & Who : 2019/06/02 09:03 pm by 정윤석
//		What: 1) 복사 생성자가 선언만 되있고 구현이 안되어있음
//				딥카피할 상황이 없기 때문에 삭제함.
//			  2) sortLists의 setter가 유즈케이스별로 눠져여있었음
//				공통 분모를 뽑아내어 string 혹은 vector<int>를 인자로 받아 set하게끔 통일
//			  3) (2.2)에 따라
//				(1) setTicketListToSearchTicket(string)
//				(2) setTicketListToCheckReservedTicket(vector<Ticket*>)
//				(3) getDefaultList()
//				(4) setHometeamAuctionTicketToSortList(string)
//			    위의 4개 함수들 삭제
//			  *4) 경매 중인 티켓을 낙찰 성공시 가격을 바꾸는 함수가 필요함
//				우선 winAuction()으로 이름 지어뒀는데 나중에 상의해야할 듯
//			  5) 기본 생성자에서 nextID를 1로 초기화하도록 함
//	3. When & Who : 2019/06/03 07:24 am by 정윤석
//		What: 1) 모든 티켓을 sortLists에 셋팅해두는 void setTicketList() 함수 만듬
//			  2) 티켓id, 가격, buyerID를 인자로 받아 티켓 정보를 업데이트하는
//				void reserveTicket(int, int, string) 함수 만듬(오버로딩됨)
//			  3) (3.2)에 따라서 winAuction()함수 삭제
//	4. When & Who : 2019/06/04 10:57 am by 정윤석
//		What: 1) 티켓 삭제함수 void deleteTicket(int ticketID) 추가
//5. When & Who : 2019/06/04 01:33pm, 이지현
//		What: 1) addNewTicket의 리턴타입 변경
//---------------------------------------------------------------------------------------------


class TicketManager {
private:
	vector<Ticket*> tickets;
	vector<pair<int, Ticket>> sortLists;//남은시간은 int형으로
	int nextID;
	static TicketManager* ticketManager;//singleton

	TicketManager();//생성자
	TicketManager(const TicketManager& other);
	~TicketManager();
	Ticket* getTicketPointer(int);
	void sortList();
	void addTicketToSortedList(int, Ticket);
public:
	static TicketManager* getInstance();
	int addNewTicket(int, Timer::TimeSet, string, string, string, bool, string);
	void setTicketList();
	void setTicketList(string);
	void setTicketList(vector<int>);
	void setTicketList(string, vector<int>);
	void reserveTicket(int, string);
	void reserveTicket(int, int, string);
	void deleteTicket(int);
	vector<pair<int, Ticket>> getTicketList();
	Ticket getTicket(int);
}; 