#pragma once
#include "Ticket.h"


Ticket::BasicInfo::BasicInfo()
	:matchTime(Timer::TimeSet()), homeTeam(""), awayTeam(""), seatPosition("") {}

Ticket::Ticket()
	: ID(0), sellerPrice(0), buyerPrice(0), enrolledTime(Timer::TimeSet()), basicInfo(),
	limitedAuction(false), sellerID(""), buyerID("") {}


//---------------------------------------------------------------------------------------
// Function: Ticket::Ticket(파라미터는 아래 참조)
// Description: Ticket의 모든 멤버를 초기화하는 생성자임.
//				buyerID는 파라미터로 받지 않고 empty string으로 초기화 함.
// Parameters:	int ID - 티켓 ID
//				int price - 티켓 가격
//				Timer::TimeSet matchTime - 경기 날짜, 시각
//				string home - 해당 경기의 홈팀 이름
//				string away - 해당 경기의 어웨이팀 이름 
//				pair<int, int> seat - 좌석 위치
//				bool la - limited auction 체크 여부
//				string sellerID - 판매자 ID
// Return Value: None
//---------------------------------------------------------------------------------------
Ticket::Ticket(int ID, int sellerPrice, Timer::TimeSet enrolledTime, Timer::TimeSet matchTime, string home, string away,
	string seat, bool la, std::string sellerID)
	: ID(ID), sellerPrice(sellerPrice),buyerPrice(sellerPrice), enrolledTime(enrolledTime), basicInfo(matchTime, home, away, seat),
	limitedAuction(la), sellerID(sellerID), buyerID("") {}


//-------------------------------------------------------
// Function: void setBuyerID(string id)
// Description: 티켓의 구매자아이디 값을 변경함
// Parameters: string buyerID - 새로운 buyerID 값
// Return Value: None
//-------------------------------------------------------
void Ticket::setBuyerID(std::string buyerID) {
	this->buyerID = buyerID;
}


//-------------------------------------------------------
// Function: void setBuyerPrice(int price)
// Description: 실제 구매 가격 정보를 변경함
// Parameters: int price - 새로운 티켓 가격
// Return Value: None
//-------------------------------------------------------
void Ticket::setBuyerPrice(int price) {
	this->buyerPrice = price;
}


//----------------------------------------------------
// Function: int getID()
// Description: 티켓의 ID 값을 반환함
// Return Value: 티켓의 ID
//----------------------------------------------------
int Ticket::getID() {
	return ID;
}


//----------------------------------------------------
// Function: int getBuyerPrice()
// Description: 티켓의 실제 구매가격을 반환함
// Return Value: 티켓의 구매 가격
//----------------------------------------------------
int Ticket::getBuyerPrice() {
	return buyerPrice;
}


//----------------------------------------------------
// Function: int getSellerPrice()
// Description: 티켓의 희망판매가격을 반환함
// Return Value: 티켓의 희망 가격
//----------------------------------------------------
int Ticket::getSellerPrice() {
	return sellerPrice;
}


//----------------------------------------------------
// Function: Timer::TimeSet getMatchTime()
// Description: 티켓의 경기 날짜 + 시각을 반환함
// Return Value: 티켓의 경기 날짜 + 시각
//----------------------------------------------------
Timer::TimeSet Ticket::getMatchTime() {
	return basicInfo.matchTime;
}


//----------------------------------------------------
// Function: string getHomeTeam()
// Description: 해당 경기의 홈팀을 반환
// Return Value: 티켓의 홈팀
//----------------------------------------------------
std::string Ticket::getHomeTeam() {
	return basicInfo.homeTeam;
}


//----------------------------------------------------
// Function: string getBuyerID()
// Description: 해당 티켓의 구매자 아이디를 반환함
// Return Value: 티켓의 buyerID
//----------------------------------------------------
std::string Ticket::getBuyerID() {
	return buyerID;
}


//----------------------------------------------------
// Function: string getSellerID()
// Description: 해당 티켓의 판매자 아이디를 반환함
// Return Value: 티켓의 sellerID
string Ticket::getSellerID() {
	return sellerID;
}


//----------------------------------------------------
// Function: bool getLimitedAuction()
// Description: 해당 티켓의 옥션 여부를 반환
// Return Value: 티켓의 옥션 여부
//----------------------------------------------------
bool Ticket::getLimitedAuction() {
	return limitedAuction;
}


//----------------------------------------------------
// Function: Timer::TimeSet getEnrolledTime()
// Description: 해당 티켓의 등록된 시간을 반환
// Return Value: 등록된 시간
//----------------------------------------------------
Timer::TimeSet Ticket::getEnrolledTime() {
	return enrolledTime;
}

//----------------------------------------------------
// Function: BasicInfo(Timer::TimeSet, string, string, pair<int, int>)
// Description: Ticket::BasicInfo 스트럭트의 생성자. 모든 멤버를 초기화한다
// Parameters:	Timer::TimerSet time - 경기 시간
//				string home - 홈팀, string away - 어웨이팀
//				pair<int, int> seat - 좌석 번호(행, 열)
//----------------------------------------------------
Ticket::BasicInfo::BasicInfo(Timer::TimeSet time, string home, string away, string seat)
	:matchTime(time), homeTeam(home), awayTeam(away), seatPosition(seat) {}


//----------------------------------------------------
// Function: bool operator < (const TIcket &a, const Ticket &b)
// Description: Ticket클래스의 < 연산자를 오버로딩
// Return Value: a.ID < b.ID 인가
//----------------------------------------------------
bool operator < (const Ticket &a, const Ticket &b) {
	return a.ID < b.ID;
}


//----------------------------------------------------
// Function: ostream& operator <<(ostream & os, const TIcket::BasicInfo &bi)
// Description: Ticket::BasicInfo 구조체의 ostream 오버로딩 함수.
//				출력 형식에 맞게 출력하도록 함
//----------------------------------------------------
ostream& operator << (ostream & os, const Ticket::BasicInfo &bi) {
	os << bi.matchTime<< ' ' << bi.homeTeam << ' ' << bi.awayTeam << ' ' << bi.seatPosition;
	return os;
}


//----------------------------------------------------
// Function: ostream& operator <<(ostream & os, const TIcket::BasicInfo &bi)
// Description: Ticket::BasicInfo 구조체의 ofstream 오버로딩 함수.
//				출력 형식에 맞게 출력하도록 함
//----------------------------------------------------
ofstream& operator << (ofstream& ofs, const Ticket::BasicInfo &bi) {
	ofs <<bi.matchTime<< ' ' << bi.homeTeam << ' ' << bi.awayTeam << ' ' << bi.seatPosition;
	return ofs;
}


//----------------------------------------------------
// Function: Ticket::BasicInfo getBasicInfo()
// Description: Ticket 클래스의 basicinfo 멤버를 반환
// Return Value: basicInfo
//----------------------------------------------------
Ticket::BasicInfo Ticket::getBasicInfo() {
	return basicInfo;
}


/*

//stream 오버로딩 테스트
int main() {
	Ticket ticket(1, 1000, Timer::TimeSet(2019, 5, 20, 18, 0), "home", "away", { 51, 3 }, true, "seller");
	Ticket::BasicInfo bi = ticket.getBasicInfo();
	ofstream outfile("out.txt");
	cout << bi;
	outfile << bi;
}
*/
