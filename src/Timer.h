#pragma once
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

// Class : Timer
// Description : 시간과 관련된 일을 수행하는 클래스.
//				현재 시간을 저장하기 위해 ctime include.
//				시간에 대한 정보와, 시간에 따라 수행하게 되는 함수를 가지고 있음.
//				멤버 변수로 timeSet 구조체의 currentTime를 가지고 있음.
//				timeSet 구조체는 시간에 대한 값을 저장할 수 있도록 int형의 변수를 선언.
//				멤버 함수로는 getCurrenTime(), setCurrentTime(), addTicketToAuctionList()를 가지고 있음.
// Created : 2019/05/29 01:00 am
// Author : 박형준
// Revisions: 
//	1. When & Who : 2019/06/03 01:58 am by 정윤석
//		What: 1) struct TimeSet을 public으로 변경
//			  2) 클래스 내부에 선언된 함수들을 분리하여 cpp파일에 구현
//			  3) static Timer* singletonInstance; 를 초기화하도록 cpp파일에 코드 추가
//			  4) Timer() 생성자를 선언만 해두고 구현하지 않음 -> cpp파일에 구현함
//			  5) Timer::TimeSet 구조체의 ostream, ofstream << 연산자 오버로딩 함.
//				형식에 맞게끔 출력하도록 오버로딩
//			  6) Timer::TimeSet 구조체의 istream, ifstream >> 연산자 오버로딩 함
//				형식에 맞게끔 입력받도록 오버로딩
//			  7) Timer::TimeSet 구조체 == 연산자 오버로딩, 모든 멤버가 같으면 true 반환
//	2. When & Who : 2019/06/03 07:38 am by 정윤석
//		What: 1) 함수 추가
//				(1) void timeRelatedAutomationFunction()
//					: setCurrentTime() 실행시 마지막에 실행됨. 아래 세 개의 함수를 실행시켜주는 함수
//				(2) void endAuction(): 경매중인 티켓의 낙찰/유찰을 결정하고 그에따라 처리
//				(3) void updateAuctionTicketList(): 시간의 흐름에 따른 새로운 경매중 티켓 업데이트
//				(4) void deleteOneYearTickets(): 판매된지 1년이 지난 티켓을 삭제
// 3. When & Who: 2019/06/23 10:23 pm by 정윤석
//		Waht: 1) pair<int, int> minToHour_Min(int) 함수 추가

class Timer
{
public:
	~Timer();
	struct TimeSet {
		unsigned int year, month, day, hour, min;

		TimeSet() { year = month = day = hour = min = 0; }
		TimeSet(int y, int m, int d, int h, int mi) : year(y), month(m), day(d), hour(h), min(mi) {}
		friend ostream& operator << (ostream&, const TimeSet&);
		friend ofstream& operator << (ofstream&, const TimeSet&);
		friend ifstream& operator >> (ifstream&, TimeSet&);
		friend istream& operator >> (istream&, TimeSet&);
		bool operator == (const TimeSet&);
	};
private:
	Timer();
	static Timer* singletonInstance;
	TimeSet currentTime;

	void timeRelatedAutomationFunction();
	void updateAuctionTicketList();
	void endAuction();
	void deleteOneYearTickets();
public:
	static Timer* getInstance();
	TimeSet getCurrentTime();

	void setCurrentTime(ifstream & in, ofstream & out);
	pair<int, int> minToHour_Min(int);
	int getRemainingTime(TimeSet t);
};

