#include "LogOutUI.h"


//function : void clickLogOutButton(ifstream &in_fp, ofstream &out_fp, LogOut &logOut);
//description : 로그아웃 UI
//parameters : ifstream &in_fp, ofstream &out_fp, LogOut &logOut

void LogOutUI::clickLogOutButton(ifstream &in_fp, ofstream &out_fp, LogOut &logOut){
	
	string curID = MemberManager::getInstance()->getCurrentSessionID();
	logOut.showLogOut();//로그인 상태 바꿈
	out_fp << "2.2. 로그아웃" << endl;
	out_fp << "> " << curID << endl;
}