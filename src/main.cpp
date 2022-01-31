#include <iostream>
#include <fstream>
#include <string>
#include "Timer.h"
//회원가입
#include "SignUpUI.h"
#include "SignUp.h"
//티켓등록
#include "RegisterTicketUI.h"
#include "RegisterTicket.h"
//티켓검색
#include "SearchTicketUI.h"
#include "SearchTicket.h"
//옥션티켓
#include "SearchAuctionTicketUI.h"
#include "SearchAuctionTicket.h"
//로그인
#include "LogInUI.h"
#include "LogIn.h"
//로그아웃
#include "LogOutUI.h"
#include "LogOut.h"
//회원탈퇴
#include "WithdrawUI.h"
#include "Withdraw.h"
//등록 티켓 확인
#include "CheckEnrolledTicketUI.h"
#include "CheckEnrolledTicket.h"
//예약 정보 조회
#include "CheckReservedTicketUI.h"

#pragma warning(disable : 4996)
using namespace std;

//revision:
//1.when&who : 2019/06/03 02:52pm, 이지현
//what : signup 위해 SignUpUI.h, SignUp.h include
//				void signUpInterface 함수 추가
//				doTask의 signup 부분 수정
//2.when&who : 2019/06/03 03:01pm, 이지현
//what : registerticket 위해 RegisterTickeUI.h, RegisterTicket.h include
//				void registerTicketInterface 함수 추가
//				doTask의 registerticket 부분 수정
// 3. When & Who : 2019/06/03 07:38 pm 정윤석
//	What: 1) 현재시간설정을 제외하고 main내에서 데이터 입/출력 하는 부분 모두 삭제
//		  2) 5.1 현재시간 설정부분 작성
//4.when&who : 2019/06/03 08:17pm, 이지현
//what : searchticket 위해 SearchTickeUI.h, SearchTicket.h include
//				void searchTicketInterface 함수 추가
//				doTask의 searchticket 부분 수정
//5.when&who : 2019/06/03 08:49pm, 이지현
//what : reserveticket 위해 void reserveTicketInterface 함수 추가
//				doTask의 reserveticket 부분 수정
//6.When&who : 2019/06/03 12:55am, 조윤해
//What : LogInUI,LogIn, LogOutUI,LogOut,WithdrawUI,Withdraw 함수 추가
void doTask();

void signUpInterface(ifstream& in_fp, ofstream& out_fp);

void registerTicketInterface(ifstream& in_fp, ofstream& out_fp);

void searchTicketInterface(ifstream& in_fp, ofstream& out_fp);

void reserveTicketInterface(ifstream& in_fp, ofstream& out_fp);

void searchAuctionTicketInterface(ifstream& in_fp, ofstream& out_fp);
void participateAuctionInterface(ifstream& in_fp, ofstream& out_fp);
void LogInInterface(ifstream &in_fp, ofstream &out_fp);
void LogOutInterface(ifstream &in_fp, ofstream &out_fp);
void WithdrawInterface(ifstream &in_fp, ofstream &out_fp);
void startCheckEnrolledTicket(ifstream &in_fp, ofstream &out_fp);
void startCheckReservedTicket(ifstream & in_fp, ofstream & out_fp);
int main(void)
{

	doTask();

	return 0;
}

void doTask()
{
	Timer * timer = Timer::getInstance();

	// 메뉴 파싱
	int menu_level_1 = 0, menu_level_2 = 0;


	bool is_program_exit = false;

	ifstream in_fp("input.txt");
	ofstream out_fp("output.txt");

	if (!in_fp.is_open())
	{
		out_fp << "Error : Can not open this file.." << endl;
		return;
	}

	while (!is_program_exit)
	{
		in_fp >> menu_level_1 >> menu_level_2;

		switch (menu_level_1)
		{
		case 1:
		{
			switch (menu_level_2)
			{
			case 1: // 회원가입
			{
				signUpInterface(in_fp, out_fp);
			}
			break;

			case 2:	// 회원탈퇴
			{
				WithdrawInterface(in_fp, out_fp);
			}
			break;

			default:
				break;
			}
		}
		break;

		case 2:
		{
			switch (menu_level_2)
			{
			case 1:	// 로그인
			{
				LogInInterface(in_fp, out_fp);
			}
			break;

			case 2: // 로그아웃
			{
				LogOutInterface(in_fp, out_fp);
			}
			break;

			default:
				break;
			}
		}
		break;

		case 3:
		{
			switch (menu_level_2)
			{
			case 1: // 판매티켓 등록
			{
				registerTicketInterface(in_fp, out_fp);
			}
			break;

			case 2: // 등록티켓 조회
			{

				startCheckEnrolledTicket(in_fp, out_fp);
			}
			break;

			default:
				break;
			}
		}
		break;

		case 4:
		{
			switch (menu_level_2)
			{
			case 1: // 티켓 검색
			{
				searchTicketInterface(in_fp, out_fp);
			}
			break;

			case 2: // 티켓 예약
			{
				reserveTicketInterface(in_fp, out_fp);
			}
			break;

			case 3: // 경매 중인 티켓 검색
			{
				searchAuctionTicketInterface(in_fp, out_fp);
			}
			break;

			case 4: // 경매 참여
			{
				participateAuctionInterface(in_fp, out_fp);
			}
			break;

			case 5: // 예약 정보 조회
			{
				startCheckReservedTicket(in_fp, out_fp);
			}
			break;

			default:
				break;
			}
		}
		break;

		case 5:
		{
			switch (menu_level_2)
			{
			case 1: // 현재시간 설정
			{
				//Timer::TimeSet curTime;
				//in_fp >> curTime;
				Timer::getInstance()->setCurrentTime(in_fp, out_fp);
				//out_fp << "> " << curTime << endl;
			}
			break;

			default:
				break;
			}
		}
		break;

		case 6:
		{
			switch (menu_level_2)
			{
			case 1: // session 변경
			{
				out_fp << "6.1. session 변경" << endl;

				string id;
				in_fp >> id;
				MemberManager::getInstance()->changeSession(id);
				out_fp << "> " << id << endl;
			}
			break;

			case 2: // guest session으로 변경
			{
				out_fp << "6.2. guest session으로 변경" << endl;
				MemberManager::getInstance()->changeSession("guest");
			}
			break;

			default:
				break;
			}
		}
		break;

		case 7:
		{
			switch (menu_level_2)
			{
			case 1:
				is_program_exit = true;
				out_fp << "7.1. 종료" << endl;
				break;

			default:
				break;
			}
		}
		break;

		default:
			break;
		}
		out_fp << endl;
	}

	in_fp.close();
	out_fp.close();
}


void signUpInterface(ifstream& in_fp, ofstream& out_fp) {
	SignUpUI signUpUI;
	SignUp signUp;
	signUpUI.inputSignUpInformation(in_fp, out_fp, signUp);
}

void registerTicketInterface(ifstream& in_fp, ofstream& out_fp) {
	RegisterTicketUI registerTicketUI;
	RegisterTicket registerTicket;
	registerTicketUI.inputTicketInformationToRegister(in_fp, out_fp, registerTicket);
}

void searchTicketInterface(ifstream& in_fp, ofstream& out_fp) {
	SearchTicketUI searchTicketUI;
	SearchTicket searchTicket;
	searchTicketUI.selectHomeTeamToTicketList(in_fp, out_fp, searchTicket);
}

void reserveTicketInterface(ifstream& in_fp, ofstream& out_fp) {
	SearchTicketUI searchTicketUI;
	SearchTicket searchTicket;
	searchTicketUI.selectTicketToReserve(in_fp, out_fp, searchTicket);
}
void searchAuctionTicketInterface(ifstream& in_fp, ofstream& out_fp) {
	SearchAuctionTicketUI searchAuctionTicketUI;
	SearchAuctionTicket searchAuctionTicket;
	searchAuctionTicketUI.selectHomeTeam(in_fp, out_fp, searchAuctionTicket);
}
void participateAuctionInterface(ifstream& in_fp, ofstream& out_fp) {
	SearchAuctionTicketUI searchAuctionTicketUI;
	SearchAuctionTicket searchAuctionTicket;
	searchAuctionTicketUI.participateAuction(in_fp, out_fp, searchAuctionTicket);
}
void LogInInterface(ifstream &in_fp, ofstream &out_fp) {

	LogInUI logInUI;
	LogIn logIn;
	logInUI.inputLogInInformation(in_fp, out_fp, logIn);
}
void LogOutInterface(ifstream &in_fp, ofstream &out_fp) {
	LogOutUI logOutUI;
	LogOut logOut;
	logOutUI.clickLogOutButton(in_fp, out_fp, logOut);
}
void WithdrawInterface(ifstream &in_fp, ofstream &out_fp) {
	WithdrawUI withdrawUI;
	Withdraw withdraw;
	withdrawUI.clickWithdrawButton(in_fp, out_fp, withdraw);
}

void startCheckEnrolledTicket(ifstream &in_fp, ofstream &out_fp) {
	CheckEnrolledTicketUI checkEnrolledTicketUI;
	checkEnrolledTicketUI.startCheckEnrolledTicket(in_fp, out_fp);
}

void startCheckReservedTicket(ifstream &in_fp, ofstream &out_fp) {
	CheckReservedTicketUI checkReservedTicketUI;
	checkReservedTicketUI.startCheckReservedTicket(in_fp, out_fp);
}