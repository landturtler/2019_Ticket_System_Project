#include "LogOut.h"



//function : void showLogOut()
//description : 로그아웃 함수실행

void LogOut::showLogOut(){
	MemberManager *memberManager = MemberManager::getInstance();
	memberManager->requestLogOut();
	
}